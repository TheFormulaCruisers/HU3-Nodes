/*
 * ADC.c
 *
 * Created: 10-Jan-20 1:05:35 PM
 *  Author: Jamir Fecunda
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>

#include "ADC.h"
#include "InputCapture.h"
#include "CAN.h"



void ADC_reading()
{
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 		// Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz

	ADMUX |= (1 << REFS0); 						// Set ADC reference to AVCC
	ADMUX |= (1 << ADLAR); 						// Left adjust ADC result to allow easy 8 bit reading

	ADMUX |= (1<<MUX2) | (1<<MUX1) ;					//  MUX values needed to be changed to use ADC5

	//ADCSRA |= (1 << ADFR);  						// Set ADC to Free-Running Mode

	ADCSRA |= (1 << ADEN);  						// Enable ADC
	ADCSRA |= (1 << ADSC);  						// Start A2D Conversions

	//return ADCH;
}


void Wait()													// delay for 200 ms between every analog reading
{
	uint8_t i;
	for(i=0;i<20;i++)
	_delay_ms(1);
}


