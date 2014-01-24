/*
 * Automated Care and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 * spister@ucsc.edu
 * dgunny@ucsc.edu
 *  
 * File: pumpControl.h
 * Author: Stark Pister
 * Created: 2/19/13 10:12
 * 
 */ 

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#ifndef pumpControl_H_
#define pumpControl_H_

#define pumpTimer 0

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: pumpSetup
 * @param None.
 * @return None.
 * @remark Set pump pin to output and initialize high. 
 */
void pumpSetup(void);

/**
 * Function: pumpRun
 * @param runTime, Time in milliseconds to run the pump.
 * @return None.
 * @remark Starts a timer for runTime milliseconds and turns on the pump. 
 */
void pumpRun(unsigned int runTime);

/**
 * Function: pumpStop
 * @param None.
 * @return None.
 * @remark Turns off the pump. 
 */
void pumpStop(void);

#endif