#include "tim.h"

struct Servo_t
{
    TIM_HandleTypeDef* htim;
    uint16_t tim_ch;
    uint16_t max_angle;
    uint16_t angle;
};

extern struct Servo_t servo_grab;
extern struct Servo_t servo_raise_r;
extern struct Servo_t servo_raise_l;
extern struct Servo_t servo_platform;

void servo_set_angle(struct Servo_t* servo,uint16_t angle);
