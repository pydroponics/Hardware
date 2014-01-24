/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * dgunny@ucsc.edu
 * spister@ucsc.edu
 * 
 * File: sysSolenoid.h
 * Author: Daniel Gunny
 * Created: 05/14/13 11:19
 *
 */ 

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#ifndef sysSolenoid_H_
#define sysSolenoid_H_

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: sysSolenoidSetup
 * @param None.
 * @return None.
 * @remark Sets up all four solenoids.
 */
void sysSolenoidSetup(void);

/**
 * Function: phUp
 * @param duration, Duration to run the solenoid.
 * @return None.
 * @remark Turns on pH Up solenoid for duration ms.
 */
void phUp(char* duration);

/**
 * Function: phDown
 * @param duration, Duration to run the solenoid.
 * @return None.
 * @remark Turns on pH Down solenoid for duration ms.
 */
void phDown(char* duration);

/**
 * Function: tdsUp
 * @param duration, Duration to run the solenoid.
 * @return None.
 * @remark Turns on tds Up solenoid for duration ms.
 */
void tdsUp(char* duration);

/**
 * Function: tdsDown
 * @param duration, Duration to run the solenoid.
 * @return None.
 * @remark Turns on tds Down solenoid for duration ms.
 */
void tdsDown(char* duration);

#endif