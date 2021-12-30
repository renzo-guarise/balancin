/*
 * mpu_6050.c
 *
 * Created: 30/9/2020 3:45:07 p. m.
 *  Author: renzo
 */ 

#include "mpu_6050.h"


/*Establece por cuanto se va a dividir el Gyroscope Output Rate.
* Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
* Gyroscope Output Rate=8 kHz when the DLPF is disabled (DLPF_CFG = 0 or 7), and 1kHz when the DLPF is enabled
*/
void set_samplerate(MPU6050 *MPU){
	
	write_byte(MPU->smplrt_div,disp_dir,MPU6050_RA_SMPLRT_DIV);			
	
}

// CONFIG register

 /** Set digital low-pass filter configuration.
 * The DLPF_CFG parameter sets the digital low pass filter configuration. It
 * also determines the internal sampling rate used by the device as shown in
 * the table below.
 *
 * Note: The accelerometer output rate is 1kHz. This means that for a Sample
 * Rate greater than 1kHz, the same accelerometer sample may be output to the
 * FIFO, DMP, and sensor registers more than once.
 *
 * <pre>
 *          |   ACCELEROMETER    |           GYROSCOPE
 * DLPF_CFG | Bandwidth | Delay  | Bandwidth | Delay  | Sample Rate
 * ---------+-----------+--------+-----------+--------+-------------
 * 0        | 260Hz     | 0ms    | 256Hz     | 0.98ms | 8kHz
 * 1        | 184Hz     | 2.0ms  | 188Hz     | 1.9ms  | 1kHz
 * 2        | 94Hz      | 3.0ms  | 98Hz      | 2.8ms  | 1kHz
 * 3        | 44Hz      | 4.9ms  | 42Hz      | 4.8ms  | 1kHz
 * 4        | 21Hz      | 8.5ms  | 20Hz      | 8.3ms  | 1kHz
 * 5        | 10Hz      | 13.8ms | 10Hz      | 13.4ms | 1kHz
 * 6        | 5Hz       | 19.0ms | 5Hz       | 18.6ms | 1kHz
 * 7        |   -- Reserved --   |   -- Reserved --   | Reserved
 */
 
void set_DLPF(MPU6050 *MPU){
	
	writeBits(disp_dir, MPU6050_RA_CONFIG, MPU6050_CFG_DLPF_CFG_BIT, MPU6050_CFG_DLPF_CFG_LENGTH, MPU->Filtro);				
		
}


/** Set external FSYNC configuration.
 * Configures the external Frame Synchronization (FSYNC) pin sampling. An
 * external signal connected to the FSYNC pin can be sampled by configuring
 * EXT_SYNC_SET. Signal changes to the FSYNC pin are latched so that short
 * strobes may be captured. The latched FSYNC signal will be sampled at the
 * Sampling Rate, as defined in register 25. After sampling, the latch will
 * reset to the current FSYNC signal state.
 *
 * The sampled value will be reported in place of the least significant bit in
 * a sensor data register determined by the value of EXT_SYNC_SET according to
 * the following table.
 *
 * EXT_SYNC_SET | FSYNC Bit Location
 * -------------+-------------------
 * 0            | Input disabled
 * 1            | TEMP_OUT_L[0]
 * 2            | GYRO_XOUT_L[0]
 * 3            | GYRO_YOUT_L[0]
 * 4            | GYRO_ZOUT_L[0]
 * 5            | ACCEL_XOUT_L[0]
 * 6            | ACCEL_YOUT_L[0]
 * 7            | ACCEL_ZOUT_L[0]
 */
void set_EXTSYNC(MPU6050 *MPU){	
	
	writeBits(disp_dir, MPU6050_RA_CONFIG, MPU6050_CFG_EXT_SYNC_SET_BIT, MPU6050_CFG_EXT_SYNC_SET_LENGTH, MPU->EXT_SYN);	
	
}


// GYRO_CONFIG register

/** Set full-scale gyroscope range.
 * The FS_SEL parameter allows setting the full-scale range of the gyro sensors,
 * as described in the table below.
 *
 * <pre>
 * 0 = +/- 250 degrees/sec
 * 1 = +/- 500 degrees/sec
 * 2 = +/- 1000 degrees/sec
 * 3 = +/- 2000 degrees/sec
 * </pre>
 */
