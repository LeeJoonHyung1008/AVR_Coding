#include <avr/io.h>
#include <avr/delay.h>

typedef unsigned char byte;
char led, i;
char initial_LED = 2;      

void delay_200m()
{
	byte k;
	for(k=0; k<20; k++)
	{
		_delay_ms(200);
	}
}
void LED_ON(unsigned char pin)  // LED를 on 해주는 함수이다.
{
//   pint = -pin;   // 입력받은 pin을 반전 시켜준다.
//   PORTA = PORTA & pin;  // 이 값을 &(AND)로 masking 해준다.
   PORTA &= (~pin);  // 입력받은 pin을 반전 시켜준다. 그리고 이 값을 &(AND)로 masking 해준다.
}
void LED_OFF(unsigned char pin)
{
   PORTA |= (pin); // 입력받은 pin 값과 |(OR) 연산해준다.
}

void IO_init()
{
   PORTA=0xFF;  // PORT A에 0xFF 값을 넣어주어 모든 LED를 OFF 해준다.
   DDRA=0xFF;   // PORT A의 모든 bit를 출력으로 설정한다.
   PORTC=0xFF;  // PORT C에 0xFF 값을 넣어주어 모든 LED를 OFF 해준다.
   DDRC=0xFF;  // PORT C의 모든 bit를 출력으로 설정한다.
   DDRD=0x1C;  // PORT D의 2,3,4 bit를 출력으로 설정한다. 나머지 bit는 입력이다.
}
unsigned char SW(unsigned char pin)
{
   unsigned char sw_input;  
   sw_input = PIND; 
   sw_input &= pin; 
   return sw_input;
}

void left()
{
    led &= (~initial_LED);
	PORTA = led;
    led = (led >> 1) | 0x80;
}


void right()
{
    led &= (~initial_LED);
    PORTA = led;
    led = (led << 1);
}

void blink()
{
	PORTA = 0x00;
	delay_200m();
	PORTA = 0xFF;
	delay_200m();
}

void main(void)
{               
IO_init();
LED_ON(initial_LED);
while(1)
   {
      if(SW(1)==0)    // Switch 1번을 누르면
      {
      left(); // LED 1,2,3,4를 켜줍니다.
      }
      else if(SW(2)==0) // Switch 2번을 누르면
      {
      right();   // LED 5,6,7,8을 켜줍니다.
      } 
      else
      {                 // 이 모든 경우가 아니라면 모든 LED를 OFF 합니다.
      LED_OFF(0xFF);
      }
   }
}

 
