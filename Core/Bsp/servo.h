#include "tim.h"

struct Servo_t
{
    TIM_HandleTypeDef* htim;
    uint16_t tim_ch;
    uint16_t max_angle;
    uint16_t angle;
	uint16_t max_set_angle;	//机械中允许的最大角度
	uint16_t min_set_angle;
};

extern struct Servo_t servo_grab;
extern struct Servo_t servo_raise_r;
extern struct Servo_t servo_raise_l;
extern struct Servo_t servo_platform;

void servo_set_angle(struct Servo_t* servo,uint16_t angle);
void servo_step_run(struct Servo_t* servo,uint16_t set_angle,int speed);
uint16_t servo_get_angle(struct Servo_t* servo);
