/*
 * DisplaySerial_Timer.c
 *
 *  Created on: 28 de set de 2018
 *      Author: Suzi
 */
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lib/avr_gpio.h"
#include "lib/bits.h"
#include "display/Relogio_mux_Timer.h"

int main(){
	/* Configura hardware do projeto */
	mux_disp_Init();
	button_config();
	timer0_hardwareInit();

	sei();
	while (1){
		iniciar_relogio();
	}
	return 0;
}
