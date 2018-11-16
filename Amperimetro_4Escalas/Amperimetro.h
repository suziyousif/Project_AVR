/*
 * Amperimetro.h
 *
 *  Created on: 3 de nov de 2018
 *      Author: Suzi
 */

#ifndef AMPERIMETRO_4ESCALAS_AMPERIMETRO_H_
#define AMPERIMETRO_4ESCALAS_AMPERIMETRO_H_

#define BUTTON_PORT GPIO_D
#define BUTTON_PIN PD6
#define N_SAMPLES 8

void button_config();
void adc_init();
void hardware_init();
void measure_current();

void f_stateA(void);
void f_stateB(void);
void f_stateC(void);
void f_stateD(void);

#endif /* AMPERIMETRO_4ESCALAS_AMPERIMETRO_H_ */
