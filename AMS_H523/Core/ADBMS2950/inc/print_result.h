/**
********************************************************************************
*
* @file:    print_result.h
*
* @brief:   This file contains the print result.
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
/*! \addtogroup Main
*  @{
*/

/*! \addtogroup Print_Result
*  @{
*/

#ifndef __RESULT_H
#define __RESULT_H

#include "adbms2950.h"

void ad29printWriteConfig(uint8_t tIC, cell_asic_29 *IC, TYPE type, GRP grp);
void ad29printReadConfig(uint8_t tIC, cell_asic_29 *IC, TYPE type, GRP grp);
void ad29printDeviceSID(uint8_t tIC, cell_asic_29 *IC, TYPE type);
void ad29printWriteCommData(uint8_t tIC, cell_asic_29 *IC, TYPE type);
void ad29printReadCommData(uint8_t tIC, cell_asic_29 *IC, TYPE type);
void ad29printCr(uint8_t tIC, cell_asic_29 *IC);
void ad29printVoltages(uint8_t tIC, cell_asic_29 *IC, TYPE type);
void ad29printVbat(uint8_t tIC, cell_asic_29 *IC);
void ad29printIvbat(uint8_t tIC, cell_asic_29 *IC);
void ad29printAccVbat(uint8_t tIC, cell_asic_29 *IC);
void ad29printAccIVbat(uint8_t tIC, cell_asic_29 *IC);
void ad29printAccCr(uint8_t tIC, cell_asic_29 *IC);
void ad29printOc(uint8_t tIC, cell_asic_29 *IC);
void ad29printRdallv(uint8_t tIC, cell_asic_29 *IC);
void ad29printRdallr(uint8_t tIC, cell_asic_29 *IC);
void ad29printRdallx(uint8_t tIC, cell_asic_29 *IC);
void ad29printGpV1(uint8_t tIC, cell_asic_29 *IC);
void ad29printStatus(uint8_t tIC, cell_asic_29 *IC, TYPE type, GRP grp);
void ad29printFlag(uint8_t tIC, cell_asic_29 *IC, TYPE type);
void ad29printAux(uint8_t tIC, cell_asic_29 *IC, TYPE type, GRP grp);
void ad29printMenu(void);
void ad29printMsg(char *msg);
void ad29printPollAdcConvTime(int count);
void ad29printResultCount(int count);
void ad29readUserInupt(int *user_command);
float ad29getVoltage(int data);
float getCurrent(uint32_t data);
float getAccCurrent(uint32_t data);
float getAccVbat(uint32_t data);
float getOverCurrent(uint8_t data);

#endif /* __RESULT_H */
/** @}*/
/** @}*/
