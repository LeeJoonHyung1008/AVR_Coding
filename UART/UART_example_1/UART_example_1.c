#include <avr/io.h>
#include <util/delay.h>
void IO_init();
void UART_init();		// UART 함수를 선언하였다.

void putch(char data1, char data2);		// data를 argument로 받는 putch 함수를 선언하였다.
char getch_1(void);		// getch_1 함수를 선언하였다.
char getch_2(void);		// getch_2 함수를 선언하였다.
void put_string(unsigned char *data);	// put_string 함수의 선언.
void putch_3dec(int data);		// put_3dec함수의 선언.

void IO_init()		// 입/출력 레지스터를 설정하는 함수이다.
{
	DDRA=0xFF;	// PORT A를 모두 출력으로 한다.
}
void UART_init()	// UART 레지스터를 설정하는 함수이다.
{
	UCSR1A=0x00;	// RXC, TXC, UDRE는 데이터가 없는 상태이므로 0으로 설정한다. 데이터가 없는 상태이므로 FE, DOR, UPE는 0, Double speed mode를 사용하지 않을 것이므로 0, multiprocessor mode를 사용하지 않을 것이므로 0으로 설정한다.
	UCSR1B=0x18;	// 인터럽트를 설정해주지 않을 것이므로 RXCIE, TXCIE, UDRIE를 0으로 설정해준다. 데이터 송/수신을 활성화 시켜야 하므로 RXEN, TXEN을 1로 설정한다. UCZ는 C 레지스터와 함게 사용할 것이므로 일단 0으로 설정한다. 그리고 RXB8와 TXB8은 8번 bit를 사용하지 않을 것이므로 0으로 설정한다.
	UCSR1C=0x06;	// 7번 bit는 없으므로 0이다. 비동기식 통신을 사용할 것이므로 UMSEL은 0으로 설정한다. UPM1과 UPM0은 parity mode를 사용하지 않을 것이므로 00으로 설정해준다. UBS는 stop bit를 1 bit크기로 설정해줄 것이므로 0으로 설정해준다. UCZ1과 UCZ0과 B 레지스터의 2번 bit를 통해 8bit의 크기로 설정할 것이기 때문에 011으로 설정해준다. UCPOL은 동기식 통신에서만 사용하기 때문에 0으로 설정한다. 
	UBRR1H=0x00;	
	UBRR1L=25;	// UBRR은 baud rate를 정해줄 때 사용하는 12 bit의 레지스터이다. H 레지스터는 0x00으로 모두 0의 값을 주고, L 레지스터에는 25의 값을 넣는다. 이때 baud rate를 구하는 수식은  이고 38461의 값이 나온다. 
}

void putch(char data1, char data2)	// putch 함수이다.
{
	while(!(UCSR1A&0x20));	// while(1)과 똑같은 말이다.(무조건 실행) UCSR1A의 5번 bit(UDRE)를 1과 &(AND) 연산 한다. UDRE는 UDRn송신 버퍼에 수신이 가능하면 Set된다. 즉 수신을 받는 과정이다.
	UDR1=x+y;	// 입력받은 데이터를 합해서 보내준다. (송신) 하지만 putch(temp+'0');를 사용했던 것처럼 'x' + 'y'로 작성해야하지 않을까? 라고 고민했지만 이는 x+y이다. putch() 함수는 argument를 char 형으로 받기 때문에 ‘0'으로 더해준 것이고 UDR1은 그냥 x+y를 넣어주면 된다. 
}

char getch_1(void)		// getch 함수이다.
{
	while(!(UCSR1A&0x80));	// while(1)과 똑같은 말이다. (무조건 실행) UCSR1A의 7번 bit(RXC)를 1과 &(AND) 연산 한다. RXC는 읽어 들이지 않은 데이터가 UDR에 저장되어있을 때 SET되고 INT모드에서는 INT를 발생시킨다. 즉 수신한 데이터를 송신하는 과정이다.
	return UDR1;	// 수신 받은 값을 return 한다.
}
char getch_2(void)		// getch 함수이다.
{
	while(!(UCSR1A&0x80));	// while(1)과 똑같은 말이다. (무조건 실행) UCSR1A의 7번 bit(RXC)를 1과 &(AND) 연산 한다. RXC는 읽어 들이지 않은 데이터가 UDR에 저장되어있을 때 SET되고 INT모드에서는 INT를 발생시킨다. 즉 수신한 데이터를 송신하는 과정이다.
	return UDR1;	// 수신 받은 값을 return 한다.
}

void put_string(unsigned char *data)	// put_string 함수이다.
{
	while(*data)	// data라는 주소에서 가져온 값 *data가 있으면
	{
		putch(*data++);		// data 값을 한 칸씩 읽으면서 문자열처럼 입력.
	}
}
void putch_3dec(int data)	// putch_3dec 함수이다.
{
	int temp, temp2;		// temp, temp2라는 변수를 선언.
	temp=data/100;		// temp는 수신 받은 데이터에서 100을 나눈 몫이다.
	temp2=data%100;	// temp2는 수신 받은 데이터에서 100을 나눈 나머지이다.
	putch(temp+'0');	// temp는 int형이고 putch함수는 char형태를 입력받는 함수이다. 그러므로 숫자 0을 더해주려면 ‘0’ 형태로 마치 char로 인식하여 더해 주어야한다. 그리고 그 temp값을 송신해준다.
	putch((temp2/10)+'0');		// temp2값에 10을 나눠주어 몫(10의 자리)을 putch함수에 넣어주어 그 temp2 값을 송신해준다.
	putch((temp2%10)+'0');		// temp2값의 10을 나눈 값의 나머지인 1의 자리 수 값((temp2%10)+'0')을 송신해준다.
}

void main()
{
	IO_init();	// 입/출력 레지스터 설정 함수를 불러온다.
	UART_init();	// UART 레지스터 설정 함수를 불러온다.
	while(1)
	{
		putch(getch_1(), getch_2());	// getch_1(), getch_2()함수를 통해 데이터를 수신하고 putch() 함수를 통해 수신 받은 데이터를 합해서 송신해준다.
	}
}
