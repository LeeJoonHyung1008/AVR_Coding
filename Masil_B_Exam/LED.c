#include <avr/io.h>
#include "LED.h"

unsigned char seg_num[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char seg_num_dp[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
// �������� ����Ǵ� ���� source file �̹Ƿ� ���⿡ �������ش�.

void IO_init()
{
	PORTA=0xFF;
	DDRA=0xFF;
	PORTC=0xFF;
	DDRC=0xFF;
	
	DDRB=0xFF;			// PORT B�� ��� �������, PORT D�� 0b0001 1100�� bit 2,3,4�� ���, �������� ��� �Է����� �����Ѵ�.
	DDRD=0x1C;
}


void LED_ON(unsigned char pin)
{
//	pint = -pin;	// �Է¹��� pin�� ���� �����ش�.
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
