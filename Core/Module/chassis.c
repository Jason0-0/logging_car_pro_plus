#include "chassis.h"
#include "math.h"
#include "navigation_module.h"


int fb_speed=50;

struct PID_t chassis_x_pid={
    .KP=0.8,
    .KI=0,
    .KD=0,
    .error_max=4000,
    .outputMax=400,
    .PID_Mode=PID_POSITION
};
struct PID_t chassis_y_pid={
    .KP=0.8,
    .KI=0,
    .KD=0,
    .error_max=4000,
    .outputMax=400,
    .PID_Mode=PID_POSITION
};
struct PID_t chassis_yaw_pid={
    .KP=0.8,
    .KI=0,
    .KD=0,
    .error_max=4000,
    .outputMax=400,
    .PID_Mode=PID_POSITION
};

struct Chassis_t chassis={

    .front_left=&can1_motor_1,
    .front_right=&can1_motor_2,
    .back_left=&can1_motor_3,
    .back_right=&can1_motor_4

    
};
