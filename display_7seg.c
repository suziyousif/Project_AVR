/*
 * display_7seg.c
 *
 *  Created on: 24 de ago de 2018
 *      Author: Suzi
 */
#include <avr/io.h>
#include <util/delay.h>

/* Bibliotecas customizadas */
#include "lib/avr_gpio.h"
#include "lib/bits.h"
#include "display/led_display.h"
#include "display/led_display_simple_mux.h"
#define BTN_PORT GPIO_B
#define BTN_PIN PB0

void hardware_init(){
	BTN_PORT->PORT = SET(BTN_PIN);
}
/*
int main(){
	uint8_t valor = 0;
	display_init();
	hardware_init();
	display_write(valor);
	while (1){
		if (GPIO_PinTstBit(BTN_PORT, BTN_PIN) == 0){
			if (valor <= 0x0f){
				display_write(valor);
				_delay_ms(500);
				valor++;
			}
			else{
				valor = 0;
			}
		}
	}
	return 0;
}*/

int main(){
	while (1){
		displaysInit(2);
		displaysWrite(22);
	}
	return 0;
}
