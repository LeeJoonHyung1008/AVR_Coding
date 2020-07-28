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
void LED_ON(unsigned char pin)  // LED�� on ���ִ� �Լ��̴�.
{
//   pint = -pin;   // �Է¹��� pin�� ���� �����ش�.
//   PORTA = PORTA & pin;  // �� ���� &(AND)�� masking ���ش�.
   PORTA &= (~pin);  // �Է¹��� pin�� ���� �����ش�. �׸��� �� ���� &(AND)�� masking ���ش�.
}
void LED_OFF(unsigned char pin)
{
   PORTA |= (pin); // �Է¹��� pin ���� |(OR) �������ش�.
}

void IO_init()
{
   PORTA=0xFF;  // PORT A�� 0xFF ���� �־��־� ��� LED�� OFF ���ش�.
   DDRA=0xFF;   // PORT A�� ��� bit�� ������� �����Ѵ�.
   PORTC=0xFF;  // PORT C�� 0xFF ���� �־��־� ��� LED�� OFF ���ش�.
   DDRC=0xFF;  // PORT C�� ��� bit�� ������� �����Ѵ�.
   DDRD=0x1C;  // PORT D�� 2,3,4 bit�� ������� �����Ѵ�. ������ bit�� �Է��̴�.
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
      if(SW(1)==0)    // Switch 1���� ������
      {
      left(); // LED 1,2,3,4�� ���ݴϴ�.
      }
      else if(SW(2)==0) // Switch 2���� ������
      {
      right();   // LED 5,6,7,8�� ���ݴϴ�.
      } 
      else
      {                 // �� ��� ��찡 �ƴ϶�� ��� LED�� OFF �մϴ�.
      LED_OFF(0xFF);
      }
   }
}

 
