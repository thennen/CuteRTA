/*
 * CuteRTA.c
 *
 * Created: 2017-11-08 5:37:04 PM
 * Author : hennen
 */ 

//#define F_CPU 8000000UL
#include <avr/io.h>
#include "hd44780.h"
//#include "lcd.h"
//#include "Adafruit_NeoPixel/Adafruit_NeoPixel.h"
#include "light_ws2812_AVR/Light_WS2812/light_ws2812.h"
#include <util/delay.h>
#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>

struct cRGB led[1];

char buffer[4];

int T[95] = {292, 293, 295, 292, 292, 292, 291, 293, 293, 293, 293, 292, 291, 292, 292, 293, 341, 395, 446, 495, 546, 596, 645, 699, 747, 797, 849, 897, 949, 1000, 999, 1000, 998, 999, 997, 999, 999, 1000, 999, 998, 999, 1001, 1000, 1000, 1000, 997, 1000, 999, 1000, 999, 1000, 998, 1000, 999, 1001, 1000, 998, 999, 999, 999, 1002, 820, 686, 585, 510, 454, 415, 385, 360, 342, 328, 319, 315, 308, 305, 302, 298, 299, 296, 297, 295, 294, 294, 293, 292, 292, 294, 294, 293, 294, 293, 292, 292, 294, 291};
int colors[95][3] = {{10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {55, 0, 0}, {107, 0, 0}, {154, 0, 0}, {202, 0, 0}, {249, 0, 0}, {255, 41, 0}, {255, 89, 0}, {255, 141, 0}, {255, 186, 0}, {255, 233, 0}, {255, 255, 42}, {255, 255, 109}, {255, 255, 184}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 2}, {255, 128, 0}, {255, 31, 0}, {215, 0, 0}, {162, 0, 0}, {126, 0, 0}, {97, 0, 0}, {73, 0, 0}, {57, 0, 0}, {42, 0, 0}, {34, 0, 0}, {31, 0, 0}, {23, 0, 0}, {21, 0, 0}, {18, 0, 0}, {15, 0, 0}, {15, 0, 0}, {13, 0, 0}, {13, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}, {10, 0, 0}};

int main(void)
{
	DDRC = 0b11111111;
	DDRB = 0b11111111;
	DDRD = 0b11111111;
	
	int i;
	
	lcd_init();
	lcd_clrscr();
	//lcd_puts("Hello Wo");
	//lcd_goto(0x40);
	//lcd_puts("rld!");
	//lcd_command(_BV(LCD_DISPLAYMODE) | _BV(LCD_DISPLAYMODE_ON));
    while (1) 
    {
		/*
		PORTB = 0b11111111;
		_delay_ms(1000);
		PORTB = 0b00000000;
		_delay_ms(1000);
		*/	
		
		for(i=0;i<95;i++)
		{
			led[0].r = colors[i][1];
			led[0].g = colors[i][0];
			led[0].b = colors[i][2];
			ws2812_setleds(led,1);
			lcd_clrscr();
			itoa(T[i],buffer,10);
			lcd_puts(buffer);
			//lcd_goto(0x40);
			//lcd_puts("rld!");
			_delay_ms(700);
		}
		/*
		led[0].r=255;led[0].g=00;led[0].b=0;    // Write red to array
		ws2812_setleds(led,1);
		_delay_ms(1000);                         // wait for 500ms.

		led[0].r=0;led[0].g=255;led[0].b=0;			// green
		ws2812_setleds(led,1);
		_delay_ms(1000);

		led[0].r=0;led[0].g=00;led[0].b=255;		// blue
		ws2812_setleds(led,1);
		_delay_ms(1000);
		*/
		
    }
}

