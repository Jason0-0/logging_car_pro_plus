#include "stepper.h"

#define SHIFT_PER_ROUND (2) //mm
#define ANGLE_PER_STEP (1) //degree

struct Stepper_t stepper={
    .htim=&htim5,
    .tim_ch=TIM_CHANNEL_2,
    .height=0,
    .highest=0,
    .lowest=0,
    .speed=2000
};

//校准用
uint8_t stepper_start_cali_flag=0;
uint8_t stepper_reach_highest_flag=0;
uint8_t stepper_reach_lowset_flag=0;

// struct Stepper_t stepper_r={
//     .htim=&htim5,
//     .tim_ch=TIM_CHANNEL_3,
//     .height=0,
//     .highest,
//     .lowest=0,

// }

void stepper_setSpeed(struct Stepper_t* stepper,int speed)
{
    stepper->speed=speed;
    __HAL_TIM_SetAutoreload(stepper->htim,1e6/stepper->speed);
    __HAL_TIM_SetCompare(stepper->htim,stepper->tim_ch,__HAL_TIM_GetAutoreload(stepper->htim)/2);   //50%占空比
    
}
