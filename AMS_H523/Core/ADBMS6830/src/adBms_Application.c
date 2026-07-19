/*******************************************************************************
Copyright (c) 2020 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensor.
******************************************************************************
* @file:    adbms_Application.c
* @brief:   adbms application test cases
* @version: $Revision$
* @date:    $Date$
* Developed by: ADIBMS Software team, Bangalore, India
*****************************************************************************/
/*! \addtogroup APPLICATION
*  @{
*/

/*! @addtogroup Application
*  @{
*/
#include "adBms_Application.h"

#include "common.h"

#include "adBms6830CmdList.h"
#include "mcuWrapper.h"
#include "serialPrintResult.h"
#include "adBms6830CmdList.h"
#include "adBms6830GenericType.h"
#include "stddef.h"
#include "math.h"
#ifdef MBED
extern Serial pc;
#endif
/**
*******************************************************************************
* @brief Setup Variables
* The following variables can be modified to configure the software.
*******************************************************************************
*/
float tV;
#define SEG_NUM 5
#define CELL_NUM 12
#define BALANCE_THRESH 0.1

#define TOTAL_IC 5

cell_asic IC[TOTAL_IC];

SEG_PARAMS *seg_paramst_list[] = {

		&SEG1,
		&SEG2,
		&SEG3,
		&SEG4,
		&SEG5
};



/* ADC Command Configurations */
RD      REDUNDANT_MEASUREMENT           = RD_ON;
CH      AUX_CH_TO_CONVERT               = GPIO10;
CONT    CONTINUOUS_MEASUREMENT          = SINGLE; //changed from single
OW_C_S  CELL_OPEN_WIRE_DETECTION        = OW_OFF_ALL_CH; // changed from off
OW_AUX  AUX_OPEN_WIRE_DETECTION         = AUX_OW_OFF;
PUP     OPEN_WIRE_CURRENT_SOURCE        = PUP_DOWN;
DCP     DISCHARGE_PERMITTED             = DCP_OFF;
RSTF    RESET_FILTER                    = RSTF_OFF;
ERR     INJECT_ERR_SPI_READ             = WITHOUT_ERR;

/* Set Under Voltage and Over Voltage Thresholds */
const float OV_THRESHOLD = 4.2;                 /* Volt */
const float UV_THRESHOLD = 2.9;                 /* Volt */
const int OWC_Threshold = 2000;                 /* Cell Open wire threshold(mili volt) */
const int OWA_Threshold = 50000;                /* Aux Open wire threshold(mili volt) */
const uint32_t LOOP_MEASUREMENT_COUNT = 1;      /* Loop measurment count */
const uint16_t MEASUREMENT_LOOP_TIME  = 10;     /* milliseconds(mS)*/
uint32_t loop_count = 0;
uint32_t pladc_count;
uint8_t val;
/*Loop Measurement Setup These Variables are ENABLED or DISABLED Remember ALL CAPS*/
LOOP_MEASURMENT MEASURE_CELL            = ENABLED;        /*   This is ENABLED or DISABLED       */
LOOP_MEASURMENT MEASURE_AVG_CELL        = ENABLED;        /*   This is ENABLED or DISABLED       */
LOOP_MEASURMENT MEASURE_F_CELL          = ENABLED;        /*   This is ENABLED or DISABLED       */
LOOP_MEASURMENT MEASURE_S_VOLTAGE       = ENABLED;        /*   This is ENABLED or DISABLED       */
LOOP_MEASURMENT MEASURE_AUX             = DISABLED;        /*   This is ENABLED or DISABLED       */
LOOP_MEASURMENT MEASURE_RAUX            = DISABLED;        /*   This is ENABLED or DISABLED       */
LOOP_MEASURMENT MEASURE_STAT            = DISABLED;        /*   This is ENABLED or DISABLED       */


//??????????????///

void adbms_init_loop(void)
{
	adBms6830_init_config(TOTAL_IC, &IC[0]);
}

