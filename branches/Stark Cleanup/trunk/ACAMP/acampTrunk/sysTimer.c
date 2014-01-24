/*
 * Automated Care and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 * spister@ucsc.edu
 * dgunny@ucsc.edu
 *  
 * File: sysTimer.c
 * Author: Stark Pister
 * Created: 2/18/13 5:37
 * Credit to Max Dunne for the base code.
 */ 

#include "GlobalGeneralDefines.h"
#include "sysTimer.h"
#include <avr/interrupt.h>

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define NUM_TIMERS 16

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
static unsigned int Timer_Array[NUM_TIMERS];
static unsigned int TimerActiveFlags;
static unsigned int TimerEventFlags;
static unsigned int sysTime;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/****************************************************************************
Function:
	sysTimerSetup

Parameters:
	None.

Returns:
	None.

Description:
	Initialize timer flags. Initialize and enable TIMER0. Enable interrupts.
	 
Notes:
	CPU clock			- 16 MHz
	Timer (prescaler)	- 250 kHz (1/64)
	Interrupt			- 1 kHz
	Timer0 counts to 249 at 250 kHz, providing interrupts every 1 millisecond.

Authors:
	Stark Pister, 2/18/13
 ****************************************************************************/

void sysTimerSetup(void) {
    TimerActiveFlags = 0;
    TimerEventFlags = 0;
    sysTime = 0;
    OCR0A = 0xF9;
    TIMSK0 |= ( 1 << OCIE0A );
    TCCR0A |= ( 1 << WGM01 );
    TCCR0B |= (( 1 << CS01 ) | ( 1 << CS00 ));
    sei();
}

/****************************************************************************
Function:
	sysGetTime

Parameters:
	None.

Returns:
	sysTime

Description:
	Returns time in milliseconds since sysTimerSetup was called.

Notes:
	None.

Author:
    Max Dunne, 1/8/12
	 
Edited:
	Stark Pister, 2/18/13
 ****************************************************************************/

unsigned int sysGetTime(void) {
    return sysTime;
}

/****************************************************************************
Function:
	sysTimerInit

Parameters:
	unsigned char timerIndex	- The timer to set and start.
	unsigned int countTime		- The number of milliseconds to be counted.

Returns:
	ERROR						- If the requested timer does not exist.
	SUCCESS						- Otherwise.

Description:
	Sets the time in milliseconds for the timer to count by setting the
	appropriate location in Timer_Array to countTime.
	Clears the appropriate TimerEventFlags bit to reset the timer's 
	completed state.
	Starts the timer by setting the appropriate TimerActiveFlags bit.

Notes:
	Functionally combines sysTimerSet, sysTimerClear, and sysTimerStart.

Author:
	Max Dunne, 11/15/11

Edited:
	Stark Pister, 2/18/13
 ****************************************************************************/

char sysTimerInit(unsigned char timerIndex, unsigned int countTime) {
    if (timerIndex >= NUM_TIMERS) {
        return ERROR;
	}	
    Timer_Array[timerIndex] = countTime;
    TimerEventFlags &= ~(1 << timerIndex);
    TimerActiveFlags |= (1 << timerIndex);
    return SUCCESS;
}

/****************************************************************************
Function:
	sysTimerSet

Parameters:
	unsigned char timerIndex	- The timer to set.
	unsigned int countTime		- The number of milliseconds to be counted.

Returns:
	ERROR						- If the requested timer does not exist.
	SUCCESS						- Otherwise.

Description:
	Sets the time in milliseconds for the timer to count by setting the
	appropriate location in Timer_Array to countTime.

Notes:
	Does not start the timer.

Author:
	Max Dunne, 11/15/11

Edited:
	Stark Pister, 2/18/13
 ****************************************************************************/

char sysTimerSet(unsigned char timerIndex, unsigned int countTime) {
    if (timerIndex >= NUM_TIMERS) {
        return ERROR;
	}		
    Timer_Array[timerIndex] = countTime;
    return SUCCESS;
}

/****************************************************************************
Function:
	sysClearTimer

Parameters:
	unsigned char timerIndex	- The timer to clear.

Returns:
	ERROR						- If the requested timer does not exist.
	SUCCESS						- Otherwise.

Description:
	Clears the appropriate TimerEventFlags bit to reset the timer's
	completed state.

Notes:
	Does not start or stop the timer.

Author:
	Max Dunne, 11/15/11

Edited:
	Stark Pister, 2/18/13
 ****************************************************************************/

