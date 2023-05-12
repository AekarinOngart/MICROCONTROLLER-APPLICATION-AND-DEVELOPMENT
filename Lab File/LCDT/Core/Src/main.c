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
#include "i2c.h"
#include "rng.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "ILI9341_GFX.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_Touchscreen.h"
#include "string.h"
#include "stdio.h"
#include "picture.h"
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

u_int16_t rcolor ;
u_int16_t gcolor ;
u_int16_t bcolor ;
u_int16_t rgbcolor;


float h=30.0,t=40.0;
u_int8_t step =0;
HAL_StatusTypeDef status;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */


uint16_t CRC16_2(uint8_t *,uint8_t);
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
  char str[50];
  uint8_t cmdBuffer[3];
  uint8_t dataBuffer[8];
  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

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
  MX_RNG_Init();
  MX_SPI5_Init();
  MX_TIM1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  ILI9341_Init();

  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);

  ILI9341_Fill_Screen(WHITE);
  uint16_t red=0;
  uint16_t green=0;
  uint16_t blue=0;
  uint16_t timeout=0;
  cmdBuffer[0]=0x03;
  cmdBuffer[1]=0x00;
  cmdBuffer[2]=0x04;



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE
     * #define ILI9341_SCREEN_HEIGHT 240
		#define ILI9341_SCREEN_WIDTH 	320
     *  */



	  HAL_Delay(50);

	  HAL_I2C_Master_Transmit(&hi2c1, 0x5c<<1, cmdBuffer, 3, 200);
	  HAL_I2C_Master_Transmit(&hi2c1, 0x5c<<1, cmdBuffer, 3, 200);
	  HAL_Delay(1);
	  HAL_I2C_Master_Receive(&hi2c1, 0x5c<<1, dataBuffer, 8, 200);
	  uint16_t Rcrc = dataBuffer[7]<<8;
	  Rcrc +=dataBuffer[6];
	  if (Rcrc == CRC16_2(dataBuffer,6))
	  {
		  uint16_t temperature = ((dataBuffer[4]%0x7F)<<8)+dataBuffer[5];
		  t = temperature/10.0;
		  t=(((dataBuffer[4]&0x80)>>7)==1)?(t*(-1)):t;
		  uint16_t humidity=(dataBuffer[2]<<8)+dataBuffer[3];
		  h= humidity/10.0;


	  }
	  char temperature[4];
	  char Humudity[10];

	  sprintf(temperature,"%4.1fC",t);
	  ILI9341_Draw_Text(temperature, 20, 25, BLACK, 2, WHITE);


	  sprintf(Humudity,"%4.1f%%RH",h);
	  ILI9341_Draw_Text(Humudity, 180, 25, BLACK, 2, WHITE);






	  rcolor=((red*25+5)>>3)<<11;
	  gcolor=((green*25+5)>>2)<<5;
	  bcolor=(blue*25+5)>>3;
	  rgbcolor=rcolor|gcolor|bcolor;

	  if(TP_Touchpad_Pressed())
	  {
		  uint16_t x_pos=0;
		  uint16_t y_pos=0;
		  HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin, GPIO_PIN_SET);
		  uint16_t position_array[2];
		  if(TP_Read_Coordinates(position_array)==TOUCHPAD_DATA_OK)
		  {
			  x_pos= position_array[0];
			  y_pos=position_array[1];
			  if(x_pos>100 && x_pos<125&&y_pos>285&&y_pos<305)
			  {
				  red++;
			  	  if (red>10)
			  	  {

			  		  red=0;
			  	  }
			  }
			  if(x_pos>150 && x_pos<180&&y_pos>285&&y_pos<305)
			  {

				  green++;
			  	  if (green>10)
			  	  {
			  		green=0;
			  	  }
			  }
			  if(x_pos>200 && x_pos<230&&y_pos>285&&y_pos<305)
			  {

				  blue++;
				  if (blue>10)
				  {
					  blue=0;
				  }
			  }
			  if(x_pos>30 && x_pos<50&&y_pos>180&&y_pos<220)
			  {

			  	  ILI9341_Fill_Screen(WHITE);
			  	  ILI9341_Draw_Image((const char*)picture, SCREEN_HORIZONTAL_2);
			  	  ILI9341_Draw_Text("Group No.15", 125, 45, rgbcolor, 2, WHITE);
			  	  ILI9341_Draw_Text("Watanyu", 125, 65, rgbcolor, 2, WHITE);
			  	  ILI9341_Draw_Text("Wasusirikul", 125, 85, rgbcolor, 2, WHITE);
			  	  ILI9341_Draw_Text("640115125", 125, 105, rgbcolor, 2, WHITE);
			  	  ILI9341_Draw_Text("Kotcharat", 125, 125, rgbcolor, 2, WHITE);
			  	  ILI9341_Draw_Text("Phutatate", 125, 145, rgbcolor, 2, WHITE);
			  	  ILI9341_Draw_Text("64015018", 125, 165, rgbcolor, 2, WHITE);
			  	  while(timeout<5000)
				  	  {
				  	  HAL_Delay(100);
				  	  timeout+=100;
				  	  if(TP_Touchpad_Pressed())
				  	  {
				  		 if(TP_Read_Coordinates(position_array)==TOUCHPAD_DATA_OK)
				  				  {
				  					  x_pos= position_array[0];
				  					  y_pos=position_array[1];
				  					  if(x_pos>70 && x_pos<190&&y_pos>180&&y_pos<300)
				  					  {
				  						  timeout=5000;
				  					  }
				  				  }

				  	  }

				  	  }
					timeout=0;
				  	ILI9341_Fill_Screen(WHITE);


			  }


		  }

		  char counter_buff[30];
		  		sprintf(counter_buff,"POS X: %.3d", x_pos);
		  		ILI9341_Draw_Text(counter_buff, 10, 80, BLACK, 2, WHITE);
		  		sprintf(counter_buff,"POS Y: %.3d", y_pos);
		  		ILI9341_Draw_Text(counter_buff, 10, 120, BLACK, 2, WHITE);

	  }
	  else
	  {
		  HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

	  }
	  ILI9341_Draw_Filled_Circle(130,40, 30,rgbcolor);

	  char counter_buff[4];
	  ILI9341_Draw_Filled_Circle(30,110, 20, RED);
	  ILI9341_Draw_Filled_Rectangle_Coord(60, 95, 190, 125, 0xF5F5);
	  ILI9341_Draw_Filled_Rectangle_Coord(60, 95, (60+(red*13)), 125, RED);
	  memset(counter_buff,0,sizeof(counter_buff));
	  sprintf(counter_buff, "%d%%", red*10);
	  //ILI9341_Draw_Filled_Rectangle_Coord(200, 100, 20, 20, WHITE);
	  ILI9341_Draw_Text(counter_buff, 200, 100, BLACK, 3, WHITE);


	  ILI9341_Draw_Filled_Circle(30,160, 20, GREEN);
	  ILI9341_Draw_Filled_Rectangle_Coord(60, 145, 190, 175,0xB7B7);
	  ILI9341_Draw_Filled_Rectangle_Coord(60, 145, (60+(green*13)), 175,GREEN);
	  memset(counter_buff,0,sizeof(counter_buff));
	  sprintf(counter_buff, "%d%%", green*10);
	  //ILI9341_Draw_Filled_Rectangle_Coord(200, 150, 20, 20, WHITE);
	  ILI9341_Draw_Text(counter_buff, 200, 150, BLACK, 3, WHITE);



	  ILI9341_Draw_Filled_Circle(30,210, 20, BLUE);
	  ILI9341_Draw_Filled_Rectangle_Coord(60, 195, 190, 225,0x7E7E);
	  ILI9341_Draw_Filled_Rectangle_Coord(60, 195, (60+(blue*13)), 225,BLUE);
	  memset(counter_buff,0,sizeof(counter_buff));
	  sprintf(counter_buff, "%d%%", blue*10);
	  //ILI9341_Draw_Filled_Rectangle_Coord(200, 150, 20, 20, WHITE);
	  ILI9341_Draw_Text(counter_buff, 200, 200, BLACK, 3, WHITE);










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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 200;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
uint16_t CRC16_2 (uint8_t *ptr, uint8_t length)
{
       uint16_t crc = 0xFFFF;
       uint8_t s = 0x00;
       while (length--)
       {
         crc ^= *ptr++;
         for (s =0 ;s< 8; s++)
         {
           if ((crc & 0x01) != 0)
           {
             crc >>= 1;
             crc ^= 0xA001;
           }
           else crc >>= 1;
         }

       }
       return crc;
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
