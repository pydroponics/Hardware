/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * dgunny@ucsc.edu
 * spister@ucsc.edu
 *  
 * File: sysADC.h
 * Author: Daniel Gunny
 * Created: 04/06/13 19:51
 *
 */ 

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#ifndef sysADC_H_
#define sysADC_H_

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: sysAdcSetup
 * @param None.
 * @return None.
 * @remark Setup for two ADC systems, Water Temperature and Photo Diode.
 */
void sysAdcSetup(void);

/**
 * Function: sysAdcGetValue
 * @param adcIndex, Index of ADC to use.
 * @return adcValue, Value of the ADC read.
 * @remark Gets a value for the corresponding ADC input.
 */
char* sysAdcGetValue(unsigned int adcIndex);

#endif