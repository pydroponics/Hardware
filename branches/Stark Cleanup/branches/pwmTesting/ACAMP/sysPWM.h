/*
 * Automated Control and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 * dgunny@ucsc.edu
 *  
 * File: sysPWM.h
 * Author: dgunny
 * Created: 03/30/2013 8:45
 */ 


#ifndef sysPWM_H_
#define sysPWM_H_

/**
 * Function: sysPwmSetup
 * @param None.
 * @return None.
 * @remark Initialzes the PWM to 7.8125 kHz with an interrupt at 0xC0
 */
void sysPwmSetup(void);




#endif /* SYSPWM_H_ */