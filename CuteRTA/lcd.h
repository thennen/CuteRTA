
#define LCD_PORT PORTD
#define LCD_DB4
#define LCD_DB3
#define LCD_DB2
#define LCD_DB4

#define LCD_OUTPUT ((1 << LCD_DB4) | (1 << LCD_DB5) | (1 << LCD_DB6) | (1 << LCD_DB7) | (1 << LCD_RS) | (1 << LCD_EN))
#define LCD_ZERO ~((1 << LCD_DB4) | (1 << LCD_DB5) | (1 << LCD_DB6) | (1 << LCD_DB7) | (1 << LCD_RS) | (1 << LCD_EN))

void lcd_init();
void lcd_send_cmd(unsigned char cmd);
void lcd_enable_pulse();
void lcd_clear();
void lcd_putch(unsigned char x);
void lcd_cursor_home();
void lcd_move_cursor(unsigned char x, unsigned char y);
void lcd_putstr(char *str);
