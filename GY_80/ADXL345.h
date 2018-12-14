/*
 * ADXL345.h
 *
 *  Created on: 3 de dez de 2018
 *      Author: Heloiza S. and Suzi Y.
 */

#ifndef GY_80_ADXL345_H_
#define GY_80_ADXL345_H_

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>

#define ADXL345_ADDRESS 0x53
#define ADXL345_ADDRESS_WRITE 0xA6
#define ADXL345_ADDRESS_READ 0xA7
#define AXIS_ADDRESS 0x32
#define AXIS_OFF_ADDRESS 0x1E
#define POWER_CTL 0x2D
#define MEASURE_ENABLE 0x08

typedef union
{
	struct {
		int16_t x;
		int16_t y;
		int16_t z;
	};
	int16_t coordinate[3];
}axis_t;

void ADXL345_init();
void Multiple_Byte_Read(axis_t *axis);
void print_axis(axis_t *axis, FILE *file);

#endif /* GY_80_ADXL345_H_ */
