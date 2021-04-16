#ifndef CHASSIS_H
#define CHASSIS_H
#include "motor.h"
#include "pid.h"

extern struct CAN_Motor can1_motor_1;
extern struct CAN_Motor can1_motor_2;
extern struct CAN_Motor can1_motor_3;
extern struct CAN_Motor can1_motor_4;

struct Chassis_t
{
    float fbSpeed;
    float lrSpeed;
    int rotate_speed;

    struct PID_t chassis_x_pid;
    struct PID_t chassis_y_pid;
    struct PID_t chassis_yaw_pid;
    struct CAN_Motor* front_left;
    struct CAN_Motor* front_right;
    struct CAN_Motor* back_left;
    struct CAN_Motor* back_right;
};


void chassis_move(float x, float y);  //  
void chassis_rotate(int angle);   //相对角度
void chassis_navigate(int x,int y); //到达时定位（初步考虑低速运行）
void chassis_brake(void);


extern struct Chassis_t chassis;

#endif // !CHASSIS_H


