#ifndef BSP_CAN_H
#define BSP_CAN_H

#include "can.h"
#include "RMD_protocol.h"
#define HCAN (hcan1)



extern HAL_StatusTypeDef CanFilterInit(CAN_HandleTypeDef* hcan);

void CanDataReceive(int motor_index,uint8_t *RxData);

#endif // !CAN_MOTOR_H