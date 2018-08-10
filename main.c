//Autor: Justin Rhyner
//Dateiname: Counter
//Datum: 08.08.2018

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

volatile uint8_t ms_100=0;
volatile uint8_t sek=0;
volatile uint8_t min=0;
volatile uint8_t h=0;

ISR(TIMER0_OVF_vect)
{
	static uint8_t ISR_zaehler=0;
	
	TCNT0 = 0;
	ISR_zaehler++;//zähler hochrechnen
	if(ISR_zaehler==12)
	{
		ms_100++; //milisekunden hochrechnen
		
		if(ms_100==10)
		{
			sek++; //sekunden hochrechnen
			ms_100=0; //milisekunden auf 0 setzen
		}
		
		if(sek==60)
		{
			min++; //minuten hochrechnen
			sek=0; //sekunden auf 0 setzen
		}
		
		if(min==60)
		{
			h++; //stunden hochrechnen
			min=0; //minuten auf 0 setzen
		}
		
		ISR_zaehler=0; //zähler auf 0 setzen
	}
	
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
		
		PORTB=min; //ausgabe der minuten auf Port B
	}
	
} //end of main