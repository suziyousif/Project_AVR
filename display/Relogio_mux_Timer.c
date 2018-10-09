/*
 * Relogio_mux_Timer.c
 *
 *  Created on: 28 de set de 2018
 *      Author: Suzi yousif
 */
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
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
volatile uint8_t i = 0, min = 0, hora = 0, seg = 0;

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
	DISPLAY_DATA_PORT->PORT = pgm_read_byte(&conv_Table_[seg]);		//enviar os dados
	SET_BIT(DISPLAY_MUX_PORT->PORT, i);		//selecionar o display

	i++;
	if (i == 6)
		i = 0;
}

void timer1_hardwareInit(){
	/*CONFIGURAÇÃO DE MODO CTC, PRESCALER = 1024, COMPARAÇÃO=15625 para tempo de 1s*/
	TIMER_1->TCCRA = 0;
	TIMER_1->TCCRB = SET(WGM12) | SET(CS12) | SET(CS10);
	TIMER_1->OCRA = 15624;

	/* Habilitação da IRQ: capture pois o top é OCR1A */
	TIMER_IRQS->TC1.BITS.OCIEA = 1;
}

ISR(TIMER1_COMPA_vect){
	if(seg >= 59){
		seg = 0;
		if(min >= 59){
			min = 0;
			if(hora >= 23){
				hora = 0;
			}
			hora++;
		}
		min++;
	}
	seg++;
}

/*botão para incrementar a hora, o minuto e o segundo*/
ISR(PCINT0_vect){
	if(!TST_BIT(PINB,PB0)){
		if(hora < 24)
			hora++;
		else
			hora = 0;
	}
	if(!TST_BIT(PINB,PB1)){
		if(min < 59)
			min++;
		else
			min = 0;
	}
	if(!TST_BIT(PINB,PB2)){
		if(seg < 59)
			seg++;
		else
			seg = 0;
	}
}

void button_config(){
	/* PINOS como entrada e pull ups */
	GPIO_B->DDR  = ~((1 << PB0) | (1 << PB1) | (1 << PB2));
	GPIO_B->PORT = (1 << PB0) | (1 << PB1)| (1 << PB2);

	/* Configura modo */
	PCICR = (1 << PCIE0);

	/* Habilita IRQ do periférico */
	PCMSK0 = (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2);
}

void mux_disp_Init(){
	DISPLAY_DATA_PORT->DDR = 0x7F;	//configuração como saída
	DISPLAY_MUX_PORT->DDR = 0x3F;	//configuração como saída
	DISPLAY_MUX_PORT->PORT = 0x0;	//desligar os displays
}

void set_disp(uint8_t display, uint8_t data){
	disp[display] = data;
}

void iniciar_relogio(){
	set_disp(0, seg % 10);
	set_disp(1, seg / 10);
	set_disp(2, min % 10);
	set_disp(3, min / 10);
	set_disp(4, hora % 10);
	set_disp(5, hora / 10);
}

void hardware_config_relogio(){
	mux_disp_Init();
	button_config();
	timer0_hardwareInit();
	timer1_hardwareInit();
}
