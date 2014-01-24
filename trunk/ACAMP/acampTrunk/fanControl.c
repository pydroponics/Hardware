/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * dgunny@ucsc.edu
 * spister@ucsc.edu
 *  
 * File: fanControl.c
 * Author: Daniel Gunny
 * Created: 03/30/13 20:11
 *
 */ 

#include "GlobalGeneralDefines.h"
#include "fanControl.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>

int increment;

/****************************************************************************
Function:
	fanSetup

Parameters:
	None.

Returns:
	None.

Description:
	Setup for fan PWM systems.
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 62500 kHz (FCPU/256)
	
Authors:
	Danny Gunny 3/30/2013
 ****************************************************************************/

void fanSetup(void) {
	//Fast PWM mode, Non-Inverting
	TCCR2A |= ((1 << WGM21) | (1 << WGM20) | (1 << COM2A1)) | (1 << COM2B1);
	TCCR4A |= ((1 << WGM40) | (1 << COM4C1));
	//Prescalar N value of 8, frequency at 62500 kHz
	TCCR2B |= (1 << CS20);
	TCCR4B |= ((1 << WGM42) | (1 << CS40));
	
	//Initialize duty cycle
	OCR2A = 0;
	OCR2B = 0;
	OCR4CL = 128;
	OCR4CH = 0;
	
	//Interrupt at OCR2A value
	TIMSK2 |= (1 << OCIE2A) | (1 << OCIE2B);
	TIMSK4 |= (1 << OCIE4C);
	
	//Digital Pin 10 will be our exhaust fan output
	DDRB |= (1 << 4);
	PORTB &= ~(1 << 4);
	
	//Digital Pin 9 will be our intake fan output
	DDRH |= (1 << 6);
	PORTH &= ~(1 << 6);
	
	//Digital Pin 8 will be our hood fan output
	DDRH |= (1 << 5);
	PORTH &= ~(1 << 5);
}

/****************************************************************************
Function:
	fanIncreaseExhaustSpeed

Parameters:
	None.

Returns:
	None.

Description:
	Increases exhaust fan speed.
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 62500 kHz (FCPU/256)

Authors:
	Danny Gunny 4/7/2013
 ****************************************************************************/

void fanIncreaseExhaustSpeed(void) {
	for(increment=0; increment < 5; increment++){
		if(OCR2A < 255){
			OCR2A++;
		}
	}
}

void exhaustSpeed(char* speed){
	OCR2A = atoi(speed);
}

void intakeSpeed(char* speed){
	OCR2B = atoi(speed);
}

void hoodSpeed(char* speed){
	OCR4CL = atoi(speed);
}


/****************************************************************************
Function:
	fanDecreaseExhaustSpeed

Parameters:
	None.

Returns:
	None.

Description:
	Decreases exhaust fan speed.
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 62500 kHz (FCPU/256)
	
Authors:
	Danny Gunny 4/7/2013
 ****************************************************************************/
void fanDecreaseExhaustSpeed(void) {
	for(increment=0; increment < 5; increment++){
		if(OCR2A > 0){
			OCR2A--;
		}
	}
}

/****************************************************************************
Function:
	fanIncreaseIntakeSpeed

Parameters:
	None.

Returns:
	None.

Description:
	Increases intake fan speed.
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 62500 kHz (FCPU/256)
	
Authors:
	Danny Gunny 5/11/2013
 ****************************************************************************/
void fanIncreaseIntakeSpeed(void) {
	for(increment=0; increment < 5; increment++){
		if(OCR2B < 255){
			OCR2B++;
		}
	}
}

/****************************************************************************
Function:
	fanDecreaseIntakeSpeed

Parameters:
	None.

Returns:
	None.

Description:
	Decreases intake fan speed.
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 62500 kHz (FCPU/256)
	
Authors:
	Danny Gunny 5/11/2013
 ****************************************************************************/
void fanDecreaseIntakeSpeed(void) {
	for(increment=0; increment < 5; increment++){
		if(OCR2B > 0){
			OCR2B--;
		}
	}
}

/****************************************************************************
Function:
	fanIncreaseHoodSpeed

Parameters:
	None.

Returns:
	None.

Description:
	Increases Hood fan speed.
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 62500 kHz (FCPU/256)

Authors:
	Danny Gunny 05/18/2013
 ****************************************************************************/

void fanIncreaseHoodSpeed(void) {
	for(increment=0; increment < 5; increment++){
		if(OCR4CL < 255){
			OCR4CL++;
		}
	}
}

/****************************************************************************
Function:
	fanDecreaseHoodSpeed

Parameters:
	None.

Returns:
	None.

Description:
	Decreases Hood fan speed.
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 62500 kHz (FCPU/256)
	
Authors:
	Danny Gunny 05/18/13
 ****************************************************************************/
void fanDecreaseHoodSpeed(void) {
	for(increment=0; increment < 5; increment++){
		if(OCR4CL > 0){
			OCR4CL--;
		}
	}
}

/****************************************************************************
Function:
	ISR(TIMER2_COMPA_vect)

Parameters:
	None.

Returns:
	None.

Description:
	Toggles the exhaust fan signal so that it operates as a PWM signal.
	 
Notes:
	None.

Authors:
	Danny Gunny 3/30/2013
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
	Toggles the intake fan signal so that it operates as a PWM signal.
	 
Notes:
	None.

Authors:
	Danny Gunny 5/11/2013
 ****************************************************************************/
ISR(TIMER2_COMPB_vect) {
	// Toggles PWM Port
	PORTH ^= (1 << 6);
}

/****************************************************************************
Function:
	ISR(TIMER4_COMPC_vect)

Parameters:
	None.

Returns:
	None.

Description:
	Toggles the hood fan signal so that it operates as a PWM signal.
	 
Notes:
	None.

Authors:
	Danny Gunny 5/11/2013
 ****************************************************************************/
ISR(TIMER4_COMPC_vect) {
	// Toggles PWM Port
	PORTH ^= (1 << 5);
}