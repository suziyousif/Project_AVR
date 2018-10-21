/*
 * TecladoMatricial.h
 *
 *  Created on: 16 de out de 2018
 *      Author: Suzi
 */

#ifndef TECLADO_MATRICIAL_TECLADOMATRICIAL_H_
#define TECLADO_MATRICIAL_TECLADOMATRICIAL_H_

#define TECLADO_PORT GPIO_D
ISR(TIMER0_COMPA_vect);
void timer0_hardwareInit_();

void init_teclado_matricial();
unsigned char ler_teclado();

#endif /* TECLADO_MATRICIAL_TECLADOMATRICIAL_H_ */
