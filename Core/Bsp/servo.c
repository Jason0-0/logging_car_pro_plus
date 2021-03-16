#include "servo.h"
#include "math.h"

struct Servo_t servo_grab={
    .htim=&htim4,
    .tim_ch=TIM_CHANNEL_1,
    .max_angle=270,
    .angle=135 //暂定
};

struct Servo_t servo_raise_l={
    .htim=&htim4,
    .tim_ch=TIM_CHANNEL_2,
    .max_angle=270,
    .angle=135 //暂定
};

struct Servo_t servo_raise_r={
    .htim=&htim4,
    .tim_ch=TIM_CHANNEL_3,
    .max_angle=270,
    .angle=135 //暂定
};

struct Servo_t servo_platform={
    .htim=&htim4,
    .tim_ch=TIM_CHANNEL_2,
    .max_angle=270,
    .angle=135 //暂定
};

void servo_set_angle(struct Servo_t* servo,uint16_t angle)
{
    uint16_t new_ccr=500+2000*angle/servo->max_angle;
    servo->angle=angle;
    __HAL_TIM_SetCompare(servo->htim,servo->tim_ch,new_ccr);

}