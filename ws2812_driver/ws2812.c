#include "ws2812.h"

/* <定义发送缓冲区> */
WS2812_Frame WS2812_SEND_BUF;
WS2812_RGB   WS2812_RGB_BUF[WS2812_NUM];
WS2812_HSV   WS2812_HSV_BUF[WS2812_NUM];
uint16_t *WS2812_Frame_Head = (uint16_t*)&WS2812_SEND_BUF;
uint16_t *WS2812_Frame_Data = &WS2812_SEND_BUF.Data[0];
/* <______________> */

void lg_ws2812_init           (void){
    uint16_t *add = (uint16_t *) &WS2812_SEND_BUF;
    for(uint16_t i=0;i<WS2812_SEND_BUF_SIZE;i++){
        *add=WS2812_0;
         add++;
    }

    WS2812_SEND_BUF.Head[0]=0;
    WS2812_SEND_BUF.Head[1]=0;
    WS2812_SEND_BUF.Head[2]=0;
    WS2812_SEND_BUF.End=0;

    /* <RGB BUF 初始化> */
    for(uint16_t i=0;i<WS2812_NUM;i++){
     WS2812_RGB_BUF[i].r=0;
     WS2812_RGB_BUF[i].g=0;
     WS2812_RGB_BUF[i].b=0;
  }
}
void lg_ws2812_clear          (void){
    for(uint16_t i=0;i<WS2812_NUM;i++){
        WS2812_RGB_BUF[i].r = 0;
		WS2812_RGB_BUF[i].g = 0;
		WS2812_RGB_BUF[i].b = 0;
    }
}
void lg_ws2812_write_data     (WS2812_RGB *data, uint16_t *add){
     //写好一个灯的数据  放在以地址add开头的存储区
     //一个灯的数据为24字节    
       uint16_t m = 0;
       uint16_t dat[3] = {0};
       dat[0] = data->g;
       dat[1] = data->r;
       dat[2] = data->b;
       for(uint8_t j=0;j<3;j++){
           for(uint8_t k=0;k<8;k++){
               if(dat[j] & 0x80){
                   add[m] = WS2812_1;
               }
               else{
                   add[m] = WS2812_0;
               }
               dat[j] = dat[j] << 1;
               m++;
           }
       }
}
void lg_ws2812_write_send_buf (void){
     for(uint16_t i=0;i<WS2812_NUM;i++){
         lg_ws2812_write_data(&WS2812_RGB_BUF[i],&WS2812_Frame_Data[24*i]);
     }	 
}
void lg_ws2812_start_send_buf (void){
     HAL_TIM_PWM_Start_DMA(&WS2812_TIM,WS2812_Chanel,(uint32_t *)&WS2812_SEND_BUF,WS2812_SEND_BUF_SIZE);
}
void lg_ws2812_stop_send_buf  (void){
     HAL_TIM_PWM_Stop_DMA(&WS2812_TIM,WS2812_Chanel);
}
void lg_ws2812_set_all_rgb    (uint8_t r,uint8_t g, uint8_t b){
    for(uint16_t i=0;i<WS2812_NUM;i++){
        WS2812_RGB_BUF[i].r = r;
        WS2812_RGB_BUF[i].g = g;
        WS2812_RGB_BUF[i].b = b;
    }
}
void lg_ws2812_set_rgb        (uint16_t number,uint8_t r,uint8_t g, uint8_t b){
     WS2812_RGB_BUF[number].r = r;
     WS2812_RGB_BUF[number].g = g;
     WS2812_RGB_BUF[number].b = b;
}


__weak void lg_ws2812_callback(void){}
/* <ws2812 回调> */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim){
     /* <发送完一帧数据后回调> */
     lg_ws2812_callback();
}
