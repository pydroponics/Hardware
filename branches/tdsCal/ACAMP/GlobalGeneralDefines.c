/*
 * Automated Control and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 *	spister@ucsc.edu
 *  
 *  
 * File: GlobalGeneralDefines.c
 * Author: spister
 * Created: 2/23/2013 9.22
 */ 

#include "GlobalGeneralDefines.h"
#include <avr/io.h>

/****************************************************************************
Function:
	sysRightShiftArray

Parameters:
	char charArray[]				- Character array to shift right.
	unsigned int charArrayLength	- Length of charArray.

Returns:
	None.

Description:
	Logic right shift on an array.
	 
Notes:
	Shifts in a 0 to the MSB.

Authors:
	Stark Pister, 2013.2.23
 ****************************************************************************/

void sysRightShiftArray(char charArray[], unsigned int charArrayLength) {
	unsigned int index = charArrayLength;
	unsigned int arrayIndex;
	for (arrayIndex = 0; arrayIndex<index; arrayIndex++){
		if (arrayIndex == index-1) {
			charArray[arrayIndex] = 0;
		} else {
			charArray[arrayIndex] = charArray[arrayIndex+1];
		}
	}
}

/****************************************************************************
Function:
	sysLeftShiftArray

Parameters:
	char charArray[]				- Character array to shift left.
	unsigned int charArrayLength	- Length of charArray.
	char newChar					- Character to shift in.

Returns:
	None.

Description:
	Logic left shift on an array. Shifts newChar into the LSB.
	 
Notes:
	Data lost if MSB is non-zero. Breaks on empty array.

Authors:
	Stark Pister, 2013.2.23
 ****************************************************************************/

void sysLeftShiftArray(char charArray[], unsigned int charArrayLength, char newChar) {
	unsigned int index = charArrayLength;
	unsigned int arrayIndex;
	for (arrayIndex = 1; arrayIndex<index; arrayIndex++) {
		charArray[index-arrayIndex] = charArray[index-arrayIndex-1];
	}
	charArray[0] = newChar;
}

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
	Danny Gunny, 2013.3.8
 ****************************************************************************/

void sysReverseArray(char sourceArray[], unsigned int arrayLength) {
	unsigned int inverseIndex = arrayLength - 1;
	unsigned char holdChar;
	unsigned int arrayIndex;
	for(arrayIndex = 0; arrayIndex<(arrayLength/2); arrayIndex++) {
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
	Stark Pister, 2013.2.24
 ****************************************************************************/

void sysZeroArray(char charArray[], unsigned int charArrayLength) {
	int arrayIndex;
	for (arrayIndex = 0; arrayIndex<charArrayLength; arrayIndex++) {
		charArray[arrayIndex] = 0;
	}	
}

/****************************************************************************
Function:
	sysCopyArray

Parameters:
	char sourceArray[]					- Character array to copy.
	unsigned int sourceArrayLength		- Length of sourceArray.
	char destinationArray[]				- Character array to clear and update.
	unsigned int destinationArrayLength	- Length of destinationArray.

Returns:
	ERROR								- If destination array is too small.
	SUCCESS								- Otherwise.

Description:
	Clears the destinationArray and copies the sourceArray into it.
	 
Notes:
	None.

Authors:
	Stark Pister, 2013.2.24
 ****************************************************************************/

unsigned int sysCopyArray(char sourceArray[], unsigned int sourceArrayLength, char destinationArray[], unsigned int destinationArrayLength) {
	if (sourceArrayLength>destinationArrayLength) {
		return ERROR;
	} else {
		sysZeroArray(destinationArray, destinationArrayLength);
		int arrayIndex;
		for (arrayIndex = 0; arrayIndex<sourceArrayLength; arrayIndex++) {
			destinationArray[arrayIndex] = sourceArray[arrayIndex];
		}
	}
	return SUCCESS;
}

/****************************************************************************
Function:
	sysCompareArray

Parameters:
	char firstArray[]					- Character array to compare.
	unsigned int firstArrayLength		- Length of firstArray.
	char secondArray[]					- Character array to compare.
	unsigned int secondArrayLength		- Length of secondArray.

Returns:
	ERROR								- If arrays are differing length.
	TRUE								- If arrays contain the same chars.
	FALSE								- If arrays differ anywhere.

Description:
	Compares the first and second charArrays.
	 
Notes:
	None.

Authors:
	Stark Pister, 2013.3.3
 ****************************************************************************/

unsigned int sysCompareArray(char firstArray[], unsigned int firstArrayLength, char secondArray[], unsigned int secondArrayLength) {
	if (firstArrayLength!=secondArrayLength) {
		return ERROR;
	} else {
		int arrayIndex;
		for (arrayIndex = 0; arrayIndex<firstArrayLength; arrayIndex++) {
			if (firstArray[arrayIndex] != secondArray[arrayIndex]) {
				return FALSE;
			}
		}
	}
	return TRUE;
}