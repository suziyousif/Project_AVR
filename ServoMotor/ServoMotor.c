/*
 * ServoMotor.c
 *
 *  Created on: 16 de out de 2018
 *      Author: Suzi
 */

#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include "../lib/avr_gpio.h"
#include "../lib/bits.h"
#include "../lib/avr_timer.h"
#include "../lib/avr_extirq.h"
#include "../display/lcd.h"
#include "ServoMotor.h"
#include "../Teclado_Matricial/TecladoMatricial.h"

prog_char msg1[]= "insira o angulo:";
prog_char msg2[]= " -->ok";

unsigned char tecla,k=0;
uint16_t duty_Cycle=0;
char buffer[4];
uint8_t angulo = 0;

void timer1_pwm_hardware_init(){
	/*PB1: pino OC1A como saída*/
	MOTOR_PORT->DDR = SET(PB2);

	/*Modo PWM modo rápido com comparação em OCR1B e pres = 64*/
	TIMER_1->TCCRA = SET(WGM11) | SET(WGM10) | SET(COM1B1);
	TIMER_1->TCCRB = SET(WGM13) | SET(WGM12) | SET(CS11) | SET(CS10);

	/* OCRA define frequência do PWM --> F=50Hz */
	TIMER_1->OCRA = 4999;

	/* OCRB define razão cíclica*/
	TIMER_1->OCRB = 249;
}

void set_DutyCycle(uint16_t duty){

	if (duty <= TIMER_1->OCRA)
		TIMER_1->OCRB = duty;
}

FILE* configure_LCD_Motor(){
	init_teclado_matricial();
	timer1_pwm_hardware_init();
	FILE *lcd_stream = inic_stream();
	inic_LCD_4bits();
	escreve_LCD_Flash(msg1);
	cmd_LCD(0xc0,0);
	return lcd_stream;
}

void Motor_control(FILE *lcd_stream){
	tecla = ler_teclado_matricial();
	if(tecla != 0xFF){
		///*caso o usuário apertar Enter*/
		if (tecla == 'B'){
			escreve_LCD_Flash(msg2);
			buffer[k] = '\0';
			angulo = atoi(buffer); 	//converter para int
			duty_Cycle = ((((uint32_t)angulo+90)*250)/180) + 125;  //cálculo da razão cíclica em função do angulo
			set_DutyCycle(duty_Cycle);
			//fprintf(lcd_stream, "%u", duty_Cycle);  //Debug
			k=0;
			_delay_ms(1000);
			cmd_LCD(0x01,0);
			escreve_LCD_Flash(msg1);
			cmd_LCD(0xc0,0);
		}
		else{
			/*enviar o caracter para o lcd*/
			lcd_putchar(tecla,lcd_stream);
			buffer[k++]=tecla;
			k = k & 3;		//proteção do Buffer
		}
	}
}



