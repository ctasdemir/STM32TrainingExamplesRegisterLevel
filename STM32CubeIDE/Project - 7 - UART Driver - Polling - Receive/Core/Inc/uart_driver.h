/**
  ******************************************************************************
  * @file    uart_driver.h
  * @author  C.T
  * @version 
  * @date    
  * @brief   UART Driver Module Header File
  *******************************************************************************/
#ifndef __UART_DRIVER_H
#define __UART_DRIVER_H
#include "stm32f0xx_hal.h"


/**
  * @brief UART Initialization Function:
  * 	   Initializes UART with the following settings:
  * 	   Word Length = 8 Bits
      	   Stop Bit = One Stop bit
      	   Parity = None
           BaudRate = 9600 baud
           Hardware flow control disabled (RTS and CTS signals)

  * @param void
  * @retval void
  */
void UART_Init(void);

#endif
