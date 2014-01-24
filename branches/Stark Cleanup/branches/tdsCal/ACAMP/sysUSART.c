/*
 * Automated Control and Monitoring of Plants
 * CMPE129
 * Senior Design Group
 *	spister@ucsc.edu
 *  
 *  
 * File: sysUSART.c
 * Author: spister
 * Created: 2/23/2013 5.29
 * 
 */ 

#include "GlobalGeneralDefines.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "sysUSART.h"

/****************************************************************************
Function:
    sysUsartInit

Parameters:
	unsigned int usartIndex		- Index of USART to initialize.
	unsigned int ubrr			- USART Baud Rate Register.

Returns:
    None.

Description:
    Initializes the USART with the specified baud rate, bits, parity and stop.
	
Notes:
    ubrr = [Clock/(16*baud rate)] - 1	Sets the baud rate of the USART.
	ucsr = [UMSEL1,UMSEL0,UPM1,UPM0,USBS,UCSZ1,UCSZ0,UCPOL]
	
	UMSEL - 00 = Asynchronous, 01 = Synchronous, 11 = Master SPI
	UPM	  - 00 = No Parity, 10 = Even Parity, 11 = Odd Parity
	USBS  - 0 = 1 Stop Bit, 1 = 2 Stop Bits
	UCSZ  - 00 = 5 Bit Character Size, 01 = 6 Bits, 10 = 7 Bits, 11 = 8 Bits
		   111 = 9 Bits (Third bit UCSZ2 needs to be set in UCSRB)
	UCPOL - 0 = TxRising RxFalling, 1 = RxRising TxFalling (Synchronous Mode)

Author:
    Stark Pister 2013.3.2
 ****************************************************************************/

