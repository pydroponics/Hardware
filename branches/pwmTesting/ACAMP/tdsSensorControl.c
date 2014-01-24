/*
 * Automated Control and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 *	spister@ucsc.edu
 *  dgunny@ucsc.edu
 *  
 * File: tdsSensorControl.c
 * Author: spister & dgunny
 * Created: 3/5/2013 6:51
 * 
 */ 

#include "GlobalGeneralDefines.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "tdsSensorControl.h"
#include "sysUSART.h"

/****************************************************************************
Function:
	tdsEnableUsart

Parameters:
	None.

Returns:
	None.

Description:
	Enable USART for TDS sensor communication.
	 
Notes:
	8 bits, no parity, one stop.
	Baud rate 38400

Authors:
	Stark Pister, 2013.3.5
	Danny Gunny, 2013.3.5
 ****************************************************************************/

void tdsEnableUsart(void) {
	unsigned int ubrr = TDSUBRR;
	sysUsartInit(tdsUsartIndex, ubrr);
}

/****************************************************************************
Function:
	tdsDebugLedToggle

Parameters:
	unsigned int state			-ON to turn on, OFF to turn off.

Returns:
	None.

Description:
	Turns the debug LEDs on or off.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 2013.3.5
	Danny Gunny, 2013.3.5
 ****************************************************************************/

void tdsDebugLedToggle(unsigned int state){
	char command[3];
	command[0] = 'L';
	command[2] = 0x0D;
	switch (state) {
		case 0:
			command[1] = '0';
			break;
		case 1:
			command[1] = '1';
			break;
	}
	sysTransmit(command,3,tdsUsartIndex,OFF);
}

/****************************************************************************
Function:
	tdsFirmwareRev

Parameters:
	None.

Returns:
	None.

Description:
	Displays the revision number of the stamp.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 2013.3.3
 ****************************************************************************/

//void tdsFirmwareRev(void){
//	To be developed. If needed.
//}

/****************************************************************************
Function:
	tdsFactoryReset

Parameters:
	None.

Returns:
	SUCCESS						- If the TDS sensor responds 'reset'.
	ERROR						- Otherwise.
	
Description:
	Reset TDS sensor to factory defaults.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 2013.3.5
	Danny Gunny, 2013.3.5
 ****************************************************************************/

//tdsFactoryResetResponse has to be "Factory reset"
unsigned int tdsFactoryReset(void){
	char tdsFactoryResetResponse[MAX_RECEIVE_LENGTH];
	tdsFactoryResetResponse[12] = 'F', tdsFactoryResetResponse[11] = 'a', tdsFactoryResetResponse[10] = 'c', tdsFactoryResetResponse[9] = 't', tdsFactoryResetResponse[8] = 'o', tdsFactoryResetResponse[7] = 'r', tdsFactoryResetResponse[6] = 'y', tdsFactoryResetResponse[5] = ' ', tdsFactoryResetResponse[4] = 'r', tdsFactoryResetResponse[3] = 'e', tdsFactoryResetResponse[2] = 's', tdsFactoryResetResponse[1] = 'e', tdsFactoryResetResponse[0] = 't';
	char command[2];
	char response[MAX_RECEIVE_LENGTH];
	command[0] = 'X';
	command[1] = 0x0D;
	sysTransmit(command,2,tdsUsartIndex,ON);
	while (tdsAckReqFlag == ON) {
	}
	sysCopyArray(tdsRxDataBuffer,MAX_RECEIVE_LENGTH,response,MAX_RECEIVE_LENGTH);
	if (sysCompareArray(response,MAX_RECEIVE_LENGTH,tdsFactoryResetResponse,MAX_RECEIVE_LENGTH)) {
		sysZeroArray(tdsRxDataBuffer,MAX_RECEIVE_LENGTH);
		return SUCCESS;
	}
	return ERROR;
}

/****************************************************************************
Function:
	tdsCalibrate

Parameters:
	unsigned in tdsNum			- TDS calibration number. 1,2,3,4

Returns:
	SUCCESS						- If the TDS sensor responds appropriately.
	ERROR						- Otherwise.
	
Description:
	Calibrates the TDS sensor for sensor type, Dry Cal, 3000 us, and 220 us.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 2013.3.5
	Danny Gunny, 2013.3.5
 ****************************************************************************/

