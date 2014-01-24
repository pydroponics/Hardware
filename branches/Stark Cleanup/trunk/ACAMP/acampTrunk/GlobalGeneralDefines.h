/*
 * Automated Care and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 * spister@ucsc.edu
 *  
 *  
 * File: GlobalGeneralDefines.h
 * Author: Stark Pister
 * Created: 2/18/13 10:30
 */ 

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
#ifndef GlobalGeneralDefines_H
#define GlobalGeneralDefines_H

#define ARRAY_ELEMENTS(x)  (sizeof(x) / sizeof(x[0]))
#define PIN_HIGH(var, mask) ((var) |= (uint8_t)(1 << mask))
#define PIN_LOW(var, mask) ((var) &= (uint8_t)~(1 << mask))

// Serial Terminal Communication
#define F_CPU 16000000
#define FOSC 16000000
#define TERMBAUD 38400
#define TERMUBRR FOSC/16/TERMBAUD-1
#define terminalUartIndex 0

// Boolean Operators
#define SUCCESS 0
#define ERROR -1
#define ON 1
#define OFF 0
#define TRUE 1
#define FALSE 0

//Port Defines
#define B0 0x01
#define B1 0x02
#define B2 0x04
#define B3 0x08
#define B4 0x10
#define B5 0x20
#define B6 0x40
#define B7 0x80

#define C0 0x01
#define C1 0x02
#define C2 0x04
#define C3 0x08
#define C4 0x10
#define C5 0x20
#define C6 0x40
#define C7 0x80

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: sysRightShiftArray
 * @param charArray[], Character array to shift right.
 * @param charArrayLength, Length of charArray.
 * @return None.
 * @remark Logic right shift on an array.
 */
void sysRightShiftArray(char charArray[], unsigned int charArrayLength);

/**
 * Function: sysLeftShiftArray
 * @param charArray[], Character array to shift left.
 * @param charArrayLength, Length of charArray.
 * @param newChar, Character to shift in.
 * @return None.
 * @remark Logic left shift on an array. Shifts newChar into the LSB.
 */
void sysLeftShiftArray(char charArray[], unsigned int charArrayLength, char newChar);

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
 * Function: sysCopyArray
 * @param sourceArray[], Character array to copy.
 * @param sourceArrayLength, Length of sourceArray.
 * @param destinationArray[], Character array to clear and update.
 * @param destinationArrayLength, Length of destinationArray.
 * @return ERROR or SUCCESS
 * @remark Clears the destinationArray and copies the sourceArray into it.
 */
unsigned int sysCopyArray(char sourceArray[], unsigned int sourceArrayLength, char destinationArray[], unsigned int destinationArrayLength);

/**
 * Function: sysCompareArray
 * @param firstArray[], Character array to compare.
 * @param firstArrayLength, Length of firstArray.
 * @param secondArray[], Character array to compare.
 * @param secondArrayLength, Length of secondArray.
 * @return ERROR or TRUE or FALSE
 * @remark Compares the first and second charArrays.
 */
unsigned int sysCompareArray(char firstArray[], unsigned int firstArrayLength, char secondArray[], unsigned int secondArrayLength);

#endif