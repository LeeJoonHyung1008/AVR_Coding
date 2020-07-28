//피아노를 keypad를 사용해서 출력할 것이다. 각 음계에 맞는 주파수를 PWM주파수 계산법을 이용해서 OCR값을 구해서 배열에 넣어준다. keypad를 누르면 각 음계에 맞는 배열값을 OCR값으로 보내준다. 
#include<avr/io.h>
#include<avr/interrupt.h>                            // 헤더파일의 선언

char array[10]={0,239,212,189,179,159,142,126,119,106 };    //각 음계에 맞는 주파수를 계산 법을 이용해서 구해준다. 여기서 나는 8분주비를 사용하였다.
void IO_init();                          //입출력함수의 선언
void TIMER_init();                     //타이머함수의 선언
int keypad();                           //키패드 함수의 선언
int data=0;                             //data라는 전역변수 선언 그 후 0으로 초기화
void delay_us(unsigned int time) 
{
   unsigned int ns_i;
   for(ns_i=0;ns_i<time;ns_i++)
   {
       asm("nop");
   }   
}
void delay_ms(unsigned int time)
{
   unsigned int ns_i;
   for(ns_i=0;ns_i<time;ns_i++)
   {
      delay_us(1000/14);
   }
}                                               //사용자 정의 delay 함수 

int keypad()                                   // 키패드 함수 정의
{
	int flag=0;                                     // flag라는 변수 선언 및 0으로 초기화

	PORTD=PORTD&0xFB;
	delay_ms(100);
	if((PIND&0x20)==0)flag=array[1];              
	if((PIND&0x40)==0)flag=array[4];
	if((PIND&0x80)==0)flag=array[7];
	PORTD|=~0xFB;

	PORTD=PORTD&0xF7;
	delay_ms(100);
	if((PIND&0x20)==0)flag=array[2];   
	if((PIND&0x40)==0)flag=array[5];    
	if((PIND&0x80)==0)flag=array[8];    
	PORTD|=~0xF7;

	PORTD=PORTD&0xEF;
	delay_ms(100);
	if((PIND&0x20)==0)flag=array[3];  
	if((PIND&0x40)==0)flag=array[6];  
	if((PIND&0x80)==0)flag=array[9];    
	PORTD|=~0xEF;

	return flag;
}                                                  //서보 모터 제어 코드와 내용은 같다. 대신 차이점이 있다면 서보모터는 스위치를 때도 초기상태로 돌아가면 안되지만 피아노는 스위치를 때도 다시 누를 수 있어야 하므로 flag값을 main문으로 보내지 않고 timer함수로 보내 OCR1A값과 ICR값을 직접 초기화 해준다.

void IO_init()                            //입출력 함수의 정의
{
   
   DDRB=0xff;                        // 부저를 사용할것이므로 PORTB 활성화(PORTB.5만 활성화 시켜줘도 무방하다.)
   DDRD=0x1C;                          // 키패드를 사용할것이므로 PORTD를 활성화해줌
}

void TIMER_init()                              // 타이머 함수의 정의
{              
	TCCR1A=0x82;                        // 10000010으로 fast PWM모드로 non_inverting 모드를 사용할 것 이므로 7번 6번 비트를 10으로 설정해주고 Fast PWM모드를 사용할것이므로 1,0번 비트를 10으로 설정해준다.
	TCCR1B=0x1B;                       // 00011011으로 fast PWM모드를 사용할것이므로 4,3번 비트를 11로 8분주비를 사용할것이므로 1번 0번 비트는 11로 설정해주었다.         
	TIMSK=0x0C;                      // 00001100으로 타이머 1번의 B핀의 output capture모드를 사용, 그리고 타이머 1번을 설정할것이므로 2번 비트를 1로 설정
	int data=0;  
	if(a == 1)
	{
	for(int i=0 ; i<9; i++)
	{                             //data라는 값을 선언해주고 0으로 초기화
		data=keypad();                           //data는 keypad함수의 리턴값을 받아옴
		ICR1=data*2;                             // duty cycle을 50%로 하기 위해서 OCR1A값의 2배를 취해줌
		OCR1A=data  ;                            // OCR1A값은 각 음계에 맞는 data값으로 초기화      
	   	sei();                             // 인터럽트 활성화!
	}
}

SIGNAL (SIG_OVERFLOW1)
{
	TCNT1=0;                                 // 오차를 최대한 줄이기 위해서 tcnt는 수시로 0으로 초기화 해준다.
}

int a = 0;

void main()
{

	IO_init();                                   //입출력함수 호출
	TIMER_init();                              //타이머 함수 호출
 
	while(1)
	{                          // 계속 키패드를 누를수있어야하므로 무한루프에 넣어줌

	}
}
