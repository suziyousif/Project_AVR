/*
 * displaySerial_Timer.h
 *
 *  Created on: 28 de set de 2018
 *      Author: Suzi
 */

#ifndef DISPLAY_DISPLAY_MUX_TIMER_H_
#define DISPLAY_DISPLAY_MUX_TIMER_H_

#define DISPLAY_SERIAL_PORT GPIO_B
#define DATA_PIN PB0
#define CLK_PIN PB1
#define STB_PIN PB2
#define COM_ANODO

void DisplaySerial_init_Timer();
void DisplaySerial_write_Timer(uint8_t hex_value);


#endif /* DISPLAY_DISPLAY_MUX_TIMER_H_ */
