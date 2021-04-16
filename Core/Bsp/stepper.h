#ifndef STEPPER_H
#define STEPPER_H

#include "tim.h"
#include "gpio.h"

#define SLAVE_HTIM htim1    //从定时器，用于检测pwm脉冲数

enum Stepper_Dir_e
{
    backward=1,forward=0
};

struct Stepper_t
{
    int16_t lowest;
    int16_t highest;
    int16_t height;
    int16_t speed; 
    enum Stepper_Dir_e dir;

    TIM_HandleTypeDef* htim;
    uint32_t tim_ch;
    GPIO_TypeDef* dir_port1;
    uint16_t dir_pin1;
		GPIO_TypeDef* dir_port2;
    uint16_t dir_pin2;

    uint8_t is_running;

};

extern struct Stepper_t stepper;

void stepper_init(struct Stepper_t* stepper);
void stepper_setSpeed(struct Stepper_t* stepper,int speed);
void stepper_setSteps(struct Stepper_t* stepper,int steps);
//void stepper_move(struct Stepper_t* stepper,uint16_t steps);
//void stepper_calibrate(struct Stepper_t* stepper);
void stepper_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim,struct Stepper_t* stepper);
void stepper_stop(struct Stepper_t* stepper);

#endif
