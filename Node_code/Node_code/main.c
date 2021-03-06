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

#define ADC_ACTIVE1												// Define what functions will be active ADC and/or input capture by commenting out the one you are not using
#define ADC_ACTIVE2												// Maximum amount of defined functions is 2
//#define Input_Capture									

volatile unsigned int Overflows = 0;

//___________________________________________________________________________________________________________________________________________________________________________________//
int main(void)
{
	can_init(0);															// Initialize CAN protocol	
	
	unsigned int Period;													// define variables
	unsigned int ADC_data1;
	unsigned int ADC_data2;
	
	unsigned int ADC_2 = 0;
	uint8_t dat[2] = {0xAA};												// Define amount of bytes in the data package
	
	DDRB = 0b00000100 ;														// Define register pins input and output
	DDRC = 0b00110000 ;
	DDRD = 0b10000000 ;
	

	TCCR0B |= (1<<CS00) | (1<<CS02);										// Set 8-bit Timer TCCR0B prescalar to 1024
	TCNT0 = 0;																// Initialize timer
		
	
	PCMSK0 |= (1<<PCINT0) | (1<<PCINT3);									// Enable interrupt pins for additions to the code (spare)
	PCICR |= (1<<PCIE0);
	sei();
	
    while (1) 
    {
		#ifdef ADC_ACTIVE1													// check if ADC1(PB5) is active			
			#ifdef ADC_ACTIVE2												// check if ADC6(PB6) is active						
				ADC_2 = 1;													// Variable bit to identify if both ADC's are active 1 = both active, 0 = just ADC_ACTIVE1
				ADC_reading(&ADC_2 , &ADC_data1 , &ADC_data2);				// call ADC_reading function
				dat[0] = ADC_data1;											// data byte 0 consist data from ADC_data1
				dat[1] = ADC_data2;											// data byte 1 consist data from ADC_data2
			#endif
			
			#ifndef ADC_ACTIVE2											
				ADC_2 = 0;										
				ADC_reading(&ADC_2, &ADC_data1 , &ADC_data2);				
				dat[0] = ADC_data1;
			#endif	
		#endif	



		#ifdef Input_Capture												// check if Input_capture pin (PD4) is active	
			Input_reading(&Period);											// call Input_reading function
			
			#ifdef ADC_ACTIVE1												// condition that data Byte 0 is reserved for any ADC that is Active
				dat[1] = Period;
			else
				dat[0] = Period;
			#endif
			
			#ifdef ADC_ACTIVE2
				dat[1] = Period;
			else
				dat[0] = Period;
			#endif	
		#endif 

		
		if((TCNT0 >= 57) && (Overflows >= 1) || (Overflows >= 2))			// Condition to transmit after interval set in wait function
			{
				can_transmit(dat, 1);										// Call CAN transmit function
				TCNT0 = 0;													// Reset Timer
				Overflows = 0;												// the timer overflows before reaching 20 milliseconds so we need to count the overflows as well
								
			}
}
	return 0;
}





//___________________________________________________________________________________________________________________________________________________________________________________________//
ISR(PCINT0_vect)															// Interrupt for additions to the code (spare)
{

}

ISR(PCINT3_vect)															// Interrupt for additions to the code (spare)
{
	// Your code here
}

ISR(TIMER0_OVF_vect)															// Interrupt for additions to the code (spare)
{
	Overflows ++;// Your code here
}


//_____________________________________________________________________________________________________________________________________________________________________________________________//