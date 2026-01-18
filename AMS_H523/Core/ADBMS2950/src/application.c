/**
********************************************************************************
*
* @file:    application.c
*
* @brief:   This file contains the application test cases.
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

/*! \addtogroup Application
*  @{
*/
/*============= I N C L U D E S =============*/
/*============== D E F I N E S ===============*/
/*============= E X T E R N A L S ============*/
/*============= E N U M E R A T O R S ============*/

#include <adi_2950.h>
#include <pal.h>
#include <print_result.h>
#include "adbms2950.h"

#ifdef MBED
extern Serial pc;
#endif /* MBED */
/**
*******************************************************************************
* @brief Setup Variables
* The following variables can be modified to configure the software.
*******************************************************************************
*/

#define TOTAL_IC_2950 1
cell_asic_29 IC2950[TOTAL_IC_2950];
int loop_measurment_count = 10;      /* Loop measurment count (default count)*/
int loop_measurment_time = 1;        /* milliseconds(mS)*/
//int loop_count = 0;





void init_contCurrentConv(void)
{
	adi2950_init_config(TOTAL_IC_2950, &IC2950[0]);
	adi2950_soft_reset(TOTAL_IC_2950, &IC2950[0]);

	adi2950_start_adi1_single_measurment(TOTAL_IC_2950, &IC2950[0]);
//	HAL_Delay(8);
}
void readI (void)
{
	adi2950_read_cr_vbat_ivbat_registers(TOTAL_IC_2950, &IC2950[0]);

}
/** @}*/
/** @}*/
