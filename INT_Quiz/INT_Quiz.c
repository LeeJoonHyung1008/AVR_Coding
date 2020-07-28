#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PORT	PORTA		// LED_PORT�� PORT A�� �����Ѵ�.
#define REF_TCNT_MAX 0		 // REF_TCNT_MAX�� 0�̶�� ����
#define REF_TCNT_DEF 1                // REF_TCNT_DEF�� 1�̶�� ����
#define REF_TCNT_MIN 2                // REF_TCNT_MIN�� 2�̶�� ����

void delay_us(unsigned int time); // delay_ms �Լ��� ���� �Լ��̴�.
void delay_ms(unsigned int time); // delay ���ִ� �Լ��̴�.
void IO_init();	// �� ��Ʈ�� �������� ��/����� �����Ѵ�.
void INT_init();	// �� Interrupt �������͸� �����Ѵ�.

int on_flag = 0;
int sign_flag = 0;
int i=500;
unsigned char count_for_INT0=0;	// count_for_INT0 �̶�� ���������� 0���� �ʱ�ȭ
unsigned char ref_tcnt,ref_tcnt_limit[3]={30,15,1};

void delay_us(unsigned int time){		// delay_us�Լ��� ����
	unsigned int ns_i;
	for(ns_i=0;ns_i<time;ns_i++){
		asm("nop");	// �� Ŭ���� ����.
	}
}

void delay_ms(unsigned int time){		// delay_ms�Լ��� ����
	unsigned int ns_i;
	for(ns_i=0;ns_i<time;ns_i++){
	delay_us(1000/14);	// delay_us�Լ��� 1000/14�� �־��ش�. �̴� ���� 1000�� �־���� ������ �ڵ尡 ����Ǵ� �ð��� �ణ ������ �־ 14�� �����ִ� ���̴�.. 
	}
}

void IO_init()
{
	DDRA=0xFF;	// PORT A�� ��� bit�� ������� �����Ѵ�. ���⼭ DDRD = 0x1C;�� ������ �ʴ� ������ INT ��ȣ�� �ޱ����� INT�� �Է��� ���� ���̱� �����̴�. I/O�ν� �޴� ���� �ƴϹǷ� SW1 �� ���� PORTD �� ����� ������ ���� �ʴ´�.
}
void INT_init()
{
	EICRA=0x02;	// 0x0A=0b00000010 �̹Ƿ� 0�� ���ͷ�Ʈ�� falling edge�� ����ϰڴٴ� ���̴�.
	EICRB=0x00;	// �ƹ��� ���ͷ�Ʈ�� ������� �����Ƿ� ��� 0���� �����Ѵ�.
	EIMSK=0x01;	// ���� 0�� ���ͷ�Ʈ�� ����� ���̹Ƿ� 0x03=0b00000001�� �����Ͽ� 0�� ���ͷ�Ʈ�� Ȱ��ȭ �����ش�.
	asm("SEI");	// ��� ���ͷ�Ʈ�� ����Ѵ�. (SREG�� 7�� ��Ʈ�� 1�� ������ִ� �������)
}

SIGNAL(SIG_INTERRUPT0)	// 0�� ���ͷ�Ʈ�� ���� �����̴�. (�Լ��� �̸��� Handle�� �̹� ���ǵǾ� �����Ƿ� ���ǵ� �̸����� ����Ѵ�.) (1�� ����ġ�̴�.)
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
	INT_init();	// IO_init()�� INT_init()�� �������ش�. ������ �ڵ������� ���������� �츮�� ����� PORT/Interrupt Register���� �������־�� �Ѵ�. �̸� main �Լ� �ۿ��� ����� ���� �Լ��� ����� ������ ���൵ main �Լ� ������ ȣ���� ���� ������ �ᱹ �ҿ��� ���� ���̴�.
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
