#include <avr/io.h>
#include "LED.h"

unsigned char seg_num[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
// �������� ����Ǵ� ���� source file �̹Ƿ� ���⿡ �������ش�.

void IO_init()
{
   DDRA=0XFF;         // PORT A(���ʼ��׸�Ʈ)�� ���������� ����� ����
   DDRC=0xFF;         // PORT C(�����ʼ��׸�Ʈ)�� ���������� ����� ����
   DDRD=0x00;		// PORT D�� ��� �Է����� ����� ����.
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
