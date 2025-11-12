#include "funciones.h"
#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile uint16_t tension_entrada;
extern volatile uint16_t tension_filtrada;

void setup_ADC(void){
	
	/*
	PRESCALER = 128 (f_adc = 125Khz)
	ADC = ENABLE
	ADC INTERRUPT = ENABLE
	PIN DE ENTRADA = ADC1
	REFERENCIA = 5V
	*/
	
	ADMUX = (1 << REFS0) | (1 << MUX0);
	ADCSRA = (1 << ADEN) | (0 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 	
	
	}
	
void setup_SWITCH(void){
	
	/*
	PIN DE ENTRADA = PD4
	CONFIGURACION = PULL-UP
	*/

	DDRD &= ~(1 << PD4);  
    PORTD |= (1 << PD4); 

    // Activar Pin Change Interrupt para Port D
    PCICR |= (1 << PCIE2);     // PCIE2 controla Port D
    PCMSK2 |= (1 << PCINT20);  // PD4 = PCINT20
	
	}

void setup_PWM(void){
	
	/*
	TIMER = 1
	MODO = FAST PWM
	PRESCALER = 1 (f = 16MHz)
	COMPARADOR PERIODO = ICR1 = 16000 (1ms)
	COMPARADOR DC = OCR1A
	PIN DE  SALIDA = PB1
	DC INICIAL = 50%
	*/
	
	DDRB |= (1 << PB1); // OC1A = PB1 en Arduino Uno

	TCCR1A = (1 << WGM11) | (1 << COM1A1);
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10); // 
	TIMSK1 |= (1 << TOIE1);
	
	ICR1 = 15999;
	OCR1A = 1;  // Valor inicial de ciclo de trabajo.
	
	}
	
uint16_t leer_ADC(){
	
	ADCSRA |= (1 << ADSC);
	
	while ( !(ADCSRA & (1 << ADIF)) ); // Se espera hasta que termine la conversion.

	ADCSRA |= (1 << ADIF);

	return ADC*C; // Devuelve el valor en milivoltios. C = 5.
	
	}
		
uint16_t filtro_RC(uint16_t error){
	
	// Filtrado
	
	float tension_salida = (alfa * tension_filtrada + beta * error);
	
	return (uint16_t) tension_salida;
	
	}

uint16_t tension_a_WC(uint16_t tension){
	
	// Convierte un valor de tensi�n en milivoltios a un entero entre 0 y 15999, que se utiliza
	// como valor de comparacion del timer1.
	// Esto define el ciclo de trabajo (WC) de la PWM de salida.
	
	return tension *  A - 1; //  A = 16000 / (5*1000)
	
	}


void test_escalon(uint16_t bajo, uint16_t alto){

	// Genera un escalon con una pwm en el pin PB1, que va desde un valor "bajo (mV)" hasta un valor "alto (mV)".
	// Luego se repite el test pero con  un escalon en sentido contrario.
	// En el pin PB2 genera una señal sincronizada al escalón, pero entre 0V y 1V, que se utiliza para medir la señal de entrada.

	DDRB |= (1 << PB2); // PB2 como salida

	// Escalon de bajo a alto
	OCR1A = tension_a_WC(bajo);
	_delay_ms(3000);

	OCR1A = tension_a_WC(alto);
	PORTB |= (1 << PB2); // Señal de sincronización a 1V
	_delay_ms(3000);

	// Escalon de alto a bajo
	OCR1A = tension_a_WC(bajo);
	PORTB &= ~(1 << PB2); // Señal de sincronización a 0V
	_delay_ms(3000);

	// Apago salida
	OCR1A = 0;
	
	}