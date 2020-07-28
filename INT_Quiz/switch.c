#include <avr/io.h>
#include "switch.h"

unsigned char SW(unsigned char pin)
{
	unsigned char sw_input;
	sw_input=PIND;
	sw_input&=pin;
	return sw_input;
}

int KEYPAD(void)
{
	//2,3,4 ������� ���, 5,6,7�� �Է����� ���.
	//2.3.4, �� �ϳ��� low ������ high�� �ְ� �� ���� PIND�� ����
	//masking�� ���� ���� 4�� bit�� �ɷ����� SEG_ON
	unsigned char sw_input;
	
	while(1)
	{
	PORTD=0b11111011;
	sw_input=PIND;
	sw_input&=0b11100000;

	if(sw_input==0b01100000)		//����ŷ�� ���� 7�̸�.
	return 1;
	else if(sw_input==0b10100000)
	return 4;
	else if(sw_input==0b11000000)
	return 7;

	PORTD=0x11110111;
	sw_input=PIND;
	sw_input&=0b11100000;
	if(sw_input==0b01100000)		//����ŷ�� ���� 7�̸�.
	return 2;
	else if(sw_input==0b10100000)
	return 5;
	else if(sw_input==0b11000000)
	return 8;

	PORTD=0x11101111;
	sw_input=PIND;
	sw_input&=0b11100000;
	if(sw_input==0b01100000)		//����ŷ�� ���� 7�̸�.
	return 3;
	else if(sw_input==0b10100000)
	return 6;
	else if(sw_input==0b11000000)
	return 9;
	}
}
