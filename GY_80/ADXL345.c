/*
 * ADXL345.c
 *
 *  Created on: 3 de dez de 2018
 *      Author: Heloiza S. and Suzi Y.
 */


#include "ADXL345.h"
#include "../lib/avr_twi_master.h"

uint8_t I2C_buf[10]={0};

void ADXL345_init(){

	TWI_Master_Initialise();					/* Inicializa modo líder */

	I2C_buf[0] = ADXL345_ADDRESS_WRITE;			/* I2C Address */
	I2C_buf[1] = POWER_CTL;						/* Power-saving features control */
	I2C_buf[2] = MEASURE_ENABLE;					/* Enable measure bit D3 in register 0xD2 (POWER_CTL) */
	TWI_Start_Transceiver_With_Data(I2C_buf, 3); /* Send message to transceiver */
}

void Multiple_Byte_Read(axis_t *axis, FILE *file){
	I2C_buf[0] = ADXL345_ADDRESS_WRITE;
	I2C_buf[1] = AXIS_ADDRESS;
	TWI_Start_Transceiver_With_Data(I2C_buf, 2);
	I2C_buf[0] = ADXL345_ADDRESS_READ;
	TWI_Start_Transceiver_With_Data(I2C_buf, 7);
	TWI_Get_Data_From_Transceiver(I2C_buf, 7);
	axis->x = *(int16_t*) &I2C_buf[1];
	axis->y = *(int16_t*) &I2C_buf[3];
	axis->z = *(int16_t*) &I2C_buf[5];

	/*Axis Offset*/
	I2C_buf[0] = ADXL345_ADDRESS_WRITE;
	I2C_buf[1] = AXIS_OFF_ADDRESS;
	TWI_Start_Transceiver_With_Data(I2C_buf, 2);
	I2C_buf[0] = ADXL345_ADDRESS_READ;
	TWI_Start_Transceiver_With_Data(I2C_buf, 4);
	TWI_Get_Data_From_Transceiver(I2C_buf, 4);

	/* Calculate the coordinates -> (axis - axis_offset)*3.9mg/LSB */
	axis->x = (int32_t)((axis->x)-I2C_buf[1])*1000/256;
	axis->y = (int32_t)((axis->y)-I2C_buf[2])*1000/256;
	axis->z = (int32_t)((axis->z)-I2C_buf[3])*1000/256;
}

void print_axis(axis_t *axis, FILE *file){
	fprintf(file,"x= %d, y= %d, z= %d\n\r",
			axis->x, axis->y, axis->z);
}



