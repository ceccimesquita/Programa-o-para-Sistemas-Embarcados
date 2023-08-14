/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/02/2017 20:05:55
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "uart.h"
#include "timer.h"
#include "gpio.h"
#include "interrupt.h"

#define TIME													1
#define WDT_WSPR 												0x48
#define WDT_WWPS 												0x34

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
void ledON(gpioMod  ,ucPinNumber );
void ledOFF(gpioMod ,ucPinNumber );
void disableWatchdog();


void timerIrqHandler(void){

    /* Clear the status of the interrupt flags */
	HWREG(SOC_DMTIMER_7_REGS + DMTIMER_IRQSTATUS) = 0x2; 

	setTimer();

    /* Stop the DMTimer */
	DMTimerDisable(SOC_DMTIMER_7_REGS);

	//Pisca o led
	//((flag_timer++ & 0x1) ? ledOn() : ledOff());
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ISR_Handler
 *  Description:  
 * =====================================================================================
 */
void ISR_Handler(void){
	/* Verifica se é interrupção do RTC */
	unsigned int irq_number = HWREG(SOC_AINTC_REGS + INTC_SIR_IRQ) & 0x7f;
	
	if(irq_number == 95)
		timerIrqHandler();
    
	/* Reconhece a IRQ */
	HWREG(SOC_AINTC_REGS + INTC_CONTROL) = 0x1;
}
	
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){
	
	DMTimerSetUp();
	Interrupt_Setup(95);
	gpioInitModule(GPIO1);
	gpioInitPin(GPIO1, 21);
	gpioSetDirection(GPIO1, 21, OUTPUT);
	
	disableWatchdog();

	while (true)
	{
		ledON(GPIO1, 21);
		Delay(3000);
		ledOFF(GPIO1, 21);
		Delay(3000);
			
	}

	return(0);

} /* ----------  end of function main  ---------- */

void ledON(gpioMod mod, ucPinNumber pin){
		gpioSetPinValue(mod, pin, HIGH);	
}/* -----  end of function ledON  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledOFF
 *  Description:  
 * =====================================================================================
 */
void ledOFF(gpioMod mod,  ucPinNumber pin ){
	gpioSetPinValue(mod, pin, LOW);
}/* -----  end of function ledOFF  ----- */

void disableWatchdog(){
	HWREG(SOC_WDT_1_REGS + WDT_WSPR) = 0xAAAA;

	while ((HWREG(SOC_WDT_1_REGS + WDT_WWPS) & ( 1 << 0x4u)) != 0);
	{}
	HWREG(SOC_WDT_1_REGS + WDT_WSPR) = 0x5555;

	while ((HWREG(SOC_WDT_1_REGS + WDT_WWPS) & ( 1 << 0x4u)) != 0);
	{
	}
}


/*FUNCTION*-------------------------------------------------------
*
* Function Name : Delay
* Comments      :
*END*-----------------------------------------------------------*/



