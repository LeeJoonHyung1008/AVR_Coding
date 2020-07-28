#include <avr/io.h>
#include <util/delay.h>
void IO_init();
void UART_init();		// UART �Լ��� �����Ͽ���.

void putch(char data1, char data2);		// data�� argument�� �޴� putch �Լ��� �����Ͽ���.
char getch_1(void);		// getch_1 �Լ��� �����Ͽ���.
char getch_2(void);		// getch_2 �Լ��� �����Ͽ���.
void put_string(unsigned char *data);	// put_string �Լ��� ����.
void putch_3dec(int data);		// put_3dec�Լ��� ����.

void IO_init()		// ��/��� �������͸� �����ϴ� �Լ��̴�.
{
	DDRA=0xFF;	// PORT A�� ��� ������� �Ѵ�.
}
void UART_init()	// UART �������͸� �����ϴ� �Լ��̴�.
{
	UCSR1A=0x00;	// RXC, TXC, UDRE�� �����Ͱ� ���� �����̹Ƿ� 0���� �����Ѵ�. �����Ͱ� ���� �����̹Ƿ� FE, DOR, UPE�� 0, Double speed mode�� ������� ���� ���̹Ƿ� 0, multiprocessor mode�� ������� ���� ���̹Ƿ� 0���� �����Ѵ�.
	UCSR1B=0x18;	// ���ͷ�Ʈ�� ���������� ���� ���̹Ƿ� RXCIE, TXCIE, UDRIE�� 0���� �������ش�. ������ ��/������ Ȱ��ȭ ���Ѿ� �ϹǷ� RXEN, TXEN�� 1�� �����Ѵ�. UCZ�� C �������Ϳ� �԰� ����� ���̹Ƿ� �ϴ� 0���� �����Ѵ�. �׸��� RXB8�� TXB8�� 8�� bit�� ������� ���� ���̹Ƿ� 0���� �����Ѵ�.
	UCSR1C=0x06;	// 7�� bit�� �����Ƿ� 0�̴�. �񵿱�� ����� ����� ���̹Ƿ� UMSEL�� 0���� �����Ѵ�. UPM1�� UPM0�� parity mode�� ������� ���� ���̹Ƿ� 00���� �������ش�. UBS�� stop bit�� 1 bitũ��� �������� ���̹Ƿ� 0���� �������ش�. UCZ1�� UCZ0�� B ���������� 2�� bit�� ���� 8bit�� ũ��� ������ ���̱� ������ 011���� �������ش�. UCPOL�� ����� ��ſ����� ����ϱ� ������ 0���� �����Ѵ�. 
	UBRR1H=0x00;	
	UBRR1L=25;	// UBRR�� baud rate�� ������ �� ����ϴ� 12 bit�� ���������̴�. H �������ʹ� 0x00���� ��� 0�� ���� �ְ�, L �������Ϳ��� 25�� ���� �ִ´�. �̶� baud rate�� ���ϴ� ������  �̰� 38461�� ���� ���´�. 
}

void putch(char data1, char data2)	// putch �Լ��̴�.
{
	while(!(UCSR1A&0x20));	// while(1)�� �Ȱ��� ���̴�.(������ ����) UCSR1A�� 5�� bit(UDRE)�� 1�� &(AND) ���� �Ѵ�. UDRE�� UDRn�۽� ���ۿ� ������ �����ϸ� Set�ȴ�. �� ������ �޴� �����̴�.
	UDR1=x+y;	// �Է¹��� �����͸� ���ؼ� �����ش�. (�۽�) ������ putch(temp+'0');�� ����ߴ� ��ó�� 'x' + 'y'�� �ۼ��ؾ����� ������? ��� ��������� �̴� x+y�̴�. putch() �Լ��� argument�� char ������ �ޱ� ������ ��0'���� ������ ���̰� UDR1�� �׳� x+y�� �־��ָ� �ȴ�. 
}

char getch_1(void)		// getch �Լ��̴�.
{
	while(!(UCSR1A&0x80));	// while(1)�� �Ȱ��� ���̴�. (������ ����) UCSR1A�� 7�� bit(RXC)�� 1�� &(AND) ���� �Ѵ�. RXC�� �о� ������ ���� �����Ͱ� UDR�� ����Ǿ����� �� SET�ǰ� INT��忡���� INT�� �߻���Ų��. �� ������ �����͸� �۽��ϴ� �����̴�.
	return UDR1;	// ���� ���� ���� return �Ѵ�.
}
char getch_2(void)		// getch �Լ��̴�.
{
	while(!(UCSR1A&0x80));	// while(1)�� �Ȱ��� ���̴�. (������ ����) UCSR1A�� 7�� bit(RXC)�� 1�� &(AND) ���� �Ѵ�. RXC�� �о� ������ ���� �����Ͱ� UDR�� ����Ǿ����� �� SET�ǰ� INT��忡���� INT�� �߻���Ų��. �� ������ �����͸� �۽��ϴ� �����̴�.
	return UDR1;	// ���� ���� ���� return �Ѵ�.
}

void put_string(unsigned char *data)	// put_string �Լ��̴�.
{
	while(*data)	// data��� �ּҿ��� ������ �� *data�� ������
	{
		putch(*data++);		// data ���� �� ĭ�� �����鼭 ���ڿ�ó�� �Է�.
	}
}
void putch_3dec(int data)	// putch_3dec �Լ��̴�.
{
	int temp, temp2;		// temp, temp2��� ������ ����.
	temp=data/100;		// temp�� ���� ���� �����Ϳ��� 100�� ���� ���̴�.
	temp2=data%100;	// temp2�� ���� ���� �����Ϳ��� 100�� ���� �������̴�.
	putch(temp+'0');	// temp�� int���̰� putch�Լ��� char���¸� �Է¹޴� �Լ��̴�. �׷��Ƿ� ���� 0�� �����ַ��� ��0�� ���·� ��ġ char�� �ν��Ͽ� ���� �־���Ѵ�. �׸��� �� temp���� �۽����ش�.
	putch((temp2/10)+'0');		// temp2���� 10�� �����־� ��(10�� �ڸ�)�� putch�Լ��� �־��־� �� temp2 ���� �۽����ش�.
	putch((temp2%10)+'0');		// temp2���� 10�� ���� ���� �������� 1�� �ڸ� �� ��((temp2%10)+'0')�� �۽����ش�.
}

void main()
{
	IO_init();	// ��/��� �������� ���� �Լ��� �ҷ��´�.
	UART_init();	// UART �������� ���� �Լ��� �ҷ��´�.
	while(1)
	{
		putch(getch_1(), getch_2());	// getch_1(), getch_2()�Լ��� ���� �����͸� �����ϰ� putch() �Լ��� ���� ���� ���� �����͸� ���ؼ� �۽����ش�.
	}
}
