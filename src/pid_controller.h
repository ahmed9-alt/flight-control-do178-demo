#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

typedef struct {
    float kp;
    float ki;
    float kd;
    float dt;      // seconds (loop period)
    float integral;
    float prev_err;
    float out_min; // saturation low
    float out_max; // saturation high
} pid_t;

void  pid_init(pid_t* pid, float kp, float ki, float kd, float dt, float out_min, float out_max);
float pid_step(pid_t* pid, float setpoint, float measured);

#endif // PID_CONTROLLER_H
