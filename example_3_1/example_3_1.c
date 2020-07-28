#include <avr/io.h>	// avr의 기본 header file이다.
#include <avr/interrupt.h>	// interrupt를 사용하기 위한 header file이다.
#include "LED.h"		// 사용자 정의 header file이다.
#include "delay2.h"	// 사용자 정의 header file이다.

#define LED_PORT PORTA	// LED_PORT를 PORT A로 설정한다.

unsigned char count_for_INT0=0;
unsigned char display_for_INT0=0;
void INT_init();	// 각 Interrupt 레지스터를 결정한다.

void INT_init()
{
	EICRA=0x0A;	// 0x0A=0b00001010 이므로 0번, 1번 인터럽트를 falling edge로 사용하겠다는 뜻이다.
	EICRB=0x00;	// 아무런 인터럽트를 사용하지 않으므로 모두 0으로 설정한다.
	EIMSK=0x03;	// 현재 0번, 1번의 인터럽트를 사용할 것이므로 0x01=0b0000011로 설정하여 0번 1번 인터럽트를 활성화 시켜준다.
	asm("SEI");	// 모든 인터럽트를 허용한다. (SREG의 7번 비트를 1로 만들어주는 어셈블리어)
}

SIGNAL(SIG_INTERRUPT0)	// 0번 인터럽트(1번 스위치)에 관한 내용이다. (함수의 이름과 Handle은 이미 정의되어 있으므로 정의된 이름으로 사용한다.) (1번 스위치이다.)
{	// Falling edge를 사용할 것이다.
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
	EICRA=0x02;			// 인터럽트신호를 다시 falling edge에서 발생하도록 설정한다. --> 스위치를 누름과 동시에 발생
	SEG_ON_two_numbers_all_in_one(display_for_INT0);
	count_for_INT0=0;
	}
	else{LED_PORT=0xFF;}

}

SIGNAL(SIG_INTERRUPT1)
{
SEG_ON_two_numbers_all_in_one(0);
}

void main()                                // main문의 내용
{
   unsigned char i;
	IO_init();		
	INT_init();	
	SEG_ON_two_numbers_all_in_one(0);
	while(1)
	{
	for(i=0;i<8;i++){
			LED_PORT =~(0x01<<i);	// 0x01에서 I만큼 << shifting 해주어 1을 왼쪽으로 1 bit씩 밀어낸다. 그리고 이 값을 반전 해주어서 결국엔 한 개의 LED씩 순차적으로 ON 해주는 코딩이다.
			delay_ms(1500);	// 1500ms 만큼 delay 해준다. 
		}
	}
}
