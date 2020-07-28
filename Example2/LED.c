#include <avr/io.h>
#include "LED.h"

void IO_init()
{
	PORTA=0xFF;
	DDRA=0xFF;
	PORTC=0xFF;
	DDRC=0xFF;
	DDRD=0x1C;
}