void adbms_readCell_loop(void)
{
	adBms6830_read_cell_voltages(TOTAL_IC, &IC[0]);
}

void adbms_startCellConv_loop(void)
{
	adBms6830_Adcv(REDUNDANT_MEASUREMENT, CONTINUOUS, DISCHARGE_PERMITTED, RESET_FILTER, CELL_OPEN_WIRE_DETECTION);
}

void adbms_readTempToggle(void)
{
	adBms6830_setgpo_69(TOTAL_IC, &IC[0]);
}

void testOpenWire(void)
{
	printOpenWireTestResult(TOTAL_IC, &IC[0],Cell);
	HAL_Delay(1000);
	printOpenWireTestResult(TOTAL_IC, &IC[0],S_volt);
	HAL_Delay(1000);
	printOpenWireTestResult(TOTAL_IC, &IC[0],Aux);
	HAL_Delay(1000);
}

void adbmsReinit(uint8_t tIC, cell_asic *ic)
{
	for(uint8_t cic = 0; cic < tIC; cic++)
	{
		if ((ic[cic].cccrc.cmd_cntr == 0) | (ic[cic].cccrc.cmd_cntr == 0x3F) | (ic[cic].cccrc.stat_pec == 1))
		{
			//ic[cic].tx_cfga.refon = PWR_UP;
			//adBmsWakeupIc(tIC);
			//adBmsWriteData(tIC, &ic[0], WRCFGA, Config, A);
			adbms_init_loop();
			adbms_readCell_loop();
		}
	}

}

void adbmsReinitMain(void)
{
	adbmsReinit(TOTAL_IC, &IC[0]);
}
//?????????????///
/**
*******************************************************************************
* @brief Set configuration register A. Refer to the data sheet
*        Set configuration register B. Refer to the data sheet
*******************************************************************************
*/
void adBms6830_init_config(uint8_t tIC, cell_asic *ic)
{
  for(uint8_t cic = 0; cic < tIC; cic++)
  {
    /* Init config A */
    ic[cic].tx_cfga.refon = PWR_UP;
//    ic[cic].cfga.cth = CVT_8_1mV;
//    ic[cic].cfga.flag_d = ConfigA_Flag(FLAG_D0, FLAG_SET) | ConfigA_Flag(FLAG_D1, FLAG_SET);

    ic[cic].tx_cfga.gpo = 0X3FF; /* All GPIO pulled up  */
    //ic[cic].tx_cfga.soakon = SOAKON_CLR;
    ic[cic].tx_cfga.fc = IIR_FPA32;

    /* Init config B */

    ic[cic].tx_cfgb.vov = SetOverVoltageThreshold(OV_THRESHOLD);
    ic[cic].tx_cfgb.vuv = SetUnderVoltageThreshold(UV_THRESHOLD);
//    ic[cic].tx_cfgb.dtmen=DTMEN_OFF;
//    ic[cic].tx_cfgb.dcto=1;
//    ic[cic].PwmA.pwma[0]=PWM_100_0_PCT;

//    ic[cic].tx_cfgb.dcc = ConfigB_DccBit(DCC16, DCC_BIT_SET);
//    SetConfigB_DischargeTimeOutValue(tIC, &ic[cic], RANG_0_TO_63_MIN, TIME_1MIN_OR_0_26HR);
  }
  adBmsWakeupIc(tIC);
  adBmsWriteData(tIC, &ic[0], WRCFGA, Config, A);
  adBmsWriteData(tIC, &ic[0], WRCFGB, Config, B);
  adBms6830_Adcv(REDUNDANT_MEASUREMENT, CONTINUOUS, DISCHARGE_PERMITTED, RESET_FILTER, CELL_OPEN_WIRE_DETECTION);
  HAL_Delay(1);
//  adBmsWakeupIcTim(1);
}

/**
*******************************************************************************
* @brief Write and Read Configuration Register A/B
*******************************************************************************
*/


