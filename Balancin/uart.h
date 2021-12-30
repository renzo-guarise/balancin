
#ifndef UART_H_
#define UART_H_

	#include <avr/io.h>
	#define F_CPU 16000000
	#include <avr/interrupt.h>
	#include <util/delay.h>
	#include <stdio.h>
	#include <stdlib.h>
	
	void configuracion_uart(unsigned int Int_UartRx,unsigned int Int_UartTx,double brate);
	int mi_putc(char c,FILE *stream);
	int mi_getc(FILE *stream);
	#define fgetc()  mi_getc(&uart_io)
	#define fputc(x) mi_putc(x,&uart_io)
	volatile int contcomando,cmd;
	
#endif