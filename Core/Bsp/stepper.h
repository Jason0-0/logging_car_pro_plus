#include "tim.h"
#include "gpio.h"

struct Stepper_t
{
    uint16_t lowest;
    uint16_t highest;
    uint16_t height;
    int speed;  //负即为反转
    TIM_HandleTypeDef* htim;
    uint32_t tim_ch;

};

extern struct Stepper_t stepper;

void stepper_init(struct Stepper_t* stepper);
void stepper_setSpeed(struct Stepper_t* stepper,int speed);
void stepper_move(struct Stepper_t* stepper,uint16_t height);
void stepper_calibrate(struct Stepper_t* stepper);
