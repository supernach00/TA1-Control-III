/*
 * TP0 Control III.c
 *
 * Created: 24/8/2025 14:55:34
 * Author : nacho
 */ 

#include "funciones.h"
#include "UART.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

volatile uint16_t tension_entrada;
volatile uint16_t tension_filtrada = 0;
uint8_t flag_lectura_ADC = 0;

#define referencia 3000 // (En milivoltios)

ISR(TIMER1_OVF_vect) {
	
	flag_lectura_ADC = 1;
	
	};

int main(void)
{
    setup_ADC();
	setup_PWM();
	USART_init();
	sei();

	// ---- RESPUESTA AL ESCALON ---- //

	test_escalon(1000, 4000); // Test de respuesta al escalon: de 1V a 4V en 5 segundos, sale por PB1.

    while (1) {

		// if (flag_lectura_ADC) {
		// 	flag_lectura_ADC = 0
			
		// 	USART_put_uint16(tension_entrada); // Verificaci�n de la correcta medici�n del ADC.
			
		// 	tension_entrada = leer_ADC();
		// 	tension_filtrada = filtro_RC(referencia - tension_entrada);
		// 	OCR1A = tension_a_WC(tension_filtrada);
			
		} 

    return 0;
}

