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

int main(){
	display_init();
	while (1){
		display_write(7);
	}
	return 0;
}
