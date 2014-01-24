/*
 * Automated Control and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 *  dgunny@ucsc.edu
 *  
 * File: motorControl.c
 * Author: dgunny
 * Created: 4/23/2013 10:20
 */ 


#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

/**
 * Function: motorSetup
 * @param None.
 * @return None.
 * @remark Initializes the motor
 * @remark Uses pins 24, 23, 22
 * @remark Sets pins low
 * @remark Pin 24: PWM = PA2
 * @remark Pin 23: Direction = PA1
 * @remark Pin 22: Brake = PA0
 */
void motorSetup();


/**
 * Function: motorOff
 * @param None.
 * @return None.
 * @remark Stops the motor
 */
void motorOff();


/**
 * Function: motorForward
 * @param None.
 * @return None.
 * @remark Spins the motor forward
 */
void motorForward();

/**
 * Function: motorReverse
 * @param None.
 * @return None.
 * @remark Spins the motor in reverse
 */
void motorReverse();

/**
 * Function: motorUp
 * @param Distance change desired in millimeters
 * @return None.
 * @remark Raises the light the distance desired
 */
void motorUp(int mm);


/**
 * Function: motorDown
 * @param Distance change desired in millimeters
 * @return None.
 * @remark Lowers the light the distance desired
 */
void motorDown(int mm);

#endif /* MOTORCONTROL_H_ */