/************************************************************************
 
 * ----------------------------------------------------------------------
 * Pin P0.26 is a analog output pin. A digital value at the register. DACR
 * A ramp wave can be observed at TP8 in CRO. Open JP5 
*************************************************************************/
 #include <lpc17xx.h>
 #include <math.h>

 #define DAC_BIAS			(0x1<<16)  //maximum update rate of 400KHz
 #define DATA_LENGTH		0x400 	   //Maximum value is 0xCFF in 10 bit DAC
	
  unsigned int vals[] = {310, 390, 465, 527, 577, 608, 620, 608, 577, 527, 465, 390, 310, 229, 155, 90, 43, 11, 0, 11, 43, 90, 155, 229};

 void DAC_Init(void);

 int main (void)
 {
	unsigned int m,i = 0;

	SystemInit();
	SystemCoreClockUpdate();

  	/* Initialize DAC  */
	DAC_Init();
	
	while ( 1 )
	{
		LPC_DAC->DACR = (vals[i] << 6) | DAC_BIAS;   // AOUT = DACR value x ((VREFP - VREFN)/1024) + VREFN
		i = (++i)%24;
		for(m = 100; m > 1; m--);	  
  	}
 }

 void DAC_Init( void )
 {
 /* Note that the DAC does not have a control bit in the PCONP register.
	To enable the DAC, its output must be selected to appear on the
	related pin, P0.26, by configuring the PINSEL1 register */

  	/* setup the related pin to DAC output */
	LPC_PINCON->PINSEL1 = 0x00200000;	/* set p0.26 to DAC output */   
    
	LPC_DAC->DACCNTVAL = 0x0050;
	LPC_DAC->DACCTRL = (0x1<<1)|(0x1<<2);	  
	return;
 }

