#include "ws2812_Screen.h"
#include "rgb_effect.h"
#include "math.h"
#include "lg_word.h"               
uint8_t X_Y[Screen_ROW][Screen_COL];
Screen_Drive screen;               
RGB rgb_null  ={0,0,0};       
HSV hsv_null  ={0,0,0};
HSV hsv_white ={0,0,255};
void Screen_set_point (uint8_t x,uint8_t y,HSV hsv){
    RGB rgb = hsv_to_rgb(hsv);
    WS2812_HSV_BUF[X_Y[x][y]].h =  hsv.h; 
    WS2812_HSV_BUF[X_Y[x][y]].s =  hsv.s; 
    WS2812_HSV_BUF[X_Y[x][y]].v =  hsv.v;

    WS2812_RGB_BUF[X_Y[x][y]].r =  rgb.r; 
    WS2812_RGB_BUF[X_Y[x][y]].g =  rgb.g; 
    WS2812_RGB_BUF[X_Y[x][y]].b =  rgb.b;   
}
void Screen_init(void){
    for(uint16_t num=0;num<WS2812_NUM;num++){
        X_Y[LED_MAP[num].x][LED_MAP[num].y] = num;
    }
}
void Screen_write_cycle(int8_t x,int8_t y,int8_t rad,HSV hsv){
    RGB rgb = hsv_to_rgb(hsv);
    for(int8_t a=0;a<16;a++){
        for(int8_t b=0;b<16;b++){
            if((a-x)*(a-x)+(b-y)*(b-y) == rad*rad){
               WS2812_RGB_BUF[X_Y[a][b]].r =  rgb.r; 
               WS2812_RGB_BUF[X_Y[a][b]].g =  rgb.g; 
               WS2812_RGB_BUF[X_Y[a][b]].b =  rgb.b;   
            }
		} 
    }
}
void Screen_write_num  (uint8_t x,uint8_t y,uint8_t num,HSV hsv){
    RGB rgb = hsv_to_rgb(hsv);
    uint8_t data=0;
     for(uint8_t i=0;i<3;i++){
			 data = num_3_5[num][i];
         for(uint8_t j=0;j<5;j++){
           if(data & 0x01){
              Screen_set_point(x-i,y-j,hsv);
           }
           else{
              Screen_set_point(x-i,y-j,hsv_null);
           }          
           data = data >> 1;
         }
     }
}
void Screen_flush(void){
    lg_ws2812_write_send_buf();
    lg_ws2812_start_send_buf();
}
