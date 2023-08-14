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

#include	"gpio.h"


/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define TIME				1000000

// state machine
typedef enum _state{
            SEQ1=1,
            SEQ2,
            SEQ3,
            SEQ4,
            SEQ5
}state;

#define WDT_WSPR 												0x48
#define WDT_WWPS 												0x34

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void delay(unsigned int );
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
	unsigned int op=SEQ2, count=0;
	ucPinNumber port=21;
	ucPinNumber in = 6;
	ucPinNumber out = 8;
	pinDirection dir_out =OUTPUT;
	pinDirection dir_in = INPUT;
	disableWatchdog();
	
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
		delay(1000);
	}
	for(count = in; count<10 ; count++){
		gpioInitPin(GPIO2, count);
		delay(1000);
	}
	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/
	for(count=port; count<25; count++){
		gpioSetDirection(GPIO1, count, dir_out);
		delay(1000);	
	}
	for(count = in ; count<8 ; count++){
		gpioSetDirection(GPIO2, count, dir_in);
		delay(1000);
	}
	for(count = out ; count<10 ; count++){
		gpioSetDirection(GPIO2, count, dir_out);
		delay(1000);
	}

	/*-----------------------------------------------------------------------------
	 *  set pin in LOW level
	 *-----------------------------------------------------------------------------*/	
	for(count=port; count<25; count++){
		ledOFF(GPIO1, count);
		delay(1000);
	}
	for(count=out; count<10; count++){
		ledOFF(GPIO2, count);
		delay(1000);
	}

	while(true){
		if(gpioGetPinValue(GPIO2, in)){
			// ledON(GPIO1, port);
			// ledON(GPIO1, port+1);
			// delay(TIME);
			// delay(TIME);
			// ledOFF(GPIO1, port);
			// ledOFF(GPIO1, port+1);

			for(count=port; count<23; count++){
				ledON(GPIO1, count);
			}
			delay(TIME);
			delay(TIME);
			delay(TIME);	
			for(count=port; count<23; count++){
				ledOFF(GPIO1, count);
			}
			
		}else{
			// ledON(GPIO1, 23);
			// ledON(GPIO1, 24);
			// delay(TIME);
			// delay(TIME);
			// ledOFF(GPIO1, 23);
			// ledOFF(GPIO1, 24);
		}
		for(count=23; count<25; count++)
			ledOFF(GPIO1, count);
		delay(TIME);
		delay(TIME);
		delay(TIME);
		for(count=23; count<25; count++)
			ledOFF(GPIO1, count);
	}
	return(0);
} /* ----------  end of function main  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledON
 *  Description:  
 * =====================================================================================
 */
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
	{
		
	}
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
static void delay(unsigned int uTime){
	volatile unsigned int ra;
	for(ra = 0; ra < uTime; ra ++);
}

