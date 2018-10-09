/*
 * displaySerial_Timer.c
 *
 *  Created on: 28 de set de 2018
 *      Author: Suzi
 */
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>

#include "../lib/avr_gpio.h"
#include "../lib/bits.h"
#include "../lib/avr_timer.h"
#include "../lib/avr_extirq.h"

#include "Relogio_mux_Timer.h"

/* Tabela de conversão em flash: Anodo comum */
#ifdef COM_ANODO
const uint8_t conv_Table_[] PROGMEM = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02,
		0x78, 0x00, 0x18, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E};
#endif
/* Tabela de conversão em flash: Catodo comum */
#ifdef COM_CATODO
const uint8_t conv_Table_[] PROGMEM = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,
		0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
#endif

volatile uint8_t disp[6];
volatile uint8_t i = 0;
volatile uint8_t min = 0, hora = 0, aux;

void timer0_hardwareInit(){
	/*CONFIGURAÇÃO DE MODO NORMAL COM OVERFLOW, PRESCALER 256*/
	TIMER_0->TCCRA = 0;
	TIMER_0->TCCRB = SET(CS02);
	TIMER_IRQS->TC0.MASK = SET(TOIE0);
}

ISR(TIMER0_OVF_vect){
	uint8_t seg;
	DISPLAY_MUX_PORT->PORT = 0x0;  //desligar os displays
	seg = disp[i];
	DISPLAY_DATA_PORT->PORT = pgm_read_byte(&conv_Table_[seg]);		//mandar os dados
	SET_BIT(DISPLAY_MUX_PORT->PORT, i);		//selecionar o display
	i++;
	if (i == 4)
		i = 0;
}

//botão para incrementar a hora e o minuto
ISR(PCINT2_vect){
	if(!TST_BIT(PIND,PD2))
		aux = 0;
	if(!TST_BIT(PIND,PD3))
		aux = 1;
	if(!TST_BIT(PIND,PD4)){
		if (aux == 0)
			hora++;
		else
			min++;
	}
}

void button_config(){
	/* PINOS PD2 e PD3 como entrada e pull ups */
	GPIO_D->DDR  = ~((1 << PD2) | (1 << PD3) | (1 << PD4));
	GPIO_D->PORT = (1 << PD2) | (1 << PD3)| (1 << PD4);

	/* Configura modo */
	PCICR = (1 << PCIE2);
	/* Habilita IRQ do periférico */
	PCMSK2 = (1 << PCINT18) | (1 << PCINT19) | (1 << PCINT20);
}

void mux_disp_Init(){
	DISPLAY_DATA_PORT->DDR = 0xFF;	//saída
	DISPLAY_MUX_PORT->DDR = 0xF;	//saída
	DISPLAY_MUX_PORT->PORT = 0x0;	//desligar os displays
}

void set_disp(uint8_t display, uint8_t data){
	disp[display] = data;
}

void iniciar_relogio(){
	set_disp(0, min % 10);
	set_disp(1, min / 10);
	set_disp(2, hora % 10);
	set_disp(3, hora / 10);
}
