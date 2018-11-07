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
#include "lib/avr_timer.h"

#define BUTTON_PORT GPIO_D
#define BUTTON_PIN PD6
volatile uint16_t valor_adc = 0;
//volatile float corrente = 0;

prog_char msg1[]= "Escala:";
prog_char msg2[]= "Corrente:";
//volatile uint8_t i =0;

void button_config(){
	/* PINOS como entrada e pull ups */
	GPIO_D->DDR  = ~(1 << PD6);
	GPIO_D->PORT = (1 << PD6);
	/* Configura modo */
	PCICR = (1 << PCIE2);
	/* Habilita IRQ do periférico */
	PCMSK2 = (1 << PCINT22);
}

void adc_init(){
	/* Ref externa no pino AVCC com capacitor de 100n em VREF.
	 * Habiltiação apenas no Canal 0 */
	ADCS->AD_MUX = SET(REFS0);
	/* Habilita AD: * Conversão contínua * IRQ ativo * Prescaler de 128 */
	ADCS->ADC_SRA = SET(ADEN)  |	//ADC Enable
					SET(ADSC)  | 	// ADC Start conversion
					SET(ADATE) |	// ADC Auto Trigger
					SET(ADPS0) | SET(ADPS1) | SET(ADPS2) | //ADPS[0..2] AD Prescaler selection
					SET(ADIE); 		//AD IRQ ENABLE
	/* Desabilita hardware digital de PC0 a PC3 */
	ADCS->DIDr0.BITS.ADC0 = 1;
	ADCS->DIDr0.BITS.ADC1 = 1;
	ADCS->DIDr0.BITS.ADC2 = 1;
	ADCS->DIDr0.BITS.ADC3 = 1;
}

ISR(ADC_vect)
{
	valor_adc = ADC;
}

/*-----------------------------------------------*/
void f_stateA(void);
void f_stateB(void);
void f_stateC(void);
void f_stateD(void);

/* Definição dos estados */
typedef enum {
	STATE_A,
	STATE_B,
	STATE_C,
	STATE_D,
	NUM_STATES
} state_t;

/* Definição da estrutura mantenedora do vetor de estados */
typedef struct {
	state_t myState;
	void (*func)(void);
}fsm_t;

/* Mapeamento entre estado e funções */
fsm_t myFSM[] = {
	{ STATE_A, f_stateA },
	{ STATE_B, f_stateB },
	{ STATE_C, f_stateC },
	{ STATE_D, f_stateD },

};

/* Estado atual */
volatile state_t curr_state = STATE_A;
/*-----------------------------------------------*/
union{
	struct{
		uint16_t decimal:4;
		uint16_t inteiro:6;
	};
	uint16_t valor;
}x;
FILE *lcd_stream;
int main(){
	/* Configura hardware do projeto */
	button_config();
	adc_init();

	lcd_stream= inic_stream();
	inic_LCD_4bits();
	escreve_LCD_Flash(msg1);
	//cmd_LCD(0xc0,0);
	sei();
	while (1){
		(*myFSM[curr_state].func)();
		//x.valor = valor_adc;
		/*corrente = (valor_adc) * 49/100;
		corrente = corrente*100/42;
		corrente = (corrente*10 / 60)/10 - 9.897;
		fprintf(lcd_stream,"%d", corrente);
		if (corrente == 9){
			lcd_putchar('*', lcd_stream);
		}*/

		/*x.valor = (valor_adc-516)*80/254;
		fprintf(lcd_stream,"%d", x.inteiro);
		lcd_putchar('.', lcd_stream);
		fprintf(lcd_stream,"%02d", (x.decimal)*100/16);*/
		_delay_ms(1000);
	}
	return 0;
}


ISR(PCINT2_vect){
	static uint8_t i = 0;
	if(!!TST_BIT(PIND,PD6))
		i++;
	CLR_BIT(ADCS->ADC_SRA, ADEN);
	switch (i) {
	case 1:
		curr_state = STATE_A;
		ADCS->AD_MUX = SET(REFS0);
		break;
	case 2:
		curr_state = STATE_B;
		ADCS->AD_MUX = SET(REFS0) | SET(MUX0);
		break;
	case 3:
		curr_state = STATE_C;
		ADCS->AD_MUX = SET(REFS0) | SET(MUX1);
		break;
	case 4:
		curr_state = STATE_D;
		ADCS->AD_MUX = SET(REFS0) | SET(MUX0) | SET(MUX1);
		break;
	default:
		i = 0;
		break;
	}
	SET_BIT(ADCS->ADC_SRA, ADEN);
	SET_BIT(ADCS->ADC_SRA, ADSC);
}

void f_stateA(void){
	x.valor = (valor_adc-516)*80/254;
	cmd_LCD(0x01, 0);
	fprintf(lcd_stream,"%d", valor_adc);
	fprintf(lcd_stream,"Escala: 10A");
	cmd_LCD(0xc0, 0);
	fprintf(lcd_stream,"corrente: %d.%02d", x.inteiro, (x.decimal)*100/16);
	//lcd_putchar('.', lcd_stream);
	//fprintf(lcd_stream,"%02d", (x.decimal)*100/16);
}

void f_stateB(void){
	x.valor = (valor_adc-344)*8/17;
	cmd_LCD(0x01, 0);
	fprintf(lcd_stream,"%d", valor_adc);
	fprintf(lcd_stream,"Escala: 20A");
	cmd_LCD(0xc0, 0);
	fprintf(lcd_stream,"corrente: %d.%02d", x.inteiro, (x.decimal)*100/16);
}

void f_stateC(void){
	x.valor = ((uint32_t)valor_adc-205)*640/819;
	cmd_LCD(0x01, 0);
	fprintf(lcd_stream,"Escala: 40A");
	cmd_LCD(0xc0, 0);
	fprintf(lcd_stream,"corrente: %d.%02d", x.inteiro, (x.decimal)*100/16);
}

void f_stateD(void){
	x.valor = ((uint32_t)valor_adc-170)*400/427;
	cmd_LCD(0x01, 0);
	fprintf(lcd_stream,"Escala: 50A");
	cmd_LCD(0xc0, 0);
	fprintf(lcd_stream,"corrente: %d.%02d", x.inteiro, (x.decimal)*100/16);
}

