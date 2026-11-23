#pragma once

/**
 * @file can_setup.hpp
 * @brief Hardware-abstracted TWAI (CAN 2.0) driver interface for vehicle firmware.
 *
 * Isolates ESP-IDF TWAI driver dependencies behind a clean C++ interface so
 * application logic remains portable across hardware and SDK revisions.
 */

#include <cstdint>
#include "esp_err.h"
#include "pin_defs.h"

/**
 * @brief SDK-independent CAN 2.0 frame container.
 */
struct CanFrame {
    uint32_t id;        /**< 11-bit standard or 29-bit extended CAN identifier. */
    uint8_t dlc;        /**< Data Length Code (valid range: 0–8 bytes). */
    bool extended_id;   /**< True for 29-bit extended ID; false for 11-bit standard ID. */
    uint8_t data[8];    /**< Raw payload bytes (zero-padded up to 8 bytes). */
};

/**
 * @brief Initializes the TWAI peripheral, arms error/Bus-Off alerts, and starts the bus.
 *
 * Must be called once at boot after `pin_init()` has configured board GPIOs and
 * placed the CAN transceiver in standby.
 *
 * @return
 *      - `ESP_OK` on successful driver installation and bus start.
 *      - `ESP_ERR_INVALID_ARG` if pin configurations are invalid.
 *      - `ESP_ERR_NO_MEM` if driver queues could not be allocated.
 *      - `ESP_FAIL` or other `esp_err_t` codes if alert setup or bus start fails.
 */
esp_err_t can_init();

/**
 * @brief Transmits a CAN frame onto the bus with a bounded queue timeout.
 *
 * Safely copies the payload into the hardware TX queue without blocking indefinitely
 * or triggering fatal assertions if the bus is busy or disconnected.
 *
 * @param[in] frame       The CAN frame to transmit.
 * @param[in] timeout_ms  Maximum time (in milliseconds) to wait for space in the TX queue.
 *                        Defaults to 10 ms.
 *
 * @return
 *      - `ESP_OK` if the frame was queued for transmission.
 *      - `ESP_ERR_TIMEOUT` if the TX queue remained full after `timeout_ms`.
 *      - `ESP_ERR_INVALID_STATE` if the TWAI controller is not in the Running state (e.g., Bus-Off).
 */
esp_err_t can_send(const CanFrame& frame, uint32_t timeout_ms = 10);

/**
 * @brief Reads the next available CAN frame from the driver's internal RX queue.
 *
 * @param[out] out_frame   Struct populated with the received frame ID, flags, DLC, and payload.
 * @param[in]  timeout_ms  Maximum time (in milliseconds) to block waiting for a frame.
 *                         Use `0` (default) for non-blocking polling.
 *
 * @return `true` if a frame was retrieved and written to `out_frame`; `false` if the queue was empty.
 */
bool can_receive(CanFrame& out_frame, uint32_t timeout_ms = 0);

/**
 * @brief Polls TWAI driver alerts and executes automatic Bus-Off recovery.
 *
 * Should be called periodically in the main control loop or a dedicated CAN task
 * to recover communication automatically if EMI spikes force the controller into Bus-Off.
 */
void can_poll_health();
