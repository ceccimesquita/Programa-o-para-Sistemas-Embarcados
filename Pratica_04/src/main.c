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
	
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){
	unsigned char cou=9; 
	unsigned int count=0;
	ucPinNumber port=21;
	ucPinNumber in = 6;
	ucPinNumber out = 8;
	pinDirection dir_out =OUTPUT;
	pinDirection dir_in = INPUT;
	disableWatchdog();

	/*-----------------------------------------------------------------------------
	 *  initialize UART modules
	 *-----------------------------------------------------------------------------*/
	uartInitModule(UART0, 115200, STOP1, PARITY_NONE, FLOW_OFF);
	
	/*-----------------------------------------------------------------------------
	 *  initialize TIMER modules
	 *-----------------------------------------------------------------------------*/
    DMTimerSetUp();

	/*-----------------------------------------------------------------------------
	 *  initialize GPIO modules
	 *-----------------------------------------------------------------------------*/
	gpioInitModule(GPIO1);
	gpioInitModule(GPIO2);
	
	/*-----------------------------------------------------------------------------
	 *  configure multplex in the pin of mudule
	 *-----------------------------------------------------------------------------*/
	for(count=port; count<25; count++){
		gpioInitPin(GPIO1, count);
		Delay(10);
	}
	for(count = in; count<10 ; count++){
		gpioInitPin(GPIO2, count);
		Delay(10);
	}
	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/
	for(count=port; count<25; count++){
		gpioSetDirection(GPIO1, count, dir_out);
		Delay(10);	
	}
	for(count = in ; count<8 ; count++){
		gpioSetDirection(GPIO2, count, dir_in);
		Delay(10);
	}
	for(count = out ; count<10 ; count++){
		gpioSetDirection(GPIO2, count, dir_out);
		Delay(10);
	}

	/*-----------------------------------------------------------------------------
	 *  set pin in LOW level
	 *-----------------------------------------------------------------------------*/	
	for(count=port; count<25; count++){
		ledOFF(GPIO1, count);
		Delay(10);
	}
	for(count=out; count<10; count++){
		ledOFF(GPIO2, count);
		Delay(10);
	}

	while(true){
		ledON(GPIO2, out);
		Delay(TIME);
		ledOFF(GPIO2, out);
		Delay(TIME);
	}

	//uartPutString(UART0,"GPIO INPUT Initialized",23);	
  	uartPutString(UART0,"Time: ",7);
  	while(cou){
		uartPutC(UART0,0x30+cou);
		Delay(1000);
		cou--;
		uartPutC(UART0,' ');
	}
	uartPutString(UART0,"OK...",5);

	
	
	
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



