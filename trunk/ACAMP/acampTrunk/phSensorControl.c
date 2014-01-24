/*
 * Pydroponics
 * CMPE129
 * Collaborators
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

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
char *command;
unsigned int bufferIndex;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

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

void phDebugLedToggle(unsigned int state) {
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
	phFactoryReset

Parameters:
	None.

Returns:
	None.
	
Description:
	Reset pH sensor to factory defaults.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 5/11/13
 ****************************************************************************/

void phFactoryReset(void) {
	command = "X\r";
	sysTransmitString(phUartIndex, command);
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
			return;
		}
		_delay_us(1);
	}
}

/****************************************************************************
Function:
	phCalibrate

Parameters:
	unsigned int phNum			- pH value to calibrate to. 4,7,10.

Returns:
	None.
	
Description:
	Calibrates the pH sensor for 4pH, 7pH, or 10pH.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 5/11/13
 ****************************************************************************/

void phCalibrate(unsigned int phNum){
	switch (phNum) {
		case 4:
		command = "F\r";
		break;
			
		case 7:
		command = "S\r";
		break;
			
		case 10:
		command = "T\r";
		break;
	}
	sysTransmitString(phUartIndex, command);
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
			return;
		}
		_delay_us(1);
	}
}

/****************************************************************************
Function:
	phGetValue

Parameters:
	char* temperature			- Temperature for pH sensor.

Returns:
	None.
	
Description:
	Gets a pH value from the pH sensor by sending a temperature for the pH
	sensor to get a more accurate reading.
	 
Notes:
	Temperature format XX.XX
	
Authors:
	Stark Pister, 5/11/13
 ****************************************************************************/

//void phGetValue(char *temperature){
void phGetValue(void){
	//command = temperature;
	//sysTransmitString(phUartIndex, command);
	sysTransmit(phUartIndex, 'R');
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
			return;
		}
		_delay_us(1);
	}
}