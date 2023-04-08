/*
 * GccApplication2.c
 *
 * Created: 2022-04-05 오전 11:58:44
 * Author : LG
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;
	char patterns[] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
    while (1) 
	{
		for(int i=0;i<8;i++){
		if(i!=4 && i!=7){
		PORTD = patterns[i] | patterns[7-i];
		_delay_ms(500);}
		}
			
	} 		
	
	return 1;
}

