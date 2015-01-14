#include "delay.h"
#include <stdint.h>

static TIM_HandleTypeDef  * phtim = NULL;

void init_delay_timer(TIM_HandleTypeDef  * ptim)
{
  
  phtim = ptim;
  __HAL_TIM_ENABLE(phtim);
 
}

void deinit_delay_timer(void)
{
  phtim = NULL;
  __HAL_TIM_DISABLE(phtim);
}

void delay_us( uint16_t delay ) 
{
  uint16_t diff, end, begin = 0;
  
  if (phtim)
  {
    begin = __HAL_TIM_GetCounter(phtim);
    do {
        end = __HAL_TIM_GetCounter(phtim);
        
        if ((end - begin) < 0) // handle overflow
          diff = (UINT16_MAX - begin) + end;
        else
          diff = end - begin;
        
    }while(diff < delay);
        
    // while((uint16_t) ((__HAL_TIM_GetCounter(phtim) - timerValue))  < usec );
  }
}
