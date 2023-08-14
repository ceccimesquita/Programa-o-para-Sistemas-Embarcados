#ifndef JOGO_H_
#define JOGO_H_


#include "gpio.h"
#include "uart.h"
#include "interrupt.h"
#include "timer.h"

//botoes
#define A1 		6
#define A2 		7
#define A3 		2
#define B1 		14
#define B2 		28
#define B3 		19
#define C1 		18
#define C2		16
#define C3		17

//leds azuis
#define AA1 	2
#define AA2 	5
#define AA3 	22
#define AB1 	23
#define AB2 	14
#define AB3 	12
#define AC1 	10
#define AC2		8
#define AC3		6

//leds vermelhos
#define VA1 	3
#define VA2 	4
#define VA3 	24 
#define VB1 	25
#define VB2 	15 
#define VB3 	13
#define VC1 	11
#define VC2		9
#define VC3		7

//char tabuleiro
char tabuleiro[3][3]={
	{' ', ' ', ' '},
	{' ', ' ', ' '},
	{' ', ' ', ' '},
};

char rodada = 'X';

void init_pinS(void);
bool verificarVencedor(char);
void atualizarLEDs();
void inverteRodada();
void ledON(gpioMod, ucPinNumber);
void ledOFF(gpioMod, ucPinNumber);


#endif /* JOGO_H_ */