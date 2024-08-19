/*
 * gpio.c
 *
 * Created: 17/01/2023 22:59:16
 *  Author: andre
 */
#include <comum.h>

volatile int flagEmergencia = 0;

void ConfigGpio(void)
{

	// PB7, PB6, PB5, PB3, PB1 como sa�das
	DDRB = (1 << DDB7) | (1 << DDB6) | (1 << DDB5) | (1 << DDB3) | (1 << DDB1);

	// PD7, PD6, PD5, PD4, PB3, PB2 como sa�das
	DDRD = (1 << DDD7) | (1 << DDD6) | (1 << DDD5) | (1 << DDD4) | (1 << DDD3) | (1 << DDD2);
	
	PCICR = (1 << PCIE1);
	PCMSK1 = (1 << PCINT12);
}

void GpioSet(unsigned char port, unsigned char pin)
{

	switch (port)
	{

	case 1:
		PORTB |= (1 << pin);
		break;

	case 2:
		PORTC |= (1 << pin);
		break;

	case 3:
		PORTD |= (1 << pin);
		break;
	}
}

void GpioClear(unsigned char port, unsigned char pin)
{

	switch (port)
	{

	case 1:
		PORTB &= ~(1 << pin);
		break;

	case 2:
		PORTC &= ~(1 << pin);
		break;

	case 3:
		PORTD &= ~(1 << pin);
		break;
	}
}

void GpioToogle(unsigned char port, unsigned char pin)
{

	switch (port)
	{

	case 1:
		PORTB ^= (1 << pin);
		break;

	case 2:
		PORTC ^= (1 << pin);
		break;

	case 3:
		PORTD ^= (1 << pin);
		break;
	}
}

ISR(PCINT1_vect)
{
	flagEmergencia = 1;
}