void set_GYROSCALE(MPU6050 *MPU){	
	
	writeBits(disp_dir, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, MPU->GYRO_SCALE);			
													
}

/** Set full-scale accelerometer range.
 * The FS_SEL parameter allows setting the full-scale range of the accelerometer
 * sensors, as described in the table below.
 *
 * <pre>
 * 0 = +/- 2g
 * 1 = +/- 4g
 * 2 = +/- 8g
 * 3 = +/- 16g
 * </pre>
 */
void set_ACCELSCALE(MPU6050 *MPU){
	
	writeBits(disp_dir, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, MPU->ACCEL_SCALE);			
								
}

//This register determines which sensor measurements are loaded into the FIFO buffer.
void fifo_en(FIFO_EN *FIFO){
	
	uint8_t aux = (FIFO->TEMP_FIFO_EN<<7) | (FIFO->XG_FIFO_EN<<6) | (FIFO->YG_FIFO_EN<<5) | (FIFO->ZG_FIFO_EN<<4) | (FIFO->ACCEL_FIFO_EN<<3) | (FIFO->SLV2_FIFO_EN<<2) | (FIFO->SLV1_FIFO_EN<<1) | (FIFO->SLV0_FIFO_EN<<0);
	write_byte(aux,disp_dir,MPU6050_RA_FIFO_EN);
	
}


/**This register configures the behavior of the interrupt signals at the INT pins 
*FSYNC_INT_EN enables the FSYNC pin to be used as an interrupt to the host application processor.
*When I2C_BYPASS_EN is equal to 1 and I2C_MST_EN (Register 106 bit[5]) is equal to 0, the host application processor will be able to directly access the auxiliary I2C bus of the MPU-60X0.

*INT_LEVEL:				When this bit is equal to 0, the logic level for the INT pin is active high.
*						When this bit is equal to 1, the logic level for the INT pin is active low.
*INT_OPEN:				When this bit is equal to 0, the INT pin is configured as push-pull.
*						When this bit is equal to 1, the INT pin is configured as open drain.
*LATCH_INT_EN:			When this bit is equal to 0, the INT pin emits a 50us long pulse.
*						When this bit is equal to 1, the INT pin is held high until the interrupt is cleared.
*INT_RD_CLEAR:			When this bit is equal to 0, interrupt status bits are cleared only by reading INT_STATUS (Register 58)
*						When this bit is equal to 1, interrupt status bits are cleared on any read operation.
*FSYNC_INT_LEVEL:		When this bit is equal to 0, the logic level for the FSYNC pin (when used as an interrupt to the host processor) is active high.
*						When this bit is equal to 1, the logic level for the FSYNC pin (when used as an interrupt to the host processor) is active low.
*FSYNC_INT_EN:			When equal to 0, this bit disables the FSYNC pin from causing an interrupt to the host processor.
*						When equal to 1, this bit enables the FSYNC pin to be used as an interrupt to the host processor.
*/
void int_ctrl(INT_MPU *interrup ){
	
	uint8_t aux = (interrup->CTR.INT_LEVEL<<7) | (interrup->CTR.INT_OPEN<<6) | (interrup->CTR.LATCH_INT_EN<<5) | (interrup->CTR.INT_RD_CLEAR<<4) | (interrup->CTR.FSYNC_INT_LEVEL<<3) | (interrup->CTR.FSYNC_INT_EN<<2) | (interrup->CTR.I2C_BYPASS_EN<<1);					
	write_byte(aux,disp_dir,MPU6050_RA_INT_PIN_CFG);		
																								
}

/**This register enables interrupt generation by interrupt sources
*DATA_RDY_EN When set to 1, this bit enables the Data Ready interrupt, which occurs each time a write operation to all of the sensor registers has been completed.
*After an interrupt, the correspondent pin have to be read for cleared it from INT_STATUS 
*/
void int_enable(INT_MPU *interrup ){
	
	uint8_t aux = (interrup->FIFO_OFLOW_EN<<4) | (interrup->I2C_MST_INT_EN<<3) | (interrup->DATA_RDY_EN<<0);							
	write_byte(aux,disp_dir,MPU6050_RA_INT_ENABLE);														
	
}


