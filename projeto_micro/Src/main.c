/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
/*Essas s�o as bibliotecas necess�rias para desenvolver o projeto. Os sensores MPU6050 utilizam comunica��o I2C.
 *
 */
#include "main.h"
#include "stm32f1xx_hal.h"
#include "i2c.h"
#include "usb_device.h"

/* USER CODE BEGIN Includes */

#include "sd_hal_mpu6050.h" //Library used to read sensor's values. Can be found at: https://github.com/sinadarvi/SD_HAL_MPU6050
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* Variables of type SD_MPU6050. Which have the sensor's values.
 * We use two sensors, so we use two variables.*/

SD_MPU6050 mpu1;
SD_MPU6050 mpu2;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
	//Flags which gives us status of the sensors mpu1 and mpu2 respectively.
	SD_MPU6050_Result result, result2;
	uint8_t mpu_ok[15] = {"MPU WORK FINE\n"};
	uint8_t mpu_not[17] = {"MPU NOT WORKING\n"};

	//	HID MOUSE
	/*  Struct with mouse's cursor informations.
	 *  If we set mouseHID.x = 10, the cursor will move 10 units in x axis. It's analogue to mouseHID.y, but in y axis.
	 *  If we set mouseHID.buttons = 1, the cursor will click. If mouseHID.buttons = 0, the cursor will release the click.
	 *  We don't use mouseHID.wheel in this project.
	 */
	struct mouseHID_t {
	      int8_t x;
	      int8_t y;
		  int8_t wheel;
		  uint8_t buttons;
	};
	struct mouseHID_t mouseHID;
	mouseHID.x 		 = 0;
	mouseHID.y		 = 0;
	mouseHID.wheel 	 = 0;
	mouseHID.buttons = 0;


  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  MX_I2C1_Init();		  // Init the first I2C comunication
  MX_I2C2_Init();   	  // Init the second I2C comunication
  MX_USB_DEVICE_Init();   // Init the USB comunication

  /* USER CODE BEGIN 2 */
  int16_t aux = 0;
  int16_t auy = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // We try to use the MPU sensors and assign them to the variables. Result will tell us if the process was successful.
	  result  = SD_MPU6050_Init(&hi2c1,&mpu1,SD_MPU6050_Device_0,SD_MPU6050_Accelerometer_2G,SD_MPU6050_Gyroscope_250s );
	  result2 = SD_MPU6050_Init(&hi2c2,&mpu2,SD_MPU6050_Device_0,SD_MPU6050_Accelerometer_2G,SD_MPU6050_Gyroscope_250s );

	  HAL_Delay(25);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

	  // Reading Mouse Position
	  SD_MPU6050_ReadGyroscope(&hi2c1, &mpu1);

	  int16_t g_x = mpu1.Gyroscope_X;
	  int16_t g_y = mpu1.Gyroscope_Y;
	  int16_t g_z = mpu1.Gyroscope_Z;

	  // X axis' value from Gyroscope, which corresponds to the Y axis' movement.
	  // This verification sets a threshold to the cursor's movement in the y axis'.
	  if((g_x - aux) > 300 && -(g_x - aux) < -300) {
		  mouseHID.y = (g_x)/150;
	  } else {
		  if(g_x < 0 && (g_x - aux) < -300) {
	  		  mouseHID.y = (g_x)/150;
	  	  } else {
	  		  mouseHID.y = 0;
	  	  }
	  }

	  // Analogue to the previous block of code, the Y axis' value from Gyroscope corresponds to the  X axis' value of the cursor.
	  // Once again, this verification sets a threshold to the cursor's movement in the x axis'.
	  if((g_y - auy) > 300 && -(g_y - auy) < -300) {
		  mouseHID.x = (g_y)/150;
	  } else {
		  if(g_y < 0 && (g_y - auy) < -300){
			  mouseHID.x = (g_y)/150;
		  } else {
			  mouseHID.x = 0;
		  }
	  }

	  // Reading Accelerometer to use in the click function of the mouse.
	  SD_MPU6050_ReadAccelerometer(&hi2c2, &mpu2);
	  int16_t a_x = mpu2.Accelerometer_X;

	  // Button Clicked: if we receive values less than -4500 in the accelerometer x axis', we understand that a click
	  // was made by the user.
	  if(a_x < -4500){
	  	  mouseHID.buttons = 1;
	  	  // We set the values below to zero so we can have more stability in the click movement.
	  	  mouseHID.x = 0;
	  	  mouseHID.y = 0;
	  	  // The SendReport function send to the mouse's driver the informations about the cursor movements and/or click.
	  	  USBD_HID_SendReport(&hUsbDeviceFS, &mouseHID, sizeof(struct mouseHID_t));
	  }
	  HAL_Delay(25);

	  // Button Released: Since we had set the click threshold to -4500, if the code passes this verification, the click is released.
	  if(a_x > -4500) {
		  mouseHID.buttons = 0;
	  }
	  USBD_HID_SendReport(&hUsbDeviceFS, &mouseHID, sizeof(struct mouseHID_t));
	  HAL_Delay(5);
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/