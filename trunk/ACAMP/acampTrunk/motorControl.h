/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * spister@usc.edu
 * dgunny@ucsc.edu
 *  
 * File: motorControl.h
 * Author: Daniel Gunny
 * Created: 4/23/13 10:20
 *
 */ 

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#ifndef motorControl_H_
#define motorControl_H_

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: motorSetup
 * @param None.
 * @return None.
 * @remark Sets up the motor inputs and outputs.
 */
void motorSetup(void);

/**
 * Function: motorDown
 * @param char* distance	- Distance in mm to lower the light.
 * @return None.
 * @remark Lowers the system by a distance millimeters.
 */
void motorDown(char* distance);

/**
 * Function: motorUp
 * @param char* distance	- Distance in mm to raise the light.
 * @return None.
 * @remark Raise the system by distance millimeters.
 */
void motorUp(char* distance);

/**
 * Function: motorReset
 * @param None.
 * @return None.
 * @remark Resets the light hood to position 0 (Top of the box).
 */
void motorReset(void);

/**
 * Function: lightHeight
 * @param None.
 * @return height, Current height of the light.
 * @remark Sends the user the current light height.
 */
char* lightHeight(void);

#endif