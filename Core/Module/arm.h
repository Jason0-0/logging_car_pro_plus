#ifndef ARM_H
#define ARM_H

#include "servo.h"
#include "stepper.h"

#define WRIST_MAX_ANGLE 210 //以相机向下为180°
#define WRIST_MIN_ANGLE 0 //以夹爪与载物盘平行为0°

enum Grabber_Status_e
{
  grabber_catch,
  grabber_release,
};
typedef struct __graber
{
  struct Servo_t* servo;
  uint16_t grab_angle;
  uint16_t release_angle;
  enum Grabber_Status_e status;
}Grabber_t;

typedef struct __wrist
{
  struct Servo_t* servo_l;
  struct Servo_t* servo_r;
  uint16_t biasAngle_l; //处于中位时舵机的角度（定义夹爪竖直向上时为中位90°
  uint16_t biasAngle_r;

  uint16_t wrist_biasAngle; //90°
  uint16_t angle; //当前所处角度

}Wrist_t;

enum Platform_ID_e
{
  H=0,
  I,
  T
};
typedef struct __platform
{
  struct Servo_t* servo;
  // uint16_t ID_H_angle;
  // uint16_t ID_I_angle;
  // uint16_t ID_T_angle;
  uint16_t ID_angle[3]; //索引按枚举体里的顺序排
  enum Platform_ID_e id;
}Platform_t;



typedef struct __Arm
{
  Grabber_t grabber;
  Wrist_t wrist;
  Platform_t platform;

  struct Stepper_t* lift;
  //uint16_t lift_height;
}Arm_t;



void arm_turn_wrist(Arm_t* arm,uint16_t angle);
void arm_lift(Arm_t* arm,uint16_t height,uint16_t speed);
void arm_catch(Arm_t* arm);
void arm_release(Arm_t* arm);
void arm_turnToID(Arm_t* arm,enum Platform_ID_e id);

void arm_attach(Arm_t* arm,struct Servo_t* grab,struct Servo_t* wrist_l,struct Servo_t* wrist_r,struct Servo_t* platform,struct Stepper_t* lift);
void arm_param_init(Arm_t* arm,enum Grabber_Status_e grabber_status,uint16_t wrist_angle,uint16_t lift_height,enum Platform_ID_e platform_id);



extern Arm_t robot_arm;

#endif // !ARM_H
