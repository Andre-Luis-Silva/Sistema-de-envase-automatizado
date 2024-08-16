/*
 * timer.h
 *
 * Created: 23/01/2023 02:16:15
 *  Author: andre
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#define TIMER_1S		1000	// Considerar um timer de 1 milissegundos
#define TIMER_100MS		100		// Considerar um timer de 1 milissegundos
#define VALOR_TCNT_100uS	155	// Tempo do contador de 255-100 = 155

void ConfigTimers( void );
void Delay100us( unsigned int tempo );

#endif /* TIMER_H_ */