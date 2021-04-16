#include "chassis.h"
#include "math.h"
#include "navigation_module.h"

extern Navi_Fdb_t navi_fdb;

int fb_speed=50;
int lr_speed=50;
int rot_speed=50;

void chassis_param_calc(void);


struct Chassis_t chassis={

    .front_right=&can1_motor_1,
    .front_right=&can1_motor_2,
    .back_left=&can1_motor_3,
    .back_right=&can1_motor_4,

    // .fbSpeed=50,
    // .lrSpeed=50,
    .rotate_speed=50,

    .chassis_x_pid={
        .KD=0,
        .KI=0,
        .KP=100,
        .outputMax=1000,
        .error={0}
    },

    .chassis_y_pid={
        .KD=0,
        .KI=0,
        .KP=100,
        .outputMax=1000,
        .error={0}
    }

    
    
};

void chassis_move(float x,float y)
{
    chassis.chassis_x_pid.ref=x;
    chassis.chassis_y_pid.ref=y;

    chassis.chassis_x_pid.fdb=navi_fdb.x;
    chassis.chassis_y_pid.fdb=navi_fdb.y;

    //输出的应是lr_speed和fb_speed
    PID_Calc(&chassis.chassis_x_pid);
    PID_Calc(&chassis.chassis_y_pid);

    chassis.fbSpeed=chassis.chassis_x_pid.output;
    chassis.lrSpeed=chassis.chassis_y_pid.output;

    //在此执行速度分解并计算速度环
    chassis_param_calc();

    // Can_SingleCtrl_Tq_Tx(&hcan1,1,chassis.front_left->speed_pid.output);
    // Can_SingleCtrl_Tq_Tx(&hcan1,2,chassis.front_right->speed_pid.output);
    // Can_SingleCtrl_Tq_Tx(&hcan1,3,chassis.back_left->speed_pid.output);
    // Can_SingleCtrl_Tq_Tx(&hcan1,4,chassis.back_right->speed_pid.output);
    CanTransmit_1234(&hcan1,chassis.front_right->speed_pid.output,\
            chassis.front_left->speed_pid.output,chassis.back_left->speed_pid.output,\
            chassis.back_right->speed_pid.output);
}


void chassis_param_calc()
{
    //速度分解
    chassis.front_left->speed_pid.ref=chassis.fbSpeed+chassis.lrSpeed+chassis.rotate_speed;
    chassis.front_right->speed_pid.ref=-chassis.fbSpeed+chassis.lrSpeed+chassis.rotate_speed;
    chassis.back_left->speed_pid.ref=chassis.fbSpeed-chassis.lrSpeed+chassis.rotate_speed;
    chassis.back_right->speed_pid.ref=-chassis.fbSpeed-chassis.lrSpeed+chassis.rotate_speed;

    chassis.front_left->speed_pid.fdb=chassis.front_left->fdbSpeed;
    chassis.front_right->speed_pid.fdb=chassis.front_right->fdbSpeed;
    chassis.back_left->speed_pid.fdb=chassis.back_left->fdbSpeed;
    chassis.back_right->speed_pid.fdb=chassis.back_right->fdbSpeed;

    //速度环
    PID_Calc(&chassis.front_left->speed_pid);
    PID_Calc(&chassis.front_right->speed_pid);
    PID_Calc(&chassis.back_left->speed_pid);
    PID_Calc(&chassis.back_right->speed_pid);
}
