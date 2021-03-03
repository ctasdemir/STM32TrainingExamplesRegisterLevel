#include "button_driver.h"
#include "stm32f0xx_hal.h"
#include "uart_driver.h"


#define BUFFER_SIZE 256

UART_HandleTypeDef UartHandle;

uint32_t rx_data = 0;


static void UART_Error_Handler(void);


/*  
  UART_Init()
  UART'i proje specifikasyonunda belirtilen hiz ve
  ayarlarla baslatir. 
  RX kesmelerini aktif hale getirir.

*/
void UART_Init()
{
	
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */  
	__HAL_RCC_GPIOA_CLK_ENABLE();

  /* Enable USARTx clock */
  __HAL_RCC_USART2_CLK_ENABLE(); 
  
  /*##-2- Configure peripheral GPIO ##########################################*/  
  /* UART TX GPIO pin configuration  */
	
	
  GPIO_InitStruct.Pin       = GPIO_PIN_2;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF1_USART2;
  
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
	
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF1_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    

/*##-3- Configure the UART peripheral ######################################*/
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART configured as follows:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = None
      - BaudRate = 9600 baud
      - Hardware flow control disabled (RTS and CTS signals) */
  UartHandle.Instance        = USART2;
	
  UartHandle.Init.BaudRate   = 9600;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT; 
	
	
  if (HAL_UART_Init(&UartHandle) != HAL_OK) {
        //ERROR
        UART_Error_Handler();
    }

   /* 4- Enable UART Receive Data Register Not Empty */
   SET_BIT(USART2->CR1, USART_CR1_RXNEIE);

   /* 5 - Enable UART Interrupt in NVIC */

   HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
   HAL_NVIC_EnableIRQ(USART2_IRQn);
}




/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void UART_Error_Handler(void)
{
     while(1)
    {      
  
    }
}


/**
 * @brief  This function handles UART interrupt request.
 * @param  None
 * @retval None
 */
void USART2_IRQHandler(void) {
	uint32_t isrflags = USART2->ISR;
	uint32_t control_reg1 = USART2->CR1;

	/* UART in mode Receiver */
	if (((isrflags & USART_ISR_RXNE) != RESET) && ((control_reg1 & USART_CR1_RXNEIE) != RESET)) {
		rx_data = (uint8_t) USART2->RDR;

		return;
	}

	/* UART in mode Transmitter */
	if (((isrflags & USART_ISR_TXE) != RESET) && ((control_reg1 & USART_CR1_TXEIE) != RESET)) {

		return;
	}
}

