# WS2812--PWM-DMA
此驱动库基于STM32HAL库进行封装
将此文件添加到你的工程文件中
一、驱动使用步骤：
1、写入灯RGB数据BUF
lg_ws2812_set_rgb(灯序号，R,G,B);
2、待发送数据写入（将第一步的RGB数据写入到发送缓冲区）
lg_ws2812_write_send_buf();
3、开始DMA发送
lg_ws2812_start_send_buf();

二、屏幕驱动是基于WS2812驱动进行封装，具体使用如下
屏幕首先得配置好灯的坐标，在ws2812_Screen_config.h文件中进行配置
先调用
Screen_init();屏幕初始化

Screen_set_point(x,y,hsv); 对应位置打点   hsv色域数值
Screen_write_num(x,y,num,hsv); 对应位置显示一个3*5的数字
Screen_flush();刷新屏幕




个人邮箱：1570139720 @qq.com
