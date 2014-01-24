/*
 * Automated Care and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 * spister@ucsc.edu
 * dgunny@ucsc.edu
 *
 * Mother Program for Integration
 * 
 * File: acampTrunk.c
 * Author: Stark Pister
 * Created: 2/18/13 5:30
 *
 */

#include "GlobalGeneralDefines.h"
//#include "sysTimer.h"
#include "sysUART.h"
//#include "pumpControl.h"
#include "phSensorControl.h"
//#include "tdsSensorControl.h"
#include "sysADC.h"
#include "sysPWM.h"
#include "motorControl.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void){
	
	//sysTimerSetup();
	//pumpSetup();
	//DDRB = B7;
	//PORTB &= ~B7;
	phEnableUart();
	
	sysAdcSetup();
	sysPwmSetup();
	motorSetup();
	//tdsEnableUart();
	sysUartInit(terminalUartIndex,TERMUBRR);
	sei();
	piDataReady = FALSE;
	phDataReady = FALSE;
	char temperature[5];
	char motor[3];
	unsigned int bufferIndex;
	while (1) {
		if (piDataReady == TRUE) {
			
			
			if (rxDataBuffer0[0] == 'T') {
				sysTransmitString(terminalUartIndex, " TDS Command -");
				if (rxDataBuffer0[1] == 'V') {
					sysTransmitString(terminalUartIndex, " Get Value -\n");
					for (bufferIndex = 2; bufferIndex < 7; bufferIndex++) {
						temperature[bufferIndex-2] = rxDataBuffer0[bufferIndex];
					}
					tdsGetValue(temperature);
				} else if (rxDataBuffer0[1] == '+') {
					sysTransmitString(terminalUartIndex, " Raise TDS -\n");
				} else if (rxDataBuffer0[1] == '-') {
				sysTransmitString(terminalUartIndex, " Lower TDS -\n");
				} else {
					sysTransmitString(terminalUartIndex, "Invalid Command.\n");
				}
				
			} else if (rxDataBuffer0[0] == 'P') {
				sysTransmitString(terminalUartIndex, " pH Command -");
				if (rxDataBuffer0[1] == 'V') {
					sysTransmitString(terminalUartIndex, " Get Value -");
					for (bufferIndex = 2; bufferIndex < 7; bufferIndex++) {
						temperature[bufferIndex-2] = rxDataBuffer0[bufferIndex];
					}
					//sysTransmitString(terminalUartIndex, temperature);
					phGetValue(temperature);
				} else if (rxDataBuffer0[1] == '+') {
					//sysTransmitString(terminalUartIndex, " Raise pH -\n");
					phDebugLedToggle(ON);
					// Turn on pH UP solenoid
				} else if (rxDataBuffer0[1] == '-') {
					//sysTransmitString(terminalUartIndex, " Lower pH -\n");
					phDebugLedToggle(OFF);
					// Turn on pH DOWN solenoid
				} else {
					sysTransmitString(terminalUartIndex, "Invalid Command.\n");
				}
							
			} else if (rxDataBuffer0[0] == 'L') {
				sysTransmitString(terminalUartIndex, " Light Command -");
				if (rxDataBuffer0[1] == '1') {
					sysTransmitString(terminalUartIndex, " On -\n");
					// Turn on Light
				} else if (rxDataBuffer0[1] == '0') {
					sysTransmitString(terminalUartIndex, " Off -\n");
					// Turn off Light
				} else if (rxDataBuffer0[1] == '+') {
					sysTransmitString(terminalUartIndex, " Raise Fixture -\n");
					// Raises light fixture x mm
					for (bufferIndex = 2; bufferIndex < 5; bufferIndex++) {
						motor[bufferIndex-2] = rxDataBuffer0[bufferIndex];
					}
					motorUp(motor);
				} else if (rxDataBuffer0[1] == '-') {
					sysTransmitString(terminalUartIndex, " Lower Fixture -\n");
					// Lowers lights fixture x mm
					for (bufferIndex = 2; bufferIndex < 5; bufferIndex++) {
						motor[bufferIndex-2] = rxDataBuffer0[bufferIndex];
					}
					motorDown(motor);
				} else if (rxDataBuffer0[1] == 'X') {
					sysTransmitString(terminalUartIndex, " Motor off -\n");
					// Turns motor off
					motorOff();
				} else {
					sysTransmitString(terminalUartIndex, "Invalid Command.\n");
				}				
			
			} else if (rxDataBuffer0[0] == 'F') {
				sysTransmitString(terminalUartIndex, " Fan Command -");
				if (rxDataBuffer0[1] == '+') {
					sysTransmitString(terminalUartIndex, " Speed Up -\n");
					// Increase Fan Duty Cycle
					Pwm2IncreaseSpeed();
				} else if (rxDataBuffer0[1] == '-') {
					sysTransmitString(terminalUartIndex, " Slow Down -\n");
					// Decrease Fan Duty Cycle
					Pwm2DecreaseSpeed();
				} else {
					sysTransmitString(terminalUartIndex, "Invalid Command.\n");
				}				
			
			} else if (rxDataBuffer0[0] == 'D') {
				sysTransmitString(terminalUartIndex, " Dehumidifier Command -");
				if (rxDataBuffer0[1] == '1') {
					sysTransmitString(terminalUartIndex, " On -\n");
					// Turn on Dehumidifier
				} else if (rxDataBuffer0[1] == '0') {
					sysTransmitString(terminalUartIndex, " Off -\n");
					// Turn off Dehumidifier
				} else {
					sysTransmitString(terminalUartIndex, "Invalid Command.\n");
				}				
				
			} else if (rxDataBuffer0[0] == 'W') {
				sysTransmitString(terminalUartIndex, " Water Pump Command -");
				if (rxDataBuffer0[1] == '1') {
					sysTransmitString(terminalUartIndex, " On - ");
					for (bufferIndex = 2; bufferIndex < piDataIndex-1; bufferIndex++) {
						sysTransmit(terminalUartIndex, rxDataBuffer0[bufferIndex]);
					}
					bufferIndex = 0;
					sysTransmitString(terminalUartIndex, "\n");
					// Turn on Water Pump for X minutes
					
				} else if (rxDataBuffer0[1] == '0') {
					sysTransmitString(terminalUartIndex, " Off -\n");
					// Turn off Water Pump
				} else {
					sysTransmitString(terminalUartIndex, "Invalid Command.\n");
				}				
			
			} else if (rxDataBuffer0[0] == 'A') {
				sysTransmitString(terminalUartIndex, " Air Pump Command -");
				if (rxDataBuffer0[1] == '1') {
					sysTransmitString(terminalUartIndex, " On -\n");
					// Turn on Air Pump
				} else if (rxDataBuffer0[1] == '0') {
					sysTransmitString(terminalUartIndex, " Off -\n");
					// Turn off Air Pump
				} else {
					sysTransmitString(terminalUartIndex, "Invalid Command. -\n");
				}				
						
			} else if (rxDataBuffer0[0] == 'E') {
				sysTransmitString(terminalUartIndex, " Water Temperature Command -");
				// Sends the water temperature data
				sysTransmitString(terminalUartIndex, sysAdcStart());
				sysTransmit(terminalUartIndex, '\n');
			} else {
				sysTransmitString(terminalUartIndex, "Invalid Command. -\n");
			}
			sysClearRxBuffer(terminalUartIndex);
			piDataIndex = 0;
			piDataReady = FALSE;
			UCSR0B |= (1<<RXCIE0);
		}
		_delay_us(1);
	}
	return 1;
}