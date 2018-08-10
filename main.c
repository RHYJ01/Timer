//Autor: Justin Rhyner
//Dateiname: Counter
//Datum: 08.08.2018

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

volatile uint8_t val=0;

ISR(TIMER0_OVF_vect)
{
	static uint8_t ISR_zaehler=0;
	
	TCNT0 = 0;
	ISR_zaehler++;
	if(ISR_zaehler==12)
	{
		ISR_zaehler=0;
	}
	val++;
}


int main(void)
{
	DDRB=0xFF; //Ganzer Port B als Ausgang 
	PORTB=0x00; //Alle LEDs ausschalten

	TCCR0A		= 0x00;
	TCCR0B		= 0x04;
	TIMSK0		|= (1 << TOIE0);
	TIFR0	|= (1 << TOV0);
	sei();
	
	
	while(1)
	{
		
		PORTB=val;
	}
	
} //end of main