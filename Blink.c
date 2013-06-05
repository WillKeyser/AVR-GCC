/* Will Keyser
 * 2013
 */

 #define F_CPU 8000000L  		//Operating Frequency

 #include <avr/io.h>			//Libraries
 #include <avr/delay.h>

 int main(void)					//Main Loop
 	{
		DDRB = 0x01;			//Set PBO as an output
		PORTB = 0;				//Turn all of PortB off

		while(1)
		{
			PORTB = 0x01;		//Switch PB0 HIGH
			_delay_ms(500);		//Wait
			PORTB = 0x00;		//Switch PB0 LOW
			_delay_ms(500);		//Wait
		}
		
		return 0;				//Never Reached
	}
