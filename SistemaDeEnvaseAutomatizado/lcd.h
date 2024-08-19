/*
 * lcd.h
 *
 * Created: 15/08/2024 21:57:52
 *  Author: Andre
 */ 


#ifndef LCD_H_
#define LCD_H_

#define comando		0
#define character	1
#define NIBBLE1		0
#define NIBBLE2		10
#define PULA_LINHA_LCD	0xC0
#define APAGA_LINHA	EscreveLcd("                ", 17);


void ConfigDisplay(void);
void ByteDisplay(unsigned char modo, unsigned char dado);
void EscreveLcd(char *dado, unsigned char size);
void AtualizaLcd(int estado, int numeroDeVasilhamesInteiro)
;
#endif /* LCD_H_ */