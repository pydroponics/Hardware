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

#include "GlobalGeneralDefines.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "sysPWM.h"


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
	Timer (prescaler)	- 62500 kHz (FCPU/256)
	

Authors:
	Danny Gunny, 03/30/2013
 ****************************************************************************/

void sysPwmSetup(void) {
	
	//Fast PWM mode, Non-Inverting
	TCCR2A |= ((1 << WGM21) | (1 << WGM20) | (1 << COM2A1));
	
	//Prescalar N value of 8, frequency at 62500 kHz
	TCCR2B |= (1 << CS20);
	
	//Initialize duty cycle
	OCR2A = 160;
	
	//Interrupt at OCR2A value
	TIMSK2 |= (1 << OCIE2A);
	
	//Digital Pin 10 will be our PWM output
	DDRB |= (1 << 4);
	PORTB &= ~(1 << 4);
	
	//Enables interrupt
	sei(); 
}


/****************************************************************************
Function:
	Pwm2IncreaseSpeed

Parameters:
	None.

Returns:
	None.

Description:
	Increases the speed of PWM2
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 62500 kHz (FCPU/256)
	

Authors:
	Danny Gunny, 04/07/2013
 ****************************************************************************/
void Pwm2IncreaseSpeed(void) {
	OCR2A = OCR2A++;
}


/****************************************************************************
Function:
	Pwm2DecreaseSpeed

Parameters:
	None.

Returns:
	None.

Description:
	Decreases the speed of PWM2
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 62500 kHz (FCPU/256)
	

Authors:
	Danny Gunny, 04/07/2013
 ****************************************************************************/
void Pwm2DecreaseSpeed(void) {
	OCR2A--;
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
	PORTB ^= (1 << 4);

}