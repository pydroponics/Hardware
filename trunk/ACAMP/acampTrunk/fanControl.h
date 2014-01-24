/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * dgunny@ucsc.edu
 * spister@ucsc.edu
 *  
 * File: fanControl.h
 * Author: Daniel Gunny
 * Created: 03/30/13 20:45
 *
 */ 

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#ifndef fanControl_H_
#define fanControl_H_

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: fanSetup
 * @param None.
 * @return None.
 * @remark Setup for fan PWM systems.
 */
void fanSetup(void);

/**
 * Function: fanIncreaseExhaustSpeed
 * @param None.
 * @return None.
 * @remark Increases exhaust fan speed.
 */
void fanIncreaseExhaustSpeed(void);

/**
 * Function: fanDecreaseExhaustSpeed
 * @param None.
 * @return None.
 * @remark Decreases exhaust fan speed.
 */
void fanDecreaseExhaustSpeed(void);

/**
 * Function: fanIncreaseIntakeSpeed
 * @param None.
 * @return None.
 * @remark Increases intake fan speed.
 */
void fanIncreaseIntakeSpeed(void);

/**
 * Function: fanDecreaseIntakeSpeed
 * @param None.
 * @return None.
 * @remark Decreases intake fan speed.
 */
void fanDecreaseIntakeSpeed(void);

/**
 * Function: fanIncreaseHoodSpeed
 * @param None.
 * @return None.
 * @remark Increases Hood fan speed.
 */
void fanIncreaseHoodSpeed(void);

/**
 * Function: fanDecreaseHoodSpeed
 * @param None.
 * @return None.
 * @remark Decreases Hood fan speed.
 */
void fanDecreaseHoodSpeed(void);

void exhaustSpeed(char* speed);

void intakeSpeed(char* speed);

void hoodSpeed(char* speed);

#endif