#include "stepper.h"

#define SHIFT_PER_ROUND (2) //mm
#define ANGLE_PER_STEP (1) //degree



struct Stepper_t stepper={
    .htim=&htim5,
    .tim_ch=TIM_CHANNEL_2,
    .dir_port=J1_STEP_R_DIR_GPIO_Port,
    .dir_pin=J1_STEP_R_DIR_Pin,

    .height=0,
    .highest=0,
    .lowest=0,
    .speed=2000,
    .dir=forward,

    .is_running=0
};

//校准用
// uint8_t stepper_start_cali_flag=0;
// uint8_t stepper_reach_highest_flag=0;
// uint8_t stepper_reach_lowset_flag=0;

// struct Stepper_t stepper_r={
//     .htim=&htim5,
//     .tim_ch=TIM_CHANNEL_3,
//     .height=0,
//     .highest,
//     .lowest=0,

// }
void stepper_init(struct Stepper_t* stepper)
{
    //方向
    HAL_GPIO_WritePin(stepper->dir_port,stepper->dir_pin,stepper->dir);

    //从定时器
    HAL_TIM_Base_Start_IT(&SLAVE_HTIM);
    __HAL_TIM_SetAutoreload(&SLAVE_HTIM,0);

    //主定时器
    HAL_TIM_PWM_Start_IT(stepper->htim,stepper->tim_ch);
    __HAL_TIM_SetAutoreload(stepper->htim,stepper->speed);
    __HAL_TIM_SetCompare(stepper->htim,stepper->tim_ch,0);
    
}

void stepper_setSpeed(struct Stepper_t* stepper,int speed)
{
    //static enum Stepper_Dir_e dir;
    if(speed>0)
    {
        stepper->dir=forward;
        stepper->speed=speed;
    }
    else
    {
        stepper->dir=backward;
        stepper->speed=-speed;
    }
    HAL_GPIO_WritePin(stepper->dir_port,stepper->dir_pin,stepper->dir);
   // __HAL_TIM_SetCounter(stepper->htim,0);
   __HAL_TIM_SetCompare(stepper->htim,stepper->tim_ch,stepper->speed/2);   //50%占空比
    __HAL_TIM_SetAutoreload(stepper->htim,stepper->speed);
    
    
}


void stepper_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim,struct Stepper_t* stepper)
{
    if(htim==(&SLAVE_HTIM))
    {
        if(__HAL_TIM_GET_FLAG(htim,TIM_FLAG_CC1)!=RESET)
        {
            __HAL_TIM_CLEAR_FLAG(htim,TIM_FLAG_CC1);
            HAL_TIM_PWM_Stop_IT(stepper->htim,stepper->tim_ch);
            HAL_TIM_Base_Stop_IT(htim);
        }
        //todo:完成脉冲和位移的换算（或者不换算了）
        stepper->height+=((int)(stepper->dir)-1)*__HAL_TIM_GetCounter(stepper->htim);
        stepper->is_running=0;  //清除运行中标志
    }

}

void stepper_setSteps(struct Stepper_t* stepper,int steps)
{
    if(stepper->is_running==0)
    {
        stepper->is_running=1;
        __HAL_TIM_SetAutoreload(&SLAVE_HTIM,steps-1);
        HAL_TIM_Base_Start_IT(&SLAVE_HTIM);
        HAL_TIM_PWM_Start_IT(stepper->htim,stepper->tim_ch);
    }
}

void stepper_stop(struct Stepper_t* stepper)
{
    //先停下pwm
    HAL_TIM_PWM_Stop_IT(stepper->htim,stepper->tim_ch);

    //通过读从定时器计数器获得已发出脉冲数，并更新当前高度
    stepper->height+=((int)(stepper->dir)-1)*__HAL_TIM_GetCounter(stepper->htim);
    //关掉从定时器，并把中断标志清除
    HAL_TIM_Base_Stop_IT(&SLAVE_HTIM);
    if(__HAL_TIM_GET_FLAG(&SLAVE_HTIM,TIM_FLAG_CC1)!=RESET)
        __HAL_TIM_CLEAR_FLAG(&SLAVE_HTIM,TIM_FLAG_CC1);
    stepper->is_running=0;  //清除运行中标志

}
