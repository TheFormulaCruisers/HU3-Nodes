/*
 * InputCapture.c
 *
 * Created: 10-Jan-20 1:06:41 PM
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

void Input_reading(unsigned int *Period)
{
	TCCR1A = 0;
	TIFR1 = (1<<ICF1);							// clear input capture flag
	TCCR1B = 0x45;								// capture on rising edge
	
	//GTCCR |= (1<<ICPSEL1);					// Select ICP1B as trigger for timer 1 input capture
	
	while ((TIFR1&(1<<ICF1)) == 0);				// monitor for capture
	 	
	*Period = ICR1;
	TIFR1 = (1<<ICF1);							// clear capture flag
	 	
	while ((TIFR1 &(1<<ICF1)) == 0);			// monitor for next rising edge capture
	 	
	*Period = ICR1 - *Period; 					// period= recent capture-previous capture
	//return t;
 }



