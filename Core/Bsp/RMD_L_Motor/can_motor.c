#include "can_motor.h"
#include "bsp_can.h"
#include "string.h"

//原始数据
// struct RMD_TorqueCtrl_Rx motor_1_fdb;
// struct RMD_TorqueCtrl_Rx motor_2_fdb;
// struct RMD_TorqueCtrl_Rx motor_3_fdb;
// struct RMD_TorqueCtrl_Rx motor_4_fdb;

struct CAN_Motor can1_motor_1;
struct CAN_Motor can1_motor_2;
struct CAN_Motor can1_motor_3;
struct CAN_Motor can1_motor_4;

CAN_TxHeaderTypeDef RMD_multiCtrl_txHeader={
    .DLC=0x08,
    .StdId=CAN_ID_MOTOR3,//CAN_ID_MULTI_MOTOR_TX,
    .IDE=CAN_ID_STD,
    .RTR=CAN_RTR_DATA
};
CAN_TxHeaderTypeDef RMD_motor1_txHeader={
    .DLC=0x08,
    .StdId=CAN_ID_MOTOR1,//CAN_ID_MULTI_MOTOR_TX,
    .IDE=CAN_ID_STD,
    .RTR=CAN_RTR_DATA
};
CAN_TxHeaderTypeDef RMD_motor2_txHeader={
    .DLC=0x08,
    .StdId=CAN_ID_MOTOR2,//CAN_ID_MULTI_MOTOR_TX,
    .IDE=CAN_ID_STD,
    .RTR=CAN_RTR_DATA
};
CAN_TxHeaderTypeDef RMD_motor3_txHeader={
    .DLC=0x08,
    .StdId=CAN_ID_MOTOR3,//CAN_ID_MULTI_MOTOR_TX,
    .IDE=CAN_ID_STD,
    .RTR=CAN_RTR_DATA
};
CAN_TxHeaderTypeDef RMD_motor4_txHeader={
    .DLC=0x08,
    .StdId=CAN_ID_MOTOR4,//CAN_ID_MULTI_MOTOR_TX,
    .IDE=CAN_ID_STD,
    .RTR=CAN_RTR_DATA
};

/**
	* @brief 电机PID参数初始化
	* @param 电机数据结构体，PID参数
	* @retval None
	*/
void MotorParamInit(struct CAN_Motor *motor, \
		float speedP,float speedI,float speedD,float speedErrormax,float speedOutmax, \
		float positionP,float positionI,float positionD,float positionErrormax,float positionOutmax)
{
	motor->speed_pid.KP = speedP;
	motor->speed_pid.KI = speedI;
	motor->speed_pid.KD = speedD;
	motor->speed_pid.error_max = speedErrormax;
	motor->speed_pid.outputMax = speedOutmax;
	motor->speed_pid.PID_Mode = PID_POSITION;
	motor->position_pid.KP = positionP;
	motor->position_pid.KI = positionI;
	motor->position_pid.KD = positionD;
	motor->position_pid.error_max = positionErrormax;
	motor->position_pid.outputMax = positionOutmax;
	motor->position_pid.PID_Mode = PID_POSITION;
}

// void RMD_get_fdb_data(struct RMD_TorqueCtrl_Rx* motor_fdb,uint8_t* can_rx_data)
// {
    // if (can_rx_data[0]!=RMD_MULTI_CTRL_CMD)
    //     return;
    // else
    //     memcpy(motor_fdb,can_rx_data,8);
    
// }

/**
	* @brief CAN通信电机的反馈数据具体解析函数
	* @param 电机数据结构体
	* @retval None
	*/
void MotorEncoderProcess(struct CAN_Motor *motor, uint8_t *RecvData)
{

	if (RecvData[0]!=RMD_MULTI_CTRL_CMD)
        return;
    else
    {
        motor->last_fdbPosition=motor->fdbPosition;
        memcpy(motor,RecvData+1,8-1);
    }

	// motor->last_real_position = motor->real_position;
	// motor->real_position = motor->fdbPosition + motor->round * 8192;	//位置环需要真实角度数据 
}

//发送，参数为四个电机的电流环控制量
void Can_MultiCtrl_Tx1234(CAN_HandleTypeDef* hcanx,int16_t cm1_iq, int16_t cm2_iq, int16_t cm3_iq, int16_t cm4_iq)
{
    uint8_t tx_data[8];
    tx_data[0]=0x00;//tx_data[0] = *(uint8_t*)(&cm1_iq);
	tx_data[1] = *((uint8_t*)(&cm1_iq)+1);
	tx_data[2] = *(uint8_t*)(&cm2_iq);
	tx_data[3] = *((uint8_t*)(&cm2_iq)+1);
	tx_data[4] = *(uint8_t*)(&cm3_iq);
	tx_data[5] = *((uint8_t*)(&cm3_iq)+1);
	tx_data[6] = *(uint8_t*)(&cm4_iq);
	tx_data[7] = *((uint8_t*)(&cm4_iq)+1);

    uint32_t Can_TxMailbox;
	HAL_CAN_AddTxMessage(hcanx,&RMD_multiCtrl_txHeader,tx_data, &Can_TxMailbox);
}

void Can_SingleCtrl_Tq_Tx(CAN_HandleTypeDef* hcanx,int id,int16_t tq)
{
	uint8_t tx_data[8]={0};
	tx_data[0]=0xA1;
	tx_data[4] = *(uint8_t*)(&tq);
	tx_data[5] = *((uint8_t*)(&tq)+1);
	
	uint32_t Can_TxMailbox;
	switch(id)
	{
		case 1:
			
	HAL_CAN_AddTxMessage(hcanx,header,tx_data, &Can_TxMailbox);
}
