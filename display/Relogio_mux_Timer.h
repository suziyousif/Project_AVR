/*
 * displaySerial_Timer.h
 *
 *  Created on: 28 de set de 2018
 *      Author: Suzi
 */

#ifndef DISPLAY_RELOGIO_MUX_TIMER_H_
#define DISPLAY_RELOGIO_MUX_TIMER_H_

#define COM_ANODO

#define DISPLAY_DATA_PORT GPIO_B
#define DISPLAY_MUX_PORT GPIO_C

ISR(TIMER0_OVF_vect);
ISR(PCINT2_vect);

void timer0_hardwareInit();
void set_disp(uint8_t display, uint8_t data);
void mux_disp_Init();
void iniciar_relogio();
void button_config();

#endif /* DISPLAY_RELOGIO_MUX_TIMER_H_ */
