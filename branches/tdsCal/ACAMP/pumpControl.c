/*
 * Automated Control and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 *	spister@ucsc.edu
 *  dgunny@ucsc.edu
 *  
 * File: pumpControl.c
 * Author: spister
 * Created: 2/19/2013 9:50
 * 
 */ 

#include <avr/io.h>
#include "sysTimer.h"
#include "pumpControl.h"
#include "GlobalGeneralDefines.h"

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/****************************************************************************
Function:
	pumpSetup

Parameters:
	None.

Returns:
	None.

Description:
	Set pump pin to output and initialize high. 
	 
Notes:
	None.

Authors:
	Stark Pister, 2013.2.19
 ****************************************************************************/
void pumpSetup(void) {
	DDRC = C7;
	PORTC = C6 + C7;
}

/****************************************************************************
Function:
	pumpRun

Parameters:
	unsigned int runTime		-Time in milliseconds to run the pump.

Returns:
	None.

Description:
	Starts a timer for runTime milliseconds and turns on the pump. 
	 
Notes:
	None.

Authors:
	Stark Pister, 2013.2.19
 ****************************************************************************/
void pumpRun(unsigned int runTime) {
	sysTimerInit(pumpTimer,runTime);
	PORTC &= ~C7;
}

/****************************************************************************
Function:
	pumpStop

Parameters:
	None.

Returns:
	None.

Description:
	Turns off the pump.
	 
Notes:
	None.

Authors:
	Stark Pister, 2013.2.19
 ****************************************************************************/
void pumpStop(void) {
	PORTC |= C7;
}