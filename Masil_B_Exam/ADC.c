#include <avr/io.h>
#include "ADC.h"

void ADC_init()
{
	ADMUX=0x40;			// 0x40=0b01000000�� �����Ͽ� �ܺ� AVCC�� ������������ ����Ͽ���.(AVCC with external capacitor at AREF pin)
	ADCSRA=0x87;		// bit7 : ADc Enable, bit6 : 1�� �����Ͽ� ��ȯ����, bit5 : 0���� �����Ͽ� Free running mode�� ������� ����(single conversion mode), bit4 : 0, bit3 : ��ȯ�Ϸ� INT�� ���, bit2,1,0 : ���ֺ� 128���� ����. 
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
