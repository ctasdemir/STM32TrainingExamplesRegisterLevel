/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
static char i2c_msg[64];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
static void i2c1_init(void);
static void i2c_scan(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  i2c1_init();

  HAL_UART_Transmit(&huart2, (uint8_t *)"I2C Master Ready\r\n", 18, 100);
  i2c_scan();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    HAL_Delay(5000);
    i2c_scan();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_0);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV4;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/**
 * I2C1 register-level init.
 * Pins : PB6 = SCL (AF6), PB7 = SDA (AF6), open-drain
 * Clock: PCLK = 12 MHz  ->  Standard Mode 100 kHz
 * TIMINGR: PRESC=2, SCLDEL=4, SDADEL=2, SCLH=16(0x10), SCLL=19(0x13)
 *          tPRESC=250ns, tSCLL=5000ns, tSCLH=4250ns => ~95kHz
 */
static void i2c1_init(void)
{
  /* 1. Enable GPIOB and I2C1 clocks */
  RCC->IOPENR  |= RCC_IOPENR_GPIOBEN;
  RCC->APBENR1 |= RCC_APBENR1_I2C1EN;

  /* 2. PB6 (SCL), PB7 (SDA): AF6, open-drain, no pull */
  /* MODER: bits [13:12]=10 (PB6 AF), [15:14]=10 (PB7 AF) */
  GPIOB->MODER &= ~((3UL << 12) | (3UL << 14));
  GPIOB->MODER |=  (2UL << 12)  | (2UL << 14);
  /* OTYPER: bits 6 and 7 = 1 (open-drain) */
  GPIOB->OTYPER |= (1U << 6) | (1U << 7);
  /* OSPEEDR: high speed */
  GPIOB->OSPEEDR |= (3UL << 12) | (3UL << 14);
  /* PUPDR: no pull */
  GPIOB->PUPDR &= ~((3UL << 12) | (3UL << 14));
  /* AFR[0]: PB6 and PB7 = AF6 (bits [27:24] and [31:28]) */
  GPIOB->AFR[0] &= ~((0xFUL << 24) | (0xFUL << 28));
  GPIOB->AFR[0] |=  (6UL << 24) | (6UL << 28);

  /* 3. Disable I2C1 before configuring */
  I2C1->CR1 &= ~I2C_CR1_PE;

  /* 4. Timing: PRESC=2, SCLDEL=4, SDADEL=2, SCLH=0x10, SCLL=0x13 */
  I2C1->TIMINGR = (2UL << 28) | (4UL << 20) | (2UL << 16) |
                  (0x10UL << 8) | 0x13UL;

  /* 5. Enable I2C1 */
  I2C1->CR1 |= I2C_CR1_PE;
}

/**
 * Scan all 7-bit I2C addresses (1-127) and report ACK responses via UART.
 */
static void i2c_scan(void)
{
  uint8_t found = 0;

  HAL_UART_Transmit(&huart2, (uint8_t *)"--- I2C Bus Scan ---\r\n", 22, 100);

  for (uint8_t addr = 1; addr < 128; addr++)
  {
    /* Send START + address (write, 0 bytes) */
    I2C1->CR2 = ((uint32_t)addr << 1) |        /* SADD[7:1] = addr */
                (0UL << 16)            |        /* NBYTES = 0       */
                I2C_CR2_START;                  /* generate START   */

    /* Wait for transfer complete (ACK) or NACK */
    uint32_t timeout = 50000U;
    while (!(I2C1->ISR & (I2C_ISR_TC | I2C_ISR_NACKF)) && --timeout);

    if (timeout && !(I2C1->ISR & I2C_ISR_NACKF))
    {
      /* Device acknowledged */
      int len = snprintf(i2c_msg, sizeof(i2c_msg),
                         "  Found: 0x%02X\r\n", addr);
      HAL_UART_Transmit(&huart2, (uint8_t *)i2c_msg, len, 100);
      found++;
    }

    /* Generate STOP and clear flags */
    I2C1->CR2  |= I2C_CR2_STOP;
    I2C1->ICR   = I2C_ICR_NACKCF | I2C_ICR_STOPCF;

    /* Wait for bus idle */
    timeout = 10000U;
    while ((I2C1->ISR & I2C_ISR_BUSY) && --timeout);
  }

  if (found == 0)
  {
    HAL_UART_Transmit(&huart2, (uint8_t *)"  No devices found.\r\n", 21, 100);
  }
  else
  {
    int len = snprintf(i2c_msg, sizeof(i2c_msg),
                       "Scan done: %u device(s) found.\r\n", found);
    HAL_UART_Transmit(&huart2, (uint8_t *)i2c_msg, len, 100);
  }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
