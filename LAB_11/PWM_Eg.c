#include<LPC17xx.h>
void pwm_init(void);
void PWM1_IRQHandler(void);
unsigned long int i;
unsigned char flag, flag1;

int main(void) // definition of the main function 
{
	SystemInit();
	SystemCoreClockUpdate();
	pwm_init(); // call of the function pwm_init
	while(1)
	{
		for(i=0;i<=1000;i++); // delay
	}
	
} // end of the main function 

void pwm_init(void) // definition of the function pwm_init
{
	LPC_SC->PCONP |= (1<<6); // config
	LPC_PINCON->PINSEL3 &= ~(0X0000C000);
	LPC_PINCON->PINSEL3 |= 0X00008000;
	LPC_PWM1->PR=0X00;
	LPC_PWM1->PCR=0X1000;
	LPC_PWM1->MCR=0X03;
	LPC_PWM1->MR0=30000;
	LPC_PWM1->MR4=0X100;
	LPC_PWM1->LER=0X00FF;
	LPC_PWM1->TCR=0X02;
	LPC_PWM1->TCR=0X09;
	NVIC_EnableIRQ(PWM1_IRQn); // Enabled
	return;
	
} // end of the function pwm_init

void PWM1_IRQHandler(void) // definition of the handler
{
	LPC_PWM1->IR=0XFF;
	if(flag == 0X00)
	{
		LPC_PWM1->MR4 += 100;
		LPC_PWM1->LER = 0X00FF;
		if(LPC_PWM1->MR4 >= 27000)
		{
				flag1 = 0XFF;
				flag = 0XFF;
				LPC_PWM1->LER = 0X00FF;
		}
	}
	else if(flag1 == 0xFF)
	{
		LPC_PWM1->MR4 -= 100;
		LPC_PWM1->LER = 0X00FF;
		if(LPC_PWM1->MR4 <= 500)
		{
				flag = 0X00;
				flag1 = 0X00;
				LPC_PWM1->LER = 0X00FF;
		}
	}
}

void EINT3_IRQHandler(void){
	
}