/*
 * Automated Care and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 * spister@ucsc.edu
 * dgunny@ucsc.edu
 *  
 * File: tdsSensorControl.c
 * Author: Stark Pister & Danny Gunny
 * Created: 3/5/2013 6:51
 * 
 */ 

#include "GlobalGeneralDefines.h"
#include "tdsSensorControl.h"
#include "sysUART.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/****************************************************************************
Function:
	tdsEnableUart

Parameters:
	None.

Returns:
	None.

Description:
	Enable UART for TDS sensor communication.
	 
Notes:
	8 bits, no parity, one stop.
	Baud rate 38400

Authors:
	Stark Pister, 3/5/13
	Danny Gunny, 3/5/13
 ****************************************************************************/

void tdsEnableUart(void) {
	unsigned int baudRate = TDSUBRR;
	sysUartInit(tdsUartIndex, baudRate);
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
	Stark Pister, 3/5/13
	Danny Gunny, 3/5/13
 ****************************************************************************/

void tdsDebugLedToggle(unsigned int state) {
	char *command;
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
	Stark Pister, 3/3/13
 ****************************************************************************/

//void tdsFirmwareRev(void) {
//	To be developed if needed.
//}

/****************************************************************************
Function:
	tdsFactoryReset

Parameters:
	None.

Returns:
	SUCCESS						- If the TDS sensor responds 'Factory reset'.
	ERROR						- Otherwise.
	
Description:
	Reset TDS sensor to factory defaults.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 3/5/13
 ****************************************************************************/

unsigned int tdsFactoryReset(void) {
	char *command = "X\r";
	char *tdsDataPointer = rxDataBuffer1;
	char *tdsFactoryResetResponse = "Factory reset";
	char tdsResponseChar;
	char tdsBufferChar;
	sysTransmitString(tdsUartIndex, command);
	while (1) {
		if (tdsDataReady == TRUE) {
			tdsDataReady = FALSE;
			while ((tdsResponseChar = *tdsFactoryResetResponse++)) {
				tdsBufferChar = *tdsDataPointer++;
				if (tdsBufferChar != tdsResponseChar) {
					return ERROR;
				}
			}
			return SUCCESS;
		}
	}
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
 ****************************************************************************/

unsigned int tdsCalibrate(unsigned int tdsNum) {
	char *command;
	char *tdsDataPointer = rxDataBuffer1;
	char *tdsTypeCalResponse = "k0.1";
	char *tdsDryCalResponse = "Dry Cal";
	char *tdsHighCalResponse = "3000 \xB5s cal";
	char *tdsLowCalResponse = "220 \xB5s cal";
	char tdsResponseChar;
	char tdsBufferChar;
	switch (tdsNum) {
		case 1:
		command = "P,1\r";
		sysTransmitString(tdsUartIndex, command);
		while (1) {
			if (tdsDataReady == TRUE) {
				tdsDataReady = FALSE;
				while ((tdsResponseChar = *tdsTypeCalResponse++)) {
					tdsBufferChar = *tdsDataPointer++;
					if (tdsBufferChar != tdsResponseChar) {
						return ERROR;
					}
				}
				return SUCCESS;
			}
		}
		
		case 2:
		command = "Z0\r";
		sysTransmitString(tdsUartIndex, command);
		while (1) {
			if (tdsDataReady == TRUE) {
				tdsDataReady = FALSE;
				while ((tdsResponseChar = *tdsDryCalResponse++)) {
					tdsBufferChar = *tdsDataPointer++;
					if (tdsBufferChar != tdsResponseChar) {
						return ERROR;
					}
				}
				return SUCCESS;
			}
		}
		
		case 3:
		command = "Z30\r";
		sysTransmitString(tdsUartIndex, command);
		while (1) {
			if (tdsDataReady == TRUE) {
				tdsDataReady = FALSE;
				while ((tdsResponseChar = *tdsHighCalResponse++)) {
					tdsBufferChar = *tdsDataPointer++;
					if (tdsBufferChar != tdsResponseChar) {
						return ERROR;
					}
				}
				return SUCCESS;
			}
		}
		
		case 4:
		command = "Z2\r";
		sysTransmitString(tdsUartIndex, command);
		while (1) {
			if (tdsDataReady == TRUE) {
				tdsDataReady = FALSE;
				while ((tdsResponseChar = *tdsLowCalResponse++)) {
					tdsBufferChar = *tdsDataPointer++;
					if (tdsBufferChar != tdsResponseChar) {
						return ERROR;
					}
				}
				return SUCCESS;
			}
		}
		
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
 ****************************************************************************/

unsigned int tdsGetValue(double temperature) {
	char *command;
	char *tdsDataPointer = rxDataBuffer1;
	char *tdsProbeErrorResponse = "check probe";
	char tdsResponseChar;
	char tdsBufferChar;
	switch (temperature == 0) {
		case 1:
		command = "R\r";
		break;
		
		default:
		sprintf(command, "%2.2f\r", temperature);
	}
	sysTransmitString(tdsUartIndex, command);
	while (1) {
		if (tdsDataReady == TRUE) {
			tdsDataReady = FALSE;
			while ((tdsResponseChar = *tdsProbeErrorResponse++)) {
				tdsBufferChar = *tdsDataPointer++;
				if (tdsBufferChar == tdsResponseChar) {
					return ERROR;
				}
			}
			return SUCCESS;
		}
	}
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
	char *command;
	switch (state) {
		case ON:
			command = "C\r";
			break;
		case OFF:
			command = "E\r";
			break;
	}
	sysTransmitString(tdsUartIndex, command);
}