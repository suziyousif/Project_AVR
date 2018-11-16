/*
 * main_Amperimetro.c
 *
 *  Created on: 3 de nov de 2018
 *      Author: Suzi Yousif
 */
#include <stdio.h>
#include <stdlib.h>
#include "Amperimetro_4Escalas/Amperimetro.h"

int main(){
	/* Configura hardware do projeto */
	hardware_init();

	while (1){
		measure_current();
	}
	return 0;
}
