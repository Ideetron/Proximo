/*
 */
#ifndef SK6812_H
#define SK6812_H


#ifdef __cplusplus
extern "C" {
#endif



#define SK6812_OFF      0x00, 0x00, 0x00
#define SK6812_GREEN    0xFF, 0x00, 0x00
#define SK6812_RED      0x00, 0xFF, 0x00
#define SK6812_BLUE     0x00, 0x00, 0xFF
#define SK6812_YELLOW   0xFF, 0xFF, 0x00
#define SK6812_PURPLE   0x00, 0xFF, 0xFF
#define SK6812_WHITE    0xFF, 0xFF, 0xFF

#include <stdio.h>
#include "nrf_drv_i2s.h"
#include "stdlib.h"
#include "app_error.h"
#include "app_util_platform.h"
#include "bsp.h"


void sk6812(uint8_t Green, uint8_t Red, uint8_t Blue);




#ifdef __cplusplus
}
#endif


#endif
