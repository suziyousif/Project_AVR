/*
 * main_gy80.c
 *
 *  Created on: 4 de dez de 2018
 *      Author: Suzi and Heloiza
 */

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "GY_80/ADXL345.h"
#include "lib/avr_usart.h"
#include "lib/avr_twi_master.h"
#include "GY_80/modbus.h"

int main(){
	/* USART initialization */
	FILE *usart_stream = get_usart_stream();
	USART_Init(B9600);

	/* coordinates variable (x, y, z) and Modbus packages */
	axis_t axis;
	package_t pkg;

	/* I2C for ADXL345 initialization */
	ADXL345_init();
	timer1_hardware_init();
	sei();

	GPIO_ClrBit(GPIO_B, PB0);

	while(1) {
		RTU_package_ADXL345(usart_stream, &pkg, &axis);
	}
	return 0;
}
