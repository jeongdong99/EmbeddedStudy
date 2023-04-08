/*
 * cntBtn.c
 *
 * Created: 2022-04-19 오전 11:29:53
 * Author : LG
 */ 
#define  F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
void INIT_PORT(void){
	//DDRB = 0x20;
	//PORTB = 0x00;
	
	DDRD = 0x00;
	PORTD = 0xF0;

}

int main(void)
{
    UART_INIT();
	INIT_PORT();
	
    while (1) {
	if( (PIND & 0x10)  == 0x10) {
	 UART_transmit('O');
	}
	else if ((PIND & 0x10) != 0x10){
		UART_transmit('X');
		}

	if((PIND & 0x20) == 0x20) {
		UART_transmit('O');
		}
	else if((PIND & 0x20) != 0x20) {
		UART_transmit('X');
	}
	
	if((PIND & 0x40) == 0x40 ) {
		UART_transmit('O');
		}
	else if((PIND & 0x40) != 0x40){
		UART_transmit('X');
	}
	
	if((PIND & 0x80) ==  0x80) {
		UART_transmit('O');
		}
	else if((PIND & 0x80) != 0x80){
		UART_transmit('X');
	}
	UART_transmit('\n');
	_delay_ms(1000);
	}
}
