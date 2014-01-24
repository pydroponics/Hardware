/*
 * Pydroponics
 * CMPE129
 * Collaborators
 * spister@ucsc.edu
 * 
 * File: sysUART.h
 * Author: Stark Pister
 * Created: 4/6/2013 5:20
 * 
 */

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#ifndef sysUART_H_
#define sysUART_H_

#define MAX_RECEIVE_LENGTH 16

/*******************************************************************************
 * PUBLIC VARIABLES                                                            *
 ******************************************************************************/

char rxDataBuffer0[MAX_RECEIVE_LENGTH];
unsigned int piDataIndex;
unsigned int piDataReady;

char rxDataBuffer1[MAX_RECEIVE_LENGTH];
unsigned int tdsDataIndex;
unsigned int tdsDataReady;

char rxDataBuffer2[MAX_RECEIVE_LENGTH];
unsigned int phDataIndex;
unsigned int phDataReady;

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: sysUartInit
 * @param uartIndex, Index of UART to transmit on.
 * @param baudRate, UART Baud Rate Register value.
 * @return None.
 * @remark Initializes the UART with the specified baud rate, bits, parity and stop.
 * Enables send and receive hardware and the receive interrupt.
 */
void sysUartInit(unsigned int uartIndex, unsigned int baudRate);

/**
 * Function: sysTransmit
 * @param uartIndex, Index of UART to transmit on.
 * @param txData, Character to transmit.
 * @return None.
 * @remark Waits for an empty buffer and then puts the transmit character in the
 * transmit buffer to be sent.
 */
void sysTransmit(unsigned int uartIndex, char txData);

/**
 * Function: sysTransmitString
 * @param uartIndex, Index of UART to transmit on.
 * @param txString, String to transmit.
 * @return None.
 * @remark Iterates over a string and transmits each character using the
 * sysTransmit function.
 */
void sysTransmitString(unsigned int uartIndex, char *txString);

/**
 * Function: sysClearRxBuffer
 * @param uartIndex, Index of UART buffer to clear.
 * @return None.
 * @remark Iterates over a the selected data buffer and zeros each location.
 */
void sysClearRxBuffer(unsigned int uartIndex);

#endif