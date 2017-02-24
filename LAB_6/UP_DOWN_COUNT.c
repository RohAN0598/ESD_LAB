#include <stdio.h>
#include <LPC17xx.h>

unsigned char LED = 0x00;
unsigned int x;
void delay(int);

int main(void){
	SystemInit();
	SystemCoreClockUpdate();
	
	//Output Pins
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0->FIODIRL |= 0x0FF0;
	
	//Input Pins
	LPC_PINCON->PINSEL4 &= 0xFDFFFFFFF;
	LPC_GPIO2->FIODIR1 |= 0x00;
	
	while(1){
		x = LPC_GPIO2->FIOPIN1 & 0x10;
		if (x != 0x10)
			LED+=0x01;
		else
			LED -= 0x01;
		
		LPC_GPIO0->FIOPINL = LED<<4;
		delay(10000);
	}
}

void delay(int i){
	long j;
	for(j=0; j<i*1000; j++);
}
