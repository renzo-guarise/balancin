#ifndef MAIN_H_
#define MAIN_H_
	#include <avr/io.h>
	#define F_CPU 16000000
	#include <avr/interrupt.h>
	#include <util/delay.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include "uart.h"
	#include "timer.h"
	#include "i2c.h"
	#include "mpu_6050.h"
	#include "PID.h"

	#define PD2_Entrada (DDRD|=(0<<DDD2))
	#define PD2_Encender (PORTD|=(1<<PORTD2))

	void interpretecomando(void);
	char comando[30];

#endif