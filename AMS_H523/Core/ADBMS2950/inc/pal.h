/**
********************************************************************************
*
* @file:    pal.h
*
* @brief:   This file contains the pal header files & functions.
*
* @details:
*
*******************************************************************************
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved. This software is
proprietary & confidential to Analog Devices, Inc. and its licensors. By using
this software you agree to the terms of the associated Analog Devices License
Agreement.
*******************************************************************************
*/

/*! \addtogroup Platform_Abstracion_Layer
*  @{
*/

#ifndef __PAL_H
#define __PAL_H

/*============= I N C L U D E S =============*/
/*============== D E F I N E S ===============*/
/*============= E X T E R N A L S ============*/
/*============= E N U M E R A T O R S ============*/

#include "common.h"

#ifdef MBED

#else   /* not MBED */

#include <application.h>
#include "stm32h5xx_hal.h"
#include "stm32h5xx_hal_tim.h"
#include "stm32h5xx_it.h"
// #include "adbms_main.h"
#include "stm32h5xx_hal_gpio.h"

#endif 	/* MBED */

void ad29Delay_ms(uint32_t delay);
void ad29Delay_us(uint32_t us);
void ad29BmsCsLow(void);
void ad29BmsCsHigh(void);
void ad29BmsWakeupIc(uint8_t total_ic);
void ad29spiWriteBytes(uint8_t *tx_data, uint16_t size);
void ad29spiWriteReadBytes(uint8_t *tx_data, uint8_t *rx_data, uint16_t size);
void ad29spiReadBytes(uint8_t *rx_data, uint16_t size);
void ad29BmsRawWriteRead(uint8_t total_ic, uint8_t *tx_data, uint8_t *rx_data, uint8_t size);
void ad29startTimer();
void ad29stopTimer();
uint32_t ad29getTimCount();
void GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState); //Taken from mcuFunctions.h
void ad29spiTransmit(SPI_HandleTypeDef *hspi,uint8_t *tx_data, uint16_t size,GPIO_TypeDef* CS_GPIO_PORT, uint16_t CS_GPIO_Pin); //Taken from mcuFunctions.h
void ad29spiTransmitReceive(SPI_HandleTypeDef *hspi,uint8_t *tx_data, uint8_t *rx_data ,uint16_t size,GPIO_TypeDef* CS_GPIO_PORT, uint16_t CS_GPIO_Pin); //Taken from mcuFunctions.h
void ad29spiReceive(SPI_HandleTypeDef *hspi,uint8_t *rx_data, uint16_t size,GPIO_TypeDef* CS_GPIO_PORT, uint16_t CS_GPIO_Pin); //Taken from mcuFunctions.h

#endif /*__PAL_H */

/** @}*/
