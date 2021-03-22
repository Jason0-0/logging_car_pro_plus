#include "servo.h"
#include "math.h"

#define TIM_FREQ (1e6)
#define TIM_ARR (20000)

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

//考虑做成线程？
void servo_step_run(struct Servo_t* servo,uint16_t set_angle,int speed)
{
    //越界处理...

    static uint8_t is_CW;
    is_CW=set_angle-servo->angle>0?1:0;

    if (is_CW)
    {
        for(uint16_t i=servo->angle;i<=set_angle;i++)
        {
            servo_set_angle(servo,i);
            HAL_Delay(speed);   //os_Delay(speed);
        }
    }
    else
    {
        for(uint16_t i=servo->angle;i>=set_angle;i--)
        {
            servo_set_angle(servo,i);
            HAL_Delay(speed);   //os_Delay(speed);
        }
    }
}

uint16_t servo_get_angle(struct Servo_t* servo)
{
    uint16_t ccrx=__HAL_TIM_GetCompare(servo->htim,servo->tim_ch); //ms*1000
    return (ccrx-500)*servo->max_angle/2000;
}