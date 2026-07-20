/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fdcan.c
  * @brief   This file provides code for the configuration
  *          of the FDCAN instances.
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
#include "fdcan.h"

/* USER CODE BEGIN 0 */
CanTxMsg canSeg1, canSeg2, canSeg3, canSeg4, canSeg5, canAccuStat, canStat, canChargeStat;

SEG_BSTAT *segstat_list[] = {
		&SEG1_B,
		&SEG2_B,
		&SEG3_B,
		&SEG4_B,
		&SEG5_B
};

ChargerData_t ChargerRxData;

FDCAN_FilterTypeDef Chrgr_Filter_All;

uint8_t ChargerTxData[8];

 FDCAN_TxHeaderTypeDef TxHeader1;
 FDCAN_RxHeaderTypeDef RxHeader1;

 int a,psr;


uint16_t TSCurrentCAN;



uint8_t ChargerRxDataA[8] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};
/* USER CODE END 0 */

FDCAN_HandleTypeDef hfdcan1;
FDCAN_HandleTypeDef hfdcan2;

/* FDCAN1 init function */
void MX_FDCAN1_Init(void)
{

  /* USER CODE BEGIN FDCAN1_Init 0 */

  /* USER CODE END FDCAN1_Init 0 */

  /* USER CODE BEGIN FDCAN1_Init 1 */

  /* USER CODE END FDCAN1_Init 1 */
  hfdcan1.Instance = FDCAN1;
  hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
  hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan1.Init.AutoRetransmission = DISABLE;
  hfdcan1.Init.TransmitPause = DISABLE;
  hfdcan1.Init.ProtocolException = DISABLE;
  hfdcan1.Init.NominalPrescaler = 16;
  hfdcan1.Init.NominalSyncJumpWidth = 4;
  hfdcan1.Init.NominalTimeSeg1 = 13;
  hfdcan1.Init.NominalTimeSeg2 = 6;
  hfdcan1.Init.DataPrescaler = 16;
  hfdcan1.Init.DataSyncJumpWidth = 1;
  hfdcan1.Init.DataTimeSeg1 = 13;
  hfdcan1.Init.DataTimeSeg2 = 6;
  hfdcan1.Init.StdFiltersNbr = 0;
  hfdcan1.Init.ExtFiltersNbr = 1;
  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN1_Init 2 */

  /* USER CODE END FDCAN1_Init 2 */

}
/* FDCAN2 init function */
void MX_FDCAN2_Init(void)
{

  /* USER CODE BEGIN FDCAN2_Init 0 */

  /* USER CODE END FDCAN2_Init 0 */

  /* USER CODE BEGIN FDCAN2_Init 1 */

  /* USER CODE END FDCAN2_Init 1 */
  hfdcan2.Instance = FDCAN2;
  hfdcan2.Init.ClockDivider = FDCAN_CLOCK_DIV1;
  hfdcan2.Init.FrameFormat = FDCAN_FRAME_FD_BRS;
  hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan2.Init.AutoRetransmission = DISABLE;
  hfdcan2.Init.TransmitPause = DISABLE;
  hfdcan2.Init.ProtocolException = DISABLE;
  hfdcan2.Init.NominalPrescaler = 1;
  hfdcan2.Init.NominalSyncJumpWidth = 21;
  hfdcan2.Init.NominalTimeSeg1 = 138;
  hfdcan2.Init.NominalTimeSeg2 = 21;
  hfdcan2.Init.DataPrescaler = 1;
  hfdcan2.Init.DataSyncJumpWidth = 9;
  hfdcan2.Init.DataTimeSeg1 = 10;
  hfdcan2.Init.DataTimeSeg2 = 9;
  hfdcan2.Init.StdFiltersNbr = 0;
  hfdcan2.Init.ExtFiltersNbr = 0;
  hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  if (HAL_FDCAN_Init(&hfdcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN2_Init 2 */

  /* USER CODE END FDCAN2_Init 2 */

}

static uint32_t HAL_RCC_FDCAN_CLK_ENABLED=0;

void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef* fdcanHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(fdcanHandle->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspInit 0 */

  /* USER CODE END FDCAN1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
    PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL1Q;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* FDCAN1 clock enable */
    HAL_RCC_FDCAN_CLK_ENABLED++;
    if(HAL_RCC_FDCAN_CLK_ENABLED==1){
      __HAL_RCC_FDCAN_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**FDCAN1 GPIO Configuration
    PB7     ------> FDCAN1_TX
    PB8     ------> FDCAN1_RX
    */
    GPIO_InitStruct.Pin = FDCAN_TX_CHG_Pin|FDCAN_RX_CHG_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* FDCAN1 interrupt Init */
    HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
    HAL_NVIC_SetPriority(FDCAN1_IT1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(FDCAN1_IT1_IRQn);
  /* USER CODE BEGIN FDCAN1_MspInit 1 */

  /* USER CODE END FDCAN1_MspInit 1 */
  }
  else if(fdcanHandle->Instance==FDCAN2)
  {
  /* USER CODE BEGIN FDCAN2_MspInit 0 */

  /* USER CODE END FDCAN2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
    PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL1Q;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* FDCAN2 clock enable */
    HAL_RCC_FDCAN_CLK_ENABLED++;
    if(HAL_RCC_FDCAN_CLK_ENABLED==1){
      __HAL_RCC_FDCAN_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**FDCAN2 GPIO Configuration
    PB12     ------> FDCAN2_RX
    PB13     ------> FDCAN2_TX
    */
    GPIO_InitStruct.Pin = FDCAN_RX_DAQ_Pin|FDCAN_TX_DAQ_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN FDCAN2_MspInit 1 */

  /* USER CODE END FDCAN2_MspInit 1 */
  }
}

void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef* fdcanHandle)
{

  if(fdcanHandle->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspDeInit 0 */

  /* USER CODE END FDCAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_FDCAN_CLK_ENABLED--;
    if(HAL_RCC_FDCAN_CLK_ENABLED==0){
      __HAL_RCC_FDCAN_CLK_DISABLE();
    }

    /**FDCAN1 GPIO Configuration
    PB7     ------> FDCAN1_TX
    PB8     ------> FDCAN1_RX
    */
    HAL_GPIO_DeInit(GPIOB, FDCAN_TX_CHG_Pin|FDCAN_RX_CHG_Pin);

    /* FDCAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
    HAL_NVIC_DisableIRQ(FDCAN1_IT1_IRQn);
  /* USER CODE BEGIN FDCAN1_MspDeInit 1 */

  /* USER CODE END FDCAN1_MspDeInit 1 */
  }
  else if(fdcanHandle->Instance==FDCAN2)
  {
  /* USER CODE BEGIN FDCAN2_MspDeInit 0 */

  /* USER CODE END FDCAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_FDCAN_CLK_ENABLED--;
    if(HAL_RCC_FDCAN_CLK_ENABLED==0){
      __HAL_RCC_FDCAN_CLK_DISABLE();
    }

    /**FDCAN2 GPIO Configuration
    PB12     ------> FDCAN2_RX
    PB13     ------> FDCAN2_TX
    */
    HAL_GPIO_DeInit(GPIOB, FDCAN_RX_DAQ_Pin|FDCAN_TX_DAQ_Pin);

  /* USER CODE BEGIN FDCAN2_MspDeInit 1 */

  /* USER CODE END FDCAN2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void canFraming(void)
{
	canStat.datas[0] = (uint8_t) round(MCUTemperature*4); // need to be verified
//	canStat.datas[1] = ERR_CODES;
	canStat.datas[1] = 0x1;
	for (int i=0; i<=11; i++)
	{
		canSeg1.datas[i] = (uint8_t) round((SEG1.CELL_V[i])*50) ;
//		canSeg1.datas[i] = (uint8_t) i++ ;
		canSeg1.datas[i+12] = (uint8_t) round((SEG1.CELL_T[i])*4) ;
	}




	for (int i=0; i<=11; i++)
	{
		canSeg2.datas[i] = (uint8_t) round((SEG2.CELL_V[i])*50) ;
		canSeg2.datas[i+12] = (uint8_t) round((SEG2.CELL_T[i])*4) ;
	}


	for (int i=0; i<=11; i++)
	{
		canSeg3.datas[i] = (uint8_t) round((SEG3.CELL_V[i])*50) ;
		canSeg3.datas[i+12] = (uint8_t) round((SEG3.CELL_T[i])*4) ;
	}


	for (int i=0; i<=11; i++)
	{
		canSeg4.datas[i] = (uint8_t) round((SEG4.CELL_V[i])*50) ;
		canSeg4.datas[i+12] = (uint8_t) round((SEG4.CELL_T[i])*4) ;
	}



	for (int i=0; i<=11; i++)
	{
		canSeg5.datas[i] = (uint8_t) round((SEG5.CELL_V[i])*50) ;
		canSeg5.datas[i+12] = (uint8_t) round((SEG5.CELL_T[i])*4) ;
	}

	//int j = 0;

	for (int j=0; j<9; j=j+2)
	{
		SEG_BSTAT *st = segstat_list[j/2];
		canAccuStat.datas[j] = st->M1to8 ;
		canAccuStat.datas[j+1] = st->M9to12 ;
	}

	TSCurrentCAN = (uint16_t) round((TS_Current)*100);
	canAccuStat.datas[10] = TSCurrentCAN & 0xFF;
	canAccuStat.datas[11] = TSCurrentCAN >> 8;
	canAccuStat.datas[12] = (uint8_t) round((AMS_SOC)*2); // SOC need to be calculated
	canAccuStat.datas[13] = AMS_SAFE;
	canAccuStat.datas[14] = (uint8_t) round((SEG1.IC_T)*4);
	canAccuStat.datas[15] = (uint8_t) round((SEG2.IC_T)*4);
	canAccuStat.datas[16] = (uint8_t) round((SEG3.IC_T)*4);
	canAccuStat.datas[17] = (uint8_t) round((SEG4.IC_T)*4);
	canAccuStat.datas[18] = (uint8_t) round((SEG5.IC_T)*4);
	canAccuStat.datas[19] = 0x00;

	canChargeStat.datas[0] = ((uint16_t) round((AMS_Charg_V)*100)) & 0xFF;
	canChargeStat.datas[1] = ((uint16_t) round((AMS_Charg_V)*100))  >> 8;
	canChargeStat.datas[2] = ((uint16_t) round((AMS_Charg_I)*100)) & 0xFF;
	canChargeStat.datas[3] = ((uint16_t) round((AMS_Charg_I)*100))  >> 8;




}

void CAN_Charger_Init (void)
{


	Chrgr_Filter_All.IdType=FDCAN_EXTENDED_ID;
	Chrgr_Filter_All.FilterIndex=0;
	Chrgr_Filter_All.FilterType=FDCAN_FILTER_MASK;
	Chrgr_Filter_All.FilterConfig=FDCAN_FILTER_TO_RXFIFO0;
	Chrgr_Filter_All.FilterID1=0x18FF50E5;
	Chrgr_Filter_All.FilterID2=0x1FFFFFFF;

	HAL_FDCAN_ConfigFilter(&hfdcan1,&Chrgr_Filter_All);

	HAL_FDCAN_ConfigGlobalFilter(&hfdcan1,
	                                 FDCAN_REJECT,
	                                 FDCAN_REJECT,
	                                 FDCAN_REJECT_REMOTE,
	                                 FDCAN_REJECT_REMOTE);

	  TxHeader1.Identifier          = 0x1806E5F4;
	  TxHeader1.IdType              = FDCAN_EXTENDED_ID;
	  TxHeader1.TxFrameType         = FDCAN_DATA_FRAME;
	  TxHeader1.DataLength          = FDCAN_DLC_BYTES_8;
	  TxHeader1.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	  TxHeader1.BitRateSwitch       = FDCAN_BRS_OFF;
	  TxHeader1.FDFormat            = FDCAN_CLASSIC_CAN;
	  TxHeader1.TxEventFifoControl  = FDCAN_NO_TX_EVENTS;
	  TxHeader1.MessageMarker       = 0;


//	  HAL_FDCAN_ActivateNotification(&hfdcan1,FDCAN_IT_TX_FIFO_EMPTY,513);
	  HAL_FDCAN_ActivateNotification(&hfdcan1,FDCAN_IT_RX_FIFO0_NEW_MESSAGE,0);

	  HAL_FDCAN_Start(&hfdcan1);
}

void CAN_Charger_transmit(void)
{
	ChargerTxData[0] = (AMS_Charg_V >> 8) & 0xFF;   // Voltage High
	ChargerTxData[1] = AMS_Charg_V & 0xFF;          // Voltage Low

	ChargerTxData[2] = (AMS_Charg_I >> 8) & 0xFF;   // Current High
	ChargerTxData[3] = AMS_Charg_I & 0xFF;          // Current Low

	ChargerTxData[4] = 0x00;   // 0 = Start Charging
	// TxData[4] = 0x01;   // Stop Charging

	ChargerTxData[5] = 0x00;
	ChargerTxData[6] = 0x00;
	ChargerTxData[7] = 0x00;

	if (HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1) > 0)
	{
		if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader1,  ChargerTxData) != HAL_OK)
		{
			Error_Handler();
		}

	}
}

void CAN_Data_Init (void)
{
//	if(HAL_FDCAN_Start(&hfdcan1)!= HAL_OK) {
//		Error_Handler();
//	}



	canSeg1.header.Identifier = 0x0E1;
	canSeg1.header.IdType = FDCAN_STANDARD_ID;
	canSeg1.header.TxFrameType = FDCAN_DATA_FRAME;
	canSeg1.header.DataLength = FDCAN_DLC_BYTES_24;
//	canSeg1.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	canSeg1.header.BitRateSwitch = FDCAN_BRS_ON;
	canSeg1.header.FDFormat = FDCAN_FD_CAN;


//	canSeg1.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
//	canSeg1.header.MessageMarker = 0;

	canSeg2.header.Identifier = 0x0E2;
	canSeg2.header.IdType = FDCAN_STANDARD_ID;
	canSeg2.header.TxFrameType = FDCAN_DATA_FRAME;
	canSeg2.header.DataLength = FDCAN_DLC_BYTES_24;
//	canSeg2.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	canSeg2.header.BitRateSwitch = FDCAN_BRS_OFF;
	canSeg2.header.FDFormat = FDCAN_FD_CAN;
//	canSeg2.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
//	canSeg2.header.MessageMarker = 0;

	canSeg3.header.Identifier = 0x0E3;
	canSeg3.header.IdType = FDCAN_STANDARD_ID;
	canSeg3.header.TxFrameType = FDCAN_DATA_FRAME;
	canSeg3.header.DataLength = FDCAN_DLC_BYTES_24;
//	canSeg3.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	canSeg3.header.BitRateSwitch = FDCAN_BRS_OFF;
	canSeg3.header.FDFormat = FDCAN_FD_CAN;
//	canSeg3.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
//	canSeg3.header.MessageMarker = 0;

	canSeg4.header.Identifier = 0x0E4;
	canSeg4.header.IdType = FDCAN_STANDARD_ID;
	canSeg4.header.TxFrameType = FDCAN_DATA_FRAME;
	canSeg4.header.DataLength = FDCAN_DLC_BYTES_24;
//	canSeg4.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	canSeg4.header.BitRateSwitch = FDCAN_BRS_OFF;
	canSeg4.header.FDFormat = FDCAN_FD_CAN;
//	canSeg4.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
//	canSeg4.header.MessageMarker = 0;

	canSeg5.header.Identifier = 0x0E5;
	canSeg5.header.IdType = FDCAN_STANDARD_ID;
	canSeg5.header.TxFrameType = FDCAN_DATA_FRAME;
	canSeg5.header.DataLength = FDCAN_DLC_BYTES_24;
//	canSeg5.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	canSeg5.header.BitRateSwitch = FDCAN_BRS_OFF;
	canSeg5.header.FDFormat = FDCAN_FD_CAN;
//	canSeg5.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
//	canSeg5.header.MessageMarker = 0;

	canAccuStat.header.Identifier = 0x0F0;
	canAccuStat.header.IdType = FDCAN_STANDARD_ID;
	canAccuStat.header.TxFrameType = FDCAN_DATA_FRAME;
	canAccuStat.header.DataLength = FDCAN_DLC_BYTES_24;
//	canAccuStat.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	canAccuStat.header.BitRateSwitch = FDCAN_BRS_OFF;
	canAccuStat.header.FDFormat = FDCAN_FD_CAN;
//	canAccuStat.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
//	canAccuStat.header.MessageMarker = 0;

	canStat.header.Identifier = 0x0FA;
	canStat.header.IdType = FDCAN_STANDARD_ID;
	canStat.header.TxFrameType = FDCAN_DATA_FRAME;
	canStat.header.DataLength = FDCAN_DLC_BYTES_24;
//	canStat.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	canStat.header.BitRateSwitch = FDCAN_BRS_OFF;
	canStat.header.FDFormat = FDCAN_FD_CAN;
//	canStat.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
//	canStat.header.MessageMarker = 0;

	canChargeStat.header.Identifier = 0x0F7;
	canChargeStat.header.IdType = FDCAN_STANDARD_ID;
	canChargeStat.header.TxFrameType = FDCAN_DATA_FRAME;
	canChargeStat.header.DataLength = FDCAN_DLC_BYTES_24;
//	canChargeStat.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	canChargeStat.header.BitRateSwitch = FDCAN_BRS_OFF;
	canChargeStat.header.FDFormat = FDCAN_FD_CAN;
//	canChargeStat.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
//	canChargeStat.header.MessageMarker = 0;
	if(HAL_FDCAN_ConfigTxDelayCompensation(&hfdcan2, 5, 0)!= HAL_OK) {

			Error_Handler();

		}


		if(HAL_FDCAN_EnableTxDelayCompensation(&hfdcan2)!= HAL_OK) {

			Error_Handler();

		}

	if(HAL_FDCAN_Start(&hfdcan2)!= HAL_OK) {
				Error_Handler();
			}



}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan,
                               uint32_t RxFifo0ITs)
{
    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != 0)
    {
        if (HAL_FDCAN_GetRxMessage(hfdcan,
                                   FDCAN_RX_FIFO0,
                                   &RxHeader1,
                                   ChargerRxDataA) != HAL_OK)
        {
            Error_Handler();
        }

        // Check that the received message is from the charger
        if (RxHeader1.Identifier == 0x18FF50E5)
        {
        	Parse_Charger_Message(ChargerRxDataA);
        	// RxData[0] to RxData[7] now contain the received bytes
        }
    }
}

void Parse_Charger_Message(uint8_t *Rx)
{
    uint16_t voltage;
    uint16_t current;

    voltage = ((uint16_t)Rx[0] << 8) | Rx[1];
    current = ((uint16_t)Rx[2] << 8) | Rx[3];

    ChargerRxData.Voltage = voltage * 0.1f;

    ChargerRxData.Charging = !(Rx[2] & 0x80);

    current &= 0x7FFF;
    ChargerRxData.Current = current * 0.1f;

    ChargerRxData.Status = Rx[4];

    ChargerRxData.Temperature = Rx[5];
}

void CAN_DataTX_1s (void)
{

	if (HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan2) > 0)
	  {
			if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &canSeg1.header, canSeg1.datas)!= HAL_OK)
			 {
			  Error_Handler();
			 }
	  }



	}
/* USER CODE END 1 */
