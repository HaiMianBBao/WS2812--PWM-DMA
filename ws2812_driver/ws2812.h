/* <WS2812驱动程序
采用PWM加DMA驱动
> */
#pragma once
/* <include__________> */
#include "stm32f1xx_hal.h"
/* <时序参数> */
#define WS2812_0  29        /* <0码> */               
#define WS2812_1  60        /* <1码> */
                            /* <速率800Khz 时序规定 不可调整> */
/* <灯数量配置> */
#define WS2812_NUM  16*16

/* <驱动硬件配置> */
extern TIM_HandleTypeDef htim2;
#define WS2812_TIM       htim2
#define WS2812_Chanel    TIM_CHANNEL_2

/* <定义数据帧> */
typedef struct 
{
     uint16_t Head[3];              /* <开头发三个0  等待dma数据稳定> */
     uint16_t Data[WS2812_NUM*24];  /* <真实的RGB数据  ws2812为 GRB> */
     uint16_t End;                  /* <末尾发个0    稳定下一帧发送> */
}WS2812_Frame;
                                    /* <！每刷新一帧  DMA将发送  （3+WS2812_NUM*24+1）个字节> */

/* <定义数据帧大小> */
#define WS2812_SEND_BUF_SIZE  (3+24*WS2812_NUM+1)

typedef struct 
{
    uint8_t g;
    uint8_t r;
    uint8_t b;
}WS2812_RGB;   /* <每一位灯所含有的数据> */

typedef struct 
{
    uint8_t h;
    uint8_t s;
    uint8_t v;
}WS2812_HSV;

/* <缓冲区> */
extern WS2812_Frame   WS2812_SEND_BUF;            /* <发送缓冲区> */
extern WS2812_RGB     WS2812_RGB_BUF[WS2812_NUM]; /* <RGB数据缓冲区> */
extern WS2812_HSV     WS2812_HSV_BUF[WS2812_NUM]; /* <HSV数据缓冲区> */
extern uint16_t       *WS2812_Frame_Data;         /* <颜色数据缓冲区> */

/* <ws2812驱动相关函数> */
void lg_ws2812_clear          (void);             /* <清屏函数> */
void lg_ws2812_init           (void);             /* <初始化函数> */
void lg_ws2812_write_send_buf (void);             /* <待发送数据写入> */
void lg_ws2812_start_send_buf (void);             /* <开始发送数据> */
void lg_ws2812_stop_send_buf  (void);             /* <停止发送数据> */
void lg_ws2812_callback       (void);             /* <发送完一帧数据产生的回调> */


void lg_ws2812_write_data     (WS2812_RGB *data, uint16_t *add);                  /* <写一个字节数据> */
void lg_ws2812_set_rgb        (uint16_t number,uint8_t r,uint8_t g, uint8_t b);   /* <指定一个灯的RGB数据> */
void lg_ws2812_set_all_rgb    (uint8_t r,uint8_t g, uint8_t b);                   /* <设定所有灯的RGB数据> */
        

