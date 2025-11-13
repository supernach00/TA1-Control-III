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
#define tau 0.398
#define alfa  tau / (T + tau)
#define beta  T / (T + tau)
#define A 16000.0 / (5.0*1000.0)
#define C  5.12;

// Funciones de configuracion
void setup_ADC(void);
void setup_PWM(void);
void setup_SWITCHS(void);
void setup_LFSR(void);

// Funciones generales
uint16_t leer_ADC(void);
uint16_t filtro_RC(uint16_t error);
uint16_t tension_a_WC(uint16_t tension);
void actualizar_PWM_PRBS(void);
uint8_t LFSR_shift(void);

// Funciones de test
void test_escalon(uint16_t bajo, uint16_t alto);
void comenzar_test_PRBS(void);
void terminar_test_PRBS(void);

#endif /* FUNCIONES_H_ */