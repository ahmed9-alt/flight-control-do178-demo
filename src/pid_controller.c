#include "pid_controller.h"

static float clamp(float v, float lo, float hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

void pid_init(pid_t* pid, float kp, float ki, float kd, float dt, float out_min, float out_max) {
    pid->kp = kp; pid->ki = ki; pid->kd = kd;
    pid->dt = dt;
    pid->integral = 0.0f;
    pid->prev_err = 0.0f;
    pid->out_min = out_min;
    pid->out_max = out_max;
}

float pid_step(pid_t* pid, float setpoint, float measured) {
    float err = setpoint - measured;
    pid->integral += err * pid->dt;
    float deriv = (err - pid->prev_err) / pid->dt;

    float out = pid->kp*err + pid->ki*pid->integral + pid->kd*deriv;
    out = clamp(out, pid->out_min, pid->out_max);

    pid->prev_err = err;
    return out;
}
