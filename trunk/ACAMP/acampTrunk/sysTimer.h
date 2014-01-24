/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * spister@ucsc.edu
 * dgunny@ucsc.edu
 *  
 * File: sysTimer.h
 * Author: Stark Pister
 * Created: 2/18/13 5:40
 * Credit to Max Dunne for the base code.
 */ 

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
#ifndef sysTimer_H
#define sysTimer_H

#define TIMER_ACTIVE 1
#define TIMER_EXPIRED 1

#define TIMER_NOT_ACTIVE 0
#define TIMER_NOT_EXPIRED 0

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: sysTimerSetup
 * @param None.
 * @return None.
 * @remark Initialize timer flags. Initialize and enable TIMER0. Enable 
 * interrupts. 
 */
void sysTimerSetup(void);

/**
 * Function: sysGetTime
 * @param None.
 * @return sysTime, Time in milliseconds since setup.
 * @remark Returns time in milliseconds since sysTimerSetup was called.
 */
unsigned int sysGetTime(void);

/**
 * Function: sysTimerInit
 * @param timerIndex, The timer to set and start.
 * @param countTime, The number of milliseconds to be counted.
 * @return ERROR or SUCCESS
 * @remark Sets the time in milliseconds for the timer to count by setting the
 * appropriate location in Timer_Array to countTime. Clears the appropriate 
 * TimerEventFlags bit to reset the timer's completed state. Starts the timer
 * by setting the appropriate TimerActiveFlags bit.
 */
char sysTimerInit(unsigned char timerIndex, unsigned int countTime);

/**
 * Function: sysTimerSet
 * @param timerIndex, The timer to set.
 * @param countTime, The number of milliseconds to be counted.
 * @return ERROR or SUCCESS
 * @remark Sets the time in milliseconds for the timer to count by setting the
 * appropriate location in Timer_Array to countTime.
 */
char sysTimerSet(unsigned char timerIndex, unsigned int countTime);

/**
 * Function: sysClearTimer
 * @param timerIndex, The timer to clear.
 * @return ERROR or SUCCESS
 * @remark Clears the appropriate TimerEventFlags bit to reset the timer's
 * completed state.
 */
char sysClearTimer(unsigned char timerIndex);

/**
 * Function: sysTimerStart
 * @param timerIndex, The timer to start.
 * @return ERROR or SUCCESS
 * @remark Starts the timer by setting the appropriate TimerActiveFlags bit.
 */
char sysTimerStart(unsigned char timerIndex);

/**
 * Function: sysTimerStop
 * @param timerIndex, The timer to stop.
 * @return ERROR or SUCCESS
 * @remark Stop the timer by clearing the appropriate TimerActiveFlags bit.
 */
char sysTimerStop(unsigned char timerIndex);

/**
 * Function: IsTimerActive
 * @param timerIndex, The timer to check for activity.
 * @return TIMER_ACTIVE, TIMER_NOT_ACTIVE or ERROR
 * @remark Returns the activity state of the timer.
 */
char IsTimerActive(unsigned char timerIndex);

/**
 * Function: IsTimerExpired
 * @param timerIndex, The timer to check for expiration.
 * @return TIMER_NOT_EXPIRED, TIMER_EXPIRED or ERROR
 * @remark Returns the expiration state of the timer. 
 */
char IsTimerExpired(unsigned char timerIndex);

#endif