unsigned int tdsCalibrate(unsigned int tdsNum) {
	char tdsTypeCalResponse[MAX_RECEIVE_LENGTH];
	tdsTypeCalResponse[3] = 'k', tdsTypeCalResponse[2] = '0', tdsTypeCalResponse[1] = '.', tdsTypeCalResponse[0] = '1';
	char tdsDryCalResponse[MAX_RECEIVE_LENGTH];
	tdsDryCalResponse[6] = 'D', tdsDryCalResponse[5] = 'r', tdsDryCalResponse[4] = 'y', tdsDryCalResponse[3] = ' ', tdsDryCalResponse[2] = 'C', tdsDryCalResponse[1] = 'a', tdsDryCalResponse[0] = 'l';
	char tdsHighCalResponse[MAX_RECEIVE_LENGTH];
	tdsHighCalResponse[10] = '3', tdsHighCalResponse[9] = '0', tdsHighCalResponse[8] = '0', tdsHighCalResponse[7] = '0', tdsHighCalResponse[6] = ' ', tdsHighCalResponse[5] = 0xB5, tdsHighCalResponse[4] = 's', tdsHighCalResponse[3] = ' ', tdsHighCalResponse[2] = 'c', tdsHighCalResponse[1] = 'a', tdsHighCalResponse[0] = 'l';
	char tdsLowCalResponse[MAX_RECEIVE_LENGTH];
	tdsLowCalResponse[9] = '2', tdsLowCalResponse[8] = '2', tdsLowCalResponse[7] = '0', tdsLowCalResponse[6] = ' ', tdsLowCalResponse[5] = 0xB5, tdsLowCalResponse[4] = 's', tdsLowCalResponse[3] = ' ', tdsLowCalResponse[2] = 'c', tdsLowCalResponse[1] = 'a', tdsLowCalResponse[0] = 'l';
	char command[4];
	char response[MAX_RECEIVE_LENGTH];
	switch (tdsNum) {
		case 1:
			command[0] = 'P';
			command[1] = ',';
			command[2] = '1';
			command[3] = 0x0D;
			sysTransmit(command, 4, tdsUsartIndex, ON);
			_delay_ms(500);
			sysCopyArray(tdsRxDataBuffer,MAX_RECEIVE_LENGTH,response,MAX_RECEIVE_LENGTH);
			sysTransmit(tdsRxDataBuffer,MAX_RECEIVE_LENGTH,0,OFF);
			sysTransmit("\n",1,0,OFF);
			sysZeroArray(tdsRxDataBuffer,MAX_RECEIVE_LENGTH);
			if (sysCompareArray(response,MAX_RECEIVE_LENGTH,tdsTypeCalResponse,MAX_RECEIVE_LENGTH)) {
				return SUCCESS;
			}
			break;
		case 2:
			command[0] = 'Z';
			command[1] = '0';
			command[2] = 0x0D;
			sysTransmit(command, 3, tdsUsartIndex, ON);
			_delay_ms(500);
			sysCopyArray(tdsRxDataBuffer,MAX_RECEIVE_LENGTH,response,MAX_RECEIVE_LENGTH);
			sysTransmit(tdsRxDataBuffer,MAX_RECEIVE_LENGTH,0,OFF);
			sysTransmit("\n",1,0,OFF);
			sysZeroArray(tdsRxDataBuffer,MAX_RECEIVE_LENGTH);
			if (sysCompareArray(response,MAX_RECEIVE_LENGTH,tdsDryCalResponse,MAX_RECEIVE_LENGTH)) {
				return SUCCESS;
			}
			break;
		case 3:
			command[0] = 'Z';
			command[1] = '3';
			command[2] = '0';
			command[3] = 0x0D;
			sysTransmit(command,4,tdsUsartIndex,ON);
			_delay_ms(500);
			sysCopyArray(tdsRxDataBuffer,MAX_RECEIVE_LENGTH,response,MAX_RECEIVE_LENGTH);
			sysTransmit(tdsRxDataBuffer,MAX_RECEIVE_LENGTH,0,OFF);
			sysTransmit("\n",1,0,OFF);
			sysZeroArray(tdsRxDataBuffer,MAX_RECEIVE_LENGTH);
			if (sysCompareArray(response,MAX_RECEIVE_LENGTH,tdsHighCalResponse,MAX_RECEIVE_LENGTH)) {
				return SUCCESS;
			}
			
			break;
		case 4:
			command[0] = 'Z';
			command[1] = '2';
			command[2] = 0x0D;
			sysTransmit(command,3,tdsUsartIndex,ON);
			_delay_ms(500);
			sysCopyArray(tdsRxDataBuffer,MAX_RECEIVE_LENGTH,response,MAX_RECEIVE_LENGTH);
			sysTransmit(tdsRxDataBuffer,MAX_RECEIVE_LENGTH,0,OFF);
			sysTransmit("\n",1,0,OFF);
			sysZeroArray(tdsRxDataBuffer,MAX_RECEIVE_LENGTH);
			if (sysCompareArray(response,MAX_RECEIVE_LENGTH,tdsLowCalResponse,MAX_RECEIVE_LENGTH)) {
				return SUCCESS;
			}
			break;
	}
	return ERROR;
}

