/*
 * Automated Control and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 *	spister@ucsc.edu
 *  
 *  
 * File: tdsSensorControl.h
 * Author: spister
 * Created: 3/5/2013 10:20
 * 
 */

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#ifndef tdsSensorControl_H_
#define tdsSensorControl_H_

#define tdsUsartIndex 1
#define tdsAckReqFlag ackReqFlag1
#define tdsRxDataBuffer rxDataBuffer1
#define tdsTxDataBuffer txDataBuffer1

#define FOSC 16000000
#define TDSBAUD 38400
#define TDSUBRR FOSC/16/TDSBAUD-1

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: tdsEnableUsart
 * @param None.
 * @return None.
 * @remark Enable USART for TDS sensor communication.
 */
void tdsEnableUsart(void);

/**
 * Function: tdsDebugLedToggle
 * @param state, ON to turn on, OFF to turn off.
 * @return None.
 * @remark Turns the debug LEDs on or off.
 */
void tdsDebugLedToggle(unsigned int state);

/**
 * Function: tdsFirmwareRev
 * @param None.
 * @return None.
 * @remark Displays the revision number of the stamp.
 */
//char* tdsFirmwareRev(void);
 

/**
 * Function: tdsFactoryReset
 * @param None.
 * @return ERROR or SUCCESS
 * @remark Reset TDS sensor to factory defaults.
 */
unsigned int tdsFactoryReset(void);

/**
 * Function: tdsCalibrate
 * @param tdsNum, TDS calibration number. 1,2,3,4
 * @return ERROR or SUCCESS
 * @remark Calibrates the TDS sensor for sensor type, Dry Cal, 3000 us, and 220 us.
 */
unsigned int tdsCalibrate(unsigned int tdsNum);

/**
 * Function: tdsGetValue
 * @param temperature, Temperature for TDS sensor.
 * @return tdsValue, TDS value.
 * @remark Gets a TDS value from the TDS sensor by sending a temperature for the TDS
 * sensor to get a more accurate reading. Send a 0 for temperature to do an
 * uncalibrated reading.
 */
int tdsGetValue(double temperature, char *response);

/**
 * Function: tdsContinuousModeToggle
 * @param state, ON to turn on, OFF to turn off.
 * @return None.
 * @remark Toggles continuous TDS reading mode on or off.
 */
void tdsContinuousModeToggle(unsigned int state);

#endif