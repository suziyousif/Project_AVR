/*
 * main_Amperimetro.c
 *
 *  Created on: 3 de nov de 2018
 *      Author: Suzi Yousif
 */


#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include "display/lcd.h"
#include "Amperimetro_4Escalas/Amperimetro.h"
#include "lib/avr_gpio.h"
#include "lib/avr_adc.h"

#define BUTTON_PORT GPIO_D
#define BUTTON_PIN PD6

prog_char msg1[]= "Escala:";
prog_char msg2[]= "Corrente:";
volatile uint8_t i =0;

ISR(PCINT2_vect){
	if (i > 3)
		i = 0;
	if(!!TST_BIT(PIND,PD6))
		i++;
}
void button_config(){
	/* PINOS como entrada e pull ups */
	GPIO_D->DDR  = ~(1 << PD6);
	GPIO_D->PORT = (1 << PD6);
	/* Configura modo */
	PCICR = (1 << PCIE2);
	/* Habilita IRQ do periférico */
	PCMSK2 = (1 << PCINT22);
}

volatile uint16_t valor_adc = 0;
volatile double corrente = 0;

void adc_init(){

	/* Ref externa no pino AVCC com capacitor de 100n em VREF.
	 * Habiltiação apenas no Canal 0 */
	ADCS->AD_MUX = SET(REFS0);
	/* Habilita AD:
	 * Conversão contínua
	 * IRQ ativo
	 * Prescaler de 128 */
	ADCS->ADC_SRA = SET(ADEN)  |	//ADC Enable
					SET(ADSC)  | 	// ADC Start conversion
					SET(ADATE) |	// ADC Auto Trigger
					SET(ADPS0) | SET(ADPS1) | SET(ADPS2) | //ADPS[0..2] AD Prescaler selection
					SET(ADIE); 		//AD IRQ ENABLE

	/* Desabilita hardware digital de PC0 */
	ADCS->DIDr0.BITS.ADC0 = 1;

}

ISR(ADC_vect)
{
	valor_adc = ADC;
}

int main(){

	/* Configura hardware do projeto */
	button_config();
	adc_init();

	FILE *lcd_stream = inic_stream();
	inic_LCD_4bits();
	escreve_LCD_Flash(msg1);
	//cmd_LCD(0xc0,0);
	sei();
	while (1){
		fprintf(lcd_stream,"%d", valor_adc);
		//corrente = ((float)valor_adc) * 19.53426/1000 -10.0516;
		corrente = ((double)valor_adc) * 5/1024;
		corrente = corrente*10/42;
		corrente = (corrente - 0.5954806)/0.0601656;
		fprintf(lcd_stream,"%f", corrente);
		_delay_ms(1000);
	}
	return 0;
}
