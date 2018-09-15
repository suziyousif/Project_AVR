/*
 * displaySerial.h
 *
 *  Created on: 7 de set de 2018
 *      Author: Suzi
 */

#ifndef DISPLAY_DISPLAYSERIAL_H_
#define DISPLAY_DISPLAYSERIAL_H_

#define DISPLAY_SERIAL_PORT GPIO_B
#define DATA_PIN PB0
#define CLK_PIN PB1
#define STB_PIN PB2
#define COM_ANODO

void DisplaySerial_init();
void DisplaySerial_write(uint8_t hex_value);

#endif /* DISPLAY_DISPLAYSERIAL_H_ */
