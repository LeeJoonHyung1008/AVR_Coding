//�ǾƳ븦 keypad�� ����ؼ� ����� ���̴�. �� ���迡 �´� ���ļ��� PWM���ļ� ������ �̿��ؼ� OCR���� ���ؼ� �迭�� �־��ش�. keypad�� ������ �� ���迡 �´� �迭���� OCR������ �����ش�. 
#include<avr/io.h>
#include<avr/interrupt.h>                            // ��������� ����

char array[10]={0,239,212,189,179,159,142,126,119,106 };    //�� ���迡 �´� ���ļ��� ��� ���� �̿��ؼ� �����ش�. ���⼭ ���� 8���ֺ� ����Ͽ���.
void IO_init();                          //������Լ��� ����
void TIMER_init();                     //Ÿ�̸��Լ��� ����
int keypad();                           //Ű�е� �Լ��� ����
int data=0;                             //data��� �������� ���� �� �� 0���� �ʱ�ȭ
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
}                                               //����� ���� delay �Լ� 

int keypad()                                   // Ű�е� �Լ� ����
{
	int flag=0;                                     // flag��� ���� ���� �� 0���� �ʱ�ȭ

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
}                                                  //���� ���� ���� �ڵ�� ������ ����. ��� �������� �ִٸ� �������ʹ� ����ġ�� ���� �ʱ���·� ���ư��� �ȵ����� �ǾƳ�� ����ġ�� ���� �ٽ� ���� �� �־�� �ϹǷ� flag���� main������ ������ �ʰ� timer�Լ��� ���� OCR1A���� ICR���� ���� �ʱ�ȭ ���ش�.

void IO_init()                            //����� �Լ��� ����
{
   
   DDRB=0xff;                        // ������ ����Ұ��̹Ƿ� PORTB Ȱ��ȭ(PORTB.5�� Ȱ��ȭ �����൵ �����ϴ�.)
   DDRD=0x1C;                          // Ű�е带 ����Ұ��̹Ƿ� PORTD�� Ȱ��ȭ����
}

void TIMER_init()                              // Ÿ�̸� �Լ��� ����
{              
	TCCR1A=0x82;                        // 10000010���� fast PWM���� non_inverting ��带 ����� �� �̹Ƿ� 7�� 6�� ��Ʈ�� 10���� �������ְ� Fast PWM��带 ����Ұ��̹Ƿ� 1,0�� ��Ʈ�� 10���� �������ش�.
	TCCR1B=0x1B;                       // 00011011���� fast PWM��带 ����Ұ��̹Ƿ� 4,3�� ��Ʈ�� 11�� 8���ֺ� ����Ұ��̹Ƿ� 1�� 0�� ��Ʈ�� 11�� �������־���.         
	TIMSK=0x0C;                      // 00001100���� Ÿ�̸� 1���� B���� output capture��带 ���, �׸��� Ÿ�̸� 1���� �����Ұ��̹Ƿ� 2�� ��Ʈ�� 1�� ����
	int data=0;  
	if(a == 1)
	{
	for(int i=0 ; i<9; i++)
	{                             //data��� ���� �������ְ� 0���� �ʱ�ȭ
		data=keypad();                           //data�� keypad�Լ��� ���ϰ��� �޾ƿ�
		ICR1=data*2;                             // duty cycle�� 50%�� �ϱ� ���ؼ� OCR1A���� 2�踦 ������
		OCR1A=data  ;                            // OCR1A���� �� ���迡 �´� data������ �ʱ�ȭ      
	   	sei();                             // ���ͷ�Ʈ Ȱ��ȭ!
	}
}

SIGNAL (SIG_OVERFLOW1)
{
	TCNT1=0;                                 // ������ �ִ��� ���̱� ���ؼ� tcnt�� ���÷� 0���� �ʱ�ȭ ���ش�.
}

int a = 0;

void main()
{

	IO_init();                                   //������Լ� ȣ��
	TIMER_init();                              //Ÿ�̸� �Լ� ȣ��
 
	while(1)
	{                          // ��� Ű�е带 �������־���ϹǷ� ���ѷ����� �־���

	}
}
