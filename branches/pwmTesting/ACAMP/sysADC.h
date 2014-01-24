/*
 * Automated Control and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 * dgunny@ucsc.edu
 *  
 * File: sysADC.h
 * Author: dgunny
 * Created: 04/06/2013 7:51PM
 */ 



#ifndef sysADC_H_
#define sysADC_H_
/**
 * Function: sysAdcSetup
 * @param None.
 * @return AdcResult in char form
 * @remark Sets up the ADC with Auto-Trigger Enabled
 */
void sysAdcSetup(void);


char* sysAdcStart(void);

#endif /* SYSADC_H_ */