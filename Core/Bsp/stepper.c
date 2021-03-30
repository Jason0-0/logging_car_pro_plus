#include "stepper.h"

#define SHIFT_PER_ROUND (2) //mm
#define ANGLE_PER_STEP (1) //degree

struct Stepper_t stepper={
    .htim=&htim5,
    .tim_ch=TIM_CHANNEL_2,
    .height=0,
    .highest=0,
    .lowest=0,
    .speed=2000,
    .is_running=0
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
void stepper_init(struct Stepper_t* stepper)
{
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_PWM_Start_IT(stepper->htim,stepper->tim_ch);
    __HAL_TIM_SetAutoreload(&htim1,0);
}

void stepper_setSpeed(struct Stepper_t* stepper,int speed)
{
    stepper->speed=speed;
    __HAL_TIM_SetAutoreload(stepper->htim,1e6/stepper->speed);
    __HAL_TIM_SetCompare(stepper->htim,stepper->tim_ch,__HAL_TIM_GetAutoreload(stepper->htim)/2);   //50%占空比
    
}

void stepper_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    if(htim==(&htim1))
    {
        if(__HAL_TIM_GET_FLAG(htim,TIM_FLAG_CC1)!=RESET)
        {
            __HAL_TIM_CLEAR_FLAG(htim,TIM_FLAG_CC1);
            HAL_TIM_PWM_Stop_IT(stepper.htim,stepper.tim_ch);
            HAL_TIM_Base_Stop_IT(htim);
        }
    }

}

void stepper_setSteps(struct Stepper_t* stepper,int steps)
{
    if(stepper->is_running==0)
    {
        stepper->is_running=1;
        __HAL_TIM_SetAutoreload(&htim1,steps-1);
        HAL_TIM_Base_Start_IT(&htim1);
        HAL_TIM_PWM_Start_IT(stepper->htim,stepper->tim_ch);
    }
}
