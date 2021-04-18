/*
 * gps.h
 *
 *  Created on: 8 abr. 2021
 *      Author: nahuu
 */

#ifndef LIBS_SAPI_SAPI_V0_5_2_SOC_PERIPHERALS_INC_GPS_H_
#define LIBS_SAPI_SAPI_V0_5_2_SOC_PERIPHERALS_INC_GPS_H_

#include <stdio.h>
#include <string.h>

void GpsInit();

void PhoneInit();

void SendPhone(uint8_t *prt);

uint8_t GpsRead();

void PhoneOn();

void PhoneOff();

void longuitud(volatile uint8_t *buffer,uint8_t *longuitud);

void latitud(volatile uint8_t *buffer,uint8_t *latitud);

void fecha(volatile uint8_t *buffer,uint8_t *fecha);

void hora(volatile uint8_t *buffer,uint8_t *hora);

void velocidad(volatile uint8_t *buffer,uint8_t *velocidad);

bool testing(volatile uint8_t *buffer);


#endif /* LIBS_SAPI_SAPI_V0_5_2_SOC_PERIPHERALS_INC_GPS_H_ */

