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



int ADC_reading(unsigned int *ADC2, unsigned int *ADC_data1 , unsigned int *ADC_data2)
{	
	
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); 		// Set ADC prescalar to 256 - 125KHz sample rate @ 16MHz

	ADMUX |= (1 << REFS0); 										// Set ADC reference to AVCC
	ADMUX |= (1 << ADLAR); 										// Left adjust ADC result to allow easy 8 bit reading


	ADMUX |= (1<<MUX1) | (1<<MUX2);								//  ADC6 , MUX values needed to be changed to use ADC7
	ADCSRA |= (1 << ADEN);  									// Enable ADC
	ADCSRA |= (1 << ADSC);  									// Start A2D Conversions
	*ADC_data1 = ADCH;
	
	if(ADC2 == 1)
	{
		ADMUX |= (1<<MUX0) | (1<<MUX1) | (1<<MUX2);				// ADC7 , MUX values needed to be changed to use ADC6
		ADCSRA |= (1 << ADEN);  								// Enable ADC
		ADCSRA |= (1 << ADSC);			
		*ADC_data2 = ADCH;										// Start A2D Conversions
		return *ADC_data1, *ADC_data2;							// Return both data
	}
	else
		return *ADC_data1;										// Return the data
}


int Wait(unsigned int *Timer)														// delay for 200 ms between every analog reading
{	
	if(*Timer == 0)
	TCCR0B |= (1<<CS00) | (1<<CS02);
	return *Timer;
}


