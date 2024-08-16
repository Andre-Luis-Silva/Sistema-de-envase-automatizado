/*
 * gpio.h
 *
 * Created: 17/01/2023 22:59:28
 *  Author: andre
 */ 


#ifndef GPIO_H_
#define GPIO_H_

void GpioSet(unsigned char port, unsigned char pin);
void GpioClear(unsigned char port, unsigned char pin);
void GpioToogle(unsigned char port, unsigned char pin);

#define portb		1
#define portc		2
#define portd		3

#define rs_on		GpioSet( portd, 2 )
#define rs_off		GpioClear( portd, 2 )
#define rs_tgl		GpioToogle( portd, 2 )

#define e_on		GpioSet( portd, 3 )
#define e_off		GpioClear( portd, 3 )
#define e_tgl		GpioToogle( portd, 3 )

#define d4_on		GpioSet( portd, 4 )
#define d4_off		GpioClear( portd, 4 )
#define d4_tgl		GpioToogle( portd, 4 )

#define d5_on		GpioSet( portd, 5 )
#define d5_off		GpioClear( portd, 5 )
#define d5_tgl		GpioToogle( portd, 5 )

#define d6_on		GpioSet( portd, 6 )
#define d6_off		GpioClear( portd, 6 )
#define d6_tgl		GpioToogle( portd, 6 )

#define d7_on		GpioSet( portd, 7 )
#define d7_off		GpioClear( portd, 7 )
#define d7_tgl		GpioToogle( portd, 7 )

#define MOTOR_DOSADOR_ON	GpioSet(portb, 1);
#define MOTOR_DOSADOR_OFF	GpioClear(portb, 1);
#define MOTOR_DOSADOR_TGL	GpioToogle(portb, 1);

#define MOTOR_ESTEIRA_ON	GpioSet(portb, 3);
#define MOTOR_ESTEIRA_OFF	GpioClear(portb, 3);
#define MOTOR_ESTEIRA_TGL	GpioToogle(portb, 3);

#define CILINDRO_ON		GpioSet(portb, 5);
#define CILINDRO_OFF	GpioClear(portb, 5);
#define CILINDRO_TGL	GpioToogle(portb, 5);

#define LAMPADA_VERMELHA_ON		GpioSet(portb, 6);
#define LAMPADA_VERMELHA_OFF	GpioClear(portb, 6);
#define LAMPADA_VERMELHA_TGL	GpioToogle(portb, 6);

#define LAMPADA_AMARELA_ON		GpioSet(portb, 7);
#define LAMPADA_AMARELA_OFF		GpioClear(portb, 7);
#define LAMPADA_AMARELA_TGL		GpioToogle(portb, 7);

#define DV	!(PINB & (1 << PINB4))
#define A1	!(PINB & (1 << PINB2))
#define ON	(PINB & (1 << PINB0))

#define BE	!((PINC & (1 << PINC4)))
#define SR	!((PINC & (1 << PINC3)))
#define SPR	!((PINC & (1 << PINC2)))
#define RS	!((PINC & (1 << PINC1)))
#define DC	!((PINC & (1 << PINC0)))

void ConfigGpio( void );

#endif /* GPIO_H_ */