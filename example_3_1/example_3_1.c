#include <avr/io.h>	// avr�� �⺻ header file�̴�.
#include <avr/interrupt.h>	// interrupt�� ����ϱ� ���� header file�̴�.
#include "LED.h"		// ����� ���� header file�̴�.
#include "delay2.h"	// ����� ���� header file�̴�.

#define LED_PORT PORTA	// LED_PORT�� PORT A�� �����Ѵ�.

unsigned char count_for_INT0=0;
unsigned char display_for_INT0=0;
void INT_init();	// �� Interrupt �������͸� �����Ѵ�.

void INT_init()
{
	EICRA=0x0A;	// 0x0A=0b00001010 �̹Ƿ� 0��, 1�� ���ͷ�Ʈ�� falling edge�� ����ϰڴٴ� ���̴�.
	EICRB=0x00;	// �ƹ��� ���ͷ�Ʈ�� ������� �����Ƿ� ��� 0���� �����Ѵ�.
	EIMSK=0x03;	// ���� 0��, 1���� ���ͷ�Ʈ�� ����� ���̹Ƿ� 0x01=0b0000011�� �����Ͽ� 0�� 1�� ���ͷ�Ʈ�� Ȱ��ȭ �����ش�.
	asm("SEI");	// ��� ���ͷ�Ʈ�� ����Ѵ�. (SREG�� 7�� ��Ʈ�� 1�� ������ִ� �������)
}

SIGNAL(SIG_INTERRUPT0)	// 0�� ���ͷ�Ʈ(1�� ����ġ)�� ���� �����̴�. (�Լ��� �̸��� Handle�� �̹� ���ǵǾ� �����Ƿ� ���ǵ� �̸����� ����Ѵ�.) (1�� ����ġ�̴�.)
{	// Falling edge�� ����� ���̴�.
	if(EICRA==0x0A)
{
while(EICRA==0x0A)
{
SEG_ON_two_numbers_all_in_one(display_for_INT0);
	delay_ms(1000);
	display_for_INT0++;
	delay_ms(1000);
if(display_for_INT0>=100)
{display_for_INT0=0;}
EICRA=0x0B;
}
}
	else if(EICRA==0x0B)
	{			
	EICRA=0x02;			// ���ͷ�Ʈ��ȣ�� �ٽ� falling edge���� �߻��ϵ��� �����Ѵ�. --> ����ġ�� ������ ���ÿ� �߻�
	SEG_ON_two_numbers_all_in_one(display_for_INT0);
	count_for_INT0=0;
	}
	else{LED_PORT=0xFF;}

}

SIGNAL(SIG_INTERRUPT1)
{
SEG_ON_two_numbers_all_in_one(0);
}

void main()                                // main���� ����
{
   unsigned char i;
	IO_init();		
	INT_init();	
	SEG_ON_two_numbers_all_in_one(0);
	while(1)
	{
	for(i=0;i<8;i++){
			LED_PORT =~(0x01<<i);	// 0x01���� I��ŭ << shifting ���־� 1�� �������� 1 bit�� �о��. �׸��� �� ���� ���� ���־ �ᱹ�� �� ���� LED�� ���������� ON ���ִ� �ڵ��̴�.
			delay_ms(1500);	// 1500ms ��ŭ delay ���ش�. 
		}
	}
}