void setFIFOEnabled(bool enabled) {
	
	writeBit(disp_dir, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_FIFO_EN_BIT, enabled);
	
}

void resetFIFO(void) {
	
    writeBit(disp_dir, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_FIFO_RESET_BIT, 1);
	
}

/** Reset all sensor registers and signal paths.
 * When set to 1, this bit resets the signal paths for all sensors (gyroscopes,
 * accelerometers, and temperature sensor). This operation will also clear the
 * sensor registers. This bit automatically clears to 0 after the reset has been
 * triggered.
 */
void resetSensors(void) {
	
    writeBit(disp_dir, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_SIG_COND_RESET_BIT,1);
	
}


/** Trigger a full device reset.
 * A small delay of ~50ms may be desirable after triggering a reset.
 */
void reset(void) {
	
    writeBit(disp_dir, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_DEVICE_RESET_BIT,1);
	
}

/** Set sleep mode status.
 * Setting the SLEEP bit in the register puts the device into very low power
 * sleep mode. In this mode, only the serial interface and internal registers
 * remain active, allowing for a very low standby current. Clearing this bit
 * puts the device back into normal mode. To save power, the individual standby
 * selections for each of the gyros should be used if any gyro axis is not used
 * by the application.
 */
void setSleepEnabled(bool enabled) {
	
	writeBit(disp_dir, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);
	
}

/** Set wake cycle enabled status.
 * When this bit is set to 1 and SLEEP is disabled, the MPU-60X0 will cycle
 * between sleep mode and waking up to take a single sample of data from active
 * sensors at a rate determined by LP_WAKE_CTRL (register 108).
 */
void setWakeCycleEnabled(bool enabled) {
	
	writeBit(disp_dir, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CYCLE_BIT, enabled);
	
}

// Set temperature sensor enabled status.
void setTempSensorEnabled(bool enabled) {
	
    // 1 is actually disabled here
    writeBit(disp_dir, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_TEMP_DIS_BIT, !enabled);
	
}

/** Set clock source setting.
 * An internal 8MHz oscillator, gyroscope based clock, or external sources can
 * be selected as the MPU-60X0 clock source. When the internal 8 MHz oscillator
 * or an external source is chosen as the clock source, the MPU-60X0 can operate
 * in low power modes with the gyroscopes disabled.
 *
 * Upon power up, the MPU-60X0 clock source defaults to the internal oscillator.
 * However, it is highly recommended that the device be configured to use one of
 * the gyroscopes (or an external clock source) as the clock reference for
 * improved stability. The clock source can be selected according to the following table:
 *
 * <pre>
 * CLK_SEL | Clock Source
 * --------+--------------------------------------
 * 0       | Internal oscillator
 * 1       | PLL with X Gyro reference
 * 2       | PLL with Y Gyro reference
 * 3       | PLL with Z Gyro reference
 * 4       | PLL with external 32.768kHz reference
 * 5       | PLL with external 19.2MHz reference
 * 6       | Reserved
 * 7       | Stops the clock and keeps the timing generator in reset
 * </pre>
 */
void setClockSource1(MPU6050 *MPU) {
	
    writeBits(disp_dir, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, MPU->CLSOURCE);
	
}


/** Set wake frequency in Accel-Only Low Power Mode.
 * The MPU-60X0 can be put into Accerlerometer Only Low Power Mode by setting
 * PWRSEL to 1 in the Power Management 1 register (Register 107). In this mode,
 * the device will power off all devices except for the primary I2C interface,
 * waking only the accelerometer at fixed intervals to take a single
 * measurement. The frequency of wake-ups can be configured with LP_WAKE_CTRL
 * as shown below:
 *
 * <pre>
 * LP_WAKE_CTRL | Wake-up Frequency
 * -------------+------------------
 * 0            | 1.25 Hz
 * 1            | 2.5 Hz
 * 2            | 5 Hz
 * 3            | 10 Hz
 * </pre>
 *
 * For further information regarding the MPU-60X0's power modes, please refer to
 * Register 107.
 */
