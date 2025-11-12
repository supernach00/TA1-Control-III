/*
 * funciones.h
 *
 * Created: 24/8/2025 14:56:21
 *  Author: nacho
 */ 


#ifndef FUNCIONES_H_
#define FUNCIONES_H_

// Includes
#include <stdint.h>
#include <util/delay.h>
// Constantes

#define T 1.0
#define tau 1000.0
#define alfa  tau / (T + tau)
#define beta  T / (T + tau)
#define A 16000.0 / (5.0*1000.0)
#define C  5.12;

// Funciones de configuraci�n

void setup_ADC(void);
void setup_PWM(void);

// Funciones generales

uint16_t leer_ADC(void);
uint16_t filtro_RC(uint16_t error);
uint16_t tension_a_WC(uint16_t tension);
void test_escalon(uint16_t bajo, uint16_t alto);

#endif /* FUNCIONES_H_ */