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

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void delay(unsigned int );
void ledON(gpioMod  ,ucPinNumber );
void ledOFF(gpioMod ,ucPinNumber );
	
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){
	unsigned int op=SEQ2, count=0;
	ucPinNumber port=22;
	pinDirection dir=OUTPUT;
	
	/*-----------------------------------------------------------------------------
	 *  initialize GPIO modules
	 *-----------------------------------------------------------------------------*/
	gpioInitModule(GPIO1);
	
	/*-----------------------------------------------------------------------------
	 *  configure multplex in the pin of mudule
	 *-----------------------------------------------------------------------------*/
	for(count=port; count<25; count++){
		gpioInitPin(GPIO1, count);
		delay(1000);
	}

	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/
	for(count=port; count<25; count++){
		gpioSetDirection(GPIO1, count, dir);
		delay(1000);	
	}

	/*-----------------------------------------------------------------------------
	 *  set pin in LOW level
	 *-----------------------------------------------------------------------------*/	
	for(count=port; count<25; count++){
		ledOFF(GPIO1, count);
		delay(1000);
	}

	while(true){
		switch (op){
			case SEQ1:
				ledON(GPIO1, port);
				delay(TIME);
				ledOFF(GPIO1, port);
				delay(TIME);
				op=SEQ1;
			break;
			case SEQ2:	
				ledON(GPIO1, port);
				delay(TIME);
				ledOFF(GPIO1, port);
				delay(TIME);
				op=SEQ3;
			break;
			case SEQ3:	
				ledON(GPIO1, port+1);
				delay(TIME);
				ledOFF(GPIO1, port+1);
				delay(TIME);
				op=SEQ4;
			break;
			case SEQ4:	
				ledON(GPIO1, port+2);
				delay(TIME);
				ledOFF(GPIO1, port+2);
				delay(TIME);
				op=SEQ5;
			break;
			case SEQ5:
				for(count=port; count<25; count++)
					ledON(GPIO1, count);
				delay(TIME);
				for(count=22; count<25; count++)
					ledOFF(GPIO1, count);
				delay(TIME);
				op=SEQ2;
			break;
			default:	
			break;
		}// -----  end switch  ----- 
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

/*FUNCTION*-------------------------------------------------------
*
* Function Name : Delay
* Comments      :
*END*-----------------------------------------------------------*/
static void delay(unsigned int uTime){
	volatile unsigned int ra;
	for(ra = 0; ra < uTime; ra ++);
}

