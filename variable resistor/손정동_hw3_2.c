/*
 * controlLed.c
 *
 * Created: 2022-04-26 오전 11:34:21
 * Author : LG
 */ 
#define F_CPU 16000000L
#include <avr/io.h>

void ADC_INIT(unsigned char channel){
	ADMUX |= 0x40;
	
	ADCSRA |= 0x07;
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADATE);
	
	ADMUX |= ((ADMUX & 0xE0) | channel);
	ADCSRA |= (1<<ADSC);
}

void PORT_INIT(void){
	DDRD=0xFF;
}

int read_ADC(void){
	while (! (ADCSRA & (1 << ADIF)));
	
	return ADC;
}

int main(void)
{
    int value;
	uint8_t on_off;
	
	ADC_INIT(0);
	PORT_INIT();
	
    while (1) 
    {
		value = read_ADC() >> 7;
		
		on_off = 0;
		/*for(int i =0; i <= value;i++){
			on_off |= (0x01 << i);
		}*/
		on_off = 0x01 << value;
		PORTD = on_off;
    }
}

