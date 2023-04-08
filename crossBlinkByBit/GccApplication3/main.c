/*
 * GccApplication3.c
 *
 * Created: 2022-04-09 오전 1:55:53
 * Author : LG
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRD = 0xFF;
    while (1) 
    {
		for(int i=0;i<8;i++)
		{	
			if(i!=4 && i!= 7){
			char patternA = 0x01 << i;
			char patternB = 0x80 >> i;
			PORTD = patternA | patternB;
			_delay_ms(500);
			}
		}
		
    }
}

