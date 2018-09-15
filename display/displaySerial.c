/*
 * displaySerial.c
 *
 *  Created on: 7 de set de 2018
 *      Author: Suzi
 */
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>
#include "../lib/avr_gpio.h"
#include "../lib/bits.h"
#include "displaySerial.h"

/* Tabela de conversão em flash: Anodo comum */
#ifdef COM_ANODO
const uint8_t conv_Table[] PROGMEM = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02,
		0x78, 0x00, 0x18, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E};
#endif

/* Tabela de conversão em flash: Catodo comum */
#ifdef COM_CATODO
const uint8_t conv_Table[] PROGMEM = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,
		0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
#endif


void DisplaySerial_init()
{
	/* Configuração de portas como saída*/
	DISPLAY_SERIAL_PORT->DDR |= (1 << PB0) | (1 << PB1) | (1 << PB2);
}

void DisplaySerial_write(uint8_t hex_value)
{
	uint8_t data = hex_value;
	int8_t i;

	GPIO_ClrBit(DISPLAY_SERIAL_PORT, STB_PIN);

	while (hex_value){
		data = (0x0f & hex_value); 		/* pegar somente um dígito */
		data = pgm_read_byte(&conv_Table[data]);
		for (i = 8; i > 0; i--){
			GPIO_ClrBit(DISPLAY_SERIAL_PORT, CLK_PIN);
			if (TST_BIT(data, (i-1)))
				GPIO_SetBit(DISPLAY_SERIAL_PORT, DATA_PIN);
			else
				GPIO_ClrBit(DISPLAY_SERIAL_PORT, DATA_PIN);

			_delay_ms(10);
			GPIO_SetBit(DISPLAY_SERIAL_PORT, CLK_PIN);
			_delay_ms(10);
		}
		hex_value = hex_value >> 4;  /* Obtém próximo dígito  */
	}

	GPIO_SetBit(DISPLAY_SERIAL_PORT, STB_PIN);
}
