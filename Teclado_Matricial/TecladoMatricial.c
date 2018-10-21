/*
 * TecladoMatricial.c
 *
 *  Created on: 16 de out de 2018
 *      Author: Suzi
 */

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "../lib/avr_timer.h"
#include "../lib/avr_extirq.h"
#include "TecladoMatricial.h"
#include "../lib/avr_gpio.h"
#include "../lib/bits.h"
/*Matriz para a decodoficação do teclado*/
const unsigned char teclado[4][4] PROGMEM = {{'1', '2', '3', 'F'},
											{'4', '5', '6', 'E'},
											{'7', '8', '9', 'D'},
											{'A', '0', 'B', 'C'}};
volatile unsigned char tecla = 0xFF;
void init_teclado_matricial(){
	TECLADO_PORT->DDR = 0x0F; //definição de entrada (PD4 a PD7) e saída (PD0 a PD3) do teclado
	TECLADO_PORT->PORT = 0xFF; //Habilitação do Pull-up das entradas e colocar as colunas em 1
}

void timer0_hardwareInit_(){
	/*CONFIGURAÇÃO DE MODO CTC, PRESCALER = 1024, COMPARAÇÃO=157 para tempo de 10ms*/
	TIMER_0->TCCRA = SET(WGM01) ;
	TIMER_0->TCCRB = SET(CS02) | SET(CS00);
	TIMER_0->OCRA = 157;

	/* Habilitação da IRQ: capture pois o top é OCR1A */
	TIMER_IRQS->TC0.BITS.OCIEA = 1;
}

ISR(TIMER0_COMPA_vect){
	unsigned char m, n;
	/*varredura das colunas 'n'*/
	for(n = 0; n < 4; n++){
		/*apagar o bit da coluna*/
		GPIO_ClrBit(TECLADO_PORT, n);
		/*varredura das linhas*/
		for (m = 0; m < 4; m++){
			if(!GPIO_PinTstBit(TECLADO_PORT, (m+4))){
				tecla = pgm_read_byte(&teclado[m][n]);
			}
		}
		GPIO_SetBit(TECLADO_PORT, n);
	}
}

unsigned char ler_teclado(){
	return tecla;
}

