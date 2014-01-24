#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void sysTransmit(char txData);
void sysClearRxBuffer();
unsigned int flag = 0;
char receiveData[10];
unsigned int dataIndex = 0;

int main (void)
{
	unsigned int baudRate = ((F_CPU / ( 16 * 38400)) - 1);
	unsigned int bufferIndex;
	UBRR0H = (unsigned char)(baudRate>>8);
	UBRR0L = (unsigned char) baudRate;
	UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
	sei();
	
	
	while(1) {
		if (flag == 1)
		{
			flag = 0;
			for (bufferIndex = 0; bufferIndex < dataIndex; bufferIndex++) {
				sysTransmit(receiveData[bufferIndex]);
				receiveData[bufferIndex] = 0;
			}
			dataIndex = 0;
			sei();
		} 
		_delay_ms(1000);
	}
	return 1;
}

void sysTransmit(char txData) {
	while ( !( UCSR0A & (1<<UDRE0)) ) {
	}
	UDR0 = txData;
}	

ISR (USART0_RX_vect) {
	receiveData[dataIndex] = UDR0;
	if (receiveData[dataIndex] == 0x0a)
	{
		flag = 1;
		cli();
	} 
	dataIndex++;
}
