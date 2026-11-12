#pragma once

#include <Arduino.h>
#include "pin_defs.h"

/**
 * @file pin_init.h
 * @brief Initializes the pins for the tractive system
 */

/**
 * @brief Initializes the pins for the tractive system with dangerous outputs (VICOR_EN, RTD_BUZZER, PRECHARGE, MAIN_CONTACT)
 */
void pin_init_dangerous();

/**
 * @brief Initializes the pins for the tractive system with safe outputs (All other pins)
 */
void pin_init_safe();


