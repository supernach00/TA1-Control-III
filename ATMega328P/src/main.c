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

volatile uint8_t contador_PRBS = 0;
volatile uint16_t tension_entrada;
volatile uint16_t tension_filtrada = 0;
volatile uint16_t registro_LFSR = 0;
volatile uint8_t flag_test_PRBS = 0;
volatile uint16_t N = 0;

uint8_t flag_lectura_ADC = 0;

#define referencia 3000 // (En milivoltios)

ISR(TIMER1_OVF_vect) {
	
	flag_lectura_ADC = 1;
	
};

ISR(PCINT2_vect) { 
	
    // Código que se ejecuta cuando se dispara la interrupción en PD4 (Switch 1)

    if (PIND & (1 << PD4)) {

		terminar_test_PRBS(); 

		test_escalon(1000, 4000); // Test de respuesta al escalon: de 1V a 4V en 5 segundos, sale por PB1.

    }
};

ISR(INT1_vect)
{
    // Código que se ejecuta cuando se dispara la interrupción en PD3  (Switch 2)

	comenzar_test_PRBS();

}

ISR(TIMER0_COMPA_vect)
{
    // Código que se ejecuta a 61 Hz

	contador_PRBS++;

	if (contador_PRBS >= 4) { // Se ejecuta aproximadamente cada 0.066 segundos

		N++;
		if (N == 2047) {

			terminar_test_PRBS();

		} else {
		
			contador_PRBS = 0;
			actualizar_PWM_PRBS();

		}
	}
}

	int main(void)
	{
		setup_ADC();
		setup_PWM();
		setup_SWITCHS();
		setup_LFSR();
		USART_init();
		sei();

		// ---- RESPUESTA AL ESCALON ---- //


		while (1)
		{

		
		} 

    return 0;
}

