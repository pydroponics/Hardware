/*
 * Automated Control and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 *  dgunny@ucsc.edu
 *  
 * File: sysPWM.c
 * Author: dgunny
 * Created: 3/30/2013 8:11
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include "sysPWM.h"
#include "GlobalGeneralDefines.h"


/****************************************************************************
Function:
	sysPwmSetup

Parameters:
	None.

Returns:
	None.

Description:
	
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 7.8125 kHz (FCPU/2048)
	

Authors:
	Danny Gunny, 03/30/2013
 ****************************************************************************/

void sysPwmSetup(void) {
	
	//Fast PWM mode, Non-Inverting
	TCCR2A |= ((1 << WGM21) | (1 << WGM20) | (1 << COM2A1));
	
	//Prescalar N value of 8, frequency at 7.8125 kHz
	TCCR2B |= (1 << CS21);
	
	//Interrupt at OCR2A value
	TIMSK2 |= (1 << OCIE2A);
	
	//Initialize duty cycle at 50%
	OCR2A = 0x80;
	
	//Digital Pin 10 will be our PWM output
	DDRB |= (1 << 4);
	PORTB |= (0 << 4);
	
	//Enables interrupt
	sei();
}


/****************************************************************************
Function:
	ISR(TIMER2_COMPA_vect)

Parameters:
	None.

Returns:
	None.

Description:
	
	 
Notes:
	Toggles the signal so that it operates as a PWM signal	

Authors:
	Danny Gunny, 03/30/2013
 ****************************************************************************/
ISR(TIMER2_COMPA_vect) {

	// Toggles PWM Port
	PORTB ^= (1 << 5);

}