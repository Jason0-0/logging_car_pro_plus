#ifndef CAN_MOTOR_H
#define CAN_MOTOR_H

#include "can.h"
#include "RMD_protocol.h"
#include "pid.h"

struct CAN_Motor
{
    int8_t temperature;         //电机温度
    int16_t electric_current;      //电机实际转矩电流
    int16_t fdbSpeed;              //电机反馈的转速/rpm
    uint16_t fdbPosition;           //电机的编码器反馈值
	uint16_t last_fdbPosition;      //电机上次的编码器反馈值
	
	short round;                 //电机转过的圈数
	int32_t real_position;       //过零处理后的电机转子位置
	int32_t last_real_position;  //上次真实转过的角度
	
	struct PID_t speed_pid;      //速度环
	struct PID_t position_pid;   //位置环

};

//void RMD_get_fdb_data(struct RMD_TorqueCtrl_Rx* motor_fdb,uint8_t* can_rx_data);
void MotorEncoderProcess(struct CAN_Motor *motor, uint8_t *RecvData);
void Can_MultiCtrl_Tx1234(CAN_HandleTypeDef* hcanx,int16_t cm1_iq, int16_t cm2_iq, int16_t cm3_iq, int16_t cm4_iq);

#endif // !CAN_MOTOR_H

