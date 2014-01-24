/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * spister@ucsc.edu
 * dgunny@ucsc.edu
 *  
 * File: sysRelay.c
 * Authors: Stark Pister
 * Created: 2/19/13 9:50
 * 
 */

#include "GlobalGeneralDefines.h"
#include "sysRelay.h"
#include <avr/io.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/****************************************************************************
Function:
	sysRelaySetup

Parameters:
	None.

Returns:
	None.

Description:
	Set relay pins to output and initialize high.
	
	 
Notes:
	Dehumidifier	= PL7 = Digital Pin 42
	Air Pump		= PL5 = Digital Pin 44
	Water Pump		= PL3 = Digital Pin 46
	Light Ballast	= PL1 = Digital Pin 48

Authors:
	Stark Pister, 2/19/13
	Danny Gunny, 5/14/13
 ****************************************************************************/

void sysRelaySetup(void) {
	DDRL |= _BV(PL7) | _BV(PL5) | _BV(PL3) | _BV(PL1);
	PORTL &= ~(_BV(PL7) | _BV(PL5) | _BV(PL3) | _BV(PL1));
	
	//LED and switch initialization
	DDRB |= _BV(PB3);
	DDRB &= ~_BV(PB7);
	PORTB &= ~_BV(PB3);
	PORTB |= _BV(PB7);
}

/****************************************************************************
Function:
	dehumidfierOn

Parameters:
	None.

Returns:
	None.

Description:
	Turns on the dehumidifier.
	 
Notes:
	None.

Authors:
	Danny Gunny, 5/17/13
 ****************************************************************************/

void dehumidifierOn(void) {
	PORTL |= _BV(PL7);
}

/****************************************************************************
Function:
	dehumidfierOff

Parameters:
	None.

Returns:
	None.

Description:
	Turns off the dehumidifier.

Notes:
	None.

Authors:
	Danny Gunny, 5/17/13
 ****************************************************************************/

void dehumidifierOff(void) {
	PORTL &= ~_BV(PL7);
}

/****************************************************************************
Function:
	waterPumpOn

Parameters:
	None.

Returns:
	None.

Description:
	Turns on the water pump. 
	 
Notes:
	None.

Authors:
	Danny Gunny, 5/14/13
 ****************************************************************************/

void waterPumpOn(void) {
	PORTL |= _BV(PL3);
}

/****************************************************************************
Function:
	waterPumpOff

Parameters:
	None.

Returns:
	None.

Description:
	Turns off the pump.

Notes:
	None.

Authors:
	Danny Gunny, 5/14/13
 ****************************************************************************/

void waterPumpOff(void) {
	PORTL &= ~_BV(PL3);
}

/****************************************************************************
Function:
	airPumpOn

Parameters:
	None.

Returns:
	None.

Description:
	Turns on the air pump.

Notes:
	None.

Authors:
	Danny Gunny, 5/17/13
 ****************************************************************************/

void airPumpOn(void) {
	PORTL |= _BV(PL5);
}

/****************************************************************************
Function:
	airPumpOff

Parameters:
	None.

Returns:
	None.

Description:
	Turns off the air pump.
 
Notes:
	None.

Authors:
	Danny Gunny, 5/17/13
 ****************************************************************************/

void airPumpOff(void) {
	PORTL &= ~_BV(PL5);
}

/****************************************************************************
Function:
	lightOn

Parameters:
	None.

Returns:
	None.

Description:
	Turns on the light.

Notes:
	None.

Authors:
	Danny Gunny, 5/17/13
 ****************************************************************************/

void lightOn(void) {
	PORTL |= _BV(PL1);
}

/****************************************************************************
Function:
	lightOff

Parameters:
	None.

Returns:
	None.

Description:
	Turns off the light.

Notes:
	None.

Authors:
	Danny Gunny, 5/17/13
 ****************************************************************************/

void lightOff(void) {
	PORTL &= ~_BV(PL1);
}