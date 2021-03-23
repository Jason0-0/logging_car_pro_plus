#include "bsp_can.h"
#include "can_motor.h"
#include "RMD_protocol.h"

extern struct CAN_Motor can1_motor_1;
extern struct CAN_Motor can1_motor_2;
extern struct CAN_Motor can1_motor_3;
extern struct CAN_Motor can1_motor_4;

uint8_t can_rx_data_FIFO0[8];
uint8_t can_rx_data_FIFO1[8];

/**
	* @brief CAN外设过滤器初始化
	* @param can结构体
	* @retval None
	*/
HAL_StatusTypeDef CanFilterInit(CAN_HandleTypeDef* hcan)
{
	// IdHigh, IdLow, MaskIdHigh, MaskIdLow 填写FIFO过滤的四个电机ID, 有空余填写0x800
	// FIFO0
	CAN_FilterTypeDef  sFilterConfig;
	if(hcan == &hcan1)
		sFilterConfig.FilterBank = 0;
	// if(hcan == &hcan2)
	// 	sFilterConfig.FilterBank = 14;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
	sFilterConfig.FilterIdHigh = CAN_ID_MOTOR1 << 5;
	sFilterConfig.FilterIdLow = CAN_ID_MOTOR3 << 5;
	sFilterConfig.FilterMaskIdHigh = 0x800 << 5;
	sFilterConfig.FilterMaskIdLow = 0x800 << 5;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;
	
	if(HAL_CAN_ConfigFilter(hcan, &sFilterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	// FIFO1
	if(hcan == &hcan1)
		sFilterConfig.FilterBank = 1;
	// if(hcan == &hcan2)
	// 	sFilterConfig.FilterBank = 15;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
	sFilterConfig.FilterIdHigh = CAN_ID_MOTOR2 << 5;
	sFilterConfig.FilterIdLow = CAN_ID_MOTOR4 << 5;
	sFilterConfig.FilterMaskIdHigh = 0x800 << 5;	
	sFilterConfig.FilterMaskIdLow = 0x800 << 5;	
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO1;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;
	
	if(HAL_CAN_ConfigFilter(hcan, &sFilterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	
	if (HAL_CAN_Start(hcan) != HAL_OK)
	{
		Error_Handler();
	}
	// FIFO0 IT
	if (HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	{
		Error_Handler();
	}
	// FIFO1 IT
	if (HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK)
	{
		Error_Handler();
	}
	return HAL_OK;
}

/**
	* @brief CAN通信接收中断回调函数-FIFO0
	* @param CAN序号
	* @retval None
	*/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef RxHeader;
	if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, can_rx_data_FIFO0) != HAL_OK)
	{
		Error_Handler();            //如果CAN通信数据接收出错，则进入死循环
	}
	if(hcan == &hcan1)
		CanDataReceive(RxHeader.StdId, can_rx_data_FIFO0);   //进行CAN数据解析
	// else if(hcan == &hcan2)
	// 	Can2DataReceive(RxHeader.StdId, can_rx_data_FIFO0);
}
/**
	* @brief CAN通信接收中断回调函数-FIFO1
	* @param CAN序号
	* @retval None
	*/
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef RxHeader;
	if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &RxHeader, can_rx_data_FIFO1) != HAL_OK)
	{
		Error_Handler();            //如果CAN通信数据接收出错，则进入死循环
	}
	if(hcan == &hcan1)
		CanDataReceive(RxHeader.StdId, can_rx_data_FIFO1);   //进行CAN数据解析
	// else if(hcan == &hcan2)
	// 	Can2DataReceive(RxHeader.StdId, can_rx_data_FIFO1);
}

/**
	* @brief 根据电机信息的ID号进行对应的数据解析-CAN1
	* @param 电机ID号
	* @retval None
	*/
void CanDataReceive(int motor_index, uint8_t *RecvData)
{
	switch(motor_index)
	{
	case CAN_ID_MOTOR1:
		MotorEncoderProcess(&can1_motor_1, RecvData);break;    //电机数据具体解析函数
	case CAN_ID_MOTOR2:
		MotorEncoderProcess(&can1_motor_2, RecvData);break;
	case CAN_ID_MOTOR3:
		MotorEncoderProcess(&can1_motor_3, RecvData);break;
	case CAN_ID_MOTOR4:
		MotorEncoderProcess(&can1_motor_4, RecvData);break;
	default:break;
	}
}
