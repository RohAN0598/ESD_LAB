#include <stdio.h>
#include <LPC17xx.h>

unsigned char LED = 0x00;
void delay(int);

int main(void){
	SystemInit();
	SystemCoreClockUpdate();
	
	//Output Pins
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0->FIODIRL |= 0x0FF0;
	
	while(1){
		LPC_GPIO0->FIOPINL = LED<<4;
		LED += 0x01;
		delay(1000);
	}
}

void delay(int i){
	long j;
	for(j=0; j<i*1000; j++);
}
