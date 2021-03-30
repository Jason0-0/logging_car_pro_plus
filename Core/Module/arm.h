#ifndef ARM_H
#define ARM_H

#include "servo.h"
#include "stepper.h"

enum Grabber_Status_e
{
  grabber_catch;
  grabber_release;
}

typedef struct __Arm
{
  struct Servo_t* grab;
  struct Servo_t* wrist_l;
  struct Servo_t* wrist_r;
  struct Servo_t* platform
  struct Stepper_t* lift;
  
  uint16_t wrist_angle;
  uint16_t lift_height;
  enum Grabber_Status_e grabber_status;
  uint8_t id;
}Arm_t;



void arm_turn_wrist(Arm_t* arm,uint16_t angle);
void arm_lift(Arm_t* arm,uint16_t height);
void arm_grab(Arm_t* arm);
void arm_release(Arm_t* arm);
void arm_turnToID(Arm_t* arm,uint8_t id);

void arm_attach(Arm_t* arm,struct Servo_t* grab,struct Servo_t* wrist_l,struct Servo_t* wrist_r,struct Servo_t* platform,struct Stepper_t* lift);
void arm_param_init(Arm_t* arm,enum Grabber_Status_e grabber_status,uint16_t wrist_angle,uint16_t lift_height,uint8_t platform_id);



extern Arm_t robot_arm;

#endif // !ARM_H