void sysUsartInit(unsigned int usartIndex, unsigned int ubrr) {
	switch (usartIndex) {
		case 0:
		UBRR0H = (unsigned char)(ubrr>>8);
		UBRR0L = (unsigned char)ubrr;
		UCSR0B = (1<<RXEN0)|(1<<TXEN0);
		UCSR0C = ((!(1<<USBS0))|(1<<UCSZ00)|(1<<UCSZ01));
		break;
		
		case 1:
		UBRR1H = (unsigned char)(ubrr>>8);
		UBRR1L = (unsigned char)ubrr;
		UCSR1B = (1<<RXEN1)|(1<<TXEN1);
		UCSR1C = (1<<UCSZ10)|(1<<UCSZ11);
		break;
		
		case 2:
		UBRR2H = (unsigned char)(ubrr>>8);
		UBRR2L = (unsigned char)ubrr;
		UCSR2B = (1<<RXCIE2)|(1<<RXEN2)|(1<<TXEN2);
		UCSR2C = (1<<UCSZ20)|(1<<UCSZ21);
		break;
		
		case 3:
		UBRR3H = (unsigned char)(ubrr>>8);
		UBRR3L = (unsigned char)ubrr;
		UCSR3B = (1<<RXEN3)|(1<<TXEN3);
		UCSR3C = (1<<UCSZ30)|(1<<UCSZ31);
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

void sysTransmit(char txData[], unsigned int txLength, unsigned int usartIndex, unsigned int ackReq) {
	switch (usartIndex) {
		case 0:
			sysCopyArray(txData, txLength, txDataBuffer0, MAX_TRANSMIT_LENGTH);
			UCSR0B |= (1<<UDRIE0);
			if(ackReq == ON) {
				UCSR0B |= (1<<RXCIE0);
				ackReqFlag0 = ON;
			}
			break;
		case 1:
		    sysCopyArray(txData, txLength, txDataBuffer1, MAX_TRANSMIT_LENGTH);
		    UCSR1B |= (1<<UDRIE1);
			if(ackReq == ON) {
				UCSR1B |= (1<<RXCIE1);
				ackReqFlag1 = ON;
			}
			break;
		case 2:
		    sysCopyArray(txData, txLength, txDataBuffer2, MAX_TRANSMIT_LENGTH);
		    UCSR2B |= (1<<UDRIE2);
			if(ackReq == ON) {
				UCSR2B |= (1<<RXCIE2);
				ackReqFlag2 = ON;
			}
			break;
		case 3:
			sysCopyArray(txData, txLength, txDataBuffer3, MAX_TRANSMIT_LENGTH);
			UCSR3B |= (1<<UDRIE3);
			if(ackReq == ON) {
				UCSR3B |= (1<<RXCIE3);
				ackReqFlag3 = ON;
			}
			break;
		}
		_delay_ms(10);
}

/****************************************************************************
Function:
    sysTransmitChar

Parameters:
    char txData					- Character to transmit.
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
    Stark Pister 2013.2.26
 ****************************************************************************/

void sysTransmitChar(char txData, unsigned int usartIndex, unsigned int ackReq) {
	char txDataArray[1];
	txDataArray[0] = txData;
	sysTransmit(txDataArray, 1, usartIndex, ackReq);
}

/****************************************************************************
Function:
    USART0_UDRE

Parameters:
    None.

Returns:
    None.

Description:
    This is the interrupt handler to support the USART transmit. It triggers
	when the UDR is empty and checks if the data buffer contains outgoing 
	data. If so, it sends it to the data register and right shifts the buffer.
	If not, it turns off tx interrupts.

Notes:
    None.

Author:
    Stark Pister 2013.2.23
 ****************************************************************************/

ISR (USART0_UDRE_vect) {
	if (txDataBuffer0[0] != FALSE) {
		UDR0 = txDataBuffer0[0];
		sysRightShiftArray(txDataBuffer0, ARRAY_ELEMENTS(txDataBuffer0));
	} else {
		UCSR0B &= ~(1<<UDRIE0);
	}	
}

/****************************************************************************
Function:
    USART0_RX

Parameters:
    None.

Returns:
    None.

Description:
    This is the interrupt handler to support the USART receive. It triggers
	on receipt of a byte and checks for carriage return before adding the new
	byte to the data buffer.

Notes:
    None.

Author:
    Stark Pister 2013.2.23
 ****************************************************************************/

ISR (USART0_RX_vect) {
	char rxData = UDR0;
	/*sysTransmitChar(rxData,0,OFF);
	if(rxData == 0x50 || rxData == 0x70){
		eventFlag = 1;
		PORTB |= B7;
	}
	else if(rxData == 0x43 || rxData == 0x63){
		eventFlag = 2;
		PORTB &= ~B7;
	}*/
	if (rxData == 0x0D) {
		UCSR0B &= !(1<<RXCIE0);
		ackReqFlag0 = OFF;
		
		// If continuous mode is on do data processing and save new ph value
		
	} else {
		sysLeftShiftArray(rxDataBuffer0, ARRAY_ELEMENTS(rxDataBuffer0), rxData);
	}
}

/****************************************************************************
Function:
    USART1_UDRE

Parameters:
    None.

Returns:
    None.

Description:
    This is the interrupt handler to support the USART transmit. It triggers
	when the UDR is empty and checks if the data buffer contains outgoing 
	data. If so, it sends it to the data register and right shifts the buffer.
	If not, it turns off tx interrupts.

Notes:
    None.

Author:
    Stark Pister 2013.2.23
 ****************************************************************************/

ISR (USART1_UDRE_vect) {
	if (txDataBuffer1[0] != FALSE) {
		UDR1 = txDataBuffer1[0];
		sysRightShiftArray(txDataBuffer1, ARRAY_ELEMENTS(txDataBuffer1));
	} else {
		UCSR1B &= ~(1<<UDRIE1);
	}	
}

/****************************************************************************
Function:
    USART1_RX

Parameters:
    None.

Returns:
    None.

Description:
    This is the interrupt handler to support the USART receive. It triggers
	on receipt of a byte and checks for carriage return before adding the new
	byte to the data buffer.

Notes:
    None.

Author:
    Stark Pister 2013.2.23
 ****************************************************************************/

ISR (USART1_RX_vect) {
	char rxData = UDR1;
	if (rxData == 0x0D) {
		ackReqFlag1 = OFF;
		// If continuous mode is on do data processing and save new tds value
	} else {
		sysLeftShiftArray(rxDataBuffer1, ARRAY_ELEMENTS(rxDataBuffer1), rxData);
		arrayLength1++;
		//sysTransmitChar(rxData,0,OFF);
	}
}

/****************************************************************************
Function:
    USART2_UDRE

Parameters:
    None.

Returns:
    None.

Description:
    This is the interrupt handler to support the USART transmit. It triggers
	when the UDR is empty and checks if the data buffer contains outgoing 
	data. If so, it sends it to the data register and right shifts the buffer.
	If not, it turns off tx interrupts.

Notes:
    None.

Author:
    Stark Pister 2013.2.23
 ****************************************************************************/

ISR (USART2_UDRE_vect) {
	if (txDataBuffer2[0] != FALSE) {
		UDR2 = txDataBuffer2[0];
		sysRightShiftArray(txDataBuffer2, ARRAY_ELEMENTS(txDataBuffer2));
	} else {
		UCSR2B &= ~(1<<UDRIE2);
	}	
}

/****************************************************************************
Function:
    USART2_RX

Parameters:
    None.

Returns:
    None.

Description:
    This is the interrupt handler to support the USART receive. It triggers
	on receipt of a byte and checks for carriage return before adding the new
	byte to the data buffer.

Notes:
    None.

Author:
    Stark Pister 2013.2.23
 ****************************************************************************/

ISR (USART2_RX_vect) {
	char rxData = UDR2;
	char CR = '\r';
	if (rxData == CR) {
		//UCSR2B &= !(1<<RXCIE2);
		ackReqFlag2 = OFF;
		// If continuous mode is on do data processing and save new ph value
	} else {
		sysLeftShiftArray(rxDataBuffer2, ARRAY_ELEMENTS(rxDataBuffer2), rxData);
		arrayLength2++;
		//sysTransmitChar(rxData,0,OFF);
	}
}

/****************************************************************************
Function:
    USART3_UDRE

Parameters:
    None.

Returns:
    None.

Description:
    This is the interrupt handler to support the USART transmit. It triggers
	when the UDR is empty and checks if the data buffer contains outgoing 
	data. If so, it sends it to the data register and right shifts the buffer.
	If not, it turns off tx interrupts.

Notes:
    None.

Author:
    Stark Pister 2013.2.23
 ****************************************************************************/

ISR (USART3_UDRE_vect) {
	if (txDataBuffer3[0] != FALSE) {
		UDR3 = txDataBuffer3[0];
		sysRightShiftArray(txDataBuffer3, ARRAY_ELEMENTS(txDataBuffer3));
	} else {
		UCSR3B &= ~(1<<UDRIE3);
	}	
}

/****************************************************************************
Function:
    USART3_RX

Parameters:
    None.

Returns:
    None.

Description:
    This is the interrupt handler to support the USART receive. It triggers
	on receipt of a byte and checks for carriage return before adding the new
	byte to the data buffer.

Notes:
    None.

Author:
    Stark Pister 2013.2.23
 ****************************************************************************/

ISR (USART3_RX_vect) {
	char rxData = UDR3;
	if (rxData == 0x0D) {
		// If ackReq=1 ackReq = 0
	} else {
		sysLeftShiftArray(rxDataBuffer3, ARRAY_ELEMENTS(rxDataBuffer3), rxData);
	}
}