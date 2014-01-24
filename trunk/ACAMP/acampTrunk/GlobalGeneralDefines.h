/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * spister@ucsc.edu
 * dgunny@ucsc.edu
 *  
 * File: GlobalGeneralDefines.h
 * Author: Stark Pister
 * Created: 2/18/13 10:30
 *
 */ 

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
#ifndef GlobalGeneralDefines_H
#define GlobalGeneralDefines_H

#define ARRAY_ELEMENTS(x)  (sizeof(x) / sizeof(x[0]))

// Serial Terminal Communication
#define F_CPU 16000000
#define FOSC 16000000
#define BAUD 38400
#define SYSUBRR FOSC/16/BAUD-1

#define terminalUartIndex 0
#define tdsUartIndex 1
#define phUartIndex 2
#define waterTempIndex 0
#define photoDiodeIndex 1

// Boolean Operators
#define SUCCESS 0
#define ERROR -1
#define ON 1
#define OFF 0
#define TRUE 1
#define FALSE 0

#define encoderCount 4.652

//Variable defines
#define encoderCount 4.652

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: sysReverseArray
 * @param sourceArray[], Character array to reverse.
 * @param sourceArrayLength, Length of sourceArray.
 * @return None.
 * @remark Reverses the direction of a character array. 
 */
void sysReverseArray(char sourceArray[], unsigned int arrayLength);

/**
 * Function: sysZeroArray
 * @param charArray[], Character array to zero.
 * @param charArrayLength, Length of charArray.
 * @return None.
 * @remark Zero's every char in the array.
 */
void sysZeroArray(char charArray[], unsigned int charArrayLength);

/**
 * Function: sysItoa
 * @param intValue, Int to convert to alphabet.
 * @return intString, String converted from int.
 * @remark Converts an integer to alphabet.
 */
char* sysItoa(unsigned int intValue);

#endif