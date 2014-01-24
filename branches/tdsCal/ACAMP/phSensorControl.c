/*
 * Automated Control and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 *	spister@ucsc.edu
 *  
 *  
 * File: phSensorControl.c
 * Author: spister
 * Created: 2/23/2013 4:41
 * 
 */ 
#include "GlobalGeneralDefines.h"
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include "phSensorControl.h"
#include "sysUSART.h"



/****************************************************************************
Function:
	phEnableUsart

Parameters:
	None.

Returns:
	None.

Description:
	Enable USART for pH sensor communication.
	 
Notes:
	8 bits, no parity, one stop.
	Baud rate 38400

Authors:
	Stark Pister, 2013.3.3
 ****************************************************************************/

void phEnableUsart(void){
	unsigned int ubrr = PHUBRR;
	sysUsartInit(phUsartIndex, ubrr);
}

/****************************************************************************
Function:
	phDebugLedToggle

Parameters:
	unsigned int state			-ON to turn on, OFF to turn off.

Returns:
	None.

Description:
	Turns the debug LEDs on or off.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 2013.3.3
 ****************************************************************************/

void phDebugLedToggle(unsigned int state){
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
	sysTransmit(command,3,phUsartIndex,OFF);
}

/****************************************************************************
Function:
	phFirmwareRev

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

//void phFirmwareRev(void){
//	To be developed. If needed.
//}

/****************************************************************************
Function:
	phFactoryReset

Parameters:
	None.

Returns:
	SUCCESS						- If the pH sensor responds 'reset'.
	ERROR						- Otherwise.
	
Description:
	Reset pH sensor to factory defaults.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 2013.3.3
 ****************************************************************************/

unsigned int phFactoryReset(void){
	char phFactoryResetResponse[MAX_RECEIVE_LENGTH];
	phFactoryResetResponse[4] = 'r', phFactoryResetResponse[3] = 'e', phFactoryResetResponse[2] = 's', phFactoryResetResponse[1] = 'e', phFactoryResetResponse[0] = 't';
	char command[2];
	command[0] = 'X';
	command[1] = 0x0D;
	sysTransmit(command,2,phUsartIndex,ON);
	while (phAckReqFlag == ON){
	}
	char response[MAX_RECEIVE_LENGTH];
	sysCopyArray(phRxDataBuffer,MAX_RECEIVE_LENGTH,response,MAX_RECEIVE_LENGTH);
	if (sysCompareArray(response,MAX_RECEIVE_LENGTH,phFactoryResetResponse,MAX_RECEIVE_LENGTH)){
		sysZeroArray(phRxDataBuffer,MAX_RECEIVE_LENGTH);
		return SUCCESS;
	}
	return ERROR;
}

/****************************************************************************
Function:
	phCalibrate

Parameters:
	unsigned int phNum			- pH value to calibrate to. 4,7,10.

Returns:
	SUCCESS						- If the pH sensor responds appropriately.
	ERROR						- Otherwise.
	
Description:
	Calibrates the pH sensor for 4pH, 7pH, or 10pH.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 2013.3.3
 ****************************************************************************/

unsigned int phCalibrate(unsigned int phNum){
	char phFourCalResponse[MAX_RECEIVE_LENGTH];
	phFourCalResponse[3] = '4', phFourCalResponse[2] = '.', phFourCalResponse[1] = '0', phFourCalResponse[0] = '0';
	char phSevenCalResponse[MAX_RECEIVE_LENGTH];
	phSevenCalResponse[3] = '7', phSevenCalResponse[2] = '.', phSevenCalResponse[1] = '0', phSevenCalResponse[0] = '0';
	char phTenCalResponse[MAX_RECEIVE_LENGTH];
	phTenCalResponse[4] = '1', phTenCalResponse[3] = '0', phTenCalResponse[2] = '.', phTenCalResponse[1] = '0', phTenCalResponse[0] = '0';
	char command[2];
	command[1] = 0x0D;
	char response[MAX_RECEIVE_LENGTH];
	switch (phNum) {
		case 4:
			command[0] = 'F';
			sysTransmit(command,2,phUsartIndex,ON);
			_delay_ms(500);
			//while (phAckReqFlag == ON){
			//}
			sysCopyArray(phRxDataBuffer,MAX_RECEIVE_LENGTH,response,MAX_RECEIVE_LENGTH);
			sysTransmit(phRxDataBuffer,MAX_RECEIVE_LENGTH,0,OFF);
			if (sysCompareArray(response,MAX_RECEIVE_LENGTH,phFourCalResponse,MAX_RECEIVE_LENGTH)){
				sysZeroArray(phRxDataBuffer,MAX_RECEIVE_LENGTH);
				return SUCCESS;
			}
			break;
		case 7:
			command[0] = 'S';
			sysTransmit(command,2,phUsartIndex,ON);
			_delay_ms(500);
			//while (phAckReqFlag == ON){
			//}
			sysCopyArray(phRxDataBuffer,MAX_RECEIVE_LENGTH,response,MAX_RECEIVE_LENGTH);
			sysTransmit(phRxDataBuffer,MAX_RECEIVE_LENGTH,0,OFF);
			if (sysCompareArray(response,MAX_RECEIVE_LENGTH,phSevenCalResponse,MAX_RECEIVE_LENGTH)){
				sysZeroArray(phRxDataBuffer,MAX_RECEIVE_LENGTH);
				return SUCCESS;
			}
			break;
		case 10:
			command[0] = 'T';
			sysTransmit(command,2,phUsartIndex,ON);
			//while (phAckReqFlag == ON){
			//}
			_delay_ms(500);
			sysCopyArray(phRxDataBuffer,MAX_RECEIVE_LENGTH,response,MAX_RECEIVE_LENGTH);
			sysTransmit(phRxDataBuffer,MAX_RECEIVE_LENGTH,0,OFF);
			if (sysCompareArray(response,MAX_RECEIVE_LENGTH,phTenCalResponse,MAX_RECEIVE_LENGTH)){
				sysZeroArray(phRxDataBuffer,MAX_RECEIVE_LENGTH);
				return SUCCESS;
			}
			break;
	}
	return ERROR;
}

