#include "stepper.h"

#define SHIFT_PER_ROUND (2) //mm
#define ANGLE_PER_STEP (1.8f) //degree
#define STEPS_PER_ROUND (200)



struct Stepper_t stepper={
    .htim=&htim3,
    .tim_ch=TIM_CHANNEL_2,
    .dir_port1=STEP1_R_DIR_GPIO_Port,
    .dir_pin1=STEP1_R_DIR_Pin,
		.dir_port2=STEP2_L_DIR_GPIO_Port,
    .dir_pin2=STEP2_L_DIR_Pin,

    .height=0,
    .highest=29500,
    .lowest=100,
    .speed=2300,
    .dir=forward,

    .is_running=0
};

void stepper_init(struct Stepper_t* stepper)
{
    //方向
    HAL_GPIO_WritePin(stepper->dir_port1,stepper->dir_pin1,stepper->dir);
		HAL_GPIO_WritePin(stepper->dir_port2,stepper->dir_pin2,stepper->dir);
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
    int abs_speed;
		
    if(speed>0)
    {
        stepper->dir=forward;
        stepper->speed=speed;
				abs_speed=speed;
    }
    else
    {
        stepper->dir=backward;
        stepper->speed=speed;
				abs_speed=-speed;
    }
    HAL_GPIO_WritePin(stepper->dir_port1,stepper->dir_pin1,stepper->dir);
		HAL_GPIO_WritePin(stepper->dir_port2,stepper->dir_pin2,stepper->dir);
    __HAL_TIM_SetCounter(stepper->htim,0);
   __HAL_TIM_SetCompare(stepper->htim,stepper->tim_ch,abs_speed/5*4);   //50%占空比
    __HAL_TIM_SetAutoreload(stepper->htim,abs_speed);
    
    
}


void stepper_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim,struct Stepper_t* stepper)
{
    if(htim==(&SLAVE_HTIM))
    {
        if(__HAL_TIM_GET_FLAG(htim,TIM_FLAG_CC2)!=RESET)
        {
            __HAL_TIM_CLEAR_FLAG(htim,TIM_FLAG_CC2);
            HAL_TIM_PWM_Stop_IT(stepper->htim,stepper->tim_ch);
            HAL_TIM_Base_Stop_IT(htim);
        }
        //todo:完成脉冲和位移的换算（或者不换算了）
        stepper->height+=(stepper->dir==forward?1:-1)*(__HAL_TIM_GetAutoreload(&SLAVE_HTIM)+1);
        stepper->is_running=0;  //清除运行中标志
    }

}

void stepper_setSteps(struct Stepper_t* stepper,int steps)
{
    if(stepper->is_running==0)
    {
        stepper->is_running=1;
				__HAL_TIM_SetCounter(&SLAVE_HTIM,0);
        __HAL_TIM_SetAutoreload(&SLAVE_HTIM,steps-1);
        HAL_TIM_Base_Start_IT(&SLAVE_HTIM);
				//stepper_setSpeed(stepper,stepper->speed*(stepper->dir-1));
        HAL_TIM_PWM_Start_IT(stepper->htim,stepper->tim_ch);
    }
}

void stepper_stop(struct Stepper_t* stepper)
{
	if(stepper->is_running==1)
	{
    //先停下pwm
    HAL_TIM_PWM_Stop_IT(stepper->htim,stepper->tim_ch);

    //通过读从定时器计数器获得已发出脉冲数，并更新当前高度
    stepper->height+=(stepper->dir==forward?1:-1)*__HAL_TIM_GetCounter(&SLAVE_HTIM);
    //关掉从定时器，并把中断标志清除
    HAL_TIM_Base_Stop_IT(&SLAVE_HTIM);
    if(__HAL_TIM_GET_FLAG(&SLAVE_HTIM,TIM_FLAG_CC2)!=RESET)
        __HAL_TIM_CLEAR_FLAG(&SLAVE_HTIM,TIM_FLAG_CC2);
    stepper->is_running=0;  //清除运行中标志
	}

}
