/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * spister@ucsc.edu
 * dgunny@ucsc.edu
 *  
 * File: GlobalGeneralDefines.c
 * Author: Stark Pister
 * Created: 2/23/13 9:22
 *
 */ 

#include "GlobalGeneralDefines.h"
#include <avr/io.h>
#include <stdlib.h>

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
int arrayIndex;
unsigned char holdChar;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/****************************************************************************
Function:
	sysReverseArray

Parameters:
	char sourceArray[]					- Character array to reverse.
	unsigned int arrayLength			- Length of sourceArray.

Returns:
	None.
	
Description:
	Reverses the direction of a character array. 
	 
Notes:
	None.

Authors:
	Danny Gunny, 3/8/13
 ****************************************************************************/

void sysReverseArray(char sourceArray[], unsigned int arrayLength) {
	unsigned int inverseIndex = arrayLength - 1;
	for(arrayIndex = 0; arrayIndex < (arrayLength/2); arrayIndex++) {
		holdChar = sourceArray[arrayIndex];
		sourceArray[arrayIndex] = sourceArray[inverseIndex];
		sourceArray[inverseIndex] = holdChar;
		inverseIndex--;
	}
}

/****************************************************************************
Function:
	sysZeroArray

Parameters:
	char charArray[]				- Character array to zero.
	unsigned int charArrayLength	- Length of charArray.

Returns:
	None.

Description:
	Zero's every char in the array.
	 
Notes:
	None.

Authors:
	Stark Pister, 2/24/13
 ****************************************************************************/

void sysZeroArray(char charArray[], unsigned int charArrayLength) {
	for (arrayIndex = 0; arrayIndex<charArrayLength; arrayIndex++) {
		charArray[arrayIndex] = '\0';
	}	
}

/****************************************************************************
Function:
	sysItoa

Parameters:
	char intValue				- Int to convert to alphabet.

Returns:
	char *intString				- String converted from int.

Description:
	Converts an integer to alphabet.
	 
Notes:
	None.

Authors:
	Danny Gunny, 5/21/13
 ****************************************************************************/

char* sysItoa(unsigned int intValue) {
	static char intString[5];
	intString[4] = '\0';
	for(arrayIndex = 3; arrayIndex >= 0; arrayIndex--) {
		intString[arrayIndex] = '0' + intValue%10;
		intValue /= 10;
	}	
	return intString;
}