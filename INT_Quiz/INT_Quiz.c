#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PORT	PORTA		// LED_PORT를 PORT A로 설정한다.
#define REF_TCNT_MAX 0		 // REF_TCNT_MAX를 0이라고 정의
#define REF_TCNT_DEF 1                // REF_TCNT_DEF을 1이라고 정의
#define REF_TCNT_MIN 2                // REF_TCNT_MIN을 2이라고 정의

void delay_us(unsigned int time); // delay_ms 함수를 위한 함수이다.
void delay_ms(unsigned int time); // delay 해주는 함수이다.
void IO_init();	// 각 포트의 레지스터 입/출력을 결정한다.
void INT_init();	// 각 Interrupt 레지스터를 결정한다.

int on_flag = 0;
int sign_flag = 0;
int i=500;
unsigned char count_for_INT0=0;	// count_for_INT0 이라는 전역변수를 0으로 초기화
unsigned char ref_tcnt,ref_tcnt_limit[3]={30,15,1};

void delay_us(unsigned int time){		// delay_us함수의 내용
	unsigned int ns_i;
	for(ns_i=0;ns_i<time;ns_i++){
		asm("nop");	// 한 클럭을 쉰다.
	}
}

void delay_ms(unsigned int time){		// delay_ms함수의 내용
	unsigned int ns_i;
	for(ns_i=0;ns_i<time;ns_i++){
	delay_us(1000/14);	// delay_us함수에 1000/14를 넣어준다. 이는 원래 1000을 넣어줘야 하지만 코드가 진행되는 시간에 약간 오차가 있어서 14를 나눠주는 것이다.. 
	}
}

void IO_init()
{
	DDRA=0xFF;	// PORT A의 모든 bit를 출력으로 설정한다. 여기서 DDRD = 0x1C;를 해주지 않는 이유는 INT 신호를 받기위해 INT로 입력을 받을 것이기 때문이다. I/O로써 받는 것이 아니므로 SW1 에 대한 PORTD 의 입출력 설정은 하지 않는다.
}
void INT_init()
{
	EICRA=0x02;	// 0x0A=0b00000010 이므로 0번 인터럽트를 falling edge로 사용하겠다는 뜻이다.
	EICRB=0x00;	// 아무런 인터럽트를 사용하지 않으므로 모두 0으로 설정한다.
	EIMSK=0x01;	// 현재 0번 인터럽트를 사용할 것이므로 0x03=0b00000001로 설정하여 0번 인터럽트를 활성화 시켜준다.
	asm("SEI");	// 모든 인터럽트를 허용한다. (SREG의 7번 비트를 1로 만들어주는 어셈블리어)
}

SIGNAL(SIG_INTERRUPT0)	// 0번 인터럽트에 관한 내용이다. (함수의 이름과 Handle은 이미 정의되어 있으므로 정의된 이름으로 사용한다.) (1번 스위치이다.)
{
	if(EICRA == 0x02)
	{
		EICRA = 0x03;
		on_flag = 1;
		if(sign_flag == 0)
		{
			sign_flag = 1;

		}
		else if(sign_flag==1)
		{
			sign_flag = 0;
		}
	}
	else if(EICRA == 0x03)
	{
		EICRA = 0x02;
		on_flag = 0;
	}
}

void main()
{
	IO_init();		
	INT_init();	// IO_init()과 INT_init()을 선언해준다. 원래의 코딩에서는 빠져있지만 우리가 사용할 PORT/Interrupt Register들을 설정해주어야 한다. 이를 main 함수 밖에서 사용자 정의 함수를 만들고 선언을 해줘도 main 함수 내에서 호출을 하지 않으면 결국 소용이 없는 것이다.
	while(1)
	{
		
			PORTA=0x00;
			delay_us(1000-i);
			PORTA=0xFF;
			delay_us(i);
		if(on_flag ==1)
		{
			if(sign_flag ==1)
			{
				i++;
				if(i>1000)
				{	i=1000;	}

			}
			else if(sign_flag==0)
			{
				i--;
				if(i<1)
				{	i=1;	}
			}	
		}
	}
}
