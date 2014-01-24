/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * spister@ucsc.edu
 * dgunny@ucsc.edu
 *  
 * File: motorControl.c
 * Author: Daniel Gunny
 * Created: 4/23/13 10:14
 *
 */ 

#include "GlobalGeneralDefines.h"
#include "motorControl.h"
#include "sysUART.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
unsigned int readingsTaken;
unsigned int readingsWanted;
unsigned int mm;
unsigned int currentPosition;
unsigned int estimatedPosition;
unsigned int distanceFromTray;
unsigned int systemReset;
unsigned int estimateCounter;
char *height;

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
void motorOff(void);
void motorForward(void);
void motorReverse(void);

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/****************************************************************************
Function:
	motorSetup()

Parameters:
	None.

Returns:
	None.

Description:
	Sets up the motor inputs and outputs.
	 
Notes:
	Direction (Output)	= PA0 = Digital Pin 22
	Brake (Output)		= PA2 = Digital Pin 24
	Bump Sensor (Input) = PA3 = Digital Pin 25
	PWM	(Output)		= PA4 = Digital Pin 26
	Encoder (Input)		= PA6 = Digital Pin 28
	Spool has 20.32 circumference.
	Encoder has 4 slots. 
	Encoder shaft rotates 240x the main shaft.

Authors:
	Danny Gunny, 4/23/13
 ****************************************************************************/
	
void motorSetup(void) {
	DDRA |= _BV(PA4) | _BV(PA2) | _BV(PA0); // 22,24,26 - Output
	DDRB &= ~_BV(PB1);						// 52 - Input
	PORTB |= _BV(PB1);						// 25 - Pull-up
	DDRA &= ~_BV(PA6);						// 28 - Input
	PORTA &= ~_BV(PA6);						// 28 - No pull-up
	PORTA &= ~(_BV(PA4));					// 26 - PWM low
	PORTA &= ~(_BV(PA0));					// 22 - Direction low
	PORTA |= _BV(PA2);						// 24 - Brake high

	systemReset = FALSE;
}

/****************************************************************************
Function:
	motorDown

Parameters:
	char* distance	- Distance in mm to lower the light.

Returns:
	None.

Description:
	Lowers the system by distance millimeters.
	 
Notes:
	None.

Authors:
	Danny Gunny, 5/3/13
 ****************************************************************************/

void motorDown(char* distance) {
	mm = atoi(distance);
	readingsTaken = 0;
	readingsWanted = mm * encoderCount; //Each mm of wire correlates to about 9.449 readings
	
	if(currentPosition <511){
		motorForward();
		_delay_ms(20);
		estimateCounter = 0;
		estimatedPosition = currentPosition;
		while(readingsTaken < readingsWanted) {
			if(estimatedPosition > 584){
				//sysTransmitString(terminalUartIndex, "At minimum height.\n");
				motorOff();
				break;
			}
			//Checks for low signal, then high signal, then increments readingTaken
			while(PINA & _BV(PA6)){}
			while(!(PINA & _BV(PA6))){}
			readingsTaken++;
			estimateCounter++;
			//Increments estimated counter every 9 readings taken
			if(estimateCounter == 4){
				estimatedPosition++;
				estimateCounter = 0;
			}
		}
		//sysTransmitString(terminalUartIndex, "Motor Done.\n");
	} else{
		//sysTransmitString(terminalUartIndex, "At minimum height.\n");
	}
	//Changes the systems idea of where the light hood is
	//Only changes if the system has been zeroed already
	if(systemReset == TRUE){
		currentPosition = currentPosition + (readingsTaken/encoderCount);
	}
	motorOff();
}

/****************************************************************************
Function:
	motorUp

Parameters:
	char* distance	- Distance in mm to raise the light.

Returns:
	None.

Description:
	Raises the system by a distance millimeters.
	
Notes:
	None.

Authors:
	Danny Gunny, 5/3/2013
 ****************************************************************************/

