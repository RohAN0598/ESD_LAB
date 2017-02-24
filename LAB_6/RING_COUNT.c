#include <stdio.h>
#include <LPC17xx.h>

unsigned long LED;
unsigned int x;
short int i, j=0;
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
		LED = 0x10;
		LED = LED<<j;
		for(i=j; i<8; i++){
			x = LPC_GPIO2->FIOPIN1 & 0x10;
			if (x != 0x10){
				j=i;
				break;
			}
			LPC_GPIO0->FIOPIN = LED;
			LED = LED<<1;
			delay(10000);
			j=0;
		}
	}
}

void delay(int i){
	long j;
	for(j=0; j<i*1000; j++);
}
