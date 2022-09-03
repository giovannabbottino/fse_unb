#ifndef LCD_16x2_DRIVER_H_
#define LCD_16x2_DRIVER_H_


#define LCD_LINE_1 0x80
#define LCD_LINE_2 0xC0


int lcd_init(void);
void lcd_set_line(int lcd_line);
void lcd_type_char(char val);
void lcd_type_int(int integer);
void lcd_type_float(float floating);
void lcd_type_line(const char *line);
void lcd_clear(void);

#endif 
