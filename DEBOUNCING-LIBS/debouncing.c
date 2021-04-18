/*
 * debouncing.c
 *
 *  Created on: 15 abr. 2021
 *      Author: nahuu
 */
#include "board.h"
#include "sapi.h"
#include "debouncing.h"

delay_t delay1;
uint8_t estado[]={no_presionado,no_presionado,no_presionado,no_presionado};
uint8_t evento[]={boton_no_apretado,boton_no_apretado,boton_no_apretado,boton_no_apretado};

void initFSM() {
	delayConfig(&delay1, 40);
}

void debouncing(gpioMap_t boton, funcion_t funcion) {

	switch (estado[boton-36]) {

	case no_presionado:


		evento[boton-36] =(gpioRead(boton) == 1) ? boton_no_apretado : boton_apretado;
		estado[boton-36] = (evento[boton-36] == boton_apretado) ? presionando : no_presionado;


            break;

	case presionando:

		evento[boton-36] =(gpioRead(boton) == 1) ? boton_no_apretado : boton_apretado;
		estado[boton-36] = (delayRead(&delay1)!=1) ? presionando : (evento[boton-36] == boton_no_apretado) ? no_presionado : soltando;

		break;

	case soltando:

		evento[boton-36] = (gpioRead(boton) == 1) ? boton_no_apretado : boton_apretado;
		estado[boton-36] = (evento[boton-36] == boton_apretado) ? soltando : no_presionado;

		if (estado[boton-36] == no_presionado) {
			(*(funcion[boton-36]))();
		}
		break;

	}
}



