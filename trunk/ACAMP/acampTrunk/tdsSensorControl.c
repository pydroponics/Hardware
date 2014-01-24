/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * spister@ucsc.edu
 * dgunny@ucsc.edu
 *  
 * File: tdsSensorControl.c
 * Author: Stark Pister
 * Created: 3/5/2013 6:51
 * 
 */ 

#include "GlobalGeneralDefines.h"
#include "tdsSensorControl.h"
#include "sysUART.h"
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
unsigned int bufferIndex;
char *command;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

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
	Stark Pister, 3/5/13
 ****************************************************************************/

void tdsDebugLedToggle(unsigned int state) {
	switch (state) {
		case 0:
		command = "L0\r";
		break;
		
		case 1:
		command = "L1\r";
		break;
	}
	sysTransmitString(tdsUartIndex, command);
}

void tdsContinuous(unsigned int state){
	switch (state) {
		case 0:
		command = "E\r";
		break;
		
		case 1:
		command = "C\r";
		break;
	}
	sysTransmitString(tdsUartIndex, command);
}

/****************************************************************************
Function:
	tdsFactoryReset

Parameters:
	None.

Returns:
	None.
	
Description:
	Reset TDS sensor to factory defaults.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 3/5/13
 ****************************************************************************/

void tdsFactoryReset(void) {
	command = "X\r";
	sysTransmitString(tdsUartIndex, command);
	while (1) {
		if (tdsDataReady == TRUE) {
			for (bufferIndex = 0; bufferIndex < tdsDataIndex; bufferIndex++) {
				sysTransmit(terminalUartIndex, rxDataBuffer1[bufferIndex]);
			}
			sysTransmit(terminalUartIndex, '\n');
			sysClearRxBuffer(tdsUartIndex);
			tdsDataIndex = 0;
			tdsDataReady = FALSE;
			UCSR1B |= (1<<RXCIE1);
			return;
		}
		_delay_us(1);
	}
}

/****************************************************************************
Function:
	tdsCalibrate

Parameters:
	unsigned in tdsNum			- TDS calibration number. 1,2,3,4

Returns:
	None.
	
Description:
	Calibrates the TDS sensor for sensor type, Dry Cal, 3000 us, and 220 us.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 3/5/13
 ****************************************************************************/

void tdsCalibrate(unsigned int tdsNum) {
	switch (tdsNum) {
		case 1:
		command = "P,1\r";
		break;
		
		case 2:
		command = "Z0\r";
		break;
		
		case 3:
		command = "Z30\r";
		break;
		
		case 4:
		command = "Z2\r";
		break;
	}
	sysTransmitString(tdsUartIndex, command);
	while (1) {
		if (tdsDataReady == TRUE) {
			for (bufferIndex = 0; bufferIndex < tdsDataIndex; bufferIndex++) {
				sysTransmit(terminalUartIndex, rxDataBuffer1[bufferIndex]);
			}
			sysTransmit(terminalUartIndex, '\n');
			sysClearRxBuffer(tdsUartIndex);
			tdsDataIndex = 0;
			tdsDataReady = FALSE;
			UCSR1B |= (1<<RXCIE1);
			return;
		}
		_delay_us(1);
	}
}

/****************************************************************************
Function:
	tdsGetValue

Parameters:
	double temperature			- Temperature for TDS sensor.

Returns:
	None.
	
Description:
	Gets a TDS value from the TDS sensor by sending a temperature for the TDS
	sensor to get a more accurate reading.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 3/5/13
 ****************************************************************************/

void tdsGetValue(void) {
	//command = temperature;
	//sysTransmitString(tdsUartIndex, command);
	sysTransmit(tdsUartIndex, 'R');
	sysTransmit(tdsUartIndex, '\r');
	while (1) {
		if (tdsDataReady == TRUE) {
			for (bufferIndex = 0; bufferIndex < tdsDataIndex; bufferIndex++) {
				sysTransmit(terminalUartIndex, rxDataBuffer1[bufferIndex]);
			}
			sysTransmit(terminalUartIndex, '\n');
			sysClearRxBuffer(tdsUartIndex);
			tdsDataIndex = 0;
			tdsDataReady = FALSE;
			UCSR1B |= (1<<RXCIE1);
			return;
		}
		_delay_us(1);
	}
}