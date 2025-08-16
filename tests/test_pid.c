#include "unity.h"
#include "pid_controller.h"

void setUp(void) {}
void tearDown(void) {}

void test_pid_basic_proportional_only(void) {
    pid_t pid;
    pid_init(&pid, 2.0f, 0.0f, 0.0f, 0.01f, -100.0f, 100.0f);

    float setpoint = 10.0f;
    float measured = 7.0f;   // error = 3
    float out = pid_step(&pid, setpoint, measured);

    // kp * err = 2 * 3 = 6
    TEST_ASSERT_FLOAT_WITHIN(1e-6, 6.0f, out);
}

void test_pid_saturation_limits(void) {
    pid_t pid;
    pid_init(&pid, 100.0f, 0.0f, 0.0f, 0.01f, -5.0f, 5.0f);

    float out = pid_step(&pid, 10.0f, 0.0f); // err=10 → P=100 → clamp to 5
    TEST_ASSERT_FLOAT_WITHIN(1e-6, 5.0f, out);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_pid_basic_proportional_only);
    RUN_TEST(test_pid_saturation_limits);
    return UNITY_END();
}
