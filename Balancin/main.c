
#include "main.h"


int16_t output,setpoint,parado=-6;
volatile uint8_t Flag_IMU=0;
double ang_y_prev,input;

//#define Angulo  //Si se quiere que se imprima el angulo del balancin descomentar

int main(void)
{
	
	double ax_f,az_f,gy_f;
	int16_t ax,az,gy;
	
	PD2_Entrada;						//Para int
	PD2_Encender;						//Encendemos la resistencia pull up para evitar ruido
	
	EIMSK |=(1<<INT0);					//Habilita int 0
	EICRA|=((1<<ISC10)|(1<<ISC11));		//Flanco subida	
	EIFR |=((1<<INTF0));				//Apaga flag
	
	T0 Timer0;
	Timer0.modo0=FastPWM01;				// Configuramos Timer. Modo FastPWM.
	Timer0.OCA0=outClear;				// Elegimos el modo clear, es decir cada vez que se iguala el valor del registro OCX1 se pone en bajo la salida.
	Timer0.OCB0=outClear;
	Timer0.Pres=CL_NOpres;				// El prescaler esta en 1.
	configTimer0(&Timer0);

	configuracion_uart(1,0,9600);		// Configuramos Uart. Baudrate=9600. Habilitamos int cuando se recibe algun dato
	printf("Uart Habilitada\r\n");	
	
	i2c ptr_i2c;
	ptr_i2c.baudrate=100000;			// Establecemos el baudrate para i2c
	ptr_i2c.prescaler=Pres1;			// Prescaler desactivado
	disp_dir=ADDR(0x68);				// Direccion del mpu
	Set_baudrate(&ptr_i2c);				// Seteamos el baudrate
	
	MPU6050 MPU;
	INT_MPU interrup;
	
	initialize_mpu(&MPU,&interrup);		// Seteamos la IMU y su interrupciones.
    printf("MPU_ok\r\n");

	pid_init(1,1,1,50,1.2,100,0.006,&input,&setpoint,&output);		//Inicializa el control PID
	limit(180,-180);												//Establece los limites del PID
	setpoint=parado;
	
	sei();								// Habilitamos int globales
	
    while (1) 
    {

		if (Flag_IMU)
		{
				
				get_gyro_gy(&gy);			//Obtenemos las lecturas del giroscopo
				get_ax_az(&ax,&az);			//Obtenemos las lecturas del acelerometro
				
				ax_f=ax*(9.81/16384.0);			//Escalamos las lecturas.
				az_f=az*(9.81/16384.0);
				gy_f=gy*(250.0/32768.0);
				
				/* FILTRO COMPLEMENTARIO */
				input = 0.98*(ang_y_prev-gy_f*0.006) + 0.02*(atan2(ax_f,az_f)*(180.0/3.14));
				ang_y_prev=input;
				
				control_pid();					//Realiza el control PID
				cambio_dir();					//Controla los motores dependiendo del valor de la variable input
				
				#ifdef Angulo
				
					printf("%.2f,%d\n\r",input,setpoint);
					
				#endif // Angulo
				
				Flag_IMU=0;
		}
		
    }
}
void interpretecomando(void){
	
	uint8_t i;
	
	switch(comando[0]){								
		case 'W':
		case 'w':										// Para realizar el movimiento del balancin asi adelante simplemente aumentamos su setpoint provocando que al intentar lograr esta posicion deseada se desplace asi adelante.
			printf("Adelante\r\n");
			setpoint+=5;
			printf("%d\r\n",setpoint);
		break;
		case 'S':
		case 's':
			printf("Atras\r\n");						// Para realizar el movimiento del balancin asi adelante simplemente disminuimos su setpoint provocando que al intentar lograr esta posicion deseada se desplace asi adelante.
			setpoint-=5;
			printf("%d\r\n",setpoint);
		break;
		case 'A':
		case 'a':
			i=0;
			setpoint=parado;
			
			while(comando[i++]!=0){						// Para realizar el giro a la izquierda hacemos que los motores giren en direcciones opuestas.
				PD4_Encender;
				PD7_Apagar;
				PB5_Encender;
				PB4_Apagar;
				OCR0A=200;
				OCR0B=200;
				_delay_ms(100);
			}
			
			printf("Izquierda\r\n");
			printf("%d\r\n",setpoint);

		break;
		case 'D':
		case 'd':
			i=0;
			setpoint=parado;
			
			while(comando[i++]!=0){
				PD4_Apagar;
				PD7_Encender;
				PB5_Apagar;
				PB4_Encender;
				OCR0A=200;
				OCR0B=200;
				_delay_ms(100);
			}
			
			printf("Derecha\r\n");
			printf("%d\r\n",setpoint);

		break;
		default:
		printf("Comando invalido");
		break;
	}
}
ISR(INT0_vect){
	
	Flag_IMU=1;

}