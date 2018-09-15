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
#include <avr/interrupt.h>

/* Bibliotecas customizadas */
#include "lib/avr_gpio.h"
#include "lib/bits.h"
#include "display/led_display_simple_mux.h"

volatile uint8_t valor = 0;

ISR(PCINT1_vect)
{
	if (!TST_BIT(PINC,PC0))
		valor++;
}

int main(){
	/* Configura hardware do projeto */
	displaysInit(2);
	/* PC0 a PC2 como entrada e pull ups */
	GPIO_C->DDR = ~((1 << PC0));
	GPIO_C->PORT = (1 << PC0);

	/* Configura modo */
	PCICR = (1 << PCIE1);
	/* Habilita IRQ do periférico */
	PCMSK1 = (1 << PCINT8);

	/* Habilita IRQ global */
	sei();

	while (1){
		if (valor > 0xff)
			valor = 0;
		displaysWrite(valor);
	}
	return 0;

}
