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
	static uint8_t ISR_ms_100=0;
	static uint8_t ISR_sek=0;
	static uint8_t ISR_min=0;
	static uint8_t ISR_h=0;

	
	TCNT0 = 0;
	ISR_zaehler++;//zähler hochrechnen
	if(ISR_zaehler==12)
	{
		ISR_ms_100++; //milisekunden hochrechnen
		
		
		if(ISR_ms_100==10)
		{
			sek++; //sekunden hochrechnen
			ISR_sek++;
			ISR_ms_100=0; //milisekunden auf 0 setzen
		}
		
		if(ISR_sek==60)
		{
			min++; //minuten hochrechnen
			ISR_min++;
			ISR_sek=0; //sekunden auf 0 setzen
		}
		
		if(ISR_min==60)
		{
			h++; //stunden hochrechnen
			ISR_h++;
			ISR_min=0; //minuten auf 0 setzen
		}
		
		ISR_zaehler=0; //zähler auf 0 setzen
	}
	
}


int main(void)
{
	
	uint8_t licht=0;
	DDRB=0xFF; //Ganzer Port B als Ausgang 
	PORTB=0x00; //Alle LEDs ausschalten

	TCCR0A		= 0x00; 			//Timer Konfigurieren
	TCCR0B		= 0x04; 			//Timer Konfigurieren
	TIMSK0		|= (1 << TOIE0);	//Timer Konfigurieren
	TIFR0	|= (1 << TOV0);			//Timer Konfigurieren
	sei();
	
	
	while(1)
	{
	
		if((!(PINC&(1<<PC4)))||(!(PINC&(1<<PC5)))) //taster 4 und 5 abfragen
		{
			sek=0;
			min=0;
			h=0;
		}
		
		PORTB=min; //ausgabe der minuten auf Port B
		
	}
	
} //end of main