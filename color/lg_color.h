#pragma once
#include "stdint.h"
typedef struct 
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}RGB;

typedef struct 
{
    uint8_t h;
    uint8_t s;
    uint8_t v;
}HSV;


/* <hsvתΪrgb> */
RGB hsv_to_rgb(HSV hsv);


