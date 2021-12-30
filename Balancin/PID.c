/*
 * PID.c
 *
 * Created: 5/10/2020 3:05:28 p. m.
 *  Author: renzo
 */ 
#include "PID.h"

int16_t outputmax,outputmin,*myoutput,*mysetpoint;
double kd,kp,ki,*myinput,error_sum=0,error_ant=0;

	
void pid_init(uint8_t P_ON, uint8_t D_ON, uint8_t I_ON,double Kp1,double Kd1,double Ki1,double paso,double *input1,int16_t *setpoint1,int16_t *output1){
	
	myinput=input1;
	mysetpoint=setpoint1;
	myoutput=output1;
	
	PD7_Salida;							//Para controlar la direccion de los motores
	PB5_Salida;							//Para controlar la direccion de los motores
	PB4_Salida;							//Para controlar la direccion de los motores
	PD4_Salida;							//Para controlar la direccion de los motores
	PD4_Apagar;
	PB5_Apagar;
	PB4_Apagar;
	PD7_Apagar;
	
	if (P_ON) kp=Kp1;
	else kp=0;
	if (D_ON) kd=Kd1/paso;
	else kd=0;
	if (I_ON) ki=Ki1*paso;
	else ki=0;
	
}

uint8_t control_pid(void){
	
	if (kp>0 || kd>0 || ki>0){
	
		double error= *mysetpoint- *myinput ;
		double derror=*myinput-error_ant;
		
		error_sum=error_sum+ki*error;
		*myoutput=kp*error-kd*derror+error_sum;
		error_ant=*myinput;	
		
		return 1;	
		
	}else return 0;
}

void cambio_dir(void){
	
	if (*myoutput<0){
		PD4_Apagar;
		PD7_Encender;
		PB5_Encender;
		PB4_Apagar;
		
		if (*myoutput<outputmin) *myoutput=outputmin;
		
		OCR0A=-*myoutput;
		OCR0B=-*myoutput;
		TCNT0=0;

	}
	if (*myoutput>0){

		PD7_Apagar;
		PD4_Encender;
		PB5_Apagar;
		PB4_Encender;
		
		if (*myoutput>outputmax) *myoutput=outputmax;
		
		OCR0A=*myoutput;
		OCR0B=*myoutput;
		TCNT0=0;

	}
}

void limit(int16_t max, int16_t min){
	
	if (max!=0 && min!=0){
		outputmin=min;
		outputmax=max;
	}else 
	{
		outputmax=255;
		outputmin=-255;
	}
}
	