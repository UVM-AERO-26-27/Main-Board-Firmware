#include <unity.h>

void setUp() {}
void tearDown() {}

void test_build_works() {
    TEST_ASSERT_TRUE(true);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_build_works);
    return UNITY_END();
}