/*
 * hw1.c
 *
 * Created: 2022-03-26 오전 1:13:25
 * Author : LG
 */ 
 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0x01;
	DDRB = 0x04;
	DDRB = 0x20;
	
	while(1)
	{
		PORTB = 0x01;
		_delay_ms(500);
		PORTB = 0x04;
		_delay_ms(500);
		PORTB = 0x20;
		_delay_ms(500);
	}
	return 1;
}






