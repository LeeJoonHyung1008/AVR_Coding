#include <avr/io.h>
#include "LED.h"

unsigned char seg_num[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
// 변수들이 선언되는 곳은 source file 이므로 여기에 선언해준다.

void IO_init()
{
   DDRA=0XFF;         // PORT A(왼쪽세그먼트)는 모두출력으로 사용할 것임
   DDRC=0xFF;         // PORT C(오른쪽세그먼트)는 모두출력으로 사용할 것임
   DDRD=0x00;		// PORT D는 모두 입력으로 사용할 것임.
}

void LED_ON(unsigned char pin)
{
//	pint = -pin;	// 입력받은 pin을 반전 시켜준다.
//	PORTA = PORTA & pin;
	PORTA &= (~pin);
}

void LED_OFF(unsigned char pin)
{
	PORTA |= (pin);
}

void SEG_ON(unsigned char PORT, unsigned char data)
{
	if(PORT=='A')
	{
	PORTA=seg_num[data];
	}
	else if(PORT=='C')
	{
	PORTC=seg_num[data];
	}
}

void SEG_ON_two_numbers_all_in_one(unsigned int data)
{
	PORTA=seg_num[data/10];
	PORTC=seg_num[data%10];
}
