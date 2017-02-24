#include <stdio.h>
#include <LPC17xx.h>

unsigned long LED;
short int i;
void delay(int);

int main(void){
	SystemInit();
	SystemCoreClockUpdate();
	
	//Output Pins
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0->FIODIRL |= 0x0FF0;
	LPC_GPIO0->FIOCLR &= 0xFFFFFFFF;
	while(1){
		LED = 0x10;
		for(i=0; i<8; i++){
			LPC_GPIO0->FIOSET = LED;
			LED = LED<<1;
			delay(1000);
		}
		LED = 0x10;
		for(i=0; i<8; i++){
			LPC_GPIO0->FIOCLR = LED;
			LED = LED<<1;
			delay(1000);
		}
	}
}

void delay(int i){
	long j;
	for(j=0; j<i*1000; j++);
}
