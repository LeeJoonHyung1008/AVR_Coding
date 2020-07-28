#include<avr/io.h>              // 메인함수의 선언
#include "delay.h"          // 시간 지연함수를 선언

int keypad()                    // keypad를 입력받는 함수를 선언과 정의 
{
int flag=0;                     // keypad를 아무것도 누르지 않았을 때 0을 출력
PORTD=PORTD&0xFB;         		// PORTD를 11111011로 마스킹 이것은 sw(3,6,9)를 활성화시키기위해서 2번비트를 마스킹해주었다.
delay_us(10);                  // 시간을 지연시켜줌
if((PIND&0x20)==0)flag=1;       // PORTD와 0b00100000와 &(AND) 마스킹해준다. sw3은 5번비트와 연결되어있기 때문에  sw6,9 인 6,7번비트는 1, 그리고 sw3은 0이여야 하므로 마스킹할 때 0이 나와야한다.
if((PIND&0x40)==0)flag=4;       // PORTD와 0b01000000와 &(AND) 마스킹해준다. sw6은 6번비트와 연결되어있기 때문에  sw3,9 인 5,7번비트는 1, 그리고 sw6은 0이여야 하므로 마스킹할 때 0이 나와야한다.
if((PIND&0x80)==0)flag=7;       // PORTD와 0b10000000와 &(AND) 마스킹해준다. sw9은 7번비트와 연결되어있기 때문에  sw3,6 인 5,6번비트는 1, 그리고 sw9은 0이여야 하므로 마스킹할 때 0이 나와야한다.
PORTD|=~0xFB;                	// 스위치를 땟을 때 다른 스위치를 누르기위해서 초기로 |(OR) 마스킹해준다.

PORTD=PORTD&0xF7;          		// PORTD를 11110111로 마스킹 이것은 sw(4,7,10)를 활성화시키기위해서 3번비트를 마스킹해주었다.
delay_us(10);                  // 시간을 지연시켜줌
if((PIND&0x20)==0)flag=2;       // PORTD와 0b00100000와 &(AND) 마스킹해준다. sw4은 5번비트와 연결되어있기 때문에  sw7,10 인 6,7번비트는 1, 그리고 sw4은 0이여야 하므로 마스킹할 때 0이 나와야한다.
if((PIND&0x40)==0)flag=5;       // PORTD와 0b01000000와 &(AND) 마스킹해준다. sw7은 6번비트와 연결되어있기 때문에  sw4,10 인 5,7번비트는 1, 그리고 sw7은 0이여야 하므로 마스킹할 때 0이 나와야한다.
if((PIND&0x80)==0)flag=8;       // PORTD와 0b10000000와 &(AND) 마스킹해준다. sw10은 7번비트와 연결되어있기 때문에  sw4,7 인 5,6번비트는 1, 그리고 sw10은 0이여야 하므로 마스킹할 때 0이 나와야한다.
PORTD|=~0xF7;                  	// 스위치를 땟을 때 다른 스위치를 누르기위해서 초기로 |(OR) 마스킹해준다.

PORTD=PORTD&0xEF;         		// PORTD를 11101111로 마스킹 이것은 sw(5,8,11)를 활성화시키기위해서 4번비트를 마스킹해주었다.
delay_us(10);                  // 시간을 지연시켜줌
if((PIND&0x20)==0)flag=3;       // PORTD와 0b00100000와 &마스킹해준다. sw5은 5번비트와 연결되어있기 때문에  sw8,11 인 6,7번비트는 1, 그리고 sw5은 0이여야 하므로 마스킹할 때 0이 나와야한다.
if((PIND&0x40)==0)flag=6;       // PORTD와 0b01000000와 &마스킹해준다. sw8은 6번비트와 연결되어있기 때문에  sw5,11 인 5,7번비트는 1, 그리고 sw8은 0이여야 하므로 마스킹할 때 0이 나와야한다.
if((PIND&0x80)==0)flag=9;      	// PORTD와 0b10000000와 &마스킹해준다. sw11은 7번비트와 연결되어있기 때문에  sw5,8 인 5,6번비트는 1, 그리고 sw11은 0이여야 하므로 마스킹할 때 0이 나와야한다.
PORTD|=~0xEF;               	// 스위치를 땟을 때 다른 스위치를 누르기위해서 초기로 |(OR) 마스킹해준다.

return flag;                    // flag값을 출력
}

void main()                     //메인함수의 선언
{
   char array[10]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8, 0x80, 0x98};  // 차례로 세그먼트에서 0~9까지일 때 활성화되는 2진수를 16진수로 변환시켜준 것이다. 0xC0은 0b11000000인데 이는 세그먼트에서 ‘.’이랑 g번 포트만 빼고 전부 켠 것이다. 그러면 세그먼트에는 0이 출력된다.
   int data=0;               	//data라는 변수를 선언, 그리고 0으로 초기화시켜준다. 
   while(1)                  	//무한루프문 진입
   {
      DDRD=0x1C;          		// PORTD는 2,3,4번 비트는 출력, 나머지 비트는 입력으로 방향을 설정
      DDRC=0xFF;            	// PORTA는 모든비트에서 출력을 설정
      data=keypad();          	// data는 keypad함수의 return값을 받음
      PORTC=array[data];     	// PORTA는 배열의 data값으로 출력
   }
} 
