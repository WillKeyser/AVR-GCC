/*  Will Keyser
 *  2013
 *	ATMEGA328P at 8MHz
 *	HD44780 LCD String! 
 */

#include <avr/io.h>		//libraries
#include <avr/delay.h> 

#define F_CPU 8000000L 	//8MHz

#define LCD				PORTD
#define DirLCD			DDRD
#define Control			PORTB
#define DirControl		DDRB
#define Enable			1
#define ReadWrite		2
#define RS				3

void Check_State(void);
void Peek_A_Boo(void);
void Send_Command(unsigned char command);
void Send_Character(unsigned char character);
void Send_String(char *StringChar);

int main(void)
{
	DirControl |= 1<<Enable | 1<<ReadWrite | 1<<RS;		//Set PinMode (output)
	_delay_ms(15);
	
	Send_Command(0x01);  								//Clear Screen
	_delay_ms(3);
	Send_Command(0x38);									//Set to 8-bit mode
	_delay_us(60);
	Send_Command(0b00001110);							//Turn display on
	_delay_us(60);										//0b00001111 would blink the cursor
	
	Send_String("Hello World");							//Our Message Goes Here
	
	
	while(1)
	{

	}
}

void Check_State()
{
	DirLCD = 0x00; 		//0b00000000
	Control |= 1<<ReadWrite;
	Control &= ~1<<RS;	
	
	while(LCD >= 0x80)    		//if PORTB >= 0b10000000 then it's busy
	{
		Peek_A_Boo();
	}
	
	
	DirLCD = 0xFF;		//0b11111111
}

void Peek_A_Boo()
{
	Control |= 1<<Enable;
	asm volatile ("nop");
	asm volatile ("nop");
	Control &= ~1<<Enable;
}

void Send_Command(unsigned char command)
{
	Check_State();
	LCD = command;
	Control &= ~ (1<<ReadWrite|1<<RS);
	Peek_A_Boo();
	LCD = 0;
}

void Send_Character(unsigned char character)
{
	Check_State();
	LCD = character;
	Control &= ~ (1<<ReadWrite);
	Control |= 1<<RS;
	Peek_A_Boo();
	LCD = 0;
}

void Send_String(char *StringChar)
{
	while(*StringChar > 0)
	{
		Send_Character(*StringChar++);
		_delay_ms(5);
	}
}
