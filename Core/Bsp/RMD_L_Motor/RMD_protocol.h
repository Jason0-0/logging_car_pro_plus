#ifndef RMD_PROTOCOL_H
#define RMD_PROTOCOL_H

#include "stm32f4xx.h"  //#include "stdint.h"

// ID
#define CAN_ID_MULTI_MOTOR_TX 0x280 
#define CAN_ID_MOTOR1 0x201
#define CAN_ID_MOTOR2 0x202
#define CAN_ID_MOTOR3 0x203
#define CAN_ID_MOTOR4 0x204

//  Command
#define RMD_MULTI_CTRL_CMD 0xA1


struct RMD_TorqueCtrl_Rx
{
    uint8_t command;    //0xA1
    int8_t temperature;    //°C
    int16_t current;   //-2048~2048 -> -33A~33A
    int16_t speed; //degree per second
    uint16_t encoder;   //0~16383
};


#endif // !RMD_L_PROTOCOL_H
