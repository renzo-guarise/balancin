
#include "i2c.h"


void Set_baudrate(i2c *ptr_i2c){
	
	TWBR= (uint8_t)((((F_CPU / ptr_i2c->baudrate) / ptr_i2c->prescaler) - 16 ) / 2);
	TWSR= (ptr_i2c->prescaler-1)<<TWPS0;
	
}

uint8_t Start_i2c(uint8_t disp_dir){
	
	TWCR = 0;
	TWCR =(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR &(1<<TWINT)));
	if ((TWSR & 0xF8) !=TW_START) return 0;
	TWDR = disp_dir;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR &(1<<TWINT)));
	uint8_t twst = TW_STATUS & 0xF8;
	if ((twst!=TW_MT_SLA_ACK)&&(twst!=TW_MR_SLA_ACK)) return 0;
	
	return 1;
	
}

uint8_t Read_i2c(uint8_t ack){
	
	TWCR = (1<<TWINT) | (1<<TWEN) | (ack<<TWEA);		
	while( !(TWCR & (1<<TWINT)) );	
						
	return TWDR;
		
}


uint8_t Write_i2c(uint8_t data){
	
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR &(1<<TWINT)));
	if ((TWSR & 0xF8) !=TW_MT_DATA_ACK) return 0;
	
	return 1;
	
}

void Stop_i2c(void){
	
	TWCR =(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);

}

void write_byte(uint8_t data, uint8_t disp_dir, uint8_t adress){
	
	while(!Start_i2c( disp_dir));
	Write_i2c(adress);
	Write_i2c(data);
	Stop_i2c();

}

uint8_t read_byte(uint8_t disp_dir, uint8_t adress){
	
 	uint8_t data;
	while(!Start_i2c(W(disp_dir)));
	Write_i2c(adress);
	Start_i2c(R(disp_dir));
	data=Read_i2c(0);
	Stop_i2c();
	
	return data;

}

uint16_t read_2byte(uint8_t disp_dir, uint8_t adress){
	
	uint8_t dataH ,dataL;
	while(!Start_i2c(W(disp_dir)));
	Write_i2c(adress);
	Start_i2c(R(disp_dir));
	dataH=Read_i2c(1);
	dataL=Read_i2c(0);
	Stop_i2c();
	
	return (dataH<<8| dataL);
}

void writeBits(uint8_t disp_dir, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) {
	
	//      010 valor a escribir
	// 76543210 numero de bits
	//    xxx   args: bitStart=4, length=3
	// 00011100 byte mascara
	// 10101111 valor original
	// 10100011 original & ~mask
	// 10101011 masked | value
	uint8_t b;
	b=read_byte(disp_dir, regAddr);
	uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
	data <<= (bitStart - length + 1); 
	data &= mask;
	b &= ~(mask);
	b |= data;
	write_byte(b,disp_dir, regAddr);

}
void writeBit(uint8_t disp_dir, uint8_t regAddr, uint8_t bitNum, uint8_t data) {
	
	uint8_t b;
	b=read_byte(disp_dir, regAddr);
	b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
	write_byte(b,disp_dir, regAddr);
	
}

uint8_t readBit(uint8_t disp_dir, uint8_t regAddr, uint8_t bitNum) {
	
	uint8_t b = read_byte(disp_dir, regAddr);
	b = b & (1 << bitNum);
	return b;
	
}

int8_t readBits(uint8_t disp_dir, uint8_t regAddr, uint8_t bitStart, uint8_t length) {
	
	// 01101001 byte leido
	// 76543210 numero bits
	//    xxx   args: bitStart=4, length=3
	//    010   mascara
	//   -> 010 
	uint8_t b;
	b = read_byte(disp_dir, regAddr);
	uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
	b &= mask;
	b >>= (bitStart - length + 1);
	return b;
	
}
