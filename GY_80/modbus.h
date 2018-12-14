/*
 * modbus.h
 *
 *  Created on: 6 de dez de 2018
 *      Author: Heloiza S. and Suzi Y.
 */

#ifndef GY_80_MODBUS_H_
#define GY_80_MODBUS_H_

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>

#define MODBUS_ADDRESS 0x15
#define MODBUS_WRITE 0x01
#define MODBUS_READ 0x02
#define MODBUS_REG_SENSOR0 0x05

#define LED_PORT GPIO_B
#define LED_PIN	PB0

typedef union{
	struct{
		uint8_t addr;
		uint8_t cmd;
		uint16_t reg;
		uint16_t data;
		uint16_t crc;
	};
	uint8_t package[8];
}package_t;

void RTU_package_ADXL345(FILE *usart_stream, package_t *pkg, axis_t *data);
void modbus_write(package_t *pkg, uint16_t sensor_reg, uint16_t data);
uint16_t CRC16_2(uint8_t *buf, int len);
uint16_t swap_bytes(uint16_t data);
void timer1_hardware_init();


#endif /* GY_80_MODBUS_H_ */