void setWakeFrequency(uint8_t frequency) {
	
    writeBits(disp_dir, MPU6050_RA_PWR_MGMT_2, MPU6050_PWR2_LP_WAKE_CTRL_BIT, MPU6050_PWR2_LP_WAKE_CTRL_LENGTH, frequency);
	
}

void set_STBYSENSOR(STBY *SENSOR){
	
	uint8_t aux = (SENSOR->STBY_XA<<5) | (SENSOR->STBY_YA<4) | (SENSOR->STBY_ZA<<3) | (SENSOR->STBY_XG<<2) | (SENSOR->STBY_YG<<1) | (SENSOR->STBY_ZG);
	writeBits(disp_dir, MPU6050_RA_PWR_MGMT_2, 5, 6, aux);
	
}


void initialize_mpu(MPU6050 *MPU,INT_MPU *interrup){
	 
	 MPU->smplrt_div=5;							// Establecemos el samplerate = 1000/(smplrt_div + 1)=166.7 Hz.
	 MPU->Filtro=DLPF_BW_42;					// Seteamos el filtro pasa bajo con un BW = 20 Hz.
	 MPU->EXT_SYN=EXT_SYNC_DISABLED;			// Desabilitamos marco de sincronización externa.
	 MPU->GYRO_SCALE=GYRO_FS_250;				// Escala del GYRO: +-250°/s.
	 MPU->ACCEL_SCALE=ACCEL_FS_2;				// Escala del ACCEL: +-2g.
	 MPU->CLSOURCE=CLOCK_PLL_XGYRO;				
	 
	 interrup->I2C_MST_INT_EN=false;
	 interrup->FIFO_OFLOW_EN=false;
	 interrup->DATA_RDY_EN=true;				// Habilitamos INT que nos indica cuando hay datos para ser leidos.
	 interrup->CTR.INT_LEVEL=true;				// Seteamos el nivel de la INT bajo de manera activa.
	 interrup->CTR.INT_OPEN=false;				// push-pull
	 interrup->CTR.LATCH_INT_EN=true;			// La señal dura 50us
	 interrup->CTR.INT_RD_CLEAR=true;			// La INT se limpia cuando se lee cualquier registro.
	 interrup->CTR.FSYNC_INT_EN=false;
	 interrup->CTR.FSYNC_INT_LEVEL=false;
	 interrup->CTR.I2C_BYPASS_EN=false;
	 
	 
	 set_DLPF(MPU);					//Activamos filtro pasa bajo.
	 setClockSource1(MPU);			//Seleccionamos XGYRO como fuente de reloj para aumentar la estabilidad
	 set_GYROSCALE(MPU);			//Rango +-250°/s
	 set_ACCELSCALE(MPU);			//Rango +-2g
	 set_samplerate(MPU);			//Establecemos una velocidad de muestreo en 100 Hz.
	 setTempSensorEnabled(false);	//Deshabilitamos sensor de temp y seleccionamos la fuente del reloj.
	 setSleepEnabled(false);
	 
	 int_ctrl(interrup);			//Habilitamos interrupcion que nos indica cuando los datos se encuentran disponibles.
	 int_enable(interrup);
	 
}

void get_gyro(int16_t *gx,int16_t *gy,int16_t *gz){
	
	*gx = read_2byte(disp_dir,MPU6050_RA_GYRO_XOUT_H);
	*gy = read_2byte(disp_dir,MPU6050_RA_GYRO_YOUT_H);
	*gz = read_2byte(disp_dir,MPU6050_RA_GYRO_ZOUT_H);
}

void get_accel(int16_t *ax,int16_t *ay,int16_t *az){
	
	*ax = read_2byte(disp_dir,MPU6050_RA_ACCEL_XOUT_H);
	*ay = read_2byte(disp_dir,MPU6050_RA_ACCEL_YOUT_H);
	*az = read_2byte(disp_dir,MPU6050_RA_ACCEL_ZOUT_H);
}

void get_ax_az(int16_t *ax,int16_t *az){
	*ax = read_2byte(disp_dir,MPU6050_RA_ACCEL_XOUT_H);
	*az = read_2byte(disp_dir,MPU6050_RA_ACCEL_ZOUT_H);
}

void get_gyro_gy(int16_t *gy){
	
	*gy = read_2byte(disp_dir,MPU6050_RA_GYRO_YOUT_H);
}
