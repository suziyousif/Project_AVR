/*
 * Amperimetro.c
 *
 *  Created on: 3 de nov de 2018
 *      Author: Suzi
 */

#include "Amperimetro.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/bits.h"
#include "../lib/avr_gpio.h"
#include "../display/lcd.h"
#include "../lib/avr_adc.h"

volatile uint16_t ADC_value = 0, current=0;
volatile uint16_t buffer[N_SAMPLES];
FILE *lcd_stream;

union{
	struct{
		uint16_t decimal:4;
		uint16_t integer:6;
	};
	uint16_t value;
}x;

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

void measure_current(){
	_delay_ms(1000);
	(*myFSM[curr_state].func)();
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
	static uint8_t j=0;
	uint16_t adc_v = ADC;

	ADC_value = ADC_value - buffer[j] + adc_v;
	buffer[j++] = adc_v;

	j&=0x7;
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

//Verificação do botão para escolher a escala
ISR(PCINT2_vect){
	static uint8_t i=1;
	if(!!TST_BIT(PIND,PD6))
		i++;
	CLR_BIT(ADCS->ADC_SRA, ADEN);							//ADC Disable
	switch (i) {
	case 1:
		curr_state = STATE_A;
		ADCS->AD_MUX = SET(REFS0);							//ADC0
		break;
	case 2:
		curr_state = STATE_B;
		ADCS->AD_MUX = SET(REFS0) | SET(MUX0);				//ADC1
		break;
	case 3:
		curr_state = STATE_C;
		ADCS->AD_MUX = SET(REFS0) | SET(MUX1);				//ADC2
		break;
	case 4:
		curr_state = STATE_D;
		ADCS->AD_MUX = SET(REFS0) | SET(MUX0) | SET(MUX1);	//ADC3
		i = 0;
		break;
	default:
		break;
	}
	SET_BIT(ADCS->ADC_SRA, ADEN);		//ADC Enable
	SET_BIT(ADCS->ADC_SRA, ADSC);		// ADC Start conversion
}

void hardware_init(){
	button_config();
	lcd_stream= inic_stream();
	inic_LCD_4bits();
	adc_init();
	sei();
}

void f_stateA(void){
	current = ADC_value>>3;  //Média móvel (T/8)

	/*calculo da corrente:
	 * retirou-se o offset -> p/ I=0 -> ADC=(0.6*Ganho*1024)/5
	 * ex: Ganho=10 -> ADC=516 -> (valor_ADC-516)
	 * valor max. ADC s/ offset=1024-516 = 508
	 * 10.0A -- 508
	 *   I   -- valor_adc_s/offset
	 * I = (valor_adc - offset)*10.0/508
	 */

	x.value = (current-516)*80/254;
	cmd_LCD(0x01, 0);			//limpar o lcd
	fprintf(lcd_stream,"Escala: 10A");
	cmd_LCD(0xc0, 0);			//2ª linha
	fprintf(lcd_stream,"corrente:%d.%02d", x.integer, (x.decimal)*100/16);
	//Máx. Escala
	if (x.integer >= 9)
		lcd_putchar('*', lcd_stream);
}

void f_stateB(void){
	current = ADC_value>>3;
	x.value = (current-344)*8/17;
	cmd_LCD(0x01, 0);
	fprintf(lcd_stream,"Escala: 20A");
	cmd_LCD(0xc0, 0);
	fprintf(lcd_stream,"corrente:%d.%02d", x.integer, (x.decimal)*100/16);
	//Máx. Escala
	if (x.integer >= 18)
		lcd_putchar('*', lcd_stream);
}

void f_stateC(void){
	current = ADC_value>>3;
	x.value = ((uint32_t)current-205)*640/819;
	cmd_LCD(0x01, 0);
	fprintf(lcd_stream,"Escala: 40A");
	cmd_LCD(0xc0, 0);
	fprintf(lcd_stream,"corrente:%d.%02d", x.integer, (x.decimal)*100/16);
	//Máx. Escala
	if (x.integer >= 36)
		lcd_putchar('*', lcd_stream);
}

void f_stateD(void){
	current = ADC_value>>3;
	x.value = ((uint32_t)current-170)*400/427;
	cmd_LCD(0x01, 0);
	fprintf(lcd_stream,"Escala: 50A");
	cmd_LCD(0xc0, 0);
	fprintf(lcd_stream,"corrente:%d.%02d", x.integer, (x.decimal)*100/16);
	//Máx. Escala
	if (x.integer >= 45)
		lcd_putchar('*', lcd_stream);
}
