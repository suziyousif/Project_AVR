/*
 * project_displaySerial.c
 *
 *  Created on: 7 de set de 2018
 *      Author: Suzi
 */


/* Bibliotecas C e AVR */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* Bibliotecas customizadas */
#include "lib/avr_gpio.h"
#include "lib/bits.h"
#include "display/displaySerial.h"

volatile uint8_t data = 0x3B;

ISR(INT0_vect)
{
	data++;
}

int main(){
	/* Configura hardware do projeto */
	DisplaySerial_init();

	/* PINOS PD2 como entrada e pull ups */
	GPIO_D->DDR  = ~((1 << PD2));
	GPIO_D->PORT = (1 << PD2);

	/* Configuração IRQ externas: INT0 na borda de descida */
	EICRA = (1 << ISC01);
	/* Habilita IRQ do periférico */
	EIMSK = (1 << INT0);

	sei();

	while (1){
		DisplaySerial_write(data);
	}
	return 0;

}
