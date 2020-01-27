/*
 * Node_code.c
 *
 * Created: 10-Jan-20 1:02:32 PM
 * Author : Jamir Fecunda
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>

#include "ADC.h"												// Include ADC header files
#include "InputCapture.h"										// Include Input capture header files
#include "CAN.h"												// Include CAN header files

#define ADC_ACTIVE												// Define what functions will be active ADC and/or input capture by commenting out the one you are not using
#define Input_Capture										


int main(void)
{
	can_init(0);							// Intialize CAN protocol	
	unsigned int t;
	
	DDRB = 0b00000100 ;						// Define register pins input and output
	DDRC = 0b00110000 ;
	DDRD = 0b10000000 ;
	
	uint8_t dat[2] = {0xAA};				// Define
	
	PCMSK0 |= (1<<PCINT0) | (1<<PCINT3);
	PCICR |= (1<<PCIE0);
	sei();
	
    while (1) 
    {
////////////////////////////////////////////////////////////////////////////////
		#ifdef ADC_ACTIVE
			ADC_reading();
			dat[0] = ADCH;
		#endif	
///////////////////////////////////////////////////////////////////////////////
		#ifdef Input_Capture
			Input_reading(&t);
			#ifdef ADC_ACTIVE
				dat[1] = t;
			#else
				dat[0] = t;
			#endif
		#endif 
////////////////////////////////////////////////////////////////////////////////
		Wait();
		can_transmit(dat, 1);	
    }
	return 0;
}

ISR(PCINT0_vect)
{

}

ISR(PCINT3_vect)
{
	// Your code here
}