void motorUp(char* distance) {
	mm = atoi(distance);
	readingsTaken = 0;
	readingsWanted = mm * encoderCount;
	//Ensures bump sensor isn't active
	if(PINB & _BV(PB1)){
		motorReverse();
		_delay_ms(20);
		while(readingsTaken < readingsWanted) {
			//Checks each loop to see if bump sensor hit
			if(PINB & _BV(PB1)){
				//Checks encoder for high signal
				while(PINA & _BV(PA6)){
					if(!(PINB & _BV(PB1))){
						//Bump sensor hit, turn off motor and end loop
						//sysTransmitString(terminalUartIndex, "Roof hit.\n");
						motorOff();
						systemReset = TRUE;
						currentPosition = 0;
						return;
					}
				}
				
				//Checks encoder for low signal
				while(!(PINA & _BV(PA6))){
					if(!(PINB & _BV(PB1))){
						//Bump sensor hit, turn off motor and end loop
						//sysTransmitString(terminalUartIndex, "Roof hit.\n");
						motorOff();
						systemReset = TRUE;
						currentPosition = 0;
						return; 
					}
				}
				readingsTaken++;
			} else{
				//Bump sensor hit, turn off motor and end loop
				//sysTransmitString(terminalUartIndex, "Roof hit - ");
				motorOff();
				systemReset = TRUE;
				currentPosition = 0;
				return;
			}
			
		}
		
		//Changes the systems idea of where the light hood is
		//Only changes if the system has been zeroed already
		if(systemReset == TRUE){
			currentPosition = currentPosition - (readingsTaken/encoderCount);
		}
		
		//sysTransmitString(terminalUartIndex, "Motor Done.\n");
		
	}
	else{
		//sysTransmitString(terminalUartIndex, "At roof.\n");
		systemReset = TRUE;
		currentPosition = 0;
	}
	
	motorOff();
}

/****************************************************************************
Function:
	motorReset

Parameters:
	None.

Returns:
	None.

Description:
	Resets the light hood to position 0 (Top of the box).

Notes:
	None.
	
Authors:
	Danny Gunny, 4/23/13
 ****************************************************************************/

void motorReset(void) {
	//motorReverse(); Pending tests
	//loop_until_bit_is_clear(PINA,PA3)
	while(PINB & _BV(PB1)) {
		motorReverse();
	}
	motorOff();
	systemReset = TRUE;
	currentPosition = 0;
	//sysTransmitString(terminalUartIndex, "Height Reset\n");
}

/****************************************************************************
Function:
	lightHeight

Parameters:
	None.

Returns:
	char* height - Current height of the light.

Description:
	Sends the user the current light height.

Notes:
	None.

Authors:
	Danny Gunny, 4/23/13
 ****************************************************************************/

char* lightHeight(void) {
	if(systemReset == FALSE) {
		height = "System not reset";
	} else {
		distanceFromTray = 966 - currentPosition;
		height = sysItoa(distanceFromTray);
	}
	return height;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

/****************************************************************************
Function:
	motorOff

Parameters:
	None.

Returns:
	None.

Description:
	Stops the motor.
	 
Notes:
<<<<<<< .mine
	Encoder is using digital pint 25 (PA3).
	Spool has 20.32 circumference, encoder has 8 slots, encoder shaft rotates 
	240x the main shaft.

Authors:
	Danny Gunny 5/3/2013
 ****************************************************************************/
void motorOff(void) {
	//PWM and direction low, brake high
	PORTA &= ~(_BV(PA4));
	PORTA &= ~(_BV(PA0));
	PORTA |= _BV(PA2);
}

/****************************************************************************
Function:
	motorForward

Parameters:
	None.

Returns:
	None.

Description:
	Lowers the light system.
	 
Notes:
	None.
	
Authors:
	Danny Gunny, 4/23/13
 ****************************************************************************/
void motorForward(void) {
	//PWM and direction high, brake low
	PORTA |= _BV(PA4);
	PORTA |= _BV(PA0);
	PORTA &= ~(_BV(PA2));
}

/****************************************************************************
Function:
	motorReverse

Parameters:
	None.

Returns:
	None.

Description:
	Raises the light system.
	 
Notes:
	None.
	
Authors: 
	Danny Gunny, 4/23/13
 ****************************************************************************/
void motorReverse(void) {
	//PWM high, direction and brake low
	PORTA |= _BV(PA4);
	PORTA &= ~(_BV(PA2));
	PORTA &= ~(_BV(PA0));
}