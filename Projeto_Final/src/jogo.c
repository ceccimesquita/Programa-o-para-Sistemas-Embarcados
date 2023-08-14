
#include "jogo.h"

#define TIME 1000


void init_pinS(){
    //Inicia o modulo
	gpioInitModule(GPIO1);
	gpioInitModule(GPIO2);

	//Seta o pino como gpio
	gpioPinMuxSetup(GPIO1, A1);
	gpioPinMuxSetup(GPIO1, A2);
	gpioPinMuxSetup(GPIO1, A3);
	gpioPinMuxSetup(GPIO1, B1);
	gpioPinMuxSetup(GPIO1, B2);
	gpioPinMuxSetup(GPIO1, B3);
	gpioPinMuxSetup(GPIO1, C1);
	gpioPinMuxSetup(GPIO1, C2);
	gpioPinMuxSetup(GPIO1, C3);
	gpioPinMuxSetup(GPIO2, AA1);
	gpioPinMuxSetup(GPIO2, AA2);
	gpioPinMuxSetup(GPIO2, AA3);
	gpioPinMuxSetup(GPIO2, AB1);
	gpioPinMuxSetup(GPIO2, AB2);
	gpioPinMuxSetup(GPIO2, AB3);
	gpioPinMuxSetup(GPIO2, AC1);
	gpioPinMuxSetup(GPIO2, AC2);
	gpioPinMuxSetup(GPIO2, AC3);
	gpioPinMuxSetup(GPIO2, VA1);
	gpioPinMuxSetup(GPIO2, VA2);
	gpioPinMuxSetup(GPIO2, VA3);
	gpioPinMuxSetup(GPIO2, VB1);
	gpioPinMuxSetup(GPIO2, VB2);
	gpioPinMuxSetup(GPIO2, VB3);
	gpioPinMuxSetup(GPIO2, VC1);
	gpioPinMuxSetup(GPIO2, VC2);
	gpioPinMuxSetup(GPIO2, VC3);

	delay(TIME);


	//Seta como entrada e saida
	gpioSetDirection(GPIO1, A1, INPUT);
	gpioSetDirection(GPIO1, A2, INPUT);
	gpioSetDirection(GPIO1, A3, INPUT);
	gpioSetDirection(GPIO1, B1, INPUT);
	gpioSetDirection(GPIO1, B2, INPUT);
	gpioSetDirection(GPIO1, B3, INPUT);
	gpioSetDirection(GPIO1, C1, INPUT);
	gpioSetDirection(GPIO1, C2, INPUT);
	gpioSetDirection(GPIO1, C3, INPUT);
	gpioSetDirection(GPIO2, AA1, OUTPUT);
	gpioSetDirection(GPIO2, AA2, OUTPUT);
	gpioSetDirection(GPIO2, AA3, OUTPUT);
	gpioSetDirection(GPIO2, AB1, OUTPUT);
	gpioSetDirection(GPIO2, AB2, OUTPUT);
	gpioSetDirection(GPIO2, AB3, OUTPUT);
	gpioSetDirection(GPIO2, AC1, OUTPUT);
	gpioSetDirection(GPIO2, AC2, OUTPUT);
	gpioSetDirection(GPIO2, AC3, OUTPUT);
	gpioSetDirection(GPIO2, VA1, OUTPUT);
	gpioSetDirection(GPIO2, VA2, OUTPUT);
	gpioSetDirection(GPIO2, VA3, OUTPUT);
	gpioSetDirection(GPIO2, VB1, OUTPUT);
	gpioSetDirection(GPIO2, VB2, OUTPUT);
	gpioSetDirection(GPIO2, VB3, OUTPUT);
	gpioSetDirection(GPIO2, VC1, OUTPUT);
	gpioSetDirection(GPIO2, VC2, OUTPUT);
	gpioSetDirection(GPIO2, VC3, OUTPUT);

	delay(TIME);

	//Desliga os pinos
	gpioSetPinValue(GPIO2, AA1, LOW);
	gpioSetPinValue(GPIO2, AA2, LOW);
	gpioSetPinValue(GPIO2, AA3, LOW);
	gpioSetPinValue(GPIO2, AB1, LOW);
	gpioSetPinValue(GPIO2, AB2, LOW);
	gpioSetPinValue(GPIO2, AB3, LOW);
	gpioSetPinValue(GPIO2, AC1, LOW);
	gpioSetPinValue(GPIO2, AC2, LOW);
	gpioSetPinValue(GPIO2, AC3, LOW);
	gpioSetPinValue(GPIO2, VA1, LOW);
	gpioSetPinValue(GPIO2, VA2, LOW);
	gpioSetPinValue(GPIO2, VA3, LOW);
	gpioSetPinValue(GPIO2, VB1, LOW);
	gpioSetPinValue(GPIO2, VB2, LOW);
	gpioSetPinValue(GPIO2, VB3, LOW);
	gpioSetPinValue(GPIO2, VC1, LOW);
	gpioSetPinValue(GPIO2, VC2, LOW);
	gpioSetPinValue(GPIO2, VC3, LOW);

	delay(TIME);

	gpioInterruptInit(GPIO1, A1, A);
	gpioInterruptInit(GPIO1, A2, A);
	gpioInterruptInit(GPIO1, A3, A);
	gpioInterruptInit(GPIO1, B1, A);
	gpioInterruptInit(GPIO1, B2, A);
	gpioInterruptInit(GPIO1, B3, A);
	gpioInterruptInit(GPIO1, C1, A);
	gpioInterruptInit(GPIO1, C2, A);
	gpioInterruptInit(GPIO1, C3, A);
}