void adBms6830_write_read_config(uint8_t tIC, cell_asic *ic)
{
  adBmsWakeupIc(tIC);
  adBmsWriteData(tIC, &ic[0], WRCFGA, Config, A);
  adBmsWriteData(tIC, &ic[0], WRCFGB, Config, B);
  adBmsReadData(tIC, &ic[0], RDCFGA, Config, A);
  adBmsReadData(tIC, &ic[0], RDCFGB, Config, B);
  printWriteConfig(tIC, &ic[0], Config, ALL_GRP);
  printReadConfig(tIC, &ic[0], Config, ALL_GRP);
}

/**
*******************************************************************************
* @brief Write Configuration Register A/B
*******************************************************************************
*/
void adBms6830_write_config(uint8_t tIC, cell_asic *ic)
{
  adBmsWakeupIc(tIC);
  adBmsWriteData(tIC, &ic[0], WRCFGA, Config, A);
  adBmsWriteData(tIC, &ic[0], WRCFGB, Config, B);
  printWriteConfig(tIC, &ic[0], Config, ALL_GRP);
}

/**
*******************************************************************************
* @brief Read Configuration Register A/B
*******************************************************************************
*/
void adBms6830_read_config(uint8_t tIC, cell_asic *ic)
{
  adBmsWakeupIc(tIC);
  adBmsReadData(tIC, &ic[0], RDCFGA, Config, A);
  adBmsReadData(tIC, &ic[0], RDCFGB, Config, B);
  printReadConfig(tIC, &ic[0], Config, ALL_GRP);
}

/**
*******************************************************************************
* @brief Start ADC Cell Voltage Measurement
*******************************************************************************
*/
void adBms6830_start_adc_cell_voltage_measurment(uint8_t tIC)
{
  adBmsWakeupIc(tIC);
  adBms6830_Adcv(REDUNDANT_MEASUREMENT, CONTINUOUS_MEASUREMENT, DISCHARGE_PERMITTED, RESET_FILTER, CELL_OPEN_WIRE_DETECTION);
  pladc_count = adBmsPollAdc(PLADC);
  printf("Cell conversion completed\n");
  printPollAdcConvTime(pladc_count);
}

/**
*******************************************************************************
* @brief Read Cell Voltages
*******************************************************************************
*/
void adBms6830_read_cell_voltages(uint8_t tIC, cell_asic *ic)
{
  adBmsWakeupIc(tIC);
  adBmsReadData(tIC, &ic[0], RDCVA, Cell, A);
  adBmsReadData(tIC, &ic[0], RDCVB, Cell, B);
  adBmsReadData(tIC, &ic[0], RDCVC, Cell, C);
  adBmsReadData(tIC, &ic[0], RDCVD, Cell, D);
  adBmsReadData(tIC, &ic[0], RDCVE, Cell, E);
  adBmsReadData(tIC, &ic[0], RDCVF, Cell, F);
  printVoltages(tIC, &ic[0], Cell);
}

/**
*******************************************************************************
* @brief Start ADC S-Voltage Measurement
*******************************************************************************
*/
void adBms6830_start_adc_s_voltage_measurment(uint8_t tIC)
{
  adBmsWakeupIc(tIC);
  adBms6830_Adsv(CONTINUOUS_MEASUREMENT, DISCHARGE_PERMITTED, CELL_OPEN_WIRE_DETECTION);
  pladc_count = adBmsPollAdc(PLADC);
  printf("S-Voltage conversion completed\n");
  printPollAdcConvTime(pladc_count);
}

/**
*******************************************************************************
* @brief Read S-Voltages
*******************************************************************************
*/
void adBms6830_read_s_voltages(uint8_t tIC, cell_asic *ic)
{
  adBmsWakeupIc(tIC);
  adBmsReadData(tIC, &ic[0], RDSVA, S_volt, A);
  adBmsReadData(tIC, &ic[0], RDSVB, S_volt, B);
  adBmsReadData(tIC, &ic[0], RDSVC, S_volt, C);
  adBmsReadData(tIC, &ic[0], RDSVD, S_volt, D);
  adBmsReadData(tIC, &ic[0], RDSVE, S_volt, E);
  adBmsReadData(tIC, &ic[0], RDSVF, S_volt, F);
  printVoltages(tIC, &ic[0], S_volt);
}

