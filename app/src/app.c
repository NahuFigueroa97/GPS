/*============================================================================
 * Autor: Nahuel Figueroa
 * Licencia:
 * Fecha: 24/01/2021
 *===========================================================================*/

// Inlcusiones
#include "app.h"         // <= Su propia cabecera
#include "sapi.h"        // <= Biblioteca sAPI
#include "gps.h"
#include "debouncing.h"

uint8_t data_t[10];
uint8_t validacion = 0;
#define size 64
volatile uint8_t buffer[size];
volatile int i = 0, state = 0, count = 0;

void UART3_IRQHandler(void) {
	buffer[i] = GpsRead();
	if (buffer[0] == '$') {
		state = (i == size) ? 1 : 0;
		i = (i == size) ? 0 : i + 1;
	} else {
		i = 0;
	}
	NVIC_ClearPendingIRQ(USART3_IRQn);
}

void aumentar() {
	count = (count == 4) ? 4 : count + 1;
}

void disminuir() {
	count = (count == 0) ? 0 : count - 1;
}

void (*funcion[])()= {aumentar,disminuir };

	int main(void) {
		boardConfig();
		GpsInit();
		PhoneInit();
		PhoneOn();
		initFSM();
		NVIC_EnableIRQ(USART3_IRQn);

		while ( TRUE) {

			debouncing(TEC1, funcion);
			debouncing(TEC2, funcion);

			if (count == 0) {
				longuitud(buffer, data_t);
			} else if (count == 1) {
				latitud(buffer, data_t);
			} else if (count == 2) {
				fecha(buffer, data_t);
			} else if (count == 3) {
				hora(buffer, data_t);
			} else if (count == 4) {
				velocidad(buffer, data_t);
			}

			if (state == 1) {

				state = 0;
				NVIC_DisableIRQ(USART3_IRQn);
				validacion = testing(buffer);

				if (validacion == true) {
					SendPhone(data_t);
				}
			}
			NVIC_EnableIRQ(USART3_IRQn);
		}
		return 0;
	}

