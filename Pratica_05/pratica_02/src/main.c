#include "interruption.h"
#include "uart.h"
#include "timer.h"
#include "gpio.h"

#define  WDT_WSPR 								0x44E35048
#define  WDT_WWPS 								0x44E35034

/**
 * \brief   This macro will check for write POSTED status
 *
 * \param   reg          Register whose status has to be checked
 *
 *    'reg' can take the following values \n
 *    DMTIMER_WRITE_POST_TCLR - Timer Control register \n
 *    DMTIMER_WRITE_POST_TCRR - Timer Counter register \n
 *    DMTIMER_WRITE_POST_TLDR - Timer Load register \n
 *    DMTIMER_WRITE_POST_TTGR - Timer Trigger register \n
 *    DMTIMER_WRITE_POST_TMAR - Timer Match register \n
 *
 **/


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  disableWdt
 *  Description:  
 * =====================================================================================
 */
void disableWdt(void){
	HWREG(WDT_WSPR) = 0xAAAA;
	while((HWREG(WDT_WWPS) & (1<<4)));
	
	HWREG(WDT_WSPR) = 0x5555;
	while((HWREG(WDT_WWPS) & (1<<4)));
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  timerIrqHandler
 *  Description:  
 * =====================================================================================
 */
void timerIrqHandler(void){

    /* Clear the status of the interrupt flags */
	HWREG(SOC_DMTIMER_7_REGS+DMTIMER_IRQSTATUS) = 0x2; 

	setflag_timer();

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
	unsigned int irq_number = HWREG(INTC_BASE+INTC_SIR_IRQ) & 0x7f;
	
	if(irq_number == 95)
		timerIrqHandler();
    
	/* Reconhece a IRQ */
	HWREG(INTC_BASE+INTC_CONTROL) = 0x1;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledON
 *  Description:  
 * =====================================================================================
 */
void ledON(gpioMod mod, ucPinNumber pin){
	gpioSetPinValue(mod, pin, HIGH);	
}
/* -----  end of function ledON  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledOFF
 *  Description:  
 * =====================================================================================
 */
void ledOFF(gpioMod mod,  ucPinNumber pin ){
	gpioSetPinValue(mod, pin, LOW);
}/* -----  end of function ledOFF  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){
	unsigned int count=0;
	ucPinNumber port=21;
	
	DMTimerSetUp();
	disableWdt();
	Interrupt_Setup(95);
	
	/* Hardware setup */
		/*-----------------------------------------------------------------------------
	 *  initialize GPIO modules
	 *-----------------------------------------------------------------------------*/
	gpioInitModule(GPIO1);
	
	/*-----------------------------------------------------------------------------
	 *  configure multplex in the pin of mudule
	 *-----------------------------------------------------------------------------*/
	for(count=port; count<25; count++){
		gpioInitPin(GPIO1, count);
		Delay(10);
	}
	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/
	for(count=port; count<25; count++){
		gpioSetDirection(GPIO1, count, OUTPUT);
		Delay(10);	
	}
	while (true)
	{

		for(count=port; count<25; count++){ \
			ledON(GPIO1, count);
		}
		Delay(3000);
		for(count=port; count<25; count++){ 
			ledOFF(GPIO1, count);
		}
		Delay(3000);
			
	}
	

	return(0);
}




