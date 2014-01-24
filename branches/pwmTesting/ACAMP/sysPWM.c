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
	TCCR2A |= ((1 << WGM21) | (1 << WGM20) | (1 << COM2A1)) | (1 << COM2B1);
	
	//Prescalar N value of 8, frequency at 62500 kHz
	TCCR2B |= (1 << CS20);
	
	//Initialize duty cycle
	OCR2A = 0;
	OCR2B = 0;
	
	//Interrupt at OCR2A value
	TIMSK2 |= (1 << OCIE2A) | (1 << OCIE2B);
	
	//Digital Pin 10 will be our Fan 0 output
	DDRB |= (1 << 4);
	PORTB &= ~(1 << 4);
	
	//Digital Pin 9 will be our Fan 1 output
	DDRH |= (1 << 6);
	PORTH &= ~(1 << 6);
	
	//Enables interrupt
	sei(); 
}


/****************************************************************************
Function:
	Fan0IncreaseSpeed

Parameters:
	None.

Returns:
	None.

Description:
	Increases the speed of Fan 0
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 62500 kHz (FCPU/256)
	

Authors:
	Danny Gunny, 04/07/2013
 ****************************************************************************/
void Fan0IncreaseSpeed(void) {
	OCR2A = OCR2A++;
}


/****************************************************************************
Function:
	Fan0DecreaseSpeed

Parameters:
	None.

Returns:
	None.

Description:
	Decreases the speed of Fan 0
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 62500 kHz (FCPU/256)
	

Authors:
	Danny Gunny, 04/07/2013
 ****************************************************************************/
void Fan0DecreaseSpeed(void) {
	OCR2A--;
}


/****************************************************************************
Function:
	Pwm1IncreaseSpeed

Parameters:
	None.

Returns:
	None.

Description:
	Increases the speed of Fan 1
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 62500 kHz (FCPU/256)
	

Authors:
	Danny Gunny, 05/11/2013
 ****************************************************************************/
void Fan1IncreaseSpeed(void) {
	OCR2B++;
}


/****************************************************************************
Function:
	Fan1DecreaseSpeed

Parameters:
	None.

Returns:
	None.

Description:
	Decreases the speed of Fan 1
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 62500 kHz (FCPU/256)
	

Authors:
	Danny Gunny, 05/11/2013
 ****************************************************************************/
void Fan1DecreaseSpeed(void) {
	OCR2B--;
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
	Toggles the 1st signal so that it operates as a PWM signal	

Authors:
	Danny Gunny, 03/30/2013
 ****************************************************************************/
ISR(TIMER2_COMPA_vect) {
	// Toggles PWM Port
	PORTB ^= (1 << 4);

}


/****************************************************************************
Function:
	ISR(TIMER2_COMPB_vect)

Parameters:
	None.

Returns:
	None.

Description:
	
	 
Notes:
	Toggles the 2nd signal so that it operates as a PWM signal	

Authors:
	Danny Gunny, 05/11/2013
 ****************************************************************************/
ISR(TIMER2_COMPB_vect) {
	// Toggles PWM Port
	PORTH ^= (1 << 6);

}