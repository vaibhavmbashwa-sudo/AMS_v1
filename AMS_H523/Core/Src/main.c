/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "adc.h"
#include "fdcan.h"
#include "gpdma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "adBms_Application.h"
#include "math.h"
#include "application.h"
#include "common.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define AVG_SLOPE (4.3F)
#define V_AT_25C  (1.43F)
#define V_REF_INT (1.2F)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
SEG_PARAMS  SEG1,SEG2,SEG3,SEG4,SEG5;


SEG_BSTAT SEG1_B, SEG2_B, SEG3_B, SEG4_B, SEG5_B;


//uint16_t TS_Current;
float AMS_SOC = 0.0;
uint8_t AMS_SAFE;

float AMS_Charg_I = 0.0;;
float AMS_Charg_V = 0.0;;
uint8_t balancingState = 0 ; // 0-> normal mode || 1-> charger connected
//uint8_t MCU_junction_temp;

uint8_t UpdateEve_MCUtemp = 0 ;
uint16_t ADC_RES[2];
float MCUTemperature, V_Sense, V_Ref;

uint8_t Charge_EN = 0;
uint8_t Charge_FullAmp = 0;
uint8_t Charge_1Amp = 0;
uint8_t SDC_Temp_CHECK = 0;
uint8_t SDC_FLAG =1;
uint8_t SDC_V_CHECK = 0;
uint8_t FAN_CTRL=0;
uint8_t FAN_CTRL1=0;
uint8_t FAN_CTRL2=0;
uint8_t FAN_CTRL3=0;
uint8_t FAN_CTRL4=0;
uint8_t FAN_CTRL5=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
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

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_GPDMA1_Init();
  MX_FDCAN1_Init();
  MX_FDCAN2_Init();
  MX_SPI1_Init();
  MX_SPI3_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_UART4_Init();
  MX_TIM5_Init();
  MX_TIM4_Init();
  MX_ADC1_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(CS2_GPIO_Port,CS2_Pin,GPIO_PIN_SET);
  HAL_TIM_Base_Start(&htim3);
  HAL_TIM_Base_Start_IT(&htim6);
////  HAL_ADCEx_Calibration_Start(&hadc1,ADC_SINGLE_ENDED);
////  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC_RES, 2);   // Start ADC Conversion for MCU temp
////
  HAL_GPIO_WritePin(monStat_GPIO_Port, monStat_Pin, GPIO_PIN_SET);
//
//  HAL_GPIO_WritePin(AMS_Fault_GPIO_Port, AMS_Fault_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_SET);
//  init_contCurrentConv();
  CAN_Data_Init();
  CAN_Charger_Init();
//  HAL_Delay(1000);
//  canFraming();
  adbms_init_loop();
//  HAL_TIM_Base_Start_IT(&htim3);
//  canFraming();
//  cantestFraming();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  while(1)
//	  if(balancingState==0)
//	  	  {
	  if(SDC_FLAG){
		  HAL_GPIO_WritePin(AMS_Fault_GPIO_Port, AMS_Fault_Pin, GPIO_PIN_SET);
	  } else {
		  HAL_GPIO_WritePin(AMS_Fault_GPIO_Port, AMS_Fault_Pin, GPIO_PIN_RESET);
	  }

	  Fan_All(FAN_CTRL);
	  Fan_1(FAN_CTRL1);
	  Fan_2(FAN_CTRL2);
	  Fan_3(FAN_CTRL3);
	  Fan_4(FAN_CTRL4);
	  Fan_5(FAN_CTRL5);





//		  readI();
//		  ad29Delay_us(2500);


//	  cantestFraming();

//	   		CAN_DataTX_1s();



	  	  adbms_readCell_loop();
	  	  adbmsReinitMain();
//	  	HAL_Delay(50);
	  	  adbms_readTempToggle();
//
	  	  adBms_delayUs(3000);
//	  	CAN_DataTX_1s();
//	  	  }
//	  else
//	  	  {

//	  	  }
//	  	  HAL_Delay(50);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_CSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.CSIState = RCC_CSI_ON;
  RCC_OscInitStruct.CSICalibrationValue = RCC_CSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 30;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the programming delay
  */
  __HAL_FLASH_SET_PROGRAM_DELAY(FLASH_PROGRAMMING_DELAY_2);
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI1|RCC_PERIPHCLK_SPI3;
  PeriphClkInitStruct.PLL3.PLL3Source = RCC_PLL3_SOURCE_CSI;
  PeriphClkInitStruct.PLL3.PLL3M = 1;
  PeriphClkInitStruct.PLL3.PLL3N = 64;
  PeriphClkInitStruct.PLL3.PLL3P = 8;
  PeriphClkInitStruct.PLL3.PLL3Q = 2;
  PeriphClkInitStruct.PLL3.PLL3R = 2;
  PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3_VCIRANGE_0;
  PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3_VCORANGE_MEDIUM;
  PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
  PeriphClkInitStruct.PLL3.PLL3ClockOut = RCC_PLL3_DIVP;
  PeriphClkInitStruct.Spi1ClockSelection = RCC_SPI1CLKSOURCE_PLL3P;
  PeriphClkInitStruct.Spi3ClockSelection = RCC_SPI3CLKSOURCE_PLL3P;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	HAL_GPIO_TogglePin(monStat_GPIO_Port, monStat_Pin); // Toggle Interrupt Rate Indicator Pin
    UpdateEve_MCUtemp = 1;
}

