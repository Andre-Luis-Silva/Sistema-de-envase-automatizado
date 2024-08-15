/*
 * gpio.c
 *
 * Created: 17/01/2023 22:59:16
 *  Author: andre
 */ 
#include <comum.h>

void ConfigGpio( void )
{
	
	// PB7, PB6, PB5, PB3, PB1 como saídas
	DDRB = (1 << DDB7) | (1 << DDB6) | (1 << DDB5) | (1 << DDB3) | (1 << DDB1); 
	
	// PD7, PD6, PD5, PD4, PB3, PB2 como saídas
	DDRD = (1 << DDD7) | (1 << DDD6) | (1 << DDD5) | (1 << DDD4) | (1 << DDD3) | (1 << DDD2); 
	
}