/**
*******************************************************************************
* @brief Start Avarage Cell Voltage Measurement
*******************************************************************************
*/
void adBms6830_start_avgcell_voltage_measurment(uint8_t tIC)
{
  adBmsWakeupIc(tIC);
  adBms6830_Adcv(RD_ON, CONTINUOUS_MEASUREMENT, DISCHARGE_PERMITTED, RESET_FILTER, CELL_OPEN_WIRE_DETECTION);
  printPollAdcConvTime(pladc_count);
}

/**
*******************************************************************************
* @brief Read Avarage Cell Voltages
*******************************************************************************
*/
void adBms6830_read_avgcell_voltages(uint8_t tIC, cell_asic *ic)
{
  adBmsWakeupIc(tIC);
  adBmsReadData(tIC, &ic[0], RDACA, AvgCell, A);
  adBmsReadData(tIC, &ic[0], RDACB, AvgCell, B);
  adBmsReadData(tIC, &ic[0], RDACC, AvgCell, C);
  adBmsReadData(tIC, &ic[0], RDACD, AvgCell, D);
  adBmsReadData(tIC, &ic[0], RDACE, AvgCell, E);
  adBmsReadData(tIC, &ic[0], RDACF, AvgCell, F);
  printVoltages(tIC, &ic[0], AvgCell);
}

/**
*******************************************************************************
* @brief Start Filtered Cell Voltages Measurement
*******************************************************************************
*/


/**
*******************************************************************************
* @brief Read Filtered Cell Voltages
*******************************************************************************
*/
void adBms6830_read_fcell_voltages(uint8_t tIC, cell_asic *ic)
{
  adBmsWakeupIc(tIC);
  adBmsReadData(tIC, &ic[0], RDFCA, F_volt, A);
  adBmsReadData(tIC, &ic[0], RDFCB, F_volt, B);
  adBmsReadData(tIC, &ic[0], RDFCC, F_volt, C);
  adBmsReadData(tIC, &ic[0], RDFCD, F_volt, D);
  adBmsReadData(tIC, &ic[0], RDFCE, F_volt, E);
  adBmsReadData(tIC, &ic[0], RDFCF, F_volt, F);
  printVoltages(tIC, &ic[0], F_volt);
}

/**
*******************************************************************************
* @brief Start AUX, VMV, V+ Voltages Measurement
*******************************************************************************
*/
void adBms6830_start_aux_voltage_measurment(uint8_t tIC, cell_asic *ic)
{
  for(uint8_t cic = 0; cic < tIC; cic++)
  {
    /* Init config A */
    ic[cic].tx_cfga.refon = PWR_UP;
    ic[cic].tx_cfga.gpo = 0X3FF; /* All GPIO pull down off */
  }
  adBmsWakeupIc(tIC);
  adBmsWriteData(tIC, &ic[0], WRCFGA, Config, A);
  adBms6830_Adax(AUX_OPEN_WIRE_DETECTION, OPEN_WIRE_CURRENT_SOURCE, AUX_CH_TO_CONVERT);
  pladc_count = adBmsPollAdc(PLADC);
  printPollAdcConvTime(pladc_count);
}

/**
*******************************************************************************
* @brief Read AUX, VMV, V+ Voltages
*******************************************************************************
*/
void adBms6830_read_aux_voltages(uint8_t tIC, cell_asic *ic)
{
  adBmsWakeupIc(tIC);
  adBmsReadData(tIC, &ic[0], RDAUXA, Aux, A);
  adBmsReadData(tIC, &ic[0], RDAUXB, Aux, B);
  adBmsReadData(tIC, &ic[0], RDAUXC, Aux, C);
  adBmsReadData(tIC, &ic[0], RDAUXD, Aux, D);
  printVoltages(tIC, &ic[0], Aux);
}

