/*
 * 
 *
 * Created: 06-Dec-19 11:26:10 AM
 * Author : Jamir Fecunda
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>




void Lees()
{
   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 		// Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz

   ADMUX |= (1 << REFS0); 						// Set ADC reference to AVCC
   ADMUX |= (1 << ADLAR); 						// Left adjust ADC result to allow easy 8 bit reading

   ADMUX |= (1<<MUX2) | (1<<MUX1) ;					//  MUX values needed to be changed to use ADC5

   //ADCSRA |= (1 << ADFR);  						// Set ADC to Free-Running Mode

   ADCSRA |= (1 << ADEN);  						// Enable ADC
   ADCSRA |= (1 << ADSC);  						// Start A2D Conversions
		
		
	if (ADCH < 64)							// if digital value is below 25% turn on led 1
	{
		PORTD |= (1<<PORTD7);
		PORTB &= ~(1<<PORTB2);
		PORTC &= ~(1<<PORTC4);
		PORTC &= ~(1<<PORTC5);
	}

	else if(( ADCH < 128) && (ADCH >= 64))				// if digital value is between 25%and 50% turn on led 1 and 2
	{
		PORTD |= (1<<PORTD7);
		PORTB |= (1<<PORTB2);
		PORTC &= ~(1<<PORTC4);
		PORTC &= ~(1<<PORTC5);
	}	
	
	else if(( ADCH < 192) &&( ADCH >= 128))				// if digital value is between 50% and 75% turn on led 1, 2 and 3
	{
		PORTD |= (1<<PORTD7);
		PORTB |= (1<<PORTB2);
		PORTC |= (1<<PORTC4);
		PORTC &= ~(1<<PORTC5);
	}	
	
	else								// if digital value is between 75% and 100% turn on led 1, 2, 3 and 4						
	{
		PORTD |= (1<<PORTD7);
		PORTB |= (1<<PORTB2);
		PORTC |= (1<<PORTC4);
		PORTC |= (1<<PORTC5);
	}
}


void Wait()						// delay for 200 ms between every analog reading	
	uint8_t i;
	for(i=0;i<20;i++)
	_delay_ms(10);
}

int main(void) {
	DDRD = 0b10000000 ;				// define register pins input and output
	DDRC = 0b00110000 ;
	DDRB = 0b00000100 ;
	
	
	while (1) 
	{
		Lees();					// call function lees()
		Wait();					// call function wait()
	}

	return 0;
}

