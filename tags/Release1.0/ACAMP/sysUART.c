/*
 * Automated Care and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 * spister@ucsc.edu
 * 
 * File: sysUART.c
 * Author: Stark Pister
 * Created: 4/5/13 4:00
 * 
 */

#include "GlobalGeneralDefines.h"
#include "sysUART.h"
#include <avr/interrupt.h>
#include <avr/io.h>

/****************************************************************************
Function:
    sysUartInit

Parameters:
	unsigned int usartIndex		- Index of USART to initialize.
	unsigned int ubrr			- USART Baud Rate Register.

Returns:
    None.

Description:
    Initializes the UART with the specified baud rate, bits, parity and stop.
	
Notes:
	UCSRnC - Uart Control and Status Register
    ubrr = [Clock/(16*baud rate)] - 1	Sets the baud rate of the USART.
	ucsr = [UMSEL1,UMSEL0,UPM1,UPM0,USBS,UCSZ1,UCSZ0,UCPOL]
	
	UMSEL - 00 = Asynchronous, 01 = Synchronous, 11 = Master SPI
	UPM	  - 00 = No Parity, 10 = Even Parity, 11 = Odd Parity
	USBS  - 0 = 1 Stop Bit, 1 = 2 Stop Bits
	UCSZ  - 00 = 5 Bit Character Size, 01 = 6 Bits, 10 = 7 Bits, 11 = 8 Bits
		   111 = 9 Bits (Third bit UCSZ2 needs to be set in UCSRB)
	UCPOL - 0 = TxRising RxFalling, 1 = RxRising TxFalling (Synchronous Mode)

Author:
    Stark Pister 4/6/2013
 ****************************************************************************/

void sysUartInit(unsigned int uartIndex, unsigned int baudRate) {
	switch (uartIndex) {
		case 0:
		UBRR0H = (unsigned char)(baudRate>>8);
		UBRR0L = (unsigned char) baudRate;
		UCSR0B = (1<<RXCIE1)|(1<<RXEN0)|(1<<TXEN0);
		UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
		break;
		
		case 1:
		UBRR1H = (unsigned char)(baudRate>>8);
		UBRR1L = (unsigned char) baudRate;
		UCSR1B = (1<<RXCIE1)|(1<<RXEN1)|(1<<TXEN1);
		UCSR1C = (1<<UCSZ10)|(1<<UCSZ11);
		break;
		
		case 2:
		UBRR2H = (unsigned char)(baudRate>>8);
		UBRR2L = (unsigned char) baudRate;
		UCSR2B = (1<<RXCIE2)|(1<<RXEN2)|(1<<TXEN2);
		UCSR2C = (1<<UCSZ20)|(1<<UCSZ21);
		break;
	}
}

/****************************************************************************
Function:
    sysTransmit

Parameters:
    char txData[]				- Array of character to transmit.
	unsigned int txLength		- Length of transmit array.
	unsigned int usartIndex		- Index of USART to transmit on.
	unsigned int ackReq			- Boolean for whether a response is expected.

Returns:
    None.

Description:
    Puts an array of characters in the transmit buffer to be sent and enables
	the interrupt allowing each byte to be sent.

Notes:
    None.

Author:
    Stark Pister 2013.2.23
 ****************************************************************************/

void sysTransmit(unsigned int usartIndex, char txData) {
	switch (usartIndex) {
		case 0:
		while ( !( UCSR0A & (1<<UDRE0)) ) {
		}		
		UDR0 = txData;
		break;
		
		case 1:
		while ( !( UCSR1A & (1<<UDRE1)) ) {
		}
		UDR1 = txData;
		break;
		
		case 2:
		while ( !( UCSR2A & (1<<UDRE2)) ) {
		}
		UDR2 = txData;
		break;
	}	
}

void sysTransmitString(unsigned int usartIndex, char *txString) {
	char txData;
	while ((txData = *txString++)) {
		sysTransmit(usartIndex, txData);
	}
}

ISR (USART0_RX_vect) {
	char rxData;
	rxData = UDR0;
	UDR0 = rxData; //Echo Back Received byte.
}

ISR (USART1_RX_vect) {
	char rxData;
	rxData = UDR1;
	UDR1 = rxData; //Echo Back Received byte.
}

ISR (USART2_RX_vect) {
	char rxData;
	rxData = UDR2;
	UDR2 = rxData; //Echo Back Received byte.
}