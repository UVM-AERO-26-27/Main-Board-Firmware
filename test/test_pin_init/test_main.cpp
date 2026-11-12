#include <unity.h>
#include "pin_defs.h"
#include "stdint.h"

void setUp() {}
void tearDown() {}



enum class BootMode : uint8_t { kOutput, kInput };
struct PinSetup { uint8_t pin; BootMode mode; };

constexpr PinSetup kBootPins[] = {
    {PIN_WATCHDOG_INPUT,  BootMode::kOutput}, 
    {PIN_WATCHDOG_OUTPUT, BootMode::kInput},
    {PIN_PEDAL_0,         BootMode::kInput},
    {PIN_PEDAL_1,         BootMode::kInput},
    {PIN_F_BRAKE,         BootMode::kInput},
    {PIN_R_BRAKE,         BootMode::kInput},
    {PIN_RTD_BUZZER,      BootMode::kOutput},
    {PIN_VICOR_ENABLE,    BootMode::kOutput},
    {PIN_BRAKE_LIGHT,     BootMode::kOutput},
    {PIN_FAULT_BMS,       BootMode::kInput},
    {PIN_FAULT_IMD,       BootMode::kInput},
    {PIN_FAULT_VICOR,     BootMode::kInput},
    {PIN_START_BUTTON,    BootMode::kInput},
};

// test/test_pins/test_main.cpp
void test_pin_init() {
    TEST_ASSERT_TRUE(kBootPins[0].mode == BootMode::kOutput);
    TEST_ASSERT_TRUE(kBootPins[1].mode == BootMode::kInput);
    TEST_ASSERT_TRUE(kBootPins[1].mode == BootMode::kInput);
    TEST_ASSERT_TRUE(kBootPins[1].mode == BootMode::kInput);
    TEST_ASSERT_TRUE(kBootPins[1].mode == BootMode::kInput);
    TEST_ASSERT_TRUE(kBootPins[1].mode == BootMode::kInput);
    TEST_ASSERT_TRUE(kBootPins[1].mode == BootMode::kOutput);
    TEST_ASSERT_TRUE(kBootPins[1].mode == BootMode::kOutput);
    TEST_ASSERT_TRUE(kBootPins[1].mode == BootMode::kOutput);
    TEST_ASSERT_TRUE(kBootPins[1].mode == BootMode::kInput);
    TEST_ASSERT_TRUE(kBootPins[1].mode == BootMode::kInput);
    TEST_ASSERT_TRUE(kBootPins[1].mode == BootMode::kInput);
    TEST_ASSERT_TRUE(kBootPins[1].mode == BootMode::kInput);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_pin_init);
    return UNITY_END();
}