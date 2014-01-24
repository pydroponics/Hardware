/*
 * Automated Control and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 *	spister@ucsc.edu
 *  dgunny@ucsc.edu
 *  
 *  
 * ACAMP.c
 *  Mother Program for Integration
 *
 * 
 * Created: 2/18/2013 5:30 - spister
 */

#include "GlobalGeneralDefines.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "sysTimer.h"
#include "sysUSART.h"
#include "pumpControl.h"
#include "phSensorControl.h"
#include "tdsSensorControl.h"

unsigned int state;
int phLength;
int tdsLength;

int main(void){
	//char printbuff[6];
	char response[MAX_RECEIVE_LENGTH];
	eventFlag = 0;
	arrayLength2 = 0;
	sei();
	
	//Pump Stuff
	sysTimerSetup();
	pumpSetup();
	DDRB = B7;
	PORTB &= ~B7;
	unsigned int count = 0;
	
	//Enable Uart Communication
	sysUsartInit(0,TERMUBRR);
	phEnableUsart();
	tdsEnableUsart();
	state = 1;
	phDebugLedToggle(state);
	tdsDebugLedToggle(state);
	
	while (1){
				
		
		switch(eventFlag){
			case 1:
			phLength = phGetValue(0,response);
			sysTransmit(response, 6, 0, OFF);
			sysTransmit("\n", 1, 0, OFF);
			_delay_ms(1000);
			eventFlag = 2;
			break;
			
			case 2:
			tdsLength = tdsGetValue(0,response);
			sysTransmit(response, 6, 0, OFF);
			sysTransmit("\n", 1, 0, OFF);
			_delay_ms(1000);
			eventFlag = 1;
			break;
		}

		
		if(eventFlag == 1){
			PORTB |= B7;
		}
		if(eventFlag == 2){
			PORTB &= ~B7;
		}
		
		phLength = phGetValue(0,response);
		sysTransmit("ph: ", 4, 0, OFF);
		sysTransmit(response, 5, 0, OFF); 
		sysTransmit("\r\n", 2, 0, OFF);
		_delay_ms(2000);
		
		tdsLength = tdsGetValue(0,response);
		sysTransmit("tds: ", 5, 0, OFF);
		sysTransmit(response, MAX_RECEIVE_LENGTH, 0, OFF);
		sysTransmit("\r\n", 2, 0, OFF);
		_delay_ms(2000);
		
		//Pump Stuff
		if (state == 1 && (PINC & C6) == C6) {
			pumpRun(10000);
			PORTB |= B7;
			state = 2;
		}
		if (state == 2 && IsTimerExpired(0) == 1) {
			pumpStop();
			state = 3;
		}
		if (state == 2 && (PINC & C6) == 0x00) {
			pumpStop();
			PORTB &= ~B7;
			state = 1;
		}
		
		//Prevent Back EMF by going to state 4, Pin was going low then high for a milli which caused the system to perpetually reset
		if(state == 3 && (PINC & C6) == 0x00){
			pumpStop();
			PORTB &= ~B7;
			sysTimerInit(1,10);
			while(IsTimerExpired(1) != 1){
			}
			if	((PINC & C6) == C6) state = 4;
			else state = 1;
		}
		if(state == 4 && (PINC & C6) == 0x00){
			state = 1;
		}
		
	}
	
	
	return 0;
}