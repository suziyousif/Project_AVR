/*
 * main_ServoMotor.c
 *
 *  Created on: 16 de out de 2018
 *      Author: Suzi
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include "ServoMotor/ServoMotor.h"
#include "display/lcd.h"
#include "Teclado_Matricial/TecladoMatricial.h"
prog_char msg[]= "insira o angulo:";

int main(){
	unsigned char c, i=0xC0;
	uint8_t G = 63;
	/* Configura hardware do projeto */
	init_teclado_matricial();
	timer0_hardwareInit_();
	timer1_pwm_hardware_init();
	FILE *lcd_stream = inic_stream();
	inic_LCD_4bits();
	escreve_LCD_Flash(msg);
	sei();

	while (1){
		c = ler_teclado();
		cmd_LCD(i,0); //vai para 2ª linha do lcd
		if(c != 0xFF){
			/*enviar o caracter para o lcd*/
			lcd_putchar(c,lcd_stream);
		}
		set_DutyCicle(G);
		G+=30;
		if (G > 156)
			G = 63;
	}
	return 0;
}

