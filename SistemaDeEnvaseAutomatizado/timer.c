/*
 * timer.c
 *
 * Created: 23/01/2023 02:16:02
 *  Author: andre
 */ 
#include <comum.h>

volatile int tempo100us = 0;

void ConfigTimers( void )
{
	
	TCCR0A = 0;
	TCCR0B = ( 1 << CS01 );
	TIFR0 = 1 << TOV0;
	TIMSK0 |= 1 << TOIE0;
	TCNT0 = 0;
	
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS11); 
	TIFR1 = 1 << OCF1A;
	TIMSK1 |= 1 << OCIE1A;
	OCR1AH = 5000 >> 8;
	OCR1AL = 5000 & 0xFF;
	
	TCCR2A = (1 << WGM21);
	TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
	TIFR2 = 1 << OCF2A;
	TIMSK2 |= 1 << OCIE2A; 
	OCR2A = 39;
	
}

void Delay100us(unsigned int tempo){
	
	tempo100us = 0;
	while(tempo100us < tempo)
	{
		
	}
	
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = VALOR_TCNT_100uS;
	if(tempo100us < 65535)
	{
		tempo100us++;
	}
}

ISR(TIMER1_COMPA_vect)
{
	LAMPADA_VERMELHA_TGL;
}

ISR(TIMER2_COMPA_vect)
{
	LAMPADA_AMARELA_TGL;
}