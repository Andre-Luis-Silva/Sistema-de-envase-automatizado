/*
 * comum.h
 *
 * Created: 17/01/2023 22:59:48
 *  Author: Emanoel Javoski
 */ 


#ifndef COMUM_H_
#define COMUM_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <lcd.h>
#include <gpio.h>
#include <uart.h>
#include <math.h>
#include <timer.h>
#include <adc.h>
#include <string.h>
#include <stdlib.h>

#define INICIO	0
#define EMERGENCIA	10
#define LIGADO	20
#define CONFIGURA_VASILHAMES	30
#define MOVE_ESTEIRA	40
#define VERIFICA_DOSADOR	50
#define MOVE_CILINDRO	55
#define PARADA_TIMEOUT_ESTEIRA  60
#define ULTIMO_ENVASE	70
#define MOVE_RECIPIENTE	75
#define RESERVATORIO_BAIXO	80
#define SENSOR_DEF	90

#endif /* COMUM_H_ */