 
#include "avr/io.h"
#include <util/delay.h>

int main ( )
{
	unsigned int t;								// create variable integer t

	DDRB = 0xFF;								// register ports B as all output
	DDRC = 0xFF;								// register ports C as all output
	DDRD = (1<<PORTD7) ;							// register port D7 as output
	
	while (1)
	{
		TCCR1A = 0;
		TIFR1 = (1<<ICF1);							// clear input capture flag
		TCCR1B = 0x41;								// capture on rising edge
			
		while ((TIFR1&(1<<ICF1)) == 0);				// monitor for capture
		
		t = ICR1;
		TIFR1 = (1<<ICF1);							// clear capture flag
		
		while ((TIFR1 &(1<<ICF1)) == 0);			// monitor for next rising edge capture
		
		t = ICR1 - t; 								// period= recent capture-previous capture

		
		if(t < 10000)
		{							// turn led 1 on if period is beneath 10000 microseconds
			PORTC |= (1<<PORTC5);
		}
		if(t < 3500)
		{							// turn led 2 on if period is beneath 3500 microseconds
			PORTC |= (1<<PORTC4);
		}		
		
		if(t < 2000)
		{							// turn led 3 on if period is beneath 2000 microseconds
			PORTB |= (1<<PORTB2);
		}		
		if(t < 1000)
		{							// turn led 4 on if period is beneath 1000 microseconds
			PORTD |= (1<<PORTD7);
		}		

		
	}
	return 0;
}



