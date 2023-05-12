/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
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

/* USER CODE BEGIN PV */
char name[100];
char username[100];
char transmit[100];
char buffer[100];
int state1 = 1;
int state2 = 1;
int state3 = 1;
int state4 = 1;
int state5 = 1;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
int strcmp1(char A,char B);
/* USER CODE BEGIN PFP */

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

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC)==RESET){}
  HAL_UART_Transmit(&huart3, (uint32_t*)"\r\nMan From U.A.R.T.1!\n\rQuit PRESS q", 35, 1000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */


	  if (state1 == 1 ){
	  	 while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC)==RESET){}
	  	 	HAL_UART_Transmit(&huart3, (uint32_t*)"\r\n\tName : ", 10, 1000);


	  	 while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_RXNE)== RESET){}
	  	 	 HAL_UART_Receive(&huart3, (uint32_t*)&username, 100,1000);


	  	if (username[0] != '\000'){
	  		while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC)==RESET){}
	  		HAL_UART_Transmit(&huart3, (uint32_t*)&username, 100, 1000);
	  		while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TC)==RESET){}
	  		HAL_UART_Transmit(&huart2, (uint32_t*)&username, strlen(username), 1000);}

	  	    state1 = 0;
	  }


	  if (state2 == 1){

				  while(name[0] == '\000'){
					  memset(name,0,sizeof(name));
					  while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)== RESET){}
					  HAL_UART_Receive(&huart2, (uint32_t)&name, 100,1000);
				  }

				  while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC)==RESET){}
				  HAL_UART_Transmit(&huart3, (uint32_t*)"\r\n\t", 4, 200);
				  HAL_UART_Transmit(&huart3, (uint32_t)&name, 100, 1000);

				  while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC)==RESET){}
				  HAL_UART_Transmit(&huart3, (uint32_t*)" is Ready!", 10, 1000);
				  memset(name,0,sizeof(name));

	 		  state2 = 0;

	 	}

	      memset(buffer,0,sizeof(buffer));
	      memset(transmit,0,sizeof(transmit));

	 	 		  while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC)==RESET){}
	 	 		  	HAL_UART_Transmit(&huart3, (uint32_t*)"\r\n\t", 4, 200);
	 	 		  	HAL_UART_Transmit(&huart3, (uint32_t*)&username, strlen(username), 1000);

	 	 		  while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC)==RESET){}
	 	 		  	HAL_UART_Transmit(&huart3, (uint32_t*)"=>", 2, 1000);

	 	 		 while(transmit[0] == '\000'){
					  memset(transmit,0,sizeof(transmit));
					  while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_RXNE)== RESET){}
						HAL_UART_Receive(&huart3, (uint32_t*)&transmit, 100,1000);
	 	 		 }

	 	 		 while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC)==RESET){}
	 	 		 HAL_UART_Transmit(&huart3, (uint32_t*)&transmit, 100, 1000);

	 	 		if((transmit[0] == 'q'||transmit[0] == 'Q') && transmit[1] == '\000'){

	 	 			while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC)==RESET){}
	 	 			HAL_UART_Transmit(&huart3, (uint32_t)"\r\nUSER1 is disconected", 20, 1000);
	 	 			sprintf(buffer,"%s",transmit);
	 	 			while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TC)==RESET){}
	 	 			HAL_UART_Transmit(&huart2, (uint32_t*)&buffer, 100, 1000);
	 	 			break;

	 	 		}
	 	 		else{
	 	 		 sprintf(buffer,"\r\n\t%s : %s",username,transmit);
	 	 		  while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TC)==RESET){}
	 	 		  HAL_UART_Transmit(&huart2, (uint32_t*)&buffer, 100, 1000);
	 	 		}



		  memset(name,0,sizeof(name));

				  while(name[0] == '\000'){
					  memset(name,0,sizeof(name));
					  while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)== RESET){}
					  HAL_UART_Receive(&huart2, (uint32_t)&name, 100,1000);

				  }
				  if((name[0] == 'q'||name[0] == 'Q') && name[1] == '\000'){
				  	state3 == 0;
				  	while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC)==RESET){}
				  	HAL_UART_Transmit(&huart3, (uint32_t)"\r\nUSER2 is disconected", 20, 1000);
				  	break;
				  }
				  else{

					  while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC)==RESET){}
					  HAL_UART_Transmit(&huart3, (uint32_t)&name, 100, 1000);
				  }




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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
int strcmp1(char A,char B){
	int couter = 0;
	if (strlen(A) > strlen(B)){
		return 1;
	}
	else if (strlen(B) > strlen(A)){
		return 0;
	}


}


/* USER CODE END 4 */

/* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

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
