/*
 * debouncing.h
 *
 *  Created on: 15 abr. 2021
 *      Author: nahuu
 */

#ifndef LIBS_SAPI_SAPI_V0_5_2_SOC_PERIPHERALS_INC_DEBOUNCING_H_
#define LIBS_SAPI_SAPI_V0_5_2_SOC_PERIPHERALS_INC_DEBOUNCING_H_

typedef void (*funcion_t[])();


typedef enum {
	no_presionado, presionando, soltando
} estados_t;

typedef enum {
	boton_apretado, boton_no_apretado
} eventos_t;



void initFSM();
void debouncing(gpioMap_t boton, funcion_t funcion);

#endif /* LIBS_SAPI_SAPI_V0_5_2_SOC_PERIPHERALS_INC_DEBOUNCING_H_ */
