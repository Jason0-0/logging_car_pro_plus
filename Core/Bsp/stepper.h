#ifndef STEPPER_H
#define STEPPER_H

#include "tim.h"
#include "gpio.h"

#define SLAVE_HTIM htim1    //从定时器，用于检测pwm脉冲数

enum Stepper_Dir_e
{
    backward=0,forward
};

struct Stepper_t
{
    uint16_t lowest;
    uint16_t highest;
    uint16_t height;
    uint16_t speed; 
    enum Stepper_Dir_e dir;

    TIM_HandleTypeDef* htim;
    uint32_t tim_ch;
    GPIO_TypeDef* dir_port;
    uint16_t dir_pin;

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
