#include "navigation_module.h"
#include "string.h"

#define NAVI_HUART huart8

#define HEADER (0x0D0A)
#define ENDER (0x0A0D)


//扔给串口的
union Navi_Rx_data_u navi_rx_data={0};
//发送
//todo...
//暴露出去的
struct Navi_Fdb_t navi_fdb={0};

void navi_init(void)
{
    //使能空闲中断和dma接收
    __HAL_UART_ENABLE_IT(&NAVI_HUART,UART_IT_IDLE);
    HAL_UART_Receive_DMA(&NAVI_HUART,&(navi_rx_data.raw_data),NAVI_RX_LEN);

    memset(&navi_rx_data,0,sizeof(union Navi_Rx_data_u));
    //memset()
}

void Navi_UART_IDLE_Callback(UART_HandleTypeDef* huart)
{
    if(__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE))
    {
        __HAL_UART_CLEAR_IDLEFLAG(huart);   //清除串口空闲中断标志位
		HAL_UART_DMAStop(huart);
        if(__HAL_DMA_GET_COUNTER(huart->hdmarx)==0)
        {
            //校验头尾，若通过就写入fdb中
            if (navi_rx_data.raw_data.header==HEADER&&navi_rx_data.raw_data.ender==ENDER)
            {
                navi_fdb=navi_rx_data.raw_data.fdb;
            }
            else    //清空缓冲区
                memset(&navi_rx_data,0,sizeof(union Navi_Rx_data_u));
        }
        HAL_UART_Receive_DMA(&NAVI_HUART,&(navi_rx_data.raw_data),NAVI_RX_LEN); //手动重新使能dma接收
    }
}
