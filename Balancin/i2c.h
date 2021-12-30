
#ifndef I2C_H_
#define I2C_H_

	#include <avr/io.h>
	#include <util/twi.h>
	#include <avr/interrupt.h>

	#define F_CPU 16000000
	#define HI(aux)		(uint8_t) (aux>>8)
	#define	ADDR(aux)	(uint8_t) (aux<<1)
	#define R(aux)		(uint8_t) (aux|1)
	#define W(aux)		(uint8_t) (aux|0)
	#define B(aux)		(uint8_t) (1<<aux)

	typedef enum{
		
		Pres1=1,
		Pres2,
		Pres3,
		Pres4,
		
	}pres;

	typedef struct
	{
		pres prescaler;
		uint32_t baudrate;
	}i2c;
	

	void Set_baudrate(i2c *ptr_i2c;);
	uint8_t Start_i2c(uint8_t disp_dir);
	uint8_t Read_i2c(uint8_t ack);
	uint8_t Write_i2c(uint8_t data);
	void Stop_i2c(void);
	void write_byte(uint8_t data, uint8_t disp_dir, uint8_t adress);
	uint8_t read_byte(uint8_t disp_dir, uint8_t adress);
	uint16_t read_2byte(uint8_t disp_dir, uint8_t adress);
	void writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
	void writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);
	uint8_t readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum);
	int8_t readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length);
	
#endif 