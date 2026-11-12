#pragma once

/**
 * @file pin_defs.h
 * @brief Tractive system pin definitions
 */

// --- CAN Bus Pins ---
#define PIN_CAN_TX          41
#define PIN_CAN_RX          42

// --- Watchdog Pins ---
#define PIN_WATCHDOG_INPUT  5
#define PIN_WATCHDOG_OUTPUT 4

// --- Analog Input Pins ---
#define PIN_PEDAL_0         45 // TODO: check with george to confirm which pins are used for the pedal sensors
#define PIN_PEDAL_1         46 // TODO: check with george to confirm which pins are used for the pedal sensors
#define PIN_F_BRAKE         6
#define PIN_R_BRAKE         7

// --- Output Pins ---
#define PIN_RTD_BUZZER      14
#define PIN_VICOR_ENABLE    13
#define PIN_BRAKE_LIGHT     37 // TODO: check with george to confirm which pin is used for the brake light

// --- FAULT input pins---
#define PIN_FAULT_BMS       15
#define PIN_FAULT_IMD       16
#define PIN_FAULT_VICOR     12

// --- State Machine Inputs ---
#define PIN_START_BUTTON    8
