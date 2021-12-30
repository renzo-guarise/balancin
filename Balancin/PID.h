/*
 * IncFile1.h
 *
 * Created: 5/10/2020 10:17:34 p. m.
 *  Author: renzo
 */ 


#ifndef PID_H_
#define PID_H_

	#include <avr/io.h>
	#include "stdlib.h"
	
	#define PB5_Salida (DDRB|=(1<<DDB5))
	#define PB4_Salida (DDRB|=(1<<DDB4))
	#define PB5_Apagar (PORTB&=~(1<<PORTB5))
	#define PB4_Apagar (PORTB&=~(1<<PORTB4))
	#define PB5_Encender (PORTB|=(1<<PORTB5))
	#define PB4_Encender (PORTB|=(1<<PORTB4))
	#define PD7_Salida (DDRD|=(1<<DDD7))
	#define PD7_Apagar (PORTD&=~(1<<PORTD7))
	#define PD7_Encender (PORTD|=(1<<PORTD7))
	#define PD4_Salida (DDRD|=(1<<DDD4))
	#define PD4_Apagar (PORTD&=~(1<<PORTD4))
	#define PD4_Encender (PORTD|=(1<<PORTD4))

	void pid_init(uint8_t P_ON, uint8_t D_ON, uint8_t I_ON,double Kp1,double Kd1,double Ki1,double paso,double *input1,int16_t *setpoint1,int16_t *output1);
	uint8_t control_pid(void);
	void cambio_dir(void);
	void limit(int16_t max, int16_t min);

#endif /* INCFILE1_H_ */