void ledON(gpioMod gpio, ucPinNumber pin){
	gpioSetPinValue(gpio, pin, HIGH);
}

void ledOFF(gpioMod gpio, ucPinNumber pin){
	gpioSetPinValue(gpio, pin, LOW);
}
void inverteRodada(){
	if(rodada == 'X') rodada = 'O';
	else rodada = 'X';
}

// Função para atualizar os LEDs com base no estado do tabuleiro
void atualizarLEDs() {
    // Percorre a matriz do tabuleiro e acende os LEDs correspondentes
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char estado = tabuleiro[i][j];
            if (estado == 'X') {
                // Acende o LED azul correspondente
                if (i == 0 && j == 0) {
                    gpioSetPinValue(GPIO2, AA1, HIGH);
                } else if (i == 0 && j == 1) {
                    gpioSetPinValue(GPIO2, AA2, HIGH);
                } else if (i == 0 && j == 2) {
                    gpioSetPinValue(GPIO2, AA3, HIGH);
                } else if (i == 1 && j == 0) {
                    gpioSetPinValue(GPIO2, AB1, HIGH);
                } else if (i == 1 && j == 1) {
                    gpioSetPinValue(GPIO2, AB2, HIGH);
                } else if (i == 1 && j == 2) {
                    gpioSetPinValue(GPIO2, AB3, HIGH);
                } else if (i == 2 && j == 0) {
                    gpioSetPinValue(GPIO2, AC1, HIGH);
                } else if (i == 2 && j == 1) {
                    gpioSetPinValue(GPIO2, AC2, HIGH);
                } else if (i == 2 && j == 2) {
                    gpioSetPinValue(GPIO2, AC3, HIGH);
                }
            } else if (estado == 'O') {
                // Acende o LED vermelho correspondente
                if (i == 0 && j == 0) {
                    gpioSetPinValue(GPIO2, VA1, HIGH);
                } else if (i == 0 && j == 1) {
                    gpioSetPinValue(GPIO2, VA2, HIGH);
                } else if (i == 0 && j == 2) {
                    gpioSetPinValue(GPIO2, VA3, HIGH);
                } else if (i == 1 && j == 0) {
                    gpioSetPinValue(GPIO2, VB1, HIGH);
                } else if (i == 1 && j == 1) {
                    gpioSetPinValue(GPIO2, VB2, HIGH);
                } else if (i == 1 && j == 2) {
                    gpioSetPinValue(GPIO2, VB3, HIGH);
                } else if (i == 2 && j == 0) {
                    gpioSetPinValue(GPIO2, VC1, HIGH);
                } else if (i == 2 && j == 1) {
                    gpioSetPinValue(GPIO2, VC2, HIGH);
                } else if (i == 2 && j == 2) {
                    gpioSetPinValue(GPIO2, VC3, HIGH);
                }
            }
        }
    }
}

