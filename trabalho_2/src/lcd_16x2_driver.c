/*
*
* by Lewis Loflin www.bristolwatch.com lewis@bvu.net
* http://www.bristolwatch.com/rpi/i2clcd.htm
* Using wiringPi by Gordon Henderson
*
*/

#include "lcd_16x2_driver.h"
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>


#define LCD_I2C_ADDRESS 0x27
#define LCD_BACKLIGHT   0x08  // On - 0x08 | Off - 0x00
#define LCD_CHR 1       // Mode - Sending data
#define LCD_CMD 0       // Mode - Sending command
#define ENABLE 0x04     //0b00000100 // Enable bit



static int file_descriptor;


static void lcd_toggle_enable(int bits){
    // Toggle enable pin on LCD display
    delayMicroseconds(500);
    wiringPiI2CReadReg8(file_descriptor, (bits | ENABLE));
    delayMicroseconds(500);
    wiringPiI2CReadReg8(file_descriptor, (bits & ~ENABLE));
    delayMicroseconds(500);
}

static void lcd_byte(int bits, int mode){
    //Send byte to data pins
    // bits = the data
    // mode = 1 for data, 0 for command
    int bits_high;
    int bits_low;
    // uses the two half byte writes to LCD
    bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT ;
    bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT ;

    // High bits
    wiringPiI2CReadReg8(file_descriptor, bits_high);
    lcd_toggle_enable(bits_high);
    
    // Low bits
    wiringPiI2CReadReg8(file_descriptor, bits_low);
    lcd_toggle_enable(bits_low);
}

int lcd_init(void){

    if (wiringPiSetup() == -1) return -1;
    file_descriptor = wiringPiI2CSetup(LCD_I2C_ADDRESS);

    // Initialise display
    lcd_byte(0x33, LCD_CMD); // Initialise
    lcd_byte(0x32, LCD_CMD); // Initialise
    lcd_byte(0x06, LCD_CMD); // Cursor move direction
    lcd_byte(0x0C, LCD_CMD); // 0x0F On, Blink Off
    lcd_byte(0x28, LCD_CMD); // Data length, number of lines, font size
    lcd_byte(0x01, LCD_CMD); // Clear display
    delayMicroseconds(500);
    
    return 0;
}

void lcd_type_char(char val){
    lcd_byte(val, LCD_CHR);
}

void lcd_type_line(const char *line){
    while (*line) lcd_byte(*(line++), LCD_CHR);
}

void lcd_type_int(int integer)   {
    char array1[20];
    sprintf(array1, "%d", integer);
    lcd_type_line(array1);
}

void lcd_type_float(float floating){
    char buffer[20];
    sprintf(buffer, "%2.1f",  floating);
    lcd_type_line(buffer);
}

void lcd_set_line(int lcd_line){
    lcd_byte(lcd_line, LCD_CMD);
}

void lcd_clear(void){
    lcd_byte(0x01, LCD_CMD);
    lcd_byte(0x02, LCD_CMD);
}
