/*
 * gps.c
 *
 *  Created on: 7 abr. 2021
 *      Author: nahuel figueroa
 */

#include "board.h"
#include "sapi.h"
#include "gps.h"

static bool estado;

void GpsInit() {

	Chip_SCU_PinMux(2, 3, MD_PUP, FUNC2);
	Chip_SCU_PinMux(2, 4, MD_PLN | MD_EZI | MD_ZI, FUNC2);
	Chip_UART_Init(LPC_USART3);
	Chip_UART_SetBaud(LPC_USART3, 9600);
	Chip_UART_SetupFIFOS(LPC_USART3,
			UART_FCR_FIFO_EN | UART_FCR_TX_RS | UART_FCR_RX_RS
					| UART_FCR_TRG_LEV0);
	Chip_UART_IntEnable(LPC_USART3, UART_IER_RBRINT);

}

void PhoneInit() {
	Chip_SCU_PinMux(1, 15, MD_PUP, FUNC1);
	Chip_SCU_PinMux(1, 16, MD_PLN | MD_EZI | MD_ZI, FUNC1);
	Chip_UART_Init(LPC_USART2);
	Chip_UART_SetBaud(LPC_USART2, 9600);
	Chip_UART_SetupFIFOS(LPC_USART2,
			UART_FCR_FIFO_EN | UART_FCR_TX_RS | UART_FCR_RX_RS
					| UART_FCR_TRG_LEV0);
	Chip_UART_IntEnable(LPC_USART2, UART_IER_RBRINT);
}

void SendPhone(uint8_t *prt) {
	while (*prt != '?') {
		while ((Chip_UART_ReadLineStatus( LPC_USART2) & UART_LSR_THRE) == FALSE)
			;
		Chip_UART_SendByte( LPC_USART2, *prt);
		prt++;
	}
	Chip_UART_SendByte( LPC_USART2, '\r\n');
}

uint8_t GpsRead() {
	if (Chip_UART_ReadLineStatus(LPC_USART3) & UART_LSR_RDR)
		return (uint8_t) Chip_UART_ReadByte(LPC_USART3);
}

void PhoneOn() {
	Chip_UART_TXEnable(LPC_USART2);
}

void PhoneOff() {
	Chip_UART_TXDisable(LPC_USART2);
}

void longuitud(volatile uint8_t *buffer, uint8_t *longuitud) {

	*longuitud = '-';
	*(longuitud + 1) = *(buffer + 19);
	*(longuitud + 2) = *(buffer + 20);
	*(longuitud + 3) = ':';
	*(longuitud + 4) = *(buffer + 21);
	*(longuitud + 5) = *(buffer + 22);
	*(longuitud + 6) = '"';
	*(longuitud + 7) = '?';
}

void latitud(volatile uint8_t *buffer, uint8_t *latitud) {

	*latitud = '-';
	*(latitud + 1) = *(buffer + 33);
	*(latitud + 2) = *(buffer + 34);
	*(latitud + 3) = ':';
	*(latitud + 4) = *(buffer + 35);
	*(latitud + 5) = *(buffer + 36);
	*(latitud + 6) = '"';
	*(latitud + 7) = '?';
}

void fecha(volatile uint8_t *buffer, uint8_t *fecha) {

	*fecha = *(buffer + 53);
	*(fecha + 1) = *(buffer + 54);
	*(fecha + 2) = '/';
	*(fecha + 3) = *(buffer + 55);
	*(fecha + 4) = *(buffer + 56);
	*(fecha + 5) = '/';
	*(fecha + 6) = *(buffer + 57);
	*(fecha + 7) = *(buffer + 58);
	*(fecha + 8) = '?';
}

void hora(volatile uint8_t *buffer, uint8_t *hora) {

	*(hora) = *(buffer + 7);
	*(hora + 1) = *(buffer + 8);
	*(hora + 2) = ':';
	*(hora + 3) = *(buffer + 9);
	*(hora + 4) = *(buffer + 10);
	*(hora + 5) = ':';
	*(hora + 6) = *(buffer + 11);
	*(hora + 7) = *(buffer + 12);
	*(hora + 8) = '?';

}

void velocidad(volatile uint8_t *buffer, uint8_t *velocidad) {

	*(velocidad) = *(buffer + 46);
	*(velocidad + 1) = *(buffer + 47);
	*(velocidad + 2) = *(buffer + 48);
	*(velocidad + 3) = *(buffer + 49);
	*(velocidad + 4) = *(buffer + 50);
	*(velocidad + 5) = '?';

}

bool testing(volatile uint8_t *buffer) {

	if (*(buffer + 1) == 'G' && *(buffer + 2) == 'P' && *(buffer + 3) == 'R'
			&& *(buffer + 4) == 'M' && *(buffer + 5) == 'C'
			&& *(buffer + 17) == 'A') {
		estado = true;
	} else
		estado = false;
	return estado;

}


