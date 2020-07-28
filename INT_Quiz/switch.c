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
	//2,3,4 출력으로 사용, 5,6,7은 입력으로 사용.
	//2.3.4, 중 하나는 low 나머진 high를 주고 이 값을 PIND에 저장
	//masking을 통해 상위 4개 bit만 걸러내서 SEG_ON
	unsigned char sw_input;
	
	while(1)
	{
	PORTD=0b11111011;
	sw_input=PIND;
	sw_input&=0b11100000;

	if(sw_input==0b01100000)		//마스킹한 값이 7이면.
	return 1;
	else if(sw_input==0b10100000)
	return 4;
	else if(sw_input==0b11000000)
	return 7;

	PORTD=0x11110111;
	sw_input=PIND;
	sw_input&=0b11100000;
	if(sw_input==0b01100000)		//마스킹한 값이 7이면.
	return 2;
	else if(sw_input==0b10100000)
	return 5;
	else if(sw_input==0b11000000)
	return 8;

	PORTD=0x11101111;
	sw_input=PIND;
	sw_input&=0b11100000;
	if(sw_input==0b01100000)		//마스킹한 값이 7이면.
	return 3;
	else if(sw_input==0b10100000)
	return 6;
	else if(sw_input==0b11000000)
	return 9;
	}
}
