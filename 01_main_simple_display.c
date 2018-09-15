/*
 * 01_main_simple_display.c
 *
 *  Created on: Aug 16, 2018
 *      Author: Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 */


/* Bibliotecas C e AVR */
#include <avr/io.h>
#include <util/delay.h>

/* Bibliotecas customizadas */
#include "lib/avr_gpio.h"
#include "lib/bits.h"
#include "display/led_display.h"
#define BUTTON_PORT GPIO_B
#define BUTTON_PIN PB0

void hardware_init(){
	BUTTON_PORT->PORT = SET(BUTTON_PIN);
}
int main(){
	/* Configura hardware do projeto */
	hardware_init();
	display_init();

	uint8_t valor = 0;
	while (1){
		if (GPIO_PinTstBit(BUTTON_PORT, BUTTON_PIN) == 0){
			if (valor <= 0x0f){
				display_write(valor);
				valor++;
				_delay_ms(200);
			}else
				valor = 0;
		}
	}
	return 0;
}
