/**
 * @file can_setup.cpp
 * @brief ESP-IDF TWAI peripheral implementation for `can_setup.hpp`.
 *
 * Encapsulates all `driver/twai.h` calls, bit-timing configuration (500 kbps),
 * hardware queue sizing, and non-blocking Bus-Off state recovery.
 */

#include "twai_init.h"
#include "driver/twai.h"
#include "esp_log.h"
#include <cstring>

/** @brief Logging tag for ESP-IDF serial diagnostics. */
static const char* TAG = "CAN_SETUP";

esp_err_t can_init() {
    // 1. Initialize general configuration via Espressif's macro to stay resilient
    //    against struct member additions in future ESP-IDF releases.
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(
        static_cast<gpio_num_t>(PIN_CAN_TX), // Cast specifically to esp idfs enum
        static_cast<gpio_num_t>(PIN_CAN_RX),
        TWAI_MODE_NORMAL
    );
    g_config.tx_queue_len = 16;
    g_config.rx_queue_len = 32;

    // 2. Standardize vehicle bus speed at 500 kbps and accept all standard/extended frames.
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    // 3. Install the TWAI driver into kernel/FreeRTOS space.
    esp_err_t err = twai_driver_install(&g_config, &t_config, &f_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "TWAI driver install failed: %s", esp_err_to_name(err));
        return err;
    }

    // 4. Enable critical bus fault alerts before starting the controller so early
    //    electrical faults on startup are captured.
    uint32_t alerts_to_enable = TWAI_ALERT_BUS_OFF |
                                TWAI_ALERT_BUS_RECOVERED |
                                TWAI_ALERT_ERR_PASS |
                                TWAI_ALERT_RX_QUEUE_FULL;
    err = twai_reconfigure_alerts(alerts_to_enable, nullptr);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "TWAI alert config failed: %s", esp_err_to_name(err));
        twai_driver_uninstall();
        return err;
    }

    // 5. Transition the TWAI controller from Stopped to Running state.
    err = twai_start();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "TWAI start failed: %s", esp_err_to_name(err));
        twai_driver_uninstall();
        return err;
    }

    ESP_LOGI(TAG, "TWAI initialized at 500 kbps");
    return ESP_OK;
}

esp_err_t can_send(const CanFrame& frame, uint32_t timeout_ms) {
    twai_message_t tx_msg = {};
    tx_msg.identifier = frame.id;
    tx_msg.extd = frame.extended_id ? 1 : 0;
    tx_msg.data_length_code = (frame.dlc > 8) ? 8 : frame.dlc;
    std::memcpy(tx_msg.data, frame.data, tx_msg.data_length_code);

    return twai_transmit(&tx_msg, pdMS_TO_TICKS(timeout_ms));
}

bool can_receive(CanFrame& out_frame, uint32_t timeout_ms) {
    twai_message_t rx_msg = {};
    if (twai_receive(&rx_msg, pdMS_TO_TICKS(timeout_ms)) == ESP_OK) {
        out_frame.id = rx_msg.identifier;
        out_frame.extended_id = (rx_msg.extd != 0);
        out_frame.dlc = rx_msg.data_length_code;
        std::memset(out_frame.data, 0, sizeof(out_frame.data));

        uint8_t copy_len = (rx_msg.data_length_code > 8) ? 8 : rx_msg.data_length_code;
        std::memcpy(out_frame.data, rx_msg.data, copy_len);
        return true;
    }
    return false;
}

void can_poll_health() {
    uint32_t alerts = 0;
    if (twai_read_alerts(&alerts, 0) == ESP_OK) {
        if (alerts & TWAI_ALERT_BUS_OFF) {
            ESP_LOGW(TAG, "TWAI Bus-Off detected! Initiating recovery...");
            twai_initiate_recovery();
        }
        if (alerts & TWAI_ALERT_BUS_RECOVERED) {
            ESP_LOGI(TAG, "TWAI Bus recovered! Restarting controller...");
            twai_start();
        }
        if (alerts & TWAI_ALERT_ERR_PASS) {
            ESP_LOGW(TAG, "TWAI entered Error-Passive state (check wiring/EMI)");
        }
        if (alerts & TWAI_ALERT_RX_QUEUE_FULL) {
            ESP_LOGW(TAG, "TWAI RX queue full — frames dropped");
        }
    }
}
