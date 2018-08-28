/*
 * Pisca_LED.c
 *
 *  Created on: 21 de ago de 2018
 *      Author: Suzi
 */

/* Bibliotecas C e AVR */
#include <avr/io.h>
#include <util/delay.h>

/* Bibliotecas customizadas */
#include "lib/avr_gpio.h"
#include "lib/bits.h"

#define LED_PORT GPIO_B
#define LED_PIN	PB0

/*#define BTN_PORT GPIO_B
#define BTN_PIN PB1*/

/**
  * @brief  Configura hardware.
  * @param	Nenhum
  *
  * @retval Nenhum.
  */
void hardware_init(){

	LED_PORT->DDR = (1<<PB3)|(1<<PB2)|(1<<PB1)|(1<<PB0)|(1<<PB4);

	/*BTN_PORT->PORT = SET(BTN_PIN);*/
}


int main(){
	/* Configura hardware do projeto */
	hardware_init();

	/*liga o led quando apertar o botão*/
	/*while (1){
		if (GPIO_PinTstBit(BTN_PORT, BTN_PIN) == 0){
			GPIO_SetBit(LED_PORT, LED_PIN);
		}else{
			GPIO_ClrBit(LED_PORT, LED_PIN);
		}
	}*/

	/*toggle*/
	/*while (1){
		if (GPIO_PinTstBit(BTN_PORT, BTN_PIN) == 0){
			GPIO_CplBit(LED_PORT, LED_PIN);
		}
	}*/

	/*pisca um LED rapidamente 	3 vezes e 3 vez lentamente.*/
	uint8_t i;
	/*while (1){
		for (i = 0; i < 3; i++){
			GPIO_SetBit(LED_PORT, LED_PIN);
			_delay_ms(100);
			GPIO_ClrBit(LED_PORT, LED_PIN);
			_delay_ms(100);
		}
		for (i = 0; i < 3; i++){
			GPIO_SetBit(LED_PORT, LED_PIN);
			_delay_ms(500);
			GPIO_ClrBit(LED_PORT, LED_PIN);
			_delay_ms(500);
		}

	}*/
	while(1){
		for (i = 0; i < 5; i++){
			GPIO_SetBit(LED_PORT, i);
			_delay_ms(100);
			GPIO_ClrBit(LED_PORT, i);
			_delay_ms(100);
		}
	}
	return 0;
}
