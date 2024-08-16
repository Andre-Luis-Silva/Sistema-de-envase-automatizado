/*
 * lcd.c
 *
 * Created: 15/08/2024 21:57:41
 *  Author: Andre
 */
#include <comum.h>

void ConfigDisplay(void)
{
	rs_off;

	Delay100us( 150 );
	ByteDisplay( comando, 0x03 );
	Delay100us( 41 );
	ByteDisplay( comando, 0x03 );
	Delay100us( 10 );
	ByteDisplay( comando, 0x03 );
	ByteDisplay( comando, 0x02 );
	ByteDisplay( comando, 0x28 );
	ByteDisplay( comando, 0x0C );
	ByteDisplay( comando, 0x01 );
	ByteDisplay( comando, 0x06 );
}

void ByteDisplay(unsigned char modo, unsigned char dado)
{

	unsigned char msb = (dado >> 4), lsb = dado & 0x0F;

	if (modo)
		rs_on;
	else
		rs_off;

	e_off;

	if (msb & 0x8)
		d7_on;
	else
		d7_off;

	if (msb & 0x4)
		d6_on;
	else
		d6_off;

	if (msb & 0x2)
		d5_on;
	else
		d5_off;

	if (msb & 0x1)
		d4_on;
	else
		d4_off;

	e_on;
	Delay100us(10);
	e_off;

	if (lsb & 0x8)
		d7_on;
	else
		d7_off;

	if (lsb & 0x4)
		d6_on;
	else
		d6_off;

	if (lsb & 0x2)
		d5_on;
	else
		d5_off;

	if (lsb & 0x1)
		d4_on;
	else
		d4_off;

	e_on;

	Delay100us(10);

	e_off;

	Delay100us(20);
}

void EscreveLcd(char *dado, unsigned char size)
{

	while ((size - 1) > 0)
	{

		unsigned char msb = (*dado) >> 4, lsb = (*dado) & 0x0F;

		rs_on;

		e_off;

		Delay100us(1);

		if (msb & 0x8)
			d7_on;
		else
			d7_off;

		if (msb & 0x4)
			d6_on;
		else
			d6_off;

		if (msb & 0x2)
			d5_on;
		else
			d5_off;

		if (msb & 0x1)
			d4_on;
		else
			d4_off;

		e_on;

		Delay100us(10);

		e_off;

		if (lsb & 0x8)
			d7_on;
		else
			d7_off;

		if (lsb & 0x4)
			d6_on;
		else
			d6_off;

		if (lsb & 0x2)
			d5_on;
		else
			d5_off;

		if (lsb & 0x1)
			d4_on;
		else
			d4_off;

		e_on;

		Delay100us(10);

		e_off;

		Delay100us(20);

		*(dado++);
		size--;
	}
	rs_off;
}