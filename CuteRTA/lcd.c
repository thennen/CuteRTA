#include <avr/io.h>
#include "definitions.h"
#include <util/delay.h>
#include "lcd.h"

void lcd_enable_pulse() {
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(2);
	LCD_PORT &= ~(1 << LCD_EN);
}

void lcd_send_cmd(unsigned char cmd) {
	LCD_PORT &= LCD_ZERO;
	if ((cmd & 0x80) == 0x80) LCD_PORT |= (1 << LCD_DB7);
	if ((cmd & 0x40) == 0x40) LCD_PORT |= (1 << LCD_DB6);
	if ((cmd & 0x20) == 0x20) LCD_PORT |= (1 << LCD_DB5);
	if ((cmd & 0x10) == 0x10) LCD_PORT |= (1 << LCD_DB4);
	lcd_enable_pulse();

	LCD_PORT &= LCD_ZERO;
	if ((cmd & 0x08) == 0x08) LCD_PORT |= (1 << LCD_DB7);
	if ((cmd & 0x04) == 0x04) LCD_PORT |= (1 << LCD_DB6);
	if ((cmd & 0x02) == 0x02) LCD_PORT |= (1 << LCD_DB5);
	if ((cmd & 0x01) == 0x01) LCD_PORT |= (1 << LCD_DB4);
	lcd_enable_pulse();

	_delay_us(50);
}

void lcd_putch(unsigned char x) {
	LCD_PORT &= LCD_ZERO;
	LCD_PORT |= (1 << LCD_RS);
	if ((x & 0x80) == 0x80) LCD_PORT |= (1 << LCD_DB7);
	if ((x & 0x40) == 0x40) LCD_PORT |= (1 << LCD_DB6);
	if ((x & 0x20) == 0x20) LCD_PORT |= (1 << LCD_DB5);
	if ((x & 0x10) == 0x10) LCD_PORT |= (1 << LCD_DB4);
	lcd_enable_pulse();

	LCD_PORT &= LCD_ZERO;
	LCD_PORT |= (1 << LCD_RS);
	if ((x & 0x08) == 0x08) LCD_PORT |= (1 << LCD_DB7);
	if ((x & 0x04) == 0x04) LCD_PORT |= (1 << LCD_DB6);
	if ((x & 0x02) == 0x02) LCD_PORT |= (1 << LCD_DB5);
	if ((x & 0x01) == 0x01) LCD_PORT |= (1 << LCD_DB4);
	lcd_enable_pulse();

	_delay_us(50);
}

void lcd_clear() {
	lcd_send_cmd(LCD_CLEAR_DISPLAY);
	_delay_ms(10);
}

void lcd_cursor_home() {
	lcd_send_cmd(LCD_CURSOR_HOME);
	_delay_ms(10);
}

void lcd_putstr(char *str) {
	while(*str) {
		lcd_putch(*str);
		str++;
	}
}

void lcd_move_cursor(unsigned char x, unsigned char y) {
  unsigned char tmp=0;

  if ((y<1) | (y>4)) return;
  if ((x<1) | (x>20)) return;
 
  switch (y) {
    case 1: tmp=0x80+0x00+x-1; break;    // 1. line
    case 2: tmp=0x80+0x40+x-1; break;    // 2. line
    case 3: tmp=0x80+0x14+x-1; break;    // 3. line
    case 4: tmp=0x80+0x54+x-1; break;    // 4. line
  }
  lcd_send_cmd(tmp);
  return;
}

void lcd_init() {
	LCD_DDR |= LCD_OUTPUT;
	LCD_PORT &= LCD_ZERO;

	// Send Initialization impulse 3 times.
	_delay_ms(20);
	LCD_PORT |= ((1 << LCD_DB4) | (1 << LCD_DB5));
	lcd_enable_pulse();
	_delay_ms(10);
	lcd_enable_pulse();
	_delay_ms(5);
	lcd_enable_pulse();

	LCD_PORT &= LCD_ZERO;
	LCD_PORT |= (1 << LCD_DB5);		// Activate 4bit mode
	lcd_enable_pulse();
	_delay_ms(5);

	lcd_send_cmd(0x28);				// 4bit, 2 lines, 5x7
	lcd_send_cmd(0x0C);				// Display on, cursor off, blinking off
	lcd_send_cmd(0x06);				// Move direction, scrolling off 
	lcd_clear();
}
