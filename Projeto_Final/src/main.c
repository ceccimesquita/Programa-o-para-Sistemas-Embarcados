// setenv app "setenv autoload no; setenv ipaddr 10.4.1.2; setenv serverip 10.4.1.1; tftp 0x80000000 appTimer.bin; echo *Booting to BareMetal *; go 0x80000000"

#include "uart.h"
#include "timer.h"
#include "interrupt.h"
#include "gpio.h"
#include "jogo.h"

//extern char tabuleiro[3][3];
//extern char rodada;

void watchdogdisable();


void putCh(char c){
	while(!(HWREG(SOC_UART_0_REGS+UARTx_OP_R_LSR) & (1<<5)));

	HWREG(SOC_UART_0_REGS+UARTx_OP_W_THR) = c;
}

char getCh(){
	while(!(HWREG(HWREG(SOC_UART_0_REGS+UARTx_OP_R_LSR) & (1<<0))));

	return(HWREG(SOC_UART_0_REGS+UARTx_OP_W_THR));
}

int putString(char *str, unsigned int length){
	for(int i = 0; i < length; i++){
    	putCh(str[i]);
	}
	return(length);
}

int getString(char *buf, unsigned int length){
	for(int i = 0; i < length; i ++){
    	buf[i] = getCh();
   	}
	return(length);
}

void watchdogdisable(){		//To disable the timer, follow this sequence:
	HWREG(SOC_WDT_1_REGS+WDT_WSPR) = 0xAAAA;						//1. Write XXXX AAAAh in WDT_WSPR.
	while((HWREG(SOC_WDT_1_REGS+WDT_WWPS) & W_PEND_WSPR) != 0x0){}	//2. Poll for posted write to complete using WDT_WWPS.W_PEND_WSPR.
	HWREG(SOC_WDT_1_REGS+WDT_WSPR) = 0x5555;						//3. Write XXXX 5555h in WDT_WSPR.
	while((HWREG(SOC_WDT_1_REGS+WDT_WWPS) & W_PEND_WSPR) != 0x0){}	//4. Poll for posted write to complete using WDT_WWPS.W_PEND_WSPR.
}

int main(void){
	watchdogdisable();
	timerSetup();

	init_pinS();
	
	while(1){
		if (flagGet(GPIO1, A1) == true)
		{
			putString("A1 ", 3);
			if (tabuleiro[0][0] == ' ')
			{
				tabuleiro[0][0] = rodada;
				inverteRodada();
			}
			else
			{
				if (tabuleiro[0][0] == 'X')
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, AA1, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, AA1, LOW);
						delay(200);
					}
				}
				else
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, VA1, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, VA1, LOW);
						delay(200);
					}
				}
			}
			flagSetFalse(GPIO1, A1);
			delay(500);
		}

		if (flagGet(GPIO1, A2) == true)
		{
			putString("A2 ", 3);
			if (tabuleiro[0][1] == ' ')
			{
				tabuleiro[0][1] = rodada;
				inverteRodada();
			}
			else
			{
				if (tabuleiro[0][1] == 'X')
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, AA2, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, AA2, LOW);
						delay(200);
					}
				}
				else
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, VA2, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, VA2, LOW);
						delay(200);
					}
				}
			}
			flagSetFalse(GPIO1, A2);
			delay(500);
		}

		if (flagGet(GPIO1, A3) == true)
		{
			putString("A3 ", 3);
			if (tabuleiro[0][2] == ' ')
			{
				tabuleiro[0][2] = rodada;
				inverteRodada();
			}
			else
			{
				if (tabuleiro[0][2] == 'X')
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, AA3, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, AA3, LOW);
						delay(200);
					}
				}
				else
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, VA3, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, VA3, LOW);
						delay(200);
					}
				}
			}
			flagSetFalse(GPIO1, A3);
			delay(500);
		}

		if (flagGet(GPIO1, B1) == true)
		{
			putString("B1 ", 3);
			if (tabuleiro[1][0] == ' ')
			{
				tabuleiro[1][0] = rodada;
				inverteRodada();
				delay(500);
			}
			else
			{
				if (tabuleiro[1][0] == 'X')
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, AB1, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, AB1, LOW);
						delay(200);
					}
				}
				else
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, VB1, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, VB1, LOW);
						delay(200);
					}
				}
			}
			flagSetFalse(GPIO1, B1);
		}

		if (flagGet(GPIO1, B2) == true)
		{
			putString("B2 ", 3);
			if (tabuleiro[1][1] == ' ')
			{
				tabuleiro[1][1] = rodada;
				inverteRodada();
				delay(500);
			}
			else
			{
				if (tabuleiro[1][1] == 'X')
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, AB2, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, AB2, LOW);
						delay(200);
					}
				}
				else
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, VB2, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, VB2, LOW);
						delay(200);
					}
				}
			}
			flagSetFalse(GPIO1, B2);
		}

		if (flagGet(GPIO1, B3) == true)
		{
			putString("B3 ", 3);
			if (tabuleiro[1][2] == ' ')
			{
				tabuleiro[1][2] = rodada;
				inverteRodada();
				delay(500);
			}
			else
			{
				if (tabuleiro[1][2] == 'X')
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, AB3, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, AB3, LOW);
						delay(200);
					}
				}
				else
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, VB3, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, VB3, LOW);
						delay(200);
					}
				}
			}
			flagSetFalse(GPIO1, B3);
		}

		if (flagGet(GPIO1, C1) == true)
		{
			putString("C1 ", 3);
			if (tabuleiro[2][0] == ' ')
			{
				tabuleiro[2][0] = rodada;
				inverteRodada();
			}
			else
			{
				if (tabuleiro[2][0] == 'X')
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, AC1, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, AC1, LOW);
						delay(200);
					}
				}
				else
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, VC1, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, VC1, LOW);
						delay(200);
					}
				}
			}
			flagSetFalse(GPIO1, C1);
			delay(500);
		}

		if (flagGet(GPIO1, C2) == true)
		{
			putString("C2 ", 3);
			if (tabuleiro[2][1] == ' ')
			{
				tabuleiro[2][1] = rodada;
				inverteRodada();
			}
			else
			{
				if (tabuleiro[2][1] == 'X')
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, AC2, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, AC2, LOW);
						delay(200);
					}
				}
				else
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, VC2, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, VC2, LOW);
						delay(200);
					}
				}
			}
			flagSetFalse(GPIO1, C2);
			delay(500);
		}

		if (flagGet(GPIO1, C3) == true)
		{
			putString("C3 ", 3);
			if (tabuleiro[2][2] == ' ')
			{
				tabuleiro[2][2] = rodada;
				inverteRodada();
			}
			else
			{
				if (tabuleiro[2][2] == 'X')
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, AC3, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, AC3, LOW);
						delay(200);
					}
				}
				else
				{
					for (int i = 0; i < 3; i++)
					{
						gpioSetPinValue(GPIO2, VC3, HIGH);
						delay(200);
						gpioSetPinValue(GPIO2, VC3, LOW);
						delay(200);
					}
				}
			}
			flagSetFalse(GPIO1, C3);
			delay(500);
		}
		// Atualiza os LEDs com base no estado do tabuleiro
        atualizarLEDs();

		verificarVencedor('O');
		verificarVencedor('X');
	}

	return(0);
} /* ----------  end of function main  ---------- */