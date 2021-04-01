#include "chassis.h"
#include "math.h"

int fb_speed=50;

struct Chassis_t chassis={

    .front_left=&can1_motor_1,
    .front_right=&can1_motor_2,
    .back_left=&can1_motor_3,
    .back_right=&can1_motor_4
};