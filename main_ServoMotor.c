/*
 * main_ServoMotor.c
 *
 *  Created on: 16 de out de 2018
 *      Author: Suzi
 */

#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include "ServoMotor/ServoMotor.h"
#include "display/lcd.h"
#include "Teclado_Matricial/TecladoMatricial.h"

int main(){

	/* Configura hardware do projeto */
	FILE *lcd_stream = configure_LCD_Motor();
	sei();
	while (1){
		Motor_control(lcd_stream);
	}
	return 0;
}

