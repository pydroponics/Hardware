/*
 * Pydroponics
 * CMPE129
 * Collaborators
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

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
char txStringChar;
unsigned int bufferIndex;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/****************************************************************************
Function:
    sysUartInit

Parameters:
	unsigned int uartIndex		- Index of UART to initialize.
	unsigned int baudRate		- UART Baud Rate Register.

Returns:
    None.

Description:
    Initializes the UART with the specified baud rate, bits, parity and stop.
	Enables send and receive hardware and the receive interrupt.
	
Notes:
	UCSRnC - UART Control and Status Register
    ubrr = [Clock/(16*baud rate)] - 1	Sets the baud rate of the UART.
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
		UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
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
	unsigned int uartIndex		- Index of UART to transmit on.
    char txData					- Character to transmit.

Returns:
    None.

Description:
    Waits for an empty buffer and then puts the transmit character in the 
	transmit buffer to be sent.

Notes:
    None.

Author:
    Stark Pister 4/6/13
 ****************************************************************************/

void sysTransmit(unsigned int uartIndex, char txData) {
	switch (uartIndex) {
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

/****************************************************************************
Function:
    sysTransmitString

Parameters:
	unsigned int uartIndex		- Index of UART to transmit on.
    char *txString				- String to transmit.

Returns:
    None.

Description:
    Iterates over a string and transmits each character using the 
	sysTransmit function.

Notes:
    None.

Author:
    Stark Pister 4/6/13
 ****************************************************************************/

void sysTransmitString(unsigned int uartIndex, char *txString) {
	while ((txStringChar = *txString++)) {
		sysTransmit(uartIndex, txStringChar);
	}
}

/****************************************************************************
Function:
    sysClearRxBuffer

Parameters:
	unsigned int uartIndex		- Index of UART buffer to clear.

Returns:
    None.

Description:
    Iterates over a the selected data buffer and zeros each location.

Notes:
    None.

Author:
    Stark Pister 4/12/13
 ****************************************************************************/

void sysClearRxBuffer(unsigned int uartIndex) {
	for (bufferIndex = 0; bufferIndex < MAX_RECEIVE_LENGTH; bufferIndex++) {
		switch (uartIndex) {
			case 0:
			rxDataBuffer0[bufferIndex] = 0;
			break;
			
			case 1:
			rxDataBuffer1[bufferIndex] = 0;
			break;
			
			case 2:
			rxDataBuffer2[bufferIndex] = 0;
			break;
		}	
	}
	
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

/****************************************************************************
Interrupt:
    USART0_RX

Parameters:
    None.

Returns:
    None.

Description:
    This is the interrupt handler to support the UART receive. It triggers
    on receipt of a byte, and reads the receive buffer (UDR0) into the
    receive array. Then it checks for end of line '\0a' (Line Feed) and sets
	the ready flag accordingly.

Notes:
    Entering the interrupt clears the interrupt flag.

Author:
    Stark Pister 4/6/13
 ****************************************************************************/

ISR (USART0_RX_vect) {
	rxDataBuffer0[piDataIndex] = UDR0;
	if (rxDataBuffer0[piDataIndex] == 0x0a) {
		piDataReady = TRUE;
		UCSR0B &= ~(1<<RXCIE0);
	}	
	piDataIndex++;
}

/****************************************************************************
Interrupt:
    USART1_RX

Parameters:
    None.

Returns:
    None.

Description:
    This is the interrupt handler to support the UART receive. It triggers
    on receipt of a byte, and reads the receive buffer (UDR1) into the
    receive array. Then it checks for end of line '\0d' (Carriage Return) and
	sets the ready flag accordingly.

Notes:
    Entering the interrupt clears the interrupt flag automatically.

Author:
    Stark Pister 4/6/13
 ****************************************************************************/

ISR (USART1_RX_vect) {
	rxDataBuffer1[tdsDataIndex] = UDR1;
	if ( rxDataBuffer1[tdsDataIndex] == 0x0d) {
		tdsDataReady = TRUE;
		UCSR1B &= ~(1<<RXCIE1);
	}
	tdsDataIndex++;
}

/****************************************************************************
Interrupt:
    USART2_RX

Parameters:
    None.

Returns:
    None.

Description:
    This is the interrupt handler to support the UART receive. It triggers
	on receipt of a byte, and reads the receive buffer (UDR2) into the 
	receive array. Then it checks for end of line '\0d' (Carriage Return) and
	sets the ready flag accordingly.

Notes:
    Entering the interrupt clears the interrupt flag automatically.

Author:
    Stark Pister 4/6/13
 ****************************************************************************/

ISR (USART2_RX_vect) {
	rxDataBuffer2[phDataIndex] = UDR2;
	if (rxDataBuffer2[phDataIndex] == 0x0d) {
		phDataReady = TRUE;
		UCSR2B &= ~(1<<RXCIE2);
	}
	phDataIndex++;
}