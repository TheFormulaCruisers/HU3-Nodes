 
#include "avr/io.h"
#include <util/delay.h>

int main ( )
{
	unsigned int t;

	DDRB = 0xFF;
	DDRC = 0xFF;	
	DDRD = (1<<PORTD7) ;	
	
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
		{							// put period count on PORTA & PORTB
			PORTC |= (1<<PORTC5);
		}
		if(t < 3500)
		{							// put period count on PORTA & PORTB
			PORTC |= (1<<PORTC4);
		}		
		
		if(t < 2000)
		{							// put period count on PORTA & PORTB
			PORTB |= (1<<PORTB2);
		}		
		if(t < 1000)
		{							// put period count on PORTA & PORTB
			PORTD |= (1<<PORTD7);
		}		

		
	}
	return 0;
}



