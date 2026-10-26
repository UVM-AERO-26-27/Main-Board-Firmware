#include <unity.h>
#include "state_machine.h"

void setUp() {}
void tearDown() {}

void test_state_numbers_match_can_values() {
    // Uses static cast to convert enum values to their integer type for comparison
    TEST_ASSERT_EQUAL_UINT8(0, static_cast<uint8_t>(SystemState::kTractiveSystemOff));
    TEST_ASSERT_EQUAL_UINT8(1, static_cast<uint8_t>(SystemState::kPrecharge));
    TEST_ASSERT_EQUAL_UINT8(2, static_cast<uint8_t>(SystemState::kReadyToDrive));
    TEST_ASSERT_EQUAL_UINT8(3, static_cast<uint8_t>(SystemState::kDrive));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_state_numbers_match_can_values);
    return UNITY_END();
}