char sysClearTimer(unsigned char timerIndex) {
    if (timerIndex >= NUM_TIMERS) {
        return ERROR;
	}	
    TimerEventFlags &= ~(1 << timerIndex);
    return SUCCESS;
}

/****************************************************************************
Function:
	sysTimerStart

Parameters;
	unsigned char timerIndex	- The timer to start.

Returns:
	ERROR						- If the requested timer does not exist.
	SUCCESS						- Otherwise.

Description:
	Starts the timer by setting the appropriate TimerActiveFlags bit.

Notes:
	No effect on already active timers.

Author:
	Max Dunne, 11/15/11

Edited:
	Stark Pister, 2/18/13
 ****************************************************************************/

char sysTimerStart(unsigned char timerIndex) {
    if (timerIndex >= NUM_TIMERS) {
        return ERROR;
	}	
    TimerActiveFlags |= (1 << timerIndex);
    return SUCCESS;
}

/****************************************************************************
Function:
	sysTimerStop

Parameters:
	unsigned char timerIndex	- The timer to stop.

Returns:
	ERROR						- If the requested timer does not exist.
	SUCCESS						- Otherwise.

Description:
	Stop the timer by clearing the appropriate TimerActiveFlags bit.

Notes:
	No effect on already inactive timers.

Author:
	Max Dunne, 11/15/11

Edited:
	Stark Pister, 2/18/13
 ****************************************************************************/

char sysTimerStop(unsigned char timerIndex) {
    if (timerIndex >= NUM_TIMERS) {
        return ERROR;
	}	
    TimerActiveFlags &= ~(1 << timerIndex);
    return SUCCESS;
}

/****************************************************************************
Function:
	IsTimerActive

Parameters:
	unsigned char timerIndex	- The timer to check for activity.

Returns:
	ERROR						- If the requested timer does not exist.
	TIMER_NOT_ACTIVE			- If the timer is not active.
	TIMER_ACTIVE				- If the timer is active.

Description:
	Returns the activity state of the timer.

Notes:
	TIMER_ACTIVE		= 1
	TIMER_NOT_ACTIVE	= 0

Author:
	Max Dunne, 11/15/11

Edited:
	Stark Pister, 2/18/13
 ****************************************************************************/

char IsTimerActive(unsigned char timerIndex) {
    if (timerIndex >= NUM_TIMERS) {
        return ERROR;
	}	
    if ((TimerActiveFlags & (1 << timerIndex)) != 0) {
        return TIMER_ACTIVE;
    } else {
        return TIMER_NOT_ACTIVE;
    }
}

/****************************************************************************
Function:
	IsTimerExpired

Parameters:
	unsigned char timerIndex	- The timer to check for expiration.

Returns:
	ERROR						- If the requested timer does not exist.
	TIMER_NOT_EXPIRED			- If the timer is not expired.
	TIMER_EXPIRED				- If the timer is expired.

Description:
	Returns the expiration state of the timer. 

Notes:
	TIMER_EXPIRED		= 1
	TIMER_NOT_EXPIRED	= 0
	
Author:
	Max Dunne, 11/15/11

Edited:
	Stark Pister, 2/18/13
 ****************************************************************************/

char IsTimerExpired(unsigned char timerIndex) {
    if (timerIndex >= NUM_TIMERS) {
        return ERROR;
	}	
    if ((TimerEventFlags & (1 << timerIndex)) != 0) {
        return TIMER_EXPIRED;
    } else {
        return TIMER_NOT_EXPIRED;
    }
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

/****************************************************************************
Function:
    TIMER0 CompareA ISR

Parameters:
    None.

Returns:
    None.

Description:
    This is the interrupt handler to support the timer module.
    It will increment time, to maintain the functionality of the
    GetTime() timer and it will check through the active timers,
    decrementing each active timers count, if the count goes to 0, it
    will set the associated event flag and clear the active flag to
    prevent further counting.

Notes:
    None.

Author:
    Max Dunne 11/15/11
	 
Adapted By:
	Stark Pister 2/18/13
 ****************************************************************************/

ISR (TIMER0_COMPA_vect) {
	sysTime++;
	int CurTimer = 0;
	if (TimerActiveFlags != 0) {
		for (CurTimer = 0; CurTimer < NUM_TIMERS; CurTimer++) {
			if ((TimerActiveFlags & (1 << CurTimer)) != 0) {
				if (--Timer_Array[CurTimer] == 0) {
					TimerEventFlags |= (1 << CurTimer);
					TimerActiveFlags &= ~(1 << CurTimer);
				}
			}
		}
	}
}