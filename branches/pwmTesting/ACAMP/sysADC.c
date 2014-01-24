/*
 * Automated Control and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 *  dgunny@ucsc.edu
 *  
 * File: sysADC.c
 * Author: dgunny
 * Created: 4/06/2013 7:28PM
 */ 

#include "GlobalGeneralDefines.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "sysADC.h"
#include "sysUSART.h"
#include "sysPWM.h"


char *ADCValue;
uint8_t tempRead;


/****************************************************************************
Function:
	sysAdcSetup

Parameters:
	None.

Returns:
	None.

Description:
	
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 125 kHz (FCPU/128)

Authors:
	Danny Gunny, 04/06/2013
 ****************************************************************************/

void sysAdcSetup(void) {
	ADMUX |= ((1 << REFS0)| (1 << ADLAR)); // ADC0 selected, AVCC reference voltage, Bit Shift Left
	ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)); //Prescalar of 128, Frequency = 125 kHz
	ADCSRA |= (1 << ADEN); //ADC enabled
	//ADCSRA |= (1 << ADIE); //ADC Interrupt Enabled
	
	//Initial conversion for higher accuracy
	ADCSRA |= (1 << ADSC); //ADC Start Conversion
	loop_until_bit_is_clear (ADCSRA, ADSC);
	sei();
}



/****************************************************************************
Function:
	sysAdcStart

Parameters:
	None.

Returns:
	uint_8 of temperature in celsius

Description:
	
	 
Notes:
	Has the ADC perform 1 conversion
	
Authors:
	Danny Gunny, 04/06/2013
 ****************************************************************************/

char* sysAdcStart(void){
	ADCSRA |= (1 << ADSC); //ADC Start Conversion
	loop_until_bit_is_clear (ADCSRA, ADSC);
	tempRead = ADCH - 20.5128;
	itoa(tempRead, ADCValue, 10);
	sysReverseArray(ADCValue, sizeof(ADCValue));
	return ADCValue;
}


/****************************************************************************
Function:
	ISR(ADC_vect)

Parameters:
	None.

Returns:
	None.

Description:
	
	 
Notes:
	Interrupts when a conversion is complete	

Authors:
	Danny Gunny, 04/06/2013
 ****************************************************************************/
ISR(ADC_vect) {
}
	