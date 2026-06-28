/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Fan3Ctrl_Pin GPIO_PIN_13
#define Fan3Ctrl_GPIO_Port GPIOC
#define Fan5Ctrl_Pin GPIO_PIN_14
#define Fan5Ctrl_GPIO_Port GPIOC
#define Fan4Ctrl_Pin GPIO_PIN_15
#define Fan4Ctrl_GPIO_Port GPIOC
#define Fan1Ctrl_Pin GPIO_PIN_0
#define Fan1Ctrl_GPIO_Port GPIOH
#define Fan2Ctrl_Pin GPIO_PIN_1
#define Fan2Ctrl_GPIO_Port GPIOH
#define RDY1_Pin GPIO_PIN_0
#define RDY1_GPIO_Port GPIOA
#define INTR1_Pin GPIO_PIN_1
#define INTR1_GPIO_Port GPIOA
#define INTR2_Pin GPIO_PIN_2
#define INTR2_GPIO_Port GPIOA
#define RDY2_Pin GPIO_PIN_3
#define RDY2_GPIO_Port GPIOA
#define CS1_Pin GPIO_PIN_4
#define CS1_GPIO_Port GPIOA
#define SCK1_Pin GPIO_PIN_5
#define SCK1_GPIO_Port GPIOA
#define MISO1_Pin GPIO_PIN_6
#define MISO1_GPIO_Port GPIOA
#define MOSI1_Pin GPIO_PIN_7
#define MOSI1_GPIO_Port GPIOA
#define MISO2_Pin GPIO_PIN_0
#define MISO2_GPIO_Port GPIOB
#define SCK2_Pin GPIO_PIN_1
#define SCK2_GPIO_Port GPIOB
#define MOSI2_Pin GPIO_PIN_2
#define MOSI2_GPIO_Port GPIOB
#define CS2_Pin GPIO_PIN_10
#define CS2_GPIO_Port GPIOB
#define FDCAN_RX_DAQ_Pin GPIO_PIN_12
#define FDCAN_RX_DAQ_GPIO_Port GPIOB
#define FDCAN_TX_DAQ_Pin GPIO_PIN_13
#define FDCAN_TX_DAQ_GPIO_Port GPIOB
#define CAN_EN_DAQ_Pin GPIO_PIN_14
#define CAN_EN_DAQ_GPIO_Port GPIOB
#define monStat_Pin GPIO_PIN_15
#define monStat_GPIO_Port GPIOB
#define balStat_Pin GPIO_PIN_8
#define balStat_GPIO_Port GPIOA
#define chgStat_Pin GPIO_PIN_9
#define chgStat_GPIO_Port GPIOA
#define AMS_Fault_Pin GPIO_PIN_10
#define AMS_Fault_GPIO_Port GPIOA
#define CAN_EN_CHG_Pin GPIO_PIN_6
#define CAN_EN_CHG_GPIO_Port GPIOB
#define FDCAN_TX_CHG_Pin GPIO_PIN_7
#define FDCAN_TX_CHG_GPIO_Port GPIOB
#define FDCAN_RX_CHG_Pin GPIO_PIN_8
#define FDCAN_RX_CHG_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#ifndef SEGM_H
#define SEGM_H
typedef struct {
	float IC_T;
	float CELL_V[12] ;
	float CELL_T[12];
	float SOC_OCV[12];
	float SOC_CC[12];
	float SOC [12];
	float DCIR[12];
	uint16_t BAL_STAT;
} SEG_PARAMS;

extern SEG_PARAMS SEG1, SEG2, SEG3, SEG4, SEG5;

#endif

#ifndef SEGB_H
#define SEGB_H

typedef struct {
	uint8_t M1to8;
	uint8_t M9to12;
} SEG_BSTAT;

extern SEG_BSTAT SEG1_B, SEG2_B, SEG3_B, SEG4_B, SEG5_B;

extern float TS_Current;
extern float AMS_SOC;
extern uint8_t AMS_SAFE;
extern uint8_t ERR_CODES;
extern float AMS_Charg_I;
extern float AMS_Charg_V;
extern uint8_t SDC_FLAG ;
extern uint8_t SDC_V_CHECK ;
extern uint8_t SDC_Temp_CHECK;
extern uint8_t FAN_CTRL;
//extern uint8_t MCU_junction_temp;
extern float tV;
extern uint8_t UpdateEve_MCUtemp;
extern uint16_t ADC_RES[2];
extern float MCUTemperature, V_Sense, V_Ref;
extern uint8_t balancingState ;
void getMCUTemp(void);

#endif


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
