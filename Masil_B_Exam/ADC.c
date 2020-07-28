#include <avr/io.h>
#include "ADC.h"

void ADC_init()
{
	ADMUX=0x40;			// 0x40=0b01000000로 설정하여 외부 AVCC를 기준전압으로 사용하였다.(AVCC with external capacitor at AREF pin)
	ADCSRA=0x87;		// bit7 : ADc Enable, bit6 : 1로 설정하여 변환시작, bit5 : 0으로 설정하여 Free running mode를 사용하지 않음(single conversion mode), bit4 : 0, bit3 : 변환완료 INT를 허용, bit2,1,0 : 분주비를 128으로 설정. 
}

unsigned int read_adc(unsigned char adc_input)
{
	unsigned int ANALOG_VALUE=0;
	ADMUX=adc_input|(0x40&0xFF);
	ADCSRA |= 0x40;
	while((ADCSRA&0x10)==0);
	ADCSRA |= 0x10;
	ANALOG_VALUE = ADCL+(ADCH<<8);
	return ANALOG_VALUE;
}
