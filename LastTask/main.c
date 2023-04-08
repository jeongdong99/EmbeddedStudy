/*
 * Task5.c
 *
 * Created: 2022-06-12 오후 9:04:45
 * Author : LG
 */ 
#include "TEXT_LCD.h"
#include <avr/interrupt.h>
#define ROTATION_DELAY 4000
#define PULSE_MIN 1300
#define PULSE_MAX 4700
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#define OPEN 0
#define CLOSE 1
#define PRESCALER 1024

uint8_t MODE = 4;
volatile int state = CLOSE;

void Timer_init(void){
	TCCR0B |= (1<< CS02) | (1 << CS00);
}

uint8_t measure_distance(void){
	PORTC |= (1<< PC0);
	_delay_us(10);
	PORTC &= ~(1 << PC0);
	
	TCNT0 = 0;
	while(!(PINC & 0x02))
	if(TCNT0 > 250) return 255;
	
	TCNT0 = 0;
	while(PINC & 0x02){
		if(TCNT0 > 250) {
			TCNT0 = 0;
			break;
		}
	}
	double pulse_width = TCNT0 * PRESCALER * 1000000.0 / F_CPU;
	
	return pulse_width / 58;
}


void INIT_TIMER1(void){
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	
	TCCR1B |= (1 << CS11);
	
	ICR1 = 40000;
	
	TCCR1A |= (1 << COM1A1);
	
	DDRB |= (1 << PB1);
}

ISR(PCINT2_vect)
{
	
	LCD_init();
	if(PIND & 0x04) {
	LCD_clear();
	LCD_write_string("Initializing...");
	_delay_ms(1000);	
	}
	
	
	else{ 
	state = OPEN;
	INIT_TIMER1();
	
	LCD_clear();
	LCD_write_string("Click!!");
	_delay_ms(1000);
	
	LCD_clear();
	LCD_write_string("Welcome!!!");
	OCR1A = PULSE_MAX;
	_delay_ms(ROTATION_DELAY);
	
	state = CLOSE;
	LCD_clear();
	LCD_write_string("Bye!!!");
	OCR1A = PULSE_MIN;
	_delay_ms(ROTATION_DELAY);

	}
}

void INIT_PORT(void){
	LCD_init();
	LCD_write_string("Initializing...");
	_delay_ms(2000);
	DDRD = 0x00;
	PORTD = 0x04;
}
void RESTART(void){
	state = CLOSE;
	LCD_init();
	LCD_write_string("Wait...");
	_delay_ms(1000);
}


void INIT_PCINT2 (void){
	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1<< PCINT18); //인터럽트 설정 다른거 알고있기
	sei();
}

int main(void)
{
	
	/* Replace with your application code */
	INIT_PORT();
	INIT_PCINT2();
	
	 uint8_t distance;
	 DDRC |= 0x01;
	 DDRC &= 0xFD;
	 Timer_init();
	
	while (1) {
		RESTART();
		_delay_ms(1000);
		
		distance = measure_distance();
		
		if(state == CLOSE && 5<=distance && distance <= 15 ){
			state = OPEN;
			INIT_TIMER1();
			LCD_clear();
			LCD_write_string("too close");
			_delay_ms(1000);
			LCD_clear();
			LCD_write_string("Welcome!!!");
			OCR1A = PULSE_MAX;
			_delay_ms(ROTATION_DELAY);
			
			state = CLOSE;
			LCD_clear();
			LCD_write_string("Bye!!!");
			OCR1A = PULSE_MIN;
			_delay_ms(ROTATION_DELAY);
		}
		
		
	}
	
}
