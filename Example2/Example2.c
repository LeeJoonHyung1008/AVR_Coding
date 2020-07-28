#include <avr/io.h>
#include "LED.h"
#include "delay.h"

void main()
{
	IO_init();
	unsigned char sw_input,sw_flag,sw_i;
	unsigned char out_status, out_flag;
	out_flag=0;
	out_status=0;

	while(1){
		LED_PORT=(1<<out_status);
		sw_flag=1;
		for(sw_i=0;sw_i<100;sw_i++)
		{
			sw_input=PIND;
			sw_input&=0x03;
			if(sw_input==1)
			{
				out_flag=1;
			}
			else if(sw_input==2)
			{
				out_flag=0;
			}
			delay_ms(1);
		}
		if(out_flag)
		{
			if(out_status==0)
			{
				out_status=7;
			}
			else
			{
				out_status--;
			}
		}
		else
		{
			out_status++;
			if(out_status>7)
			out_status=0;
		}
	}
}

