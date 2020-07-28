#include <avr/io.h>
#include "delay.h"

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
}
