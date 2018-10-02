/*
 * DisplaySerial_Timer.c
 *
 *  Created on: 28 de set de 2018
 *      Author: Suzi
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* Bibliotecas customizadas */
#include "lib/avr_gpio.h"
#include "lib/bits.h"
#include "display/display_mux_Timer.h"

volatile uint8_t data = 0x3B;



int main(){
	/* Configura hardware do projeto */
	DisplaySerial_init_Timer();


	while (1){
		DisplaySerial_write_Timer(data);
	}
	return 0;

}

