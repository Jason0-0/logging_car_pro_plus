#include "arm.h"

Arm_t robot_arm;

void arm_attach(Arm_t* arm,struct Servo_t* grab,struct Servo_t* wrist_l,struct Servo_t* wrist_r,struct Servo_t* platform,struct Stepper_t* lift)
{
  	arm->grab=grab;
  	arm->wrist_l=wrist_l;
 	arm->wrist_r=wrist_r;
 	arm->platform=platform;
	arm->lift=lift;
}

void arm_param_init(Arm_t* arm,enum Grabber_Status_e grabber_status,uint16_t wrist_angle,uint16_t lift_height,uint8_t platform_id)
{
	arm->grabber_status=grabber_status;
	arm->wrist_angle=wrist_angle;
	arm->lift_height=lift_height;
	arm->id=platform_id;
	
	arm_turn_wrist(arm,arm->wrist_angle);
	arm_lift(arm,arm->lift_height);
	arm_turnToID(arm,arm->id);
	if(arm->grabber_status==grabber_catch)
		arm_grab(arm);
	else
		arm_release(arm);
}

void arm_turn_wrist(Arm_t* arm,uint16_t angle)
{
	
}
void arm_lift(Arm_t* arm,uint16_t height)
{
	
}
void arm_grab(Arm_t* arm)
{
	
}
void arm_release(Arm_t* arm)
{
	
}
void arm_turnToID(Arm_t* arm,uint8_t id)
{
	
}
	
