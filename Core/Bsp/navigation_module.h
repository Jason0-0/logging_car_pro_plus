#ifndef NAVIGATION_MODULE_H
#define NAVIGATION_MODULE_H

#include "usart.h"
#include "dma.h"

#define NAVI_RX_LEN 28

typedef __packed struct __Navi_Fdb_t
{
    float yaw;
    float pitch;
    float roll;
    float x;
    float y;
    float angular_velocity_yaw;

}Navi_Fdb_t;

enum Navi_Tx_DataType_e
{
  cali=0,
  clear,
  update_yaw,
  update_x,
  update_y,
  update_xy,
  update_yaw_xy
  //...  
};

typedef __packed struct __Navi_Rx_data_t
{
    uint16_t header;
	Navi_Fdb_t fdb;
    uint16_t ender;
}Navi_Rx_data_t;

union Navi_Rx_data_u
{
    uint8_t rx[NAVI_RX_LEN];
    Navi_Rx_data_t raw_data;
};


void navi_init(void);

void Navi_UART_IDLE_Callback(UART_HandleTypeDef* huart);

void navi_data_rx_handle(uint8_t rx[]);
void navi_data_tx_handle(uint8_t tx[]);

extern Navi_Fdb_t navi_fdb;
extern uint8_t navi_tx_data[];
//extern uint8_t navi_rx_data[NAVI_RX_LEN];

#endif // !NAVIGATION_MODULE_H
