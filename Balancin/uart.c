#include "main.h"
#include "uart.h"

FILE uart_io = FDEV_SETUP_STREAM(mi_putc,mi_getc,_FDEV_SETUP_RW);

void configuracion_uart(unsigned int Int_UartRx, unsigned int Int_UartTx, double brate)
{
	UBRR0=F_CPU/16.0/(brate-1);
	UCSR0B=((1<<RXEN0)|(1<<TXEN0));
	UCSR0C=(3<<UCSZ00);
	
	stdout=stdin=&uart_io;
	
	if (Int_UartRx)
	{
		UCSR0A |=(1<<RXC0);
		UCSR0B|=(1<<RXCIE0);
	}
	if (Int_UartTx)
	{
		UCSR0A |=(1<<RXC0);
		UCSR0B|=(1<<TXCIE0);
	}
}
ISR(USART_RX_vect)
{
	char dato;
	dato=fgetc();
	switch(dato)
	{
		case ':':
		cmd=1;
		contcomando=0;
		break;
		case '/':
		cmd=1;
		contcomando=0;
		break;
		case 13:
		if (cmd)
		{
			comando[contcomando]=0;
			interpretecomando();
			cmd=0;
		}
		break;
		case 8:
		if (contcomando>0)
		{
			contcomando--;
		}
		break;
		default:
		if(contcomando<30)
		{
			if (cmd)
			{
				comando[contcomando++]=dato;
			}
		}
		break;
	}
	UCSR0A |= (1<<RXC0);
}

int mi_putc(char c, FILE *stream)
{
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0=c;
	return 0;
}

int mi_getc( FILE *stream)
{
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}