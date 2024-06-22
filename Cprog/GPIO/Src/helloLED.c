/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include <stdint.h>
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SYSCLK		64000000
#define AHB_PRESC	1
#define HCLK		( SYSCLK / AHB_PRESC )
#define T_HCLK		( 1.0 / HCLK )
#define PRESCALER	63999
#define TIME_1S		1.0
#define TIM_COUNT_1S	(( 65535 + 1 ) - ( round( TIME_1S / ( T_HCLK * ( PRESCALER + 1 )))))
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void USER_TIM2_Init(void);
void USER_Delay(uint16_t count);
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
  /* USER CODE BEGIN 2 */
  USER_TIM2_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  GPIOA->BSRR	=	GPIO_BSRR_BS5;//	value to set pin5 of port A (Turn-ON LD2)
	  USER_Delay( TIM_COUNT_1S );
	  GPIOA->BRR	=	GPIO_BRR_BR5;//		value to reset pin5 of port A (Turn-OFF LD2)
	  USER_Delay( TIM_COUNT_1S );
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
  // RCC_APB2ENR modified to IO port A clock enable
  // RCC->APB2ENR	|=	 RCC_APB2ENR_IOPAEN;
  // GPIOx_BRR modified to reset pin 5 of port A (LD2 is connected to PA5)
  GPIOA->BRR	 =	 GPIO_BRR_BR5;
  // GPIOx_CRL modified to configure pin5 as output
  GPIOA->CRL	&=	~GPIO_CRL_CNF5	& 	~GPIO_CRL_MODE5_1;
  // GPIOx_CRL modified to select pin5 max speed of 10MHz
  GPIOA->CRL	|=	 GPIO_CRL_MODE5_0;
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void USER_TIM2_Init(void){
	RCC->APB1ENR	|=   RCC_APB1ENR_TIM2EN;//	TIM2 peripheral clock enable
	TIM2->SMCR	&=  ~TIM_SMCR_SMS;//		select internal clock
	TIM2->CR1	&=  ~TIM_CR1_CMS//		edge-aligned mode
			&   ~TIM_CR1_DIR//		upcounter
			&   ~TIM_CR1_UDIS;//		update event (UEV) enabled
}
/* Function to generate a 1 second delay */
void USER_Delay(uint16_t count){
	TIM2->PSC	 =  PRESCALER;//		1:977 prescaler
	TIM2->EGR	|=  TIM_EGR_UG;//		update the prescaler
	TIM2->CNT	 =  count;//			initial count
	TIM2->SR	&= ~TIM_SR_UIF;//		clear TIM overflow-event flag
	TIM2->CR1	|=  TIM_CR1_CEN;//		timer enabled
	while( !(TIM2->SR &  TIM_SR_UIF) );//		wait until overflows
	TIM2->CR1	&=  TIM_CR1_CEN;//		timer disabled
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

#ifdef  USE_FULL_ASSERT
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
