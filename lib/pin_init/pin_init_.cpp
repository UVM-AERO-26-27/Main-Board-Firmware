#include "pin_init.h"

/**
 * @brief Initializes the pins for the tractive system with dangerous outputs (VICOR_EN, RTD_BUZZER, PRECHARGE, MAIN_CONTACT)
 */
void pin_init_dangerous() {
    pinMode(PIN_VICOR_ENABLE, OUTPUT);
    digitalWrite(PIN_VICOR_ENABLE, LOW); // Ensure VICOR is disabled at startup
    pinMode(PIN_RTD_BUZZER, OUTPUT);
    digitalWrite(PIN_RTD_BUZZER, LOW); // Ensure RTD buzzer is off at startup
}

/**
 * @brief Initializes the pins for the tractive system with safe outputs (All other pins)
 */
void pin_init_safe() {
    // --- Watchdog Pins ---
    pinMode(PIN_WATCHDOG_INPUT, OUTPUT);  
    pinMode(PIN_WATCHDOG_OUTPUT, INPUT); 

    // --- Analog Input Pins ---
    pinMode(PIN_PEDAL_0, INPUT);
    pinMode(PIN_PEDAL_1, INPUT);             
    pinMode(PIN_F_BRAKE, INPUT);
    pinMode(PIN_R_BRAKE, INPUT);             

    // --- Output Pins ---
    pinMode(PIN_BRAKE_LIGHT, OUTPUT);
        
    // --- FAULT input pins---
    pinMode(PIN_FAULT_BMS, INPUT);             
    pinMode(PIN_FAULT_IMD, INPUT);
    pinMode(PIN_FAULT_VICOR, INPUT);    

    // --- State Machine Inputs ---
    pinMode(PIN_START_BUTTON, INPUT);
}