/**
*******************************************************************************
* @brief Start Redundant GPIO Voltages Measurement
*******************************************************************************
*/
void adBms6830_start_raux_voltage_measurment(uint8_t tIC,  cell_asic *ic)
{
  for(uint8_t cic = 0; cic < tIC; cic++)
  {
    /* Init config A */
    ic[cic].tx_cfga.refon = PWR_UP;
    ic[cic].tx_cfga.gpo = 0X3FF; /* All GPIO pull down off */
  }
  adBmsWakeupIc(tIC);
  adBmsWriteData(tIC, &ic[0], WRCFGA, Config, A);
  adBms6830_Adax2(AUX_CH_TO_CONVERT);
  pladc_count = adBmsPollAdc(PLADC);
  printPollAdcConvTime(pladc_count);
}

/**
*******************************************************************************
* @brief Read Redundant GPIO Voltages
*******************************************************************************
*/
void adBms6830_read_raux_voltages(uint8_t tIC, cell_asic *ic)
{
  adBmsWakeupIc(tIC);
  adBmsReadData(tIC, &ic[0], RDRAXA, RAux, A);
  adBmsReadData(tIC, &ic[0], RDRAXB, RAux, B);
  adBmsReadData(tIC, &ic[0], RDRAXC, RAux, C);
  adBmsReadData(tIC, &ic[0], RDRAXD, RAux, D);
  printVoltages(tIC, &ic[0], RAux);
}

/**
*******************************************************************************
* @brief Read Status Reg. A, B, C, D and E.
*******************************************************************************
*/
void adBms6830_read_status_registers(uint8_t tIC, cell_asic *ic)
{
  adBmsWakeupIc(tIC);
  adBmsWriteData(tIC, &ic[0], WRCFGA, Config, A);
  adBmsWriteData(tIC, &ic[0], WRCFGB, Config, B);
  adBms6830_Adax(AUX_OPEN_WIRE_DETECTION, OPEN_WIRE_CURRENT_SOURCE, AUX_CH_TO_CONVERT);
  pladc_count = adBmsPollAdc(PLADC);
  adBms6830_Adcv(REDUNDANT_MEASUREMENT, CONTINUOUS_MEASUREMENT, DISCHARGE_PERMITTED, RESET_FILTER, CELL_OPEN_WIRE_DETECTION);
  pladc_count = pladc_count + adBmsPollAdc(PLADC);

  adBmsReadData(tIC, &ic[0], RDSTATA, Status, A);
  adBmsReadData(tIC, &ic[0], RDSTATB, Status, B);
  adBmsReadData(tIC, &ic[0], RDSTATC, Status, C);
  adBmsReadData(tIC, &ic[0], RDSTATD, Status, D);
  adBmsReadData(tIC, &ic[0], RDSTATE, Status, E);
  printPollAdcConvTime(pladc_count);
  printStatus(tIC, &ic[0], Status, ALL_GRP);
}

/**
**********************************************************************
**********************************************************************

/**
*******************************************************************************
* @brief Clear Cell measurement reg.
*******************************************************************************
*/
void adBms6830_clear_cell_measurement(uint8_t tIC)
{
  adBmsWakeupIc(tIC);
  spiSendCmd(CLRCELL);
}

/**
*******************************************************************************
* @brief Clear Aux measurement reg.
*******************************************************************************
*/
void adBms6830_clear_aux_measurement(uint8_t tIC)
{
  adBmsWakeupIc(tIC);
  spiSendCmd(CLRAUX);
}

/**
*******************************************************************************
* @brief Clear spin measurement reg.
*******************************************************************************
*/
void adBms6830_clear_spin_measurement(uint8_t tIC)
{
  adBmsWakeupIc(tIC);
  spiSendCmd(CLRSPIN);
}

/**
*******************************************************************************
* @brief Clear fcell measurement reg.
*******************************************************************************
*/
void adBms6830_clear_fcell_measurement(uint8_t tIC)
{
  adBmsWakeupIc(tIC);
  spiSendCmd(CLRFC);
}