/****************************************************************************
Function:
	phGetValue

Parameters:
	double temperature			- Temperature for pH sensor.

Returns:
	double phValue				- pH value.
	
Description:
	Gets a pH value from the pH sensor by sending a temperature for the pH
	sensor to get a more accurate reading. Send a 0 for temperature to do an
	uncalibrated reading.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 2013.3.3
 ****************************************************************************/

int phGetValue(double temperature, char *response){
	char phProbeErrorResponse[MAX_RECEIVE_LENGTH];
	extern char ackReqFlag2;
	ackReqFlag2 = ON;
	phProbeErrorResponse[10] = 0x63, phProbeErrorResponse[9] = 'h', phProbeErrorResponse[8] = 'e', phProbeErrorResponse[7] = 'c', phProbeErrorResponse[6] = 'k', phProbeErrorResponse[5] = ' ', phProbeErrorResponse[4] = 'p', phProbeErrorResponse[3] = 'r', phProbeErrorResponse[2] = 'o', phProbeErrorResponse[1] = 'b', phProbeErrorResponse[0] = 'e';
	char command[6];
	int length;
	switch (temperature == 0) {
		case 1:
			command[0] = 'R';
			command[1] = 0x0D;
			sysTransmit(command,2,phUsartIndex,ON);
			break;
		default:
			sprintf(command, "%2.2f", temperature);
			sysRightShiftArray(command,6);
			char tempChar1 = command[3];
			char tempChar2 = command[4];
			command[3] = command[1];
			command[4] = command[0];
			command[1] = tempChar1;
			command[0] = tempChar2;
			command[5] = 0x0D;
			sysTransmit(command,6,phUsartIndex,ON);
	}
	
	_delay_ms(1000);
	//while (ackReqFlag2 == ON){
	//}
	sysCopyArray(phRxDataBuffer,MAX_RECEIVE_LENGTH,response,MAX_RECEIVE_LENGTH);
	sysReverseArray(response, arrayLength2);
	length = arrayLength2;
	arrayLength2 = 0;
	sysZeroArray(phRxDataBuffer,MAX_RECEIVE_LENGTH);
	return length;
}

/****************************************************************************
Function:
	phContinuousModeToggle

Parameters:
	unsigned int state			- ON to turn on, OFF to turn off.

Returns:
	None.
	
Description:
	Toggles continuous pH reading mode on or off.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 2013.3.3
 ****************************************************************************/

void phContinuousModeToggle(unsigned int state){
	char phProbeErrorResponse[MAX_RECEIVE_LENGTH];
	phProbeErrorResponse[10] = 0x63, phProbeErrorResponse[9] = 'h', phProbeErrorResponse[8] = 'e', phProbeErrorResponse[7] = 'c', phProbeErrorResponse[6] = 'k', phProbeErrorResponse[5] = ' ', phProbeErrorResponse[4] = 'p', phProbeErrorResponse[3] = 'r', phProbeErrorResponse[2] = 'o', phProbeErrorResponse[1] = 'b', phProbeErrorResponse[0] = 'e';
	char command[2];
	command[1] = 0x0D;
	switch (state){
		case ON:
			command[0] = 'C';
			break;
		case OFF:
			command[0] = 'E';
			break;
	}
	sysTransmit(command,2,phUsartIndex,OFF);
}