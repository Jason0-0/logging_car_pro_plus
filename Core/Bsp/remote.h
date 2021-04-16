/**
  ******************************************************************************
  * 文件名          : remote.c
  * 创建时间        : 2018.12.28
  * 作者            : 刘文熠
  *-----------------------------------------------------------------------------
  * 最近修改时间    : 2019.12.28
  * 修改人          : 邓紫龙
  ******************************************************************************
  * 1.本代码基于STMF427IIT6开发，编译环境为Keil 5，基于FreeRTOS进行开发。
  * 2.本代码只适用于RoboMaster机器人，不建议用于其他用途
	* 3.本代码包含大量中文注释，请以UTF-8编码格式打开
	* 4.本代码最终解释权归哈尔滨工业大学（深圳）南工骁鹰战队Critical HIT所有
	* 
	* Copyright (c) 哈尔滨工业大学（深圳）南工骁鹰战队Critical HIT 版权所有
  ******************************************************************************
  */

    /********************遥控接收系统规格参数*********************
    *DJI DESSET 2.4G遥控接收系统   工作频率           2.4GHz ISM *
    *                              通信距离(开阔室外)   1km      *
    *------------------------------------------------------------*
    *DT7遥控器                     特性                7通道     *
    *                              工作电流/电压       120mA@3.7V*
    *                              电池          3.7V2000mA锂电池*
    *------------------------------------------------------------*
    *DR16接收机                    特性          2.4GHz D-Bus协议*
    *                              接收灵敏度(1%PER)   -97dBm    *
    *                              工作电流/电压       145mA@5V  *
    *                              电源                4-8.4V    *
    *                              电压             41mm*29mm*5mm*
    *                              重量                 10g      *
    **************************************************************/

    /************************接收机DR16***************************
    *遥控器接收机输出信号为标准DBUS协议数据，当接收机和发射机建立*
    *连接后，接收机便会每隔7ms通过DBus发送一帧数据(18字节)       *
    *                                                            *
    *DBus通信参数如下:                                           *
    *                                                            *
    *DBus参数            数值                                    *
    *波特率             100Kbps                                  *
    *单元数据长度         9                                      *
    *奇偶校验位         偶校验                                   *
    *结束位               2                                      *
    *流控                 无                                     *
    **************************************************************/


    /*************************发射机DT7***************************
    *                                                            *						   
    *   -----------------------------------------------------    *
    *   |     (上-1)                               (上-1)   |    *
    *   |SW_L|(中-3)                          SW_R|(中-3)   |    *
    *   |     (下-2)                               (下-2)   |    *
    *   |                                                   |    *
    *   |    | ^ |                                | ^ |     |    *
    *   |    | 3 |左摇杆                     右摇杆| 1 |     |    *
    *   | ---     ---                          ---     ---  |    *
    *   |<           2>                       <           0>|    *
    *   | ---     ---                          ---     ---  |    *
    *   |    |   |                                |   |     |    *
    *   |    |   |                                |   |     |    *
    *   |                                                   |    *
    *   -----------------------------------------------------    *
    *                                                            *
    **************************遥控器信息**************************
    *域            通道0      通道1   通道2   通道3   S1     S2  *
    *偏移            0          11      22      33    44     46  *
    *长度(bit)      11          11      11      11     2      2  *
    *符号位         无          无      无      无    无     无  *
    *范围           ***********最大值1684*********    *最大值3*  *
    *               *          中间值1024        *    *最小值1*  *
    *               ***********最小值364**********               *
    *功能                                            1:上   1:上 *
    *                                                2:下   2:下 *
    *                                                3:中   3:中 *
    *                                                            *
    ***************************鼠标信息***************************
    *域         鼠标x轴   鼠标y轴   鼠标z轴   鼠标左键   鼠标右键*
    *偏移         48        64        80        86        94   *
    *长度         16        16        16        8         8    *
    *符号位       有        有        有        无         无   *
    *范围         ******最大值32767*****        ***最大值1***   *
    *             *     最小值-32768   *        ***最小值0***   *
    *             ******静止值0*********                        *
    *功能       ***鼠标在XYZ轴的移动速度***   *鼠标左右键是否按下*
    *           *  负值表示往左移动       *   *    0:没按下      *
    *           ***正值表示往右移动********   *****1:按下*********
    *                                                           *
    *                                                           *
    ***************************键盘信息***************************
    *域              按键                                       *
    *偏移            102                                        *
    *长度            16                                         *
    *符号位          无                                          *
    *范围            位值标识                                    *
    *功能            每个按键对应一个bit                          *
    *                Bit 0:W键                                   *
    *                Bit 1:S键                                   *
    *                Bit 2:A键                                   *
    *                Bit 3:D键                                   *
    *                Bit 4:Shift键                               *
    *                Bit 5:Ctrl键                                *
    *                Bit 6:Q键                                   *
    *                Bit 7:E键                                   *
    *                Bit 8:R键                                   *
    *                Bit 9:F键                                   *
    *                Bit10:G键                                   *
    *                Bit11:Z键                                   *
    *                Bit12:X键                                   *
    *                Bit13:C键                                   *
    *                Bit14:V键                                   *
    *                Bit15:B键                                   *
    **************************************************************/


#ifndef _REMOTE_H_
#define _REMOTE_H_

#include "usart.h"
/**
	* 修改说明：
	* USART_Remote为Cube配置的串口号
	* huart_Remote为Cube配置的串口号
	*/
#define USART_Remote USART1
#define huart_Remote huart1

#define CHx_BIAS 1024   //通道中间值为1024

#define Key_W     0x0001  //键盘对应的通信协议数据
#define Key_S     0x0002
#define Key_D     0x0004
#define Key_A     0x0008
#define Key_Shift 0x0010
#define Key_ECtrl 0x0020
#define Key_Q     0x0040
#define Key_E     0x0080
#define Key_R     0x0100
#define Key_F     0x0200
#define Key_G     0x0400
#define Key_Z     0x0800
#define Key_X     0x1000
#define Key_C     0x2000
#define Key_V     0x4000
#define Key_B     0x8000

struct Remote_t
{
	int16_t ch0;
	int16_t ch1;
	int16_t ch2;
	int16_t ch3;
	int16_t ch4;
	int8_t s1;       //左拨杆
	int8_t s2;       //右拨杆
};

struct Mouse_t
{
	int16_t x;
	int16_t y;
	int16_t z;
	uint8_t press_l;
	uint8_t press_r;
};

struct Key_t
{
	int w;
	int s;
	int a;
	int d;
	int shift;
	int ctrl;
	int q;
	int e;
	int r;
	int f;
	int g;
	int z;
	int x;
	int c;
	int v;
	int b;
};

enum RemoteInputMode_e
{
	RC_Stop,
  RC_Remote,
	RC_MouseKey
};

struct DT7Remote_t
{
	struct Remote_t rc;         //遥控器
	struct Remote_t last_rc;
  struct Mouse_t mouse;       //鼠标
	struct Mouse_t last_mouse;
	uint16_t keyboard;          //键盘
	uint16_t last_keyboard;
	struct Key_t key;           //键盘各键位状态
	enum RemoteInputMode_e inputmode;//机器人工作模式
};

extern void REMOTE_IDLE_Callback(UART_HandleTypeDef *huart);//中断回调函数
extern void Remote_init(void);
void RemoteData(void);
void KeyStateChange(void);    //键位状态更新

#endif
