/*
 * main.c
 *
 *  Created on: Nov 10, 2016
 *      Author: xtarke
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lib/bits.h"
#include "one-wire/one_wire.h"


int main(){


	uint8_t temp_LSB, temp_MSB;


	while(1){

		reset_1w();						//reset do sensor (a resposta de presença é retornada mas não avaliada).
		write_byte_1w(0xCC);			//comando para pular ROM (só 1 dispositivo no barramento).
		write_byte_1w(0x44);			//manda iniciar a conversão

		reset_1w();
		write_byte_1w(0xCC);
		write_byte_1w(0xBE);			//avisa que quer ler a memória

		temp_LSB = read_byte_1w();		//só interesse em ler os dois bytes da temperatura
		temp_MSB = read_byte_1w();

		_delay_ms(500);
	}



	return 0;
}
