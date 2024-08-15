/*
 * adc.c
 *
 * Created: 15/08/2024 11:04:21
 *  Author: Andre
 */ 

#include <comum.h>

void ConfigADC(void)
{
  /* 
  The ADC was configured using the 1.1 internal regulator to make 
  the measure of the voltage of battery 
  */
  ADMUX = (1 << REFS1) | (1 << REFS0);
  ADCSRA = (1 << ADEN);
}

int ReadAdc(int channel)
{
	ADMUX &= (0xF0);
	ADMUX |= (channel); // Read the value of the channel
	ADCSRA |= (1 << ADSC);  // Start the conversion
	while(ADCSRA & (1 << ADSC));  // Wait the flag of finish conversion
	return ADC; // Return the value of ADC
}