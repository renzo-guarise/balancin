/*
 * timer.h
 *
 * Created: 3/1/2021 4:58:26 p. m.
 *  Author: renzo
 */ 


#ifndef TIMER_H_
#define TIMER_H_

	#include <stdbool.h>
	#include <avr/io.h>
	#include <avr/interrupt.h>

	#define PD6_salida (DDRD|=(1<<DDD6))
	#define PD5_salida (DDRD|=(1<<DDD5))
	#define PB1_salida (DDRB|=(1<<DDB1))
	#define PB2_salida (DDRB|=(1<<DDB2))
	#define PB3_salida (DDRB|=(1<<DDB3))
	#define PD3_salida (DDRD|=(1<<DDD3))

	typedef enum{
		outNo,
		outToggle,
		outClear,
		outSet
	}T_OUT; 
	
	typedef enum{
		Normal0,
		PWM01,
		CTC0,
		FastPWM01,
		Reserved0,
		PWM02,
		Reserved02,
		FastPWM02	
	}modeT0y2;
	
	typedef enum{
		Normal,
		PWM8bit,
		PWM9bit,
		PWM10bit,
		CTC,
		FastPWM8bit,
		FastPWM9bit,
		FastPWM10bit,
		PWM1,
		PWM2,
		PWM3,
		PWM4,
		CTC2,
		Reserved2,
		FastPWM1,
		FastPWM2
	}modeT1;

	typedef enum{
		NoCS1,
		CL1_NOpres,
		CL1x8pres,
		CL1x64,
		CL1x256,
		CL1x1024,
		ExCL_f1,
		ExCL_r1
	}CL_pres0y1;
	
	typedef enum{
		NoCS,
		CL_NOpres,
		CLx8pres,
		CLx32,
		CLx64,
		CLx128,
		CLx256,
		CLx1024,
	}CL_pres2;
	
	typedef struct{
		bool TOV_int;
		bool OCA_int;
		bool OCB_int;
		bool IC1_int;
	}intT1;
	
	typedef struct{
		bool TOV_int;
		bool OCA_int;
		bool OCB_int;
	}intT0y2;
	
	typedef struct{
		T_OUT OCA0;
		T_OUT OCB0;
		modeT0y2 modo0;
		CL_pres0y1 Pres;
	}T0;
	
	typedef struct{
		T_OUT OCA1;
		T_OUT OCB1;
		modeT1 modo1;
		CL_pres0y1 Pres;
	}T1;
	
	typedef struct{
		T_OUT OCA2;
		T_OUT OCB2;
		modeT0y2 modo2;
		CL_pres2 Pres;
	}T2;
	
	void configTimer0(T0 *ptr_T0);
	void configTimer1(T1 *ptr_T1);
	void configTimer2(T2 *ptr_T2);
	void int_Timer1(intT1 *ptr_intT1);
	void int_Timer0(intT0y2 *ptr_intT0);
	void int_Timer2(intT0y2 *ptr_intT2);
	
	uint16_t count;
	
#endif /* TIMER_H_ */