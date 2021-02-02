#pragma once
#include "stdint.h"
#include "lg_color.h"
#include "ws2812_Screen_config.h"
typedef struct 
{
    void(*init)         (void);         /* <屏幕初始化函数> */
    void(*flush)        (void);         /* <刷新屏幕> */
    void(*set_color_all)(void);         /* <填充整个屏幕> */
	void(*write_cache)  (void);         /* <写好缓冲区> */
	void(*clear_all)    (void);         /* <清屏> */
	void(*set_color)    (uint16_t index,uint8_t r,uint8_t g,uint8_t b);/* <指定一个灯RGB数据> */
}Screen_Drive;

extern Screen_Drive screen;                  /* <屏幕驱动> */
extern uint8_t X_Y[Screen_ROW][Screen_COL];  /* <将灯坐标数据映射到此数组里面 方面快速查表> */

extern RGB rgb_null;
extern HSV hsv_null;
extern HSV hsv_white;

void Screen_init (void);               /* <屏幕初始化函数> */
void Screen_task (void);               /* <屏幕任务函数> */
void Screen_flush(void);               /* <屏幕刷新函数> */
void Screen_set_point  (uint8_t x,uint8_t y,HSV hsv);                 /* <指定坐标处打点> */
void Screen_write_line (uint8_t x,uint8_t y,uint8_t length,HSV hsv);  /* <指定坐标开始画一条长度为length的线> */
void Screen_write_cycle(int8_t  x,int8_t  y,int8_t  rad, HSV hsv);    /* <指定坐标为圆心画半径rad的圆> */
void Screen_write_num  (uint8_t x,uint8_t y,uint8_t num,HSV hsv);     /* <指定位置显示一个数字> */

