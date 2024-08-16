/*
 * SistemaDeEnvaseAutomatizado.c
 *
 * Created: 14/08/2024 21:44:20
 * Author : Emanoel Javoski
 */ 

#include "comum.h"

int main(void)
{
    /* Replace with your application code */
	ConfigGpio();
	ConfigADC();
	ConfigUart();
	sei();
	ConfigTimers();
	ConfigDisplay();
	
    while (1) 
    {

    }
}