/** @}*/
/** @}*/

//void adBms6830_togDischarge(cell_asic *ic,uint8_t cic, uint16_t dischCell, uint8_t dischEN)
//{
////	for(uint8_t cic = 0; cic < tIC; cic++)
////	  {
//		ic[cic].tx_cfgb.dtmen=DTMEN_ON;
//		ic[cic].tx_cfgb.dcc = ConfigB_DccBit(dischCell, dischEN);
////		SetConfigB_DischargeTimeOutValue(tIC, &ic[ic], RANG_0_TO_63_MIN, TIME_1MIN_OR_0_26HR);
////	  }
//}

void adBms6830_setgpo_69(uint8_t tIC, cell_asic *ic) {
		float icTV;
		int val;

		for (int i = 1; i <= tIC; i++) {
			 val=0;
			 SEG_PARAMS *st = seg_paramst_list[i];
		    for (uint8_t value = 0x0; value <= 0xB; value++) {
						ic[i].tx_cfga.refon = PWR_UP;
						ic[i].tx_cfga.gpo = (((reverse4bits(value) << 5) & 0x3FF) | 0x21F) ;
						adBmsWakeupIc(tIC);
						adBmsWriteData(tIC, &ic[i], WRCFGA, Config, A);
						adBmsWakeupIc(tIC);
						adBms6830_Adax(AUX_OPEN_WIRE_DETECTION, OPEN_WIRE_CURRENT_SOURCE, GPIO10);
						HAL_Delay(8);
						adBmsWakeupIc(tIC);
						adBmsReadData(tIC, &ic[i], RDAUXD, Aux, D);
	//					adBmsReadData(tIC, &ic[0], RDSTATA, Status, A);
						tV = getVoltage(ic[i].aux.a_codes[9]);

						st->CELL_T[val]=get_temp_from_voltage(tV);
						val++;

						if(SDC_Temp_CHECK){
								if(get_temp_from_voltage(tV)>=55.0) {
									SDC_FLAG = 0;
											}
								else {
									SDC_FLAG = 1;
								}
									}
						adBmsWakeupIc(tIC);
	//					adBmsWriteData(tIC, &ic[0], WRCFGA, Config, A);
	//					adBmsWriteData(tIC, &ic[0], WRCFGB, Config, B);
						adBms6830_Adax(AUX_OPEN_WIRE_DETECTION, OPEN_WIRE_CURRENT_SOURCE, 0);
						adBmsReadData(tIC, &ic[i], RDSTATA, Status, A);
						icTV = getVoltage(ic[i].stata.itmp);
						st->IC_T = (icTV/0.0075)-273 ;


		    }

		}

}


//void balancingLoop(void)
//{
//
//}

void cellDischarge (uint8_t cic, uint16_t cellD, uint8_t bit, cell_asic *ic)
{
	ic[cic].tx_cfgb.dcc = ConfigB_DccBit(cellD, bit);
}
//uint16_t updateBalancing(void)
// {
//
//	 float tSegmAvgCellV = 0.0;
//	 float segmAvgCellV = 0.0;
//	 for(int i=1; i<=SEG_NUM; i++)
//	 {
//		 SEG_PARAMS *m = seg_paramst_list[i];
//		 for(uint16_t j =0; j<CELL_NUM;j++)
//		 {
//			 tSegmAvgCellV += m->CELL_V[j];
//			 segmAvgCellV = tSegmAvgCellV/CELL_NUM;
//		 }
//		 for(int j =0; j<CELL_NUM;j++)
//		 {
//			 if ((m->CELL_V[j] - segmAvgCellV) > BALANCE_THRESH)
//			 {
//				// set bits
//				 adBms6830_togDischarge(&ic[i], j, 1);
//				 m->BAL_STAT = (1 << j);
//
//			 }
//			 else
//			 {
//				 // unset the bits
//				 adBms6830_togDischarge(&ic[i], j, 0);
//				 m->BAL_STAT = (0 << j);
//			 }
//		 }
//
//	 }
// }






















