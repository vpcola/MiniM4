/*----------------------------------------------------------------------------
 * Name:    Serial.c
 * Purpose: Low level serial routines
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2004-2013 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "serial.h"
#include "task.h"

static UART_HandleTypeDef * phuart = NULL;

/*-----------------------------------------------------------------------------
 *       serialInit:  Initialize Serial Interface
 *----------------------------------------------------------------------------*/
void serialInit (UART_HandleTypeDef * puart) {
	phuart = puart;
}


/*-----------------------------------------------------------------------------
 *       SER_PutChar:  Write a character to Serial Port
 *----------------------------------------------------------------------------*/
int32_t serialPutChar (int32_t ch) {
	HAL_StatusTypeDef ret = HAL_OK;
	uint32_t chData = ch;
	
	if (phuart)
	{
		// Wait untill uart is ready
		while( phuart->State != HAL_UART_STATE_READY) taskYIELD();
		ret = HAL_UART_Transmit(phuart, (uint8_t *) &chData, 1 , 1000);	
		if (ret != HAL_OK) 
			return -1;
	}
	
  return 0;
}


/*-----------------------------------------------------------------------------
 *       SER_GetChar:  Read a character from Serial Port
 *----------------------------------------------------------------------------*/
int32_t serialGetChar (void) {
	HAL_StatusTypeDef ret = HAL_OK;
	uint32_t chData;

	if (phuart)
	{
		// Wait untill uart is ready
		while( phuart->State != HAL_UART_STATE_READY) taskYIELD();
		ret = HAL_UART_Receive(phuart, (uint8_t *) &chData, 1 , 10);	
		if (ret == HAL_OK) 
			return chData;
	}
	
  return (-1);
}

/*-----------------------------------------------------------------------------
 * end of file
 *----------------------------------------------------------------------------*/
