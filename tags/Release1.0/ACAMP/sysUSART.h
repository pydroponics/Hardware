/*
 * Automated Control and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 *	spister@ucsc.edu
 *  
 *  
 * File: sysUSART.h
 * Author: spister
 * Created: 2/23/2013 5.44
 * 
 */ 

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#ifndef sysUSART_H_
#define sysUSART_H_

#ifndef MAX_TRANSMIT_LENGTH
#define MAX_TRANSMIT_LENGTH 20
#define MAX_RECEIVE_LENGTH 20
#endif


unsigned int eventFlag;
char txDataBuffer0[MAX_TRANSMIT_LENGTH];
char rxDataBuffer0[MAX_RECEIVE_LENGTH];
char ackReqFlag0;
char txDataBuffer1[MAX_TRANSMIT_LENGTH];
char rxDataBuffer1[MAX_RECEIVE_LENGTH];
char ackReqFlag1;
unsigned int arrayLength1;
char txDataBuffer2[MAX_TRANSMIT_LENGTH];
char rxDataBuffer2[MAX_RECEIVE_LENGTH];
char ackReqFlag2;
unsigned int arrayLength2;
char txDataBuffer3[MAX_TRANSMIT_LENGTH];
char rxDataBuffer3[MAX_RECEIVE_LENGTH];
char ackReqFlag3;

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: sysUsartInit
 * @param usartIndex, Index of USART to transmit on.
 * @param ubrr, USART Baud Rate Register.

 * @return None.
 * @remark Initializes the USART with the specified baud rate, bits, parity and
 * stop.
 */
void sysUsartInit(unsigned int usartIndex, unsigned int ubrr);

/**
 * Function: sysTransmit
 * @param txData[], Array of character to transmit.
 * @param txLength, Length of transmit array.
 * @param usartIndex, Index of USART to transmit on.
 * @param ackReq, Boolean for whether a response is expected.
 * @return None.
 * @remark Puts an array of characters in the transmit buffer to be sent and 
 * enables the interrupt allowing each byte to be sent.
 */
void sysTransmit(char txData[], unsigned int txLength, unsigned int usartIndex, unsigned int ackReq);

/**
 * Function: sysTransmitChar
 * @param txData, Character to transmit.
 * @param usartIndex, Index of USART to transmit on.
 * @param ackReq, Boolean for whether a response is expected.
 * @return None.
 */
void sysTransmitChar(char txData, unsigned int usartIndex, unsigned int ackReq);

#endif 