/****************************************************************************
Function:
	tdsGetValue

Parameters:
	double temperature			- Temperature for TDS sensor.

Returns:
	double tdsValue				- TDS value.
	
Description:
	Gets a TDS value from the TDS sensor by sending a temperature for the TDS
	sensor to get a more accurate reading. Send a 0 for temperature to do an
	uncalibrated reading.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 2013.3.5
	Danny Gunny, 2013.3.5
 ****************************************************************************/

int tdsGetValue(double temperature, char *response) {
	char tdsProbeErrorResponse[MAX_RECEIVE_LENGTH];
	tdsProbeErrorResponse[10] = 'c', tdsProbeErrorResponse[9] = 'h', tdsProbeErrorResponse[8] = 'e', tdsProbeErrorResponse[7] = 'c', tdsProbeErrorResponse[6] = 'k', tdsProbeErrorResponse[5] = ' ', tdsProbeErrorResponse[4] = 'p', tdsProbeErrorResponse[3] = 'r', tdsProbeErrorResponse[2] = 'o', tdsProbeErrorResponse[1] = 'b', tdsProbeErrorResponse[0] = 'e';
	int length;
	char command[6];
	//char delims[] = ",";
	char tempChar1;
	char tempChar2;
	switch (temperature == 0) {
		case 1:
			command[0] = 'R';
			command[1] = 0x0D;
			sysTransmit(command,2,tdsUsartIndex,ON);
			break;
		default:
			sprintf(command, "%2.2f", temperature);
			sysRightShiftArray(command,6);
			tempChar1 = command[3];
			tempChar2 = command[4];
			command[3] = command[1];
			command[4] = command[0];
			command[1] = tempChar1;
			command[0] = tempChar2;
			command[5] = 0x0D;
			sysTransmit(command,6,tdsUsartIndex,ON);
	}
	//while (tdsAckReqFlag == ON) {
	//}
	_delay_ms(1000);
	sysCopyArray(tdsRxDataBuffer,MAX_RECEIVE_LENGTH,response,MAX_RECEIVE_LENGTH);
	sysReverseArray(response, arrayLength1);
	length = arrayLength1;
	arrayLength1 = 0;
	sysZeroArray(tdsRxDataBuffer,MAX_RECEIVE_LENGTH);
	return length;
}

/****************************************************************************
Function:
	tdsContinuousModeToggle

Parameters:
	unsigned int state			- ON to turn on, OFF to turn off.

Returns:
	None.
	
Description:
	Toggles continuous TDS reading mode on or off.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 2013.3.5
	Danny Gunny, 2013.3.5
 ****************************************************************************/

void tdsContinuousModeToggle(unsigned int state) {
	char tdsProbeErrorResponse[MAX_RECEIVE_LENGTH];
	tdsProbeErrorResponse[10] = 'c', tdsProbeErrorResponse[9] = 'h', tdsProbeErrorResponse[8] = 'e', tdsProbeErrorResponse[7] = 'c', tdsProbeErrorResponse[6] = 'k', tdsProbeErrorResponse[5] = ' ', tdsProbeErrorResponse[4] = 'p', tdsProbeErrorResponse[3] = 'r', tdsProbeErrorResponse[2] = 'o', tdsProbeErrorResponse[1] = 'b', tdsProbeErrorResponse[0] = 'e';
	char command[2];
	command[1] = 0x0D;
	switch (state) {
		case ON:
			command[0] = 'C';
			break;
		case OFF:
			command[0] = 'E';
			break;
	}
	sysTransmit(command,2,tdsUsartIndex,OFF);
}