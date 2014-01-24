/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * spister@ucsc.edu
 * dgunny@ucsc.edu
 *  
 * File: sysRelay.h
 * Authors: Stark Pister, Danny Gunny
 * Created: 2/19/13 10:12
 * Revised: 05/17/13 9:00
 */ 

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#ifndef pumpControl_H_
#define pumpControl_H_

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: sysRelaySetup
 * @param None.
 * @return None.
 * @remark Set relay pin to output and initialize high. 
 */
void sysRelaySetup(void);

/**
 * Function: dehumidifierOn
 * @param None.
 * @return None.
 * @remark Turns on the dehumidifier.
 */
void dehumidifierOn(void);

/**
 * Function: dehumidifierOff
 * @param None.
 * @return None.
 * @remark Turns off the dehumidifier.
 */
void dehumidifierOff(void);

/**
 * Function: waterPumpOn
 * @param None.
 * @return None.
 * @remark Turns on the water pump.
 */
void waterPumpOn(void);

/**
 * Function: waterPumpOff
 * @param None.
 * @return None.
 * @remark Turns off the water pump. 
 */
void waterPumpOff(void);

/**
 * Function: airPumpOn
 * @param None.
 * @return None.
 * @remark Turns on the air pump.
 */
void airPumpOn(void);

/**
 * Function: airPumpOff
 * @param None.
 * @return None.
 * @remark Turns off the air pump.
 */
void airPumpOff(void);

/**
 * Function: lightOn
 * @param None.
 * @return None.
 * @remark Turns on the light.
 */
void lightOn(void);

/**
 * Function: lightOff
 * @param None.
 * @return None.
 * @remark Turns off the light.
 */
void lightOff(void);

#endif