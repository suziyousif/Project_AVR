/*
 * Relogio_mux_Timer.h
 *
 *  Created on: 28 de set de 2018
 *      Author: Suzi yousif
 */

#ifndef DISPLAY_RELOGIO_MUX_TIMER_H_
#define DISPLAY_RELOGIO_MUX_TIMER_H_

#define COM_ANODO

#define DISPLAY_DATA_PORT GPIO_D
#define DISPLAY_MUX_PORT GPIO_C

/*habilição dos Interrupções*/
ISR(TIMER0_OVF_vect);
ISR(PCINT0_vect);
ISR(TIMER1_COMPA_vect);

/* Inicialização do timer */
void timer0_hardwareInit();
void timer1_hardwareInit();

/*configuração dos botões*/
void button_config();

/*configuração dos displays*/
void mux_disp_Init();
void set_disp(uint8_t display, uint8_t data);
void iniciar_relogio();

/*configuração geral do hardware*/
void hardware_config_relogio();

#endif /* DISPLAY_RELOGIO_MUX_TIMER_H_ */
