/*
 * timer.c
 *
 * Created: 23/01/2023 02:16:02
 *  Author: andre
 */ 
#include <comum.h>

volatile int tempo100us = 0, timer100us = 0;
volatile int timer1ms = 0, timer10ms = 0, timer100ms = 0;
volatile int timer1s = 0;

extern int timeoutEsteira, flagEsteiraOn, flagMotorDosadorOn, flagUltimoEnvase, flagReservatorioBaixo;

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
	while(tempo100us < tempo);
	
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = VALOR_TCNT_100uS;
	
	if(tempo100us < 65535)
	{
		tempo100us++;
	}

	timer100us++;
	if(timer100us > 9)
	{
		timer100us = 0;
		timer1ms++;
	}

	if(timer1ms > 9)
	{
		timer1ms = 0;
		timer10ms++;
	}

	if(timer10ms > 9)
	{
		timer10ms = 0;
		timer100ms++;
	}

	if(timer100ms > 9)
	{
		timer100ms = 0;
		if(timeoutEsteira < 65535)
		{
			timeoutEsteira++;
		}
		flagUltimoEnvase = !flagUltimoEnvase;
		flagReservatorioBaixo = !flagReservatorioBaixo;
	}

}

ISR(TIMER1_COMPA_vect)
{
	if(flagEsteiraOn)
	{
		MOTOR_ESTEIRA_TGL;
	}
}

ISR(TIMER2_COMPA_vect)
{
	if(flagMotorDosadorOn)
	{
		MOTOR_DOSADOR_TGL;
	}
}