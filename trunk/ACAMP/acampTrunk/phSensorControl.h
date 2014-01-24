/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * spister@ucsc.edu
 *  
 * File: phSensorControl.h
 * Author: Stark Pister
 * Created: 3/2/13 7:51
 * 
 */

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#ifndef phSensorControl_H_
#define phSensorControl_H_

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: phDebugLedToggle
 * @param state, ON to turn on, OFF to turn off.
 * @return None.
 * @remark Turns the debug LEDs on or off.
 */
void phDebugLedToggle(unsigned int state);

/**
 * Function: phFactoryReset
 * @param None.
 * @return None.
 * @remark Reset pH sensor to factory defaults.
 */
void phFactoryReset(void);

/**
 * Function: phCalibrate
 * @param phNum, pH value to calibrate to. 4,7,10.
 * @return None.
 * @remark Calibrates the pH sensor for 4pH, 7pH, or 10pH.
 */
void phCalibrate(unsigned int phNum);

/**
 * Function: phCalibrate
 * @param temperature, Temperature for pH sensor.
 * @return None.
 * @remark Gets a pH value from the pH sensor by sending a temperature for the pH
 * sensor to get a more accurate reading.
 */
//void phGetValue(char *temperature);
void phGetValue(void);

#endif