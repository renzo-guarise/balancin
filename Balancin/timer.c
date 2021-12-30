/*
 * timer.c
 *
 * Created: 3/1/2021 4:57:52 p. m.
 *  Author: renzo
 */
#include "timer.h"



void configTimer0(T0 *ptr_T0){
	
	if (ptr_T0->OCA0) PD6_salida;
	if (ptr_T0->OCB0) PD5_salida;	 
	TCCR0A = (ptr_T0->OCA0<<COM0A0)|(ptr_T0->OCB0<<COM0B0)|(ptr_T0->modo0&0x03);
	TCCR0B = (((ptr_T0->modo0)<<1)&0x08)|ptr_T0->Pres;
	
}
	
void configTimer1(T1 *ptr_T1){
	
	if (ptr_T1->OCA1) PB1_salida;
	if (ptr_T1->OCB1) PB2_salida;
	TCCR1A = (ptr_T1->OCA1<<COM1A0)|(ptr_T1->OCB1<<COM1B0)|(ptr_T1->modo1&0x03);
	TCCR1B = (((ptr_T1->modo1)<<1)&0x18)|ptr_T1->Pres;
	
}

void configTimer2(T2 *ptr_T2){
	
	if (ptr_T2->OCA2) PB3_salida;
	if (ptr_T2->OCB2) PD3_salida;
	TCCR2A = (ptr_T2->OCA2<<COM2A0)|(ptr_T2->OCB2<<COM2B0)|(ptr_T2->modo2&0x03);
	TCCR2B = (((ptr_T2->modo2)<<1)&0x08)|ptr_T2->Pres;
	
}

void int_Timer1(intT1 *ptr_intT1){
	
	TIMSK1=(ptr_intT1->IC1_int<<ICIE1)|(ptr_intT1->OCB_int<<2)|(ptr_intT1->OCA_int<<1)|(ptr_intT1->TOV_int<<0);
	TIFR1=(ptr_intT1->IC1_int<<ICF1)|(ptr_intT1->OCB_int<<2)|(ptr_intT1->OCA_int<<1)|(ptr_intT1->TOV_int<<0);
	
}

void int_Timer0(intT0y2 *ptr_intT0){
	
	TIMSK0=(ptr_intT0->OCB_int<<2)|(ptr_intT0->OCA_int<<1)|(ptr_intT0->TOV_int<<0);
	TIFR0=(ptr_intT0->OCB_int<<2)|(ptr_intT0->OCA_int<<1)|(ptr_intT0->TOV_int<<0);
	
}

void int_Timer2(intT0y2 *ptr_intT2){
	
	TIMSK2=(ptr_intT2->OCB_int<<2)|(ptr_intT2->OCA_int<<1)|(ptr_intT2->TOV_int<<0);
	TIFR2=(ptr_intT2->OCB_int<<2)|(ptr_intT2->OCA_int<<1)|(ptr_intT2->TOV_int<<0);
	
}

