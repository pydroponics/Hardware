/*
 * Automated Care and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 * spister@ucsc.edu
 *  
 * File: phSensorControl.c
 * Author: Stark Pister
 * Created: 2/23/13 4:41
 * 
 */ 

#include "GlobalGeneralDefines.h"
#include "phSensorControl.h"
#include "sysUART.h"
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

/****************************************************************************
Function:
	phEnableUart

Parameters:
	None.

Returns:
	None.

Description:
	Enable UART for pH sensor communication.
	 
Notes:
	8 bits, no parity, one stop.
	Baud rate 38400

Authors:
	Stark Pister, 3/3/13
 ****************************************************************************/

void phEnableUart(void){
	unsigned int baudRate = PHUBRR;
	sysUartInit(phUartIndex, baudRate);
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
	Stark Pister, 3/3/13
 ****************************************************************************/

void phDebugLedToggle(unsigned int state){
	char *command;
	switch (state) {
		case OFF:
			command = "L0\r";
			break;
		case ON:
			command = "L1\r";
			break;
	}
	sysTransmitString(phUartIndex, command);
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
	Stark Pister, 3/3/13
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
	Stark Pister, 3/3/13
 ****************************************************************************/

unsigned int phFactoryReset(void){
	char *command = "X\r";
	char *phDataPointer = rxDataBuffer2;
	char *phFactoryResetResponse = "reset";
	char phResponseChar;
	char phBufferChar;
	sysTransmitString(phUartIndex, command);
	while (1) {
		if (phDataReady == TRUE) {
			phDataReady = FALSE;
			while ((phResponseChar = *phFactoryResetResponse++)) {
				phBufferChar = *phDataPointer++;
				if (phBufferChar != phResponseChar) {
					return ERROR;
				}
			}
			return SUCCESS;
		}
	}
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
	Stark Pister, 3/3/13
 ****************************************************************************/

unsigned int phCalibrate(unsigned int phNum){
	char *command;
	char *phDataPointer = rxDataBuffer2;
	char *phFourCalResponse = "4.00";
	char *phSevenCalResponse = "7.00";
	char *phTenCalResponse = "10.00";
	char phResponseChar;
	char phBufferChar;
	switch (phNum) {
		case 4:
		command = "F\r";
		sysTransmitString(phUartIndex, command);
		while (1) {
			if (phDataReady == TRUE) {
				phDataReady = FALSE;
				while ((phResponseChar = *phFourCalResponse++)) {
					phBufferChar = *phDataPointer++;
					if (phBufferChar != phResponseChar) {
						return ERROR;
					}
				}
				return SUCCESS;
			}
		}
		break;
			
		case 7:
		command = "S\r";
		sysTransmitString(phUartIndex, command);
		while (1) {
			if (phDataReady == TRUE) {
				phDataReady = FALSE;
				while ((phResponseChar = *phSevenCalResponse++)) {
					phBufferChar = *phDataPointer++;
					if (phBufferChar != phResponseChar) {
						return ERROR;
					}
				}
				return SUCCESS;
			}
		}
		break;
			
		case 10:
		command = "T\r";
		sysTransmitString(phUartIndex, command);
		while (1) {
			if (phDataReady == TRUE) {
				phDataReady = FALSE;
				while ((phResponseChar = *phTenCalResponse++)) {
					phBufferChar = *phDataPointer++;
					if (phBufferChar != phResponseChar) {
						return ERROR;
					}
				}
				return SUCCESS;
			}
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
	Stark Pister, 3/3/13
 ****************************************************************************/

unsigned int phGetValue(char *temperature){
	char *command = temperature;
	unsigned int bufferIndex;
	//switch (temperature == 0) {
		//case 1:
		//command = "R\r";
		//break;
		//
		//default:
		//command = "27.70\r";
	//}
	sysTransmitString(phUartIndex, command);
	sysTransmit(phUartIndex, '\r');
	
	while (1) {
		if (phDataReady == TRUE) {
			for (bufferIndex = 0; bufferIndex < phDataIndex; bufferIndex++) {
				sysTransmit(terminalUartIndex, rxDataBuffer2[bufferIndex]);
			}
			sysTransmit(terminalUartIndex, '\n');
			sysClearRxBuffer(phUartIndex);
			phDataIndex = 0;
			phDataReady = FALSE;
			UCSR2B |= (1<<RXCIE2);
			return SUCCESS;
		}
		_delay_us(1);
	}
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
	Stark Pister, 3/3/13
 ****************************************************************************/

void phContinuousModeToggle(unsigned int state){
	char *command;
	switch (state){
		case ON:
			command = "C\r";
			break;
		case OFF:
			command = "E\r";
			break;
	}
	sysTransmitString(phUartIndex, command);
}