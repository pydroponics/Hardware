/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * dgunny@ucsc.edu
 * spister@ucsc.edu
 *  
 * File: sysADC.c
 * Author: Daniel Gunny
 * Created: 04/06/2013 19:28
 *
 */ 

#include "GlobalGeneralDefines.h"
#include "sysADC.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
char *adcValue;
unsigned int tempRead;
unsigned int unused;

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
void sysAdcConvert(void);

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/****************************************************************************
Function:
	sysAdcSetup

Parameters:
	None.

Returns:
	None.

Description:
	Setup for two ADC systems, Water Temperature and Photo Diode.
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 125 kHz (F_CPU/128)

Authors:
	Danny Gunny, 4/6/13
 ****************************************************************************/

void sysAdcSetup(void) {
	ADMUX |= ((1 << REFS0)| (1 << ADLAR));
	ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
	ADCSRA |= (1 << ADEN);
}

/****************************************************************************
Function:
	sysAdcGetValue

Parameters:
	unsigned int adcIndex	- Index for the ADC to use.
	
Returns:
	char* adcValue			- Value of the ADC read.

Description:
	Gets a value for the corresponding ADC input.

Notes:
	None.
	
Authors:
	Danny Gunny 4/6/2013
 ****************************************************************************/

char* sysAdcGetValue(unsigned int adcIndex) {
	switch (adcIndex) {
		case waterTempIndex:
			ADMUX &= ~(1 << MUX0);
			sysAdcConvert();
			unused = ADCL;
			tempRead = ADCH - 20.5128;
			adcValue = sysItoa(tempRead);
			break;
			
		case photoDiodeIndex:
			ADMUX |= (1 << MUX0);
			sysAdcConvert();
			unused = ADCL;
			if (ADCH >= 180) {
				adcValue = "Light On";
			} else if(ADCH <180 && ADCH > 60){
				adcValue = "Ambient Light";
			} else {
				adcValue = "No Light";
			}
			
			break;
	}
	return adcValue;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

/****************************************************************************
Function:
	sysAdcConvert

Parameters:
	None.

Returns:
	None.

Description:
	Has the ADC perform 2 conversions to get an accurate reading.
	 
Notes:
	None.
	
Authors:
	Stark Pister, 5/11/13
 ****************************************************************************/

void sysAdcConvert(void) {
	ADCSRA |= (1 << ADSC);
	loop_until_bit_is_clear (ADCSRA, ADSC);
	ADCSRA |= (1 << ADSC);
	loop_until_bit_is_clear (ADCSRA, ADSC);
	ADCSRA |= (1 << ADIF);
}