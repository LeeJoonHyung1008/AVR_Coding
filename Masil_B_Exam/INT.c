#include "INT.h"
#include <avr/interrupt.h>

void INT_init()
{
	EICRA=0x0A;	// 0x0A=0b00001010 이므로 0번, 1번 인터럽트를 falling edge로 사용하겠다는 뜻이다.
	EICRB=0x00;	// 아무런 인터럽트를 사용하지 않으므로 모두 0으로 설정한다.
	EIMSK=0x03;	// 현재 0번, 1번 인터럽트를 사용할 것이므로 0x01=0b00000011로 설정하여 0번 인터럽트를 활성화 시켜준다.
	asm("SEI");	// 모든 인터럽트를 허용한다. (SREG의 7번 비트를 1로 만들어주는 어셈블리어)
}
