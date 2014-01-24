/*
 * Automated Control and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 *  dgunny@ucsc.edu
 *  
 * File: motorControl.c
 * Author: dgunny
 * Created: 4/23/2013 10:14
 */ 

#include "GlobalGeneralDefines.h"
#include <avr/io.h>

#include "motorControl.h"

unsigned int readingsTaken;
unsigned int readingsWanted;

/****************************************************************************
Function:
	motorSetup()

Parameters:
	None.

Returns:
	None.

Description:
	
	 
Notes:
	Uses pins 25, 24, 23, 22
	Sets  output pins low
	Pin 25: Encoder Input = PA3, uses pull up resistor
	Pin 24: PWM = PA2
	Pin 23: Direction = PA1
	Pin 22: Brake = PA0
	
	

Authors:
	Danny Gunny, 04/23/2013
 ****************************************************************************/
void motorSetup(){
	//Sets 22-24 as output pins
	DDRA |= _BV(PA2) | _BV(PA1) | _BV(PA0);
	
	//sets 25 as input pin, no pull up resistor
	DDRA &= ~_BV(PA3);
	PORTA &= ~_BV(PA3);
	
	//Sets PWM and direction low, brake high
	PORTA &= ~(_BV(PA2));
	PORTA &= ~(_BV(PA1));
	PORTA |= _BV(PA0);
}


/****************************************************************************
Function:
	motorOff

Parameters:
	None.

Returns:
	None.

Description:
	Stops the motor
	 
Notes:
	None.

Authors:
	Danny Gunny, 04/23/2013
 ****************************************************************************/

void motorOff(){
	PORTA &= ~(_BV(PA2));
	PORTA &= ~(_BV(PA1));
	PORTA |= _BV(PA0);
}


/****************************************************************************
Function:
	motorForward

Parameters:
	None.

Returns:
	None.

Description:
	Lowers the light system
	 
Notes:
	None.
	

Authors:
	Danny Gunny, 04/23/2013
 ****************************************************************************/

void motorForward(){
	//PWM and direction high, brake low
	PORTA |= _BV(PA2);
	PORTA |= _BV(PA1);
	PORTA &= ~(_BV(PA0));
}

/****************************************************************************
Function:
	motorReverse

Parameters:
	None.

Returns:
	None.

Description:
	Raises the light system
	 
Notes:
	None.
	

Authors:
	Danny Gunny, 04/23/2013
 ****************************************************************************/

void motorReverse(){
	//Pwm high, direction and brake low
	PORTA |= _BV(PA2);
	PORTA &= ~(_BV(PA1));
	PORTA &= ~(_BV(PA0));
}

/****************************************************************************
Function:
	motorDown

Parameters:
	None.

Returns:
	None.

Description:
	Lowers the system by a certain amount
	Encoder is using digital pint 25 (PA3)
	Spool has 20.32 circumference, encoder has 8 slots, encoder shaft rotates 240x the main shaft
	 
Notes:
	None.
	

Authors:
	Danny Gunny, 05/03/2013
 ****************************************************************************/

void motorDown(int mm){
	readingsTaken = 0;
	readingsWanted = mm * 9.449; //Each mm of wire correlates to about 9.449 readings
	
	//Loop to control motor for desired change in height
	while(readingsTaken < readingsWanted){
		motorForward();
		
		//Checks for low signal, then high signal, then increments readingTaken
		while(!(PINA & 0x08)){}
		while(PINA & 0x08){}
		readingsTaken++;			
	}
}

/****************************************************************************
Function:
	motorUp

Parameters:
	None.

Returns:
	None.

Description:
	Raises the system by a certain amount
	Encoder is using digital pint 25 (PA3)
	Spool has 20.32 circumference, encoder has 8 slots, encoder shaft rotates 240x the main shaft
	 
Notes:
	None.
	

Authors:
	Danny Gunny, 05/03/2013
 ****************************************************************************/

void motorUp(int mm){
	readingsTaken = 0;
	readingsWanted = mm * 9.449; //Each mm of wire correlates to about 9.449 readings
	
	//Loop to control motor for desired change in height
	while(readingsTaken < readingsWanted){
		motorReverse();
		
		//Checks encoder for low signal, then high signal, then increments readingTaken
		while(!(PINA & 0x08)){}
		while(PINA & 0x08){}
		readingsTaken++;
	}
}