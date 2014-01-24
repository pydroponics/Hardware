/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * spister@ucsc.edu
 * dgunny@ucsc.edu
 *
 * Mother Program for Integration
 * 
 * File: Pydroponics.c
 * Author: Stark Pister
 * Created: 2/18/13 5:30
 *
 */

#include "GlobalGeneralDefines.h"
#include "sysUART.h"
#include "sysRelay.h"
#include "phSensorControl.h"
#include "tdsSensorControl.h"
#include "sysADC.h"
#include "fanControl.h"
#include "motorControl.h"
#include "sysSolenoid.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void){
	unsigned int bufferIndex;
	piDataReady = FALSE;
	phDataReady = FALSE;
	char temperature[6];
	temperature[5] = '\0';
	char mmDistance[4];
	mmDistance[3] = '\0';
	char solenoidTime[4];
	solenoidTime[3] = '\0';
	char fanSpeed[4];
	fanSpeed[3] = '\0';
	sysUartInit(terminalUartIndex,SYSUBRR);
	sysUartInit(phUartIndex,SYSUBRR);
	sysUartInit(tdsUartIndex,SYSUBRR);
	sysAdcSetup();
	fanSetup();
	motorSetup();
	sysSolenoidSetup();
	sei();
	phDebugLedToggle(ON);
	while (1) {
		if (piDataReady == TRUE) {
			
			if (rxDataBuffer0[0] == 'T') {
				//sysTransmitString(terminalUartIndex, "TDS Command - ");
				if (rxDataBuffer0[1] == 'V') {
					//sysTransmitString(terminalUartIndex, "Get Value - ");
					/*for (bufferIndex = 2; bufferIndex < 7; bufferIndex++) {
						temperature[bufferIndex-2] = rxDataBuffer0[bufferIndex];
					}*/
					tdsGetValue();
				} else if (rxDataBuffer0[1] == '+') {
					//sysTransmitString(terminalUartIndex, "Raise TDS Solenoid - ");
					for (bufferIndex = 2; bufferIndex < 5; bufferIndex++) {
						solenoidTime[bufferIndex-2] = rxDataBuffer0[bufferIndex];
						
					}
					tdsUp(solenoidTime);
					//sysTransmitString(terminalUartIndex,"Solenoid done.\n");
				} else if (rxDataBuffer0[1] == '-') {
					//sysTransmitString(terminalUartIndex, "Lower TDS Solenoid - ");
					for (bufferIndex = 2; bufferIndex < 5; bufferIndex++) {
						solenoidTime[bufferIndex-2] = rxDataBuffer0[bufferIndex];
						
					}
					tdsDown(solenoidTime);
					//sysTransmitString(terminalUartIndex,"Solenoid done.\n");
				} else {
					sysTransmitString(terminalUartIndex, "Invalid Command.\n");
				}
				
			} else if (rxDataBuffer0[0] == 'P') {
				//sysTransmitString(terminalUartIndex, "pH Command - ");
				if (rxDataBuffer0[1] == 'V') {
					//sysTransmitString(terminalUartIndex, "Get Value - ");
					/*for (bufferIndex = 2; bufferIndex < 7; bufferIndex++) {
						temperature[bufferIndex-2] = rxDataBuffer0[bufferIndex];
					}*/

					phGetValue();
				} else if (rxDataBuffer0[1] == '+') {
					//sysTransmitString(terminalUartIndex, "Raise pH Solenoid - ");
					for (bufferIndex = 2; bufferIndex < 5; bufferIndex++) {
						solenoidTime[bufferIndex-2] = rxDataBuffer0[bufferIndex];
						
					}
					phUp(solenoidTime);
					//sysTransmitString(terminalUartIndex,"Solenoid done.\n");
				} else if (rxDataBuffer0[1] == '-') {
					//sysTransmitString(terminalUartIndex, "Lower pH Solenoid - ");
					for (bufferIndex = 2; bufferIndex < 5; bufferIndex++) {
						solenoidTime[bufferIndex-2] = rxDataBuffer0[bufferIndex];
						
					}
					phDown(solenoidTime);
					//sysTransmitString(terminalUartIndex,"Solenoid done.\n");
				} else {
					//sysTransmitString(terminalUartIndex, "Invalid Command.\n");
				}
							
			} else if (rxDataBuffer0[0] == 'L') {
				//sysTransmitString(terminalUartIndex, "Light Command - ");
				if (rxDataBuffer0[1] == '1') {
					//sysTransmitString(terminalUartIndex, "On.\n");
					// Turn on Light
					lightOn();
				} else if (rxDataBuffer0[1] == '0') {
					//sysTransmitString(terminalUartIndex, "Off.\n");
					// Turn off Light
					lightOff();
				} else if (rxDataBuffer0[1] == '+') {
					//sysTransmitString(terminalUartIndex, "Raise Fixture - ");
					for (bufferIndex = 2; bufferIndex < 5; bufferIndex++) {
						mmDistance[bufferIndex-2] = rxDataBuffer0[bufferIndex];
					}
					motorUp(mmDistance); // Raises light fixture x mm
				} else if (rxDataBuffer0[1] == '-') {
					//sysTransmitString(terminalUartIndex, "Lower Fixture - ");
					for (bufferIndex = 2; bufferIndex < 5; bufferIndex++) {
						mmDistance[bufferIndex-2] = rxDataBuffer0[bufferIndex];
					}
					motorDown(mmDistance); // Lowers lights fixture x mm
				} else if (rxDataBuffer0[1] == 'H') {
					//sysTransmitString(terminalUartIndex, "Hood Height - ");
					sysTransmitString(terminalUartIndex, lightHeight());
					sysTransmit(terminalUartIndex, '\n');
				} else if (rxDataBuffer0[1] == 'R') {
					//sysTransmitString(terminalUartIndex, "Reset height - ");
					motorReset();
				} else {
					//sysTransmitString(terminalUartIndex, "Invalid Command.\n");
				}				
			
			} else if (rxDataBuffer0[0] == 'F') {
				//sysTransmitString(terminalUartIndex, "Fan Command - ");
				if (rxDataBuffer0[1] == 'E'){
					//sysTransmitString(terminalUartIndex, "Exhaust - ");
					for (bufferIndex = 2; bufferIndex < 5; bufferIndex++) {
						fanSpeed[bufferIndex-2] = rxDataBuffer0[bufferIndex];
						
					}
					//sysTransmitString(terminalUartIndex, fanSpeed);
					//sysTransmit(terminalUartIndex,'\n');
					//exhaustSpeed(fanSpeed);
					/*
					if (rxDataBuffer0[2] == '+') {
						if(OCR2A == 255){
							sysTransmitString(terminalUartIndex, "Max Speed.\n");
						}
						else{
							sysTransmitString(terminalUartIndex, "Speed Up.\n");
							fanIncreaseExhaustSpeed();
						}
					} else if (rxDataBuffer0[2] == '-') {
						if(OCR2A == 0){
							sysTransmitString(terminalUartIndex, "Min Speed.\n");
						}
						else{
							sysTransmitString(terminalUartIndex, " Slow Down.\n");
							fanDecreaseExhaustSpeed();	
						}
					}*/
										
				} else if (rxDataBuffer0[1] == 'I'){
					//sysTransmitString(terminalUartIndex, "Intake - ");
					for (bufferIndex = 2; bufferIndex < 5; bufferIndex++) {
						fanSpeed[bufferIndex-2] = rxDataBuffer0[bufferIndex];
						
					}
					//sysTransmitString(terminalUartIndex, fanSpeed);
					//sysTransmit(terminalUartIndex,'\n');
					intakeSpeed(fanSpeed);
					/*
					if (rxDataBuffer0[2] == '+') {
						if(OCR2B == 255){
							sysTransmitString(terminalUartIndex, "Max Speed.\n");
						}
						else{
							sysTransmitString(terminalUartIndex, "Speed Up.\n");
							fanIncreaseIntakeSpeed();
						}
					} else if (rxDataBuffer0[2] == '-') {
						if(OCR2B == 0){
							sysTransmitString(terminalUartIndex, "Min Speed.\n");
						}
						else{
							sysTransmitString(terminalUartIndex, "Slow Down.\n");
							fanDecreaseIntakeSpeed();
						}
					}*/
				} else if (rxDataBuffer0[1] == 'H'){
					//sysTransmitString(terminalUartIndex, "Hood - ");
					/*if (rxDataBuffer0[2] == '+') {
						if(OCR4CL == 255){
							sysTransmitString(terminalUartIndex, "Max Speed.\n");
						}
						else{
							sysTransmitString(terminalUartIndex, "Speed Up.\n");
							fanIncreaseHoodSpeed();
						}
					} else if (rxDataBuffer0[2] == '-') {
						if(OCR4CL == 0){
							sysTransmitString(terminalUartIndex, "Min Speed.\n");
						}
						else{
							sysTransmitString(terminalUartIndex, "Slow Down.\n");
							fanDecreaseHoodSpeed();
						}
					}*/
					for (bufferIndex = 2; bufferIndex < 5; bufferIndex++) {
						fanSpeed[bufferIndex-2] = rxDataBuffer0[bufferIndex];
						
					}
					//sysTransmitString(terminalUartIndex, fanSpeed);
					//sysTransmit(terminalUartIndex,'\n');
					//hoodSpeed(fanSpeed);
				} else {
					//sysTransmitString(terminalUartIndex, "Invalid Command.\n");
				}				
			
			} else if (rxDataBuffer0[0] == 'D') {
				//sysTransmitString(terminalUartIndex, "Dehumidifier Command - ");
				if (rxDataBuffer0[1] == '1') {
					//sysTransmitString(terminalUartIndex, "On.\n");
					//Turn on Dehumidifier
					dehumidifierOn();
				} else if (rxDataBuffer0[1] == '0') {
					//sysTransmitString(terminalUartIndex, "Off.\n");
					// Turn off Dehumidifier
					dehumidifierOff();
				} else {
					//sysTransmitString(terminalUartIndex, "Invalid Command.\n");
				}				
				
			} else if (rxDataBuffer0[0] == 'W') {
				//sysTransmitString(terminalUartIndex, "Water Pump Command - ");
				if (rxDataBuffer0[1] == '1') {
					//sysTransmitString(terminalUartIndex, "On.\n");
					//Turn on Water Pump
					waterPumpOn();
				} else if (rxDataBuffer0[1] == '0') {
					//sysTransmitString(terminalUartIndex, "Off.\n");
					//Turn off Water Pump
					waterPumpOff();
				} else {
					//sysTransmitString(terminalUartIndex, "Invalid Command.\n");
				}				
			
			} else if (rxDataBuffer0[0] == 'A') {
				//sysTransmitString(terminalUartIndex, "Air Pump Command - ");
				if (rxDataBuffer0[1] == '1') {
					//sysTransmitString(terminalUartIndex, "On.\n");
					// Turn on Air Pump
					airPumpOn();
	 			} else if (rxDataBuffer0[1] == '0') {
					//sysTransmitString(terminalUartIndex, "Off.\n");
					// Turn off Air Pump
					airPumpOff();
				} else {
					//sysTransmitString(terminalUartIndex, "Invalid Command.\n");
				}				
						
			} else if (rxDataBuffer0[0] == 'E') {
				//sysTransmitString(terminalUartIndex, "ADC Command - ");
				if(rxDataBuffer0[1] == 'W'){
					//sysTransmitString(terminalUartIndex, "Water Temperature Command - ");
					sysTransmitString(terminalUartIndex, sysAdcGetValue(waterTempIndex));
					sysTransmit(terminalUartIndex, '\n');
				}
				else if(rxDataBuffer0[1] == 'L'){
					//sysTransmitString(terminalUartIndex, "Light Sensor Command - ");
					sysTransmitString(terminalUartIndex, sysAdcGetValue(photoDiodeIndex));
					sysTransmit(terminalUartIndex, '\n');
				} else {
					//sysTransmitString(terminalUartIndex, "Invalid Command.\n");
				}
				
			} else {
				sysTransmitString(terminalUartIndex, "Invalid Command.\n");
			}
			sysClearRxBuffer(terminalUartIndex);
			piDataIndex = 0;
			piDataReady = FALSE;
			UCSR0B |= (1<<RXCIE0);
		}
		/*0if(PINB & _BV(PB7)){
			PORTB |= _BV(PB3);
		}else{
			PORTB &= ~_BV(PB3);
		}*/
		_delay_us(1);
	}
	return 1;
}