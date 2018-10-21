/*
 * ServoMotor.c
 *
 *  Created on: 16 de out de 2018
 *      Author: Suzi
 */

#include <avr/interrupt.h>
#include <stdint.h>

#include "../lib/avr_gpio.h"
#include "../lib/bits.h"
#include "../lib/avr_timer.h"
#include "../lib/avr_extirq.h"
#include "../display/lcd.h"
#include "ServoMotor.h"

volatile int angulo = 45;

void timer1_pwm_hardware_init(){
	/*PB1: pino OC1A como saída*/
	MOTOR_PORT->DDR = SET(PB2);

	/*Modo PWM modo rápido com comparação em OCR1B e pres = 256*/
	TIMER_1->TCCRA = SET(WGM11) | SET(WGM10) | SET(COM1B1);
	TIMER_1->TCCRB = SET(WGM13) | SET(WGM12) | SET(CS12);

	/* OCRA define frequência do PWM --> F=50Hz */
	TIMER_1->OCRA = 1249;

	/* OCRB define razão cíclica*/
	TIMER_1->OCRB = 63;
}

void set_DutyCicle(uint8_t duty){

	if (duty <= TIMER_1->OCRA)
		TIMER_1->OCRB = duty;
}

