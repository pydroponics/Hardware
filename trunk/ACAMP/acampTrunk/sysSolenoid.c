/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * spister@ucsc.edu
 * dgunny@ucsc.edu
 *  
 * File: sysSolenoid.c
 * Author: Daniel Gunny
 * Created: 05/14/13 8:31
 *
 */

#include "GlobalGeneralDefines.h"
#include "sysSolenoid.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
unsigned int time;
unsigned int counter;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/****************************************************************************
Function:
	sysSolenoidSetup

Parameters:
	None.

Returns:
	None.

Description:
	Sets up all four solenoids.
	 
Notes:
	Uses pins 31, 33, 35, & 37
	Sets  output pins low
	pH up solenoid = pin 31 = PC6
	pH down solenoid = pin 33 = PC4
	tds up solenoid = pin 35 = PC2
	tds down solenoid = pin 37 = PC0
	
Authors:
	Danny Gunny, 5/14/2013
 ****************************************************************************/

void sysSolenoidSetup(void) {
	DDRC |= _BV(PC6) | _BV(PC4) | _BV(PC2) | _BV(PC0);
	PORTC &= ~(_BV(PC6) | _BV(PC4) | _BV(PC2) | _BV(PC0));
}

/****************************************************************************
Function:
	phUp

Parameters:
	char* duration

Returns:
	None.

Description:
	Turns on pH Up solenoid for duration ms.
	 
Notes:
	None.

Authors:
	Danny Gunny, 5/17/2013
 ****************************************************************************/

void phUp(char* duration) {
	time = atoi(duration);
	PORTC |= _BV(PC4);
	for(counter = 0; counter < time; counter++) {
		_delay_ms(1);
	}
	PORTC &= ~_BV(PC4);
}

/****************************************************************************
Function:
	phDown

Parameters:
	char* duration

Returns:
	None.

Description:
	Turns on pH Down solenoid for duration ms.
	 
Notes:
	None.

Authors:
	Danny Gunny, 5/17/2013
 ****************************************************************************/

void phDown(char* duration) {
	time = atoi(duration);
	PORTC |= _BV(PC6);
	for(counter = 0; counter < time; counter++) {
		_delay_ms(1);
	}
	PORTC &= ~_BV(PC6);
}

/****************************************************************************
Function:
	tdsUp

Parameters:
	char* duration

Returns:
	None.

Description:
	Turns on tds Up solenoid for duration ms.
	 
Notes:
	None.

Authors:
	Danny Gunny, 5/17/2013
 ****************************************************************************/

void tdsUp(char* duration) {
	time = atoi(duration);
	PORTC |= _BV(PC0);
	for(counter = 0; counter < time; counter++) {
		_delay_ms(1);
	}
	PORTC &= ~_BV(PC0);
}

/****************************************************************************
Function:
	tdsDown

Parameters:
	char* duration

Returns:
	None.

Description:
	Turns on tds Down solenoid for duration ms.
	 
Notes:
	None.

Authors:
	Danny Gunny, 5/17/2013
 ****************************************************************************/

void tdsDown(char* duration) {
	time = atoi(duration);
	PORTC |= _BV(PC2);
	for(counter = 0; counter < time; counter++) {
		_delay_ms(1);
	}
	PORTC &= ~_BV(PC2);
	
}
