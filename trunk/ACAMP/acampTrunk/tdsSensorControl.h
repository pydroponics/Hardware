/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * spister@ucsc.edu
 * 
 * File: tdsSensorControl.h
 * Author: Stark Pister
 * Created: 3/5/2013 10:20
 * 
 */

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#ifndef tdsSensorControl_H_
#define tdsSensorControl_H_

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: tdsDebugLedToggle
 * @param state, ON to turn on, OFF to turn off.
 * @return None.
 * @remark Turns the debug LEDs on or off.
 */
void tdsDebugLedToggle(unsigned int state);

/**
 * Function: tdsFactoryReset
 * @param None.
 * @return None.
 * @remark Reset TDS sensor to factory defaults.
 */
void tdsFactoryReset(void);

/**
 * Function: tdsCalibrate
 * @param tdsNum, TDS calibration number. 1,2,3,4
 * @return None.
 * @remark Calibrates the TDS sensor for sensor type, Dry Cal, 3000 us, and 220 us.
 */
void tdsCalibrate(unsigned int tdsNum);

/**
 * Function: tdsGetValue
 * @param temperature, Temperature for TDS sensor.
 * @return None.
 * @remark Gets a TDS value from the TDS sensor by sending a temperature for the TDS
 * sensor to get a more accurate reading.
 */
void tdsGetValue(void);

void tdsContinuous(unsigned int state);

#endif