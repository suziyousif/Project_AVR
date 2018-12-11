/*
 * modbus.c
 *
 *  Created on: 6 de dez de 2018
 *      Author: Heloiza S. and Suzi Y.
 */

#include "../lib/avr_usart.h"
#include <util/delay.h>
#include "ADXL345.h"
#include "modbus.h"

void RTU_package_ADXL345(FILE *usart_stream, package_t *pkg, axis_t *data)
{
	uint16_t sensor_reg = 0x05;		/*Initialization with sensor_0 Address */
	uint8_t i;

	/* Read ADXL345 sensor_reg */
	Multiple_Byte_Read(data, usart_stream);

	pkg->addr = MODBUS_ADDRESS;
	pkg->cmd = MODBUS_WRITE;

	for(i = 0; i < 3; i++){
		modbus_write(pkg, sensor_reg, data->coordinate[i]);

		pkg->crc = CRC16_2(pkg->package, 6);
		pkg->data = swap_bytes(pkg->data);
		pkg->reg = swap_bytes(pkg->reg);

		USART_tx(pkg->addr);
		USART_tx(pkg->cmd);
		USART_tx((uint8_t)(pkg->reg >> 8));
		USART_tx((uint8_t)(pkg->reg));
		USART_tx((int8_t)(pkg->data >> 8));
		USART_tx((int8_t)(pkg->data));
		USART_tx((uint8_t)(pkg->crc >> 8));
		USART_tx((uint8_t)(pkg->crc));

		pkg->addr = USART_rx();
		pkg->cmd = USART_rx();
		pkg->reg = USART_rx();
		pkg->reg = (pkg->reg <<8) | USART_rx();
		pkg->data = USART_rx();
		pkg->data = (pkg->data <<8) | USART_rx();
		pkg->crc = USART_rx();
		pkg->crc = (pkg->crc <<8) | USART_rx();

		/*Usart_Get_Data((uint8_t*)pkg->addr, 1);
		Usart_Get_Data((uint8_t*)pkg->cmd, 1);
		Usart_Get_Data((uint8_t*)pkg->reg, 2);
		Usart_Get_Data((uint8_t*)pkg->data, 2);
		Usart_Get_Data((uint8_t*)pkg->crc, 2);*/
		sensor_reg++;
		_delay_ms(3500);
	}
}

void modbus_write(package_t *pkg, uint16_t sensor_reg, uint16_t data)
{
	pkg->data = swap_bytes(data);
	pkg->reg = swap_bytes(sensor_reg);
}

uint16_t CRC16_2(uint8_t *buf, int len)
{
	uint32_t crc = 0xFFFF;
	int i;

	for (i = 0; i < len; i++)
	{
	crc ^= (uint16_t)buf[i]; // XOR byte into least sig. byte of crc
		for (int i = 8; i != 0; i--) { // Loop over each bit
			if ((crc & 0x0001) != 0) { // If the LSB is set
				crc >>= 1; // Shift right and XOR 0xA001
				crc ^= 0xA001;
			}
			else // Else LSB is not set
				crc >>= 1; // Just shift right
		}
	}
	return crc;
}

/***************************************************************
Call this function to swap the first two bytes with the last two
of a value of type uint16_t
*****************************************************************/
uint16_t swap_bytes(uint16_t data)
{
	int16_t new_data, data_;
	new_data = data >>8;
	data_ = data <<8;
	new_data |= data_;
	return new_data;
}
