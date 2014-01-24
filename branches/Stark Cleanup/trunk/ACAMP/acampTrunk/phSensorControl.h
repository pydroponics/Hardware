/*
 * Automated Care and Monitoring of Plants
 * CMPE129
 * Senior Design Group
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

#define phUartIndex 2

#define FOSC 16000000
#define PHBAUD 38400
#define PHUBRR FOSC/16/PHBAUD-1

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: phEnableUart
 * @param None.
 * @return None.
 * @remark Enable UART for pH sensor communication.
 */
void phEnableUart(void);

/**
 * Function: phDebugLedToggle
 * @param state, ON to turn on, OFF to turn off.
 * @return None.
 * @remark Turns the debug LEDs on or off.
 */
void phDebugLedToggle(unsigned int state);

/**
 * Function: phFirmwareRev
 * @param None.
 * @return None.
 * @remark Displays the revision number of the stamp.
 */
//char* phFirmwareRev(void);

/**
 * Function: phFactoryReset
 * @param None.
 * @return ERROR or SUCCESS
 * @remark Reset pH sensor to factory defaults.
 */
unsigned int phFactoryReset(void);

/**
 * Function: phCalibrate
 * @param phNum, pH value to calibrate to. 4,7,10.
 * @return ERROR or SUCCESS
 * @remark Calibrates the pH sensor for 4pH, 7pH, or 10pH.
 */
unsigned int phCalibrate(unsigned int phNum);

/**
 * Function: phCalibrate
 * @param temperature, Temperature for pH sensor.
 * @return phValue, pH value.
 * @remark Gets a pH value from the pH sensor by sending a temperature for the pH
 * sensor to get a more accurate reading. Send a 0 for temperature to do an
 * uncalibrated reading.
 */
unsigned int phGetValue(char *temperature);

/**
 * Function: phContinuousModeToggle
 * @param state, ON to turn on, OFF to turn off.
 * @return None.
 * @remark Toggles continuous pH reading mode on or off.
 */
void phContinuousModeToggle(unsigned int state);

#endif