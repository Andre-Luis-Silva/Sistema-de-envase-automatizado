/*
 * SistemaDeEnvaseAutomatizado.c
 *
 * Created: 14/08/2024 21:44:20
 * Author : Emanoel Javoski
 */ 

#include "comum.h"

extern volatile int flagEmergencia;
extern char recebeuDado;

int flagEsteiraOn = 0, flagMotorDosadorOn = 0, flagUltimoEnvase = 0, flagReservatorioBaixo = 0;
int timeoutEsteira = 0;

int main(void)
{
    /* Replace with your application code */
	ConfigGpio();
	ConfigADC();
	ConfigUart();
	sei();
	ConfigTimers();
	ConfigDisplay();
	char *msg = "Estado:Config";
	char numeroDeVasilhames[2] = {0,0};
	int estado = CONFIGURA_VASILHAMES, contCaracteres = 0, numeroDeVasilhamesInteiro = 0;
	float valorTemperatura = 0.0;	

	EscreveLcd(msg, strlen(msg)+1);
	ByteDisplay(comando,PULA_LINHA_LCD);
	EscreveLcd(numeroDeVasilhames, 2);
	while (1) 
    {
		if(flagEmergencia == 1)
		{
			estado = EMERGENCIA;
			MOTOR_DOSADOR_OFF;
			MOTOR_ESTEIRA_OFF;
			CILINDRO_OFF;
			LAMPADA_VERMELHA_ON;
			flagEsteiraOn = 0;
			flagMotorDosadorOn = 0;
			flagEmergencia = 0;
		}

		switch(estado)
		{
			case CONFIGURA_VASILHAMES:
				if(numeroDeVasilhamesInteiro == 0)
				{
					msg = "Escreva a quantidade de vasilhames: ";
					EscritaTexto("Escreva a quantidade de vasilhames: ", strlen(msg));
					do   // Fa�a enquanto o n�mero definido n�o est� entre 1 e 5
					{
						if( recebeuDado != 0 )	// Se h� algo na serial
						{
							EscritaTexto(&(recebeuDado),1);
							if(recebeuDado == '\r' || recebeuDado == '\n')
							{
								contCaracteres = 0;
								recebeuDado = 0;
								break;
							}
							else if( recebeuDado < '0' || recebeuDado > '9')	// Se o valor est� fora de 1 a 5
							{
								EscritaTexto("\rNumero errado!. Escolha apenas numeros\r", sizeof("\rNumero errado!. Escolha apenas numeros\r"));
							}
							else
							{
								numeroDeVasilhames[contCaracteres] = recebeuDado;
								contCaracteres++;
							}
							recebeuDado = 0;
						}

					}while(contCaracteres < 3);
					EscritaTexto(numeroDeVasilhames, sizeof(numeroDeVasilhames));
					PULA_LINHA;
					numeroDeVasilhamesInteiro = atoi(numeroDeVasilhames);
				}
				
				estado = INICIO;
			break;
			
			case INICIO:
				
				if(ON)
				{
					estado = LIGADO;
				}
			
			break;
			
			case LIGADO:
			
				valorTemperatura = ReadAdc(5) * 0.00488;
				if(SR)
				{
					estado = RESERVATORIO_BAIXO;
				}
				else if(valorTemperatura > 3.5)
				{
					estado = MOVE_ESTEIRA;
					flagEsteiraOn = 1;
					timeoutEsteira = 0;
				}
			
			break;
			
			case MOVE_ESTEIRA:
			
				if(SR)
				{
					estado = RESERVATORIO_BAIXO;
					flagEsteiraOn = 0;
					flagMotorDosadorOn = 0;
					MOTOR_DOSADOR_OFF;
					MOTOR_ESTEIRA_OFF;
				}
				else if(SPR)
				{
					estado = VERIFICA_DOSADOR;
					flagEsteiraOn = 0;
					MOTOR_ESTEIRA_OFF;
				}
				else if(numeroDeVasilhamesInteiro == 0)
				{
					estado = ULTIMO_ENVASE;
					flagUltimoEnvase = 1;
					flagEsteiraOn = 0;
					flagMotorDosadorOn = 0;
					MOTOR_DOSADOR_OFF;
					MOTOR_ESTEIRA_OFF;
					CILINDRO_OFF;
				}
				else if(timeoutEsteira > 15)
				{
					estado = PARADA_TIMEOUT_ESTEIRA;
					flagEsteiraOn = 0;
					MOTOR_DOSADOR_OFF;
					MOTOR_ESTEIRA_OFF;
					CILINDRO_OFF;
					LAMPADA_VERMELHA_ON;
				}
			
			break;
			
			case VERIFICA_DOSADOR:
			
				if(DC && !DV)
				{
					estado = SENSOR_DEF;
					MOTOR_DOSADOR_OFF;
					MOTOR_ESTEIRA_OFF;
					CILINDRO_OFF;
					LAMPADA_VERMELHA_ON;
					flagEsteiraOn = 0;
					flagMotorDosadorOn = 0;
				}
				else if(DC && DV)
				{
					flagMotorDosadorOn = 0;
					MOTOR_DOSADOR_OFF;
					CILINDRO_ON;
					estado = MOVE_CILINDRO;
				}
				else if(!DV)
				{
					flagMotorDosadorOn = 1;
				}

			
			break;
			
			case MOVE_CILINDRO:
			
				if(!DV)
				{
					CILINDRO_OFF;
					estado = MOVE_RECIPIENTE;
					flagEsteiraOn = 1;
					timeoutEsteira = 0;
				}			
			
			break;
			
			case MOVE_RECIPIENTE:
			
				if(!SPR)
				{
					estado = MOVE_ESTEIRA;
					numeroDeVasilhamesInteiro--;
				}
				else if(timeoutEsteira > 15)
				{
					estado = PARADA_TIMEOUT_ESTEIRA;
					flagEsteiraOn = 0;
					MOTOR_DOSADOR_OFF;
					MOTOR_ESTEIRA_OFF;
					CILINDRO_OFF;
					LAMPADA_VERMELHA_ON;
				}
				
			break;
			
			case ULTIMO_ENVASE:
			
				if(flagUltimoEnvase)
				{
					LAMPADA_AMARELA_ON;
				}
				else
				{
					LAMPADA_AMARELA_OFF;
				}
				if(RS)
				{
					estado = CONFIGURA_VASILHAMES;
					LAMPADA_AMARELA_OFF;
				}
				
			break;

			case PARADA_TIMEOUT_ESTEIRA:

				if(RS)
				{
					estado = CONFIGURA_VASILHAMES;
					LAMPADA_VERMELHA_OFF;
				}

			break;

			case EMERGENCIA:
			
				if(!BE)
				{
					LAMPADA_VERMELHA_OFF;
					estado = CONFIGURA_VASILHAMES;
				}
				
			break;
			
			case RESERVATORIO_BAIXO:
			
				if(flagReservatorioBaixo)
				{
					LAMPADA_VERMELHA_ON;
				}
				else
				{
					LAMPADA_VERMELHA_OFF;
				}
				if(!SR)
				{
					estado = CONFIGURA_VASILHAMES;
					LAMPADA_VERMELHA_OFF;
				}
			
			break;
			
			case SENSOR_DEF:
		
				if(RS)
				{
					estado = CONFIGURA_VASILHAMES;
					LAMPADA_VERMELHA_OFF;
				}
			
			break;
		}
		AtualizaLcd(estado,numeroDeVasilhamesInteiro);
    }
}
