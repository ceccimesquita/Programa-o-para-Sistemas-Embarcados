/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/05/2018 14:32:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */
#include "gpio.h"
#include "hw_types.h"
#include "interrupt.h"
#include "bbb_regs.h"
#include "timer.h"

#define WDT_WSPR 												0x48
#define WDT_WWPS 												0x34


bool flag_gpio = false;

typedef enum _pinNum{
	PIN1=1,
	PIN2
}pinNum;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  disableWdt
 *  Description:  
 * =====================================================================================
 */
void disableWatchdog(){
	HWREG(SOC_WDT_1_REGS + WDT_WSPR) = 0xAAAA;

	while ((HWREG(SOC_WDT_1_REGS + WDT_WWPS) & ( 1 << 0x4u)) != 0);
	{}
	HWREG(SOC_WDT_1_REGS + WDT_WSPR) = 0x5555;

	while ((HWREG(SOC_WDT_1_REGS + WDT_WWPS) & ( 1 << 0x4u)) != 0);
	{
	}
}



void putCh(char c){
	while(!(HWREG(UART0_LSR) & (1<<5)));

	HWREG(UART0_THR) = c;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getCh
 *  Description:  
 * =====================================================================================
 */
char getCh(){
	while(!(HWREG(UART0_LSR) & (1<<0)));

	return(HWREG(UART0_RHR));
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  putString
 *  Description:  
 * =====================================================================================
 */
int putString(char *str, unsigned int length){
	for(int i = 0; i < length; i++){
    	putCh(str[i]);
	}
	return(length);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getString
 *  Description:  
 * =====================================================================================
 */
int getString(char *buf, unsigned int length){
	for(int i = 0; i < length; i ++){
    	buf[i] = getCh();
   	}
	return(length);
}

void delay(unsigned int mSec){
    volatile unsigned int count;
    
	for(count=0; count<mSec; count++);

}

void ledON(gpioMod mod, ucPinNumber pin){
		gpioSetPinValue(mod, pin, HIGH);	
}

void ledOFF(gpioMod mod,  ucPinNumber pin ){
	gpioSetPinValue(mod, pin, LOW);
}
void gpioIsrHandler(void){

    /* Clear the status of the interrupt flags */
	HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0) = 0x10000000; //gpio1 = 0x4804_C000 + gpio_irqstatus_0 = 0x2C

	flag_gpio = true;
}

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
	/* Verify active IRQ number */
	unsigned int irq_number = HWREG(SOC_AINTC_REGS + INTC_SIR_IRQ) & 0x7f; //inct = 0x4820_0000 + sir_iqr = 0x40
	
	if(irq_number == 98)
		gpioIsrHandler();
	if(irq_number == 95)
		timerIrqHandler();
	/* acknowledge IRQ */
	HWREG(SOC_AINTC_REGS + INTC_CONTROL) = 0x1;  //inct = 0x4820_0000 + control = 0x48
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){
	/*set clok gpio1*/
	Interrupt_Setup(98);
	Interrupt_Setup(95);
	putString("gpio Interrupt...\n\r", 19);
	DMTimerSetUp();
	putString("gpio Interrupt...\n\r", 19);
	gpioInitModule(GPIO1);
	putString("gpio Interrupt...\n\r", 19);
	gpioInitPin(GPIO1, 28);
	putString("gpio Interrupt...\n\r", 19);
	gpioSetDirection(GPIO1, 28, INPUT);
	putString("gpio Interrupt...\n\r", 19);
	gpioInitPin(GPIO1, 23);
	gpioSetDirection(GPIO1, 23, OUTPUT);
	gpioInitPin(GPIO1, 24);
	gpioSetDirection(GPIO1, 24, OUTPUT);
	gpio_interrupt_config(GPIO1, 28, 0);

	disableWatchdog();


	while(true){
		if(flag_gpio){
			ledON(GPIO1, 23);
			Delay(1000);
			ledOFF(GPIO1, 23);
			Delay(1000);
			flag_gpio = false;
		}else{
			ledON(GPIO1, 24);
			Delay(1000);
			ledOFF(GPIO1, 24);
			Delay(1000);
		}
	}

	return(0);
}