// Função para verificar se há um vencedor
bool verificarVencedor(char jogador) {
    // Verifica todas as possibilidades de vitória
    for (int i = 0; i < 3; i++) {
        // Verifica as linhas
        if (tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) {
			if(jogador == 'X'){ // X == AZUL
				switch(i){
					case 0:
						while (1)
						{
							ledON(GPIO2, AA1);
							ledON(GPIO2, AA2);
							ledON(GPIO2, AA3);
							delay(TIME);
							ledOFF(GPIO2, AA1);
							ledOFF(GPIO2, AA2);
							ledOFF(GPIO2, AA3);
							delay(TIME);
						}
						break;
					case 1:
						while (1)
						{
							ledON(GPIO2, AB1);
							ledON(GPIO2, AB2);
							ledON(GPIO2, AB3);
							delay(TIME);
							ledOFF(GPIO2, AB1);
							ledOFF(GPIO2, AB2);
							ledOFF(GPIO2, AB3);
							delay(TIME);
						}
						break;
					case 2:
						while (1)
						{
							ledON(GPIO2, AC1);
							ledON(GPIO2, AC2);
							ledON(GPIO2, AC3);
							delay(TIME);
							ledOFF(GPIO2, AC1);
							ledOFF(GPIO2, AC2);
							ledOFF(GPIO2, AC3);
							delay(TIME);
						}
						break;
					}
				}else { // O == VERMELHO
					switch(i){
					case 0:
						while (1)
						{
							ledON(GPIO2, VA1);
							ledON(GPIO2, VA2);
							ledON(GPIO2, VA3);
							delay(TIME);
							ledOFF(GPIO2, VA1);
							ledOFF(GPIO2, VA2);
							ledOFF(GPIO2, VA3);
							delay(TIME);
						}
						break;
					case 1:
						while (1)
						{
							ledON(GPIO2, VB1);
							ledON(GPIO2, VB2);
							ledON(GPIO2, VB3);
							delay(TIME);
							ledOFF(GPIO2, VB1);
							ledOFF(GPIO2, VB2);
							ledOFF(GPIO2, VB3);
							delay(TIME);
						}
						break;
					case 2:
						while (1)
						{
							ledON(GPIO2, VC1);
							ledON(GPIO2, VC2);
							ledON(GPIO2, VC3);
							delay(TIME);
							ledOFF(GPIO2, VC1);
							ledOFF(GPIO2, VC2);
							ledOFF(GPIO2, VC3);
							delay(TIME);
						}
						break;

					}
				}

        	}
			return true;
		
        // Verifica as colunas
        if (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador) {
			if(jogador == 'X'){ // X == AZUL
				switch(i){
					case 0:
						while (1)
						{
							ledON(GPIO2, AA1);
							ledON(GPIO2, AB1);
							ledON(GPIO2, AC1);
							delay(TIME);
							ledOFF(GPIO2, AA1);
							ledOFF(GPIO2, AB1);
							ledOFF(GPIO2, AC1);
							delay(TIME);
						}
						break;
					case 1:
						while (1)
						{
							ledON(GPIO2, AA2);
							ledON(GPIO2, AB2);
							ledON(GPIO2, AC2);
							delay(TIME);
							ledOFF(GPIO2, AA2);
							ledOFF(GPIO2, AB2);
							ledOFF(GPIO2, AC2);
							delay(TIME);
						}
						break;
					case 2:
						while (1)
						{
							ledON(GPIO2, AA3);
							ledON(GPIO2, AB3);
							ledON(GPIO2, AC3);
							delay(TIME);
							ledOFF(GPIO2, AA3);
							ledOFF(GPIO2, AB3);
							ledOFF(GPIO2, AC3);
							delay(TIME);
						}
						break;
					}
				}else { // O == VERMELHO
					switch(i){
					case 0:
						while (1)
						{
							ledON(GPIO2, VA1);
							ledON(GPIO2, VB1);
							ledON(GPIO2, VC1);
							delay(TIME);
							ledOFF(GPIO2, VA1);
							ledOFF(GPIO2, VB1);
							ledOFF(GPIO2, VC1);
							delay(TIME);
						}
						break;
					case 1:
						while (1)
						{
							ledON(GPIO2, VA2);
							ledON(GPIO2, VB2);
							ledON(GPIO2, VC2);
							delay(TIME);
							ledOFF(GPIO2, VA2);
							ledOFF(GPIO2, VB2);
							ledOFF(GPIO2, VC2);
							delay(TIME);
						}
						break;
					case 2:
						while (1)
						{
							ledON(GPIO2, VA3);
							ledON(GPIO2, VB3);
							ledON(GPIO2, VC3);
							delay(TIME);
							ledOFF(GPIO2, VA3);
							ledOFF(GPIO2, VB3);
							ledOFF(GPIO2, VC3);
							delay(TIME);
						}
						break;

					}
				}
			
            return true;
        }
    }
    // Verifica as diagonais
    if (tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) {
		while (1){
			if(jogador == 'X'){
				ledON(GPIO2, AA1);
				ledON(GPIO2, AB2);
				ledON(GPIO2, AC3);
				delay(TIME);
				ledOFF(GPIO2, AA1);
				ledOFF(GPIO2, AB2);
				ledOFF(GPIO2, AC3);
				delay(TIME);
			}else{
				ledON(GPIO2, VA1);
				ledON(GPIO2, VB2);
				ledON(GPIO2, VC3);
				delay(TIME);
				ledOFF(GPIO2, VA1);
				ledOFF(GPIO2, VB2);
				ledOFF(GPIO2, VC3);
				delay(TIME);
			}
		}
        return true;
    }
    if (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador) {
		while (1)
			if(jogador == 'X'){
				ledON(GPIO2, AC1);
				ledON(GPIO2, AB2);
				ledON(GPIO2, AA3);
				delay(TIME);
				ledOFF(GPIO2, AC1);
				ledOFF(GPIO2, AB2);
				ledOFF(GPIO2, AA3);
				delay(TIME);
			}else{
				ledON(GPIO2, VC1);
				ledON(GPIO2, VB2);
				ledON(GPIO2, VA3);
				delay(TIME);
				ledOFF(GPIO2, VC1);
				ledOFF(GPIO2, VB2);
				ledOFF(GPIO2, VA3);
				delay(TIME);
			}
		return true;
	}
    return false;
}


