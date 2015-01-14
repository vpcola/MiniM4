#ifndef __STMNUCLEO_DELAY_H__
#define __STMNUCLEO_DELAY_H__

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

#ifdef __cplusplus
extern "C" {
#endif

void init_delay_timer(TIM_HandleTypeDef  * ptim);
void deinit_delay_timer(void);
void delay_us( uint16_t usec );

#ifdef __cplusplus
}
#endif


#endif

