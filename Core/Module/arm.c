#include "arm.h"

Arm_t robot_arm={
	.grabber.grab_angle=115,
	.grabber.release_angle=135,
	.wrist.wrist_biasAngle=90,
	.wrist.biasAngle_l=135,
	.wrist.biasAngle_r=135,
	.platform.ID_angle={25,132,245}
};

void arm_attach(Arm_t* arm,struct Servo_t* grab,struct Servo_t* wrist_l,struct Servo_t* wrist_r,struct Servo_t* platform,struct Stepper_t* lift)
{
  	arm->grabber.servo=grab;
  	arm->wrist.servo_l=wrist_l;
 	arm->wrist.servo_r=wrist_r;
 	arm->platform.servo=platform;
	arm->lift=lift;
}

void arm_param_init(Arm_t* arm,enum Grabber_Status_e grabber_status,uint16_t wrist_angle,uint16_t lift_height,enum Platform_ID_e platform_id)
{
	arm->grabber.status=grabber_status;
	arm->wrist.angle=wrist_angle;
	arm->lift->height=lift_height;
	arm->platform.id=platform_id;
	
	arm_turn_wrist(arm,arm->wrist.angle);
	//arm_lift(arm,arm->lift->height,2000);
	arm_turnToID(arm,arm->platform.id);
	if(arm->grabber.status==grabber_catch)
		arm_catch(arm);
	else
		arm_release(arm);
}

//angle 为绝对值
void arm_turn_wrist(Arm_t* arm,uint16_t angle)
{
	//限位
	angle=angle>WRIST_MAX_ANGLE?WRIST_MAX_ANGLE:angle;
	angle=angle<WRIST_MIN_ANGLE?WRIST_MIN_ANGLE:angle;

	//转
	servo_set_angle(arm->wrist.servo_r,arm->wrist.biasAngle_r-arm->wrist.wrist_biasAngle+angle);
	servo_set_angle(arm->wrist.servo_l,arm->wrist.biasAngle_l+arm->wrist.wrist_biasAngle-angle);
	arm->wrist.angle=angle;
}

//速度用绝对值
void arm_lift(Arm_t* arm,uint16_t height,uint16_t speed)
{
	if(arm->lift->is_running==0)
	{
		if(height>arm->lift->highest)
			height=arm->lift->highest;
		else if (height<arm->lift->lowest)
			height=arm->lift->lowest;
		
		int delta_h;	//高度差
		delta_h=height-arm->lift->height;
		if(delta_h>0)
		{
			stepper_setSpeed(arm->lift,speed);
			stepper_setSteps(arm->lift,delta_h);	//暂时这么写
		}
		else if(delta_h<0)
		{
			stepper_setSpeed(arm->lift,-speed);
			stepper_setSteps(arm->lift,delta_h);
		}

	}
	
}
void arm_catch(Arm_t* arm)
{
	// if (arm->grabber.status!=grabber_catch)
	// {
		servo_set_angle(arm->grabber.servo,arm->grabber.grab_angle);
		arm->grabber.status=grabber_catch;
	// }
	
}
void arm_release(Arm_t* arm)
{
	// if (arm->grabber.status!=grabber_release)
	// {
		servo_set_angle(arm->grabber.servo,arm->grabber.release_angle);
		arm->grabber.status=grabber_release;
	// }
}
void arm_turnToID(Arm_t* arm,enum Platform_ID_e id)
{
	// if (id!=arm->platform.id)
	// {
		servo_set_angle(arm->platform.servo,arm->platform.ID_angle[id]);
		arm->platform.id=id;
	// }
	
}
	
