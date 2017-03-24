#include <LPC17xx.h>
#define FIRST_SEG 0xF87FFFFF
#define SECOND_SEG 0xF8FFFFFF
#define THIRD_SEG 0xF97FFFFF
#define FOURTH_SEG 0xF9FFFFFF
#define DISABLE_ALL 0xFA7FFFFF

void delay(void);
void scan(void);
void display(void);

unsigned char col,row,flag;
unsigned long int i,temp,temp3;

unsigned long seg_list[4] = {FIRST_SEG, SECOND_SEG, THIRD_SEG, FOURTH_SEG};
unsigned char seg_disp[16] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7c,0x58,0x5e,0x79,0x71};
unsigned char SEVEN_CODE[4][4] = {{0x3F,0x06,0x5B,0x03},{0x66,0x6D,0x7D,0x80},{0x7F,0x6F,0x77,0x00},{0x58,0x5e,0x79,0x00}};
char sign[4] = {'+', '-'};
unsigned char one_sec_flg = 0x00;
int val[2], neg_fl=0, c=0;

int main(void)
{
	int res;	char op;
	SystemInit();
	SystemCoreClockUpdate();
	 
	LPC_PINCON->PINSEL0 &= 0x7F0000FF;	 //P0.4 to P0.11 GPIO data lines
	LPC_PINCON->PINSEL1 &= 0xFFFFFFF8;
	LPC_GPIO0->FIODIR |= 0x00078FF0;		//P0.4 to P0.11 output
	LPC_PINCON->PINSEL3 &= 0xFFC03FFF; 	//P1.23 to P1.26 MADE GPIO
	LPC_PINCON->PINSEL4 &= 0xF00FFFFF; 	//P2.10 t P2.13 made GPIO
	LPC_GPIO2->FIODIRL |= 0x3C00; 		//made output P2.10 to P2.13 (rows)
	LPC_GPIO1->FIODIRH &= 0xF87F; 		//made input P1.23 to P1.26 (cols)

	while(1)
		for(row=0;row<4;row++){
			if(row == 0)
			temp = 0x00000400;
			else if(row == 1)
			temp = 0x00000800;
			else if(row == 2)
			temp = 0x00001000;
			else if(row == 3)
			temp = 0x00002000;
		
			LPC_GPIO2->FIOPIN = temp;
			flag = 0;
			scan();
			if(flag == 1)
			{
				for(i=0; i<100000; i++);
				c++;
				switch(c){
					case 1:	val[0] = row * 3 + col;
					case 2:	op = sign[col];
					case 3:	val[1] = row * 3 + col;
				}
				if(c==3){
					switch(op){
						case '+' :  res = val[0]+val[1];
									break;
						case '-' : 	res = val[0]-val[1];
									break;
					}
					if (res<0){
						neg_fl = 1;
						res *= -1;
					}
					for(i=0; i<2; i++){
						val[i] = res%10;
						res /=10;
					}
				}
			}
			display();
		}		
}

void display(void){
	int n;long i;
	if(c==1){
		LPC_GPIO0->FIOMASK= seg_list[0]>>4;
		LPC_GPIO0->FIOPIN = seg_list[0]>>4;
		LPC_GPIO0->FIOMASK=0xFFFFF00F;
		LPC_GPIO0->FIOPIN = SEVEN_CODE[row][col]<<4;
	}
	else if(c==2){
		LPC_GPIO0->FIOMASK= seg_list[0]>>4;
		LPC_GPIO0->FIOPIN = seg_list[0]>>4;
		LPC_GPIO0->FIOMASK=0xFFFFF00F;
		LPC_GPIO0->FIOPIN = SEVEN_CODE[row][col]<<4;
	}
	else if(c==3){
		LPC_GPIO0->FIOMASK= seg_list[0]>>4;
		LPC_GPIO0->FIOPIN = seg_list[0]>>4;
		LPC_GPIO0->FIOMASK=0xFFFFF00F;
		LPC_GPIO0->FIOPIN = SEVEN_CODE[row][col]<<4;
	}
	else{
		if(neg_fl){
				LPC_GPIO0->FIOMASK=THIRD_SEG>>4;
				LPC_GPIO0->FIOPIN = 0x80>>4;
		}
		for(n=0; n<2; n++){	
			LPC_GPIO0->FIOMASK= seg_list[n]>>4;
			LPC_GPIO0->FIOPIN = seg_list[n]>>4;
			LPC_GPIO0->FIOMASK=0xFFFFF00F;
			LPC_GPIO0->FIOPIN = seg_disp[val[n]]<<4;
			for(i=0; i<500; i++);
			LPC_GPIO0->FIOCLRL = 0x0FF0;
		}
	}
}

void scan(void)
{
 	unsigned long temp3;
	temp3 = LPC_GPIO1->FIOPIN;	
	temp3 &= 0x07800000;
	if(temp3 != 0x00000000)
	{
		flag = 1;
		if (temp3 ==0x00800000)
			col=0;
		else if (temp3==0x01000000)
			col=1;
		else if (temp3==0x02000000)
			col=2;
		else if (temp3==0x04000000)
			col=3;
	}
}