void getMCUTemp(void)
{
	          V_Ref = (float)((V_REF_INT * 4095.0)/ADC_RES[0]);
	          V_Sense = (float)(ADC_RES[1] * V_Ref) / 4095.0;
	          MCUTemperature = (((V_AT_25C - V_Sense) * 1000.0) /AVG_SLOPE) + 25.0;
	          UpdateEve_MCUtemp = 0;

}

void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim)
{
 	if (htim == &htim4) {
// 		all++;
// 		canFraming();
//

 	}

 	if (htim == &htim6) {
 	// 		a++;
 	// 		canFraming();

 	 		CAN_Charger_transmit();
 	// 		HAL_Delay(100);

 	 	}

}

void Fan_All (uint8_t FANCtrl)
{
	if(FANCtrl){
			    HAL_GPIO_WritePin(Fan5Ctrl_GPIO_Port, Fan5Ctrl_Pin, GPIO_PIN_SET);
			    HAL_GPIO_WritePin(Fan4Ctrl_GPIO_Port, Fan4Ctrl_Pin, GPIO_PIN_SET);
		  		HAL_GPIO_WritePin(Fan1Ctrl_GPIO_Port, Fan1Ctrl_Pin, GPIO_PIN_SET);
		  		HAL_GPIO_WritePin(Fan2Ctrl_GPIO_Port, Fan2Ctrl_Pin, GPIO_PIN_SET);
		  		HAL_GPIO_WritePin(Fan3Ctrl_GPIO_Port, Fan3Ctrl_Pin, GPIO_PIN_SET);

		  	  } else {
		  		HAL_GPIO_WritePin(Fan5Ctrl_GPIO_Port, Fan5Ctrl_Pin, GPIO_PIN_RESET);
		  	    HAL_GPIO_WritePin(Fan4Ctrl_GPIO_Port, Fan4Ctrl_Pin, GPIO_PIN_RESET);
		  		HAL_GPIO_WritePin(Fan1Ctrl_GPIO_Port, Fan1Ctrl_Pin, GPIO_PIN_RESET);
		  			  		HAL_GPIO_WritePin(Fan2Ctrl_GPIO_Port, Fan2Ctrl_Pin, GPIO_PIN_RESET);
		  			  		HAL_GPIO_WritePin(Fan3Ctrl_GPIO_Port, Fan3Ctrl_Pin, GPIO_PIN_RESET);

		  	  }
}

void Fan_1 (uint8_t FANCtrl1)
{
	if(FANCtrl1){
	//
		  	  		HAL_GPIO_WritePin(Fan1Ctrl_GPIO_Port, Fan1Ctrl_Pin, GPIO_PIN_SET);
	//
		  	  	  } else {

		  	  		HAL_GPIO_WritePin(Fan1Ctrl_GPIO_Port, Fan1Ctrl_Pin, GPIO_PIN_RESET);

		  	  	  }
}

void Fan_2 (uint8_t FANCtrl2)
{
	if(FAN_CTRL2){

		  	  		HAL_GPIO_WritePin(Fan2Ctrl_GPIO_Port, Fan2Ctrl_Pin, GPIO_PIN_SET);

		  	  	  } else {

		  	  			  		HAL_GPIO_WritePin(Fan2Ctrl_GPIO_Port, Fan2Ctrl_Pin, GPIO_PIN_RESET);

		  	  	  }
}
void Fan_3 (uint8_t FANCtrl3)
{
	if(FAN_CTRL3){

		  	  		HAL_GPIO_WritePin(Fan3Ctrl_GPIO_Port, Fan3Ctrl_Pin, GPIO_PIN_SET);

		  	  	  } else {

		  	  			  		HAL_GPIO_WritePin(Fan3Ctrl_GPIO_Port, Fan3Ctrl_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(Fan5Ctrl_GPIO_Port, Fan5Ctrl_Pin, GPIO_PIN_RESET);
		  	  	  }
}
void Fan_4 (uint8_t FANCtrl4)
{
	if(FAN_CTRL4){
		  	  		  HAL_GPIO_WritePin(Fan4Ctrl_GPIO_Port, Fan4Ctrl_Pin, GPIO_PIN_SET);

		  	  	  } else {
		  	  		  HAL_GPIO_WritePin(Fan4Ctrl_GPIO_Port, Fan4Ctrl_Pin, GPIO_PIN_RESET);

		  	  	  }
}
void Fan_5 (uint8_t FANCtrl5)
{
	if(FAN_CTRL5){

		  	  		HAL_GPIO_WritePin(Fan5Ctrl_GPIO_Port, Fan5Ctrl_Pin, GPIO_PIN_SET);
		  	  	  } else {

		  	  			  		HAL_GPIO_WritePin(Fan5Ctrl_GPIO_Port, Fan5Ctrl_Pin, GPIO_PIN_RESET);
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
