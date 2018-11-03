/*
 *  main_RelogioMux_Timer.c
 *
 *  Created on: 28 de set de 2018
 *      Author: Suzi yousif
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include "Relogio/Relogio_mux_Timer.h"

int main(){

	/* Configura hardware do projeto */
	hardware_config_relogio();

	sei();

	while (1){
		relogio();
	}
	return 0;
}
