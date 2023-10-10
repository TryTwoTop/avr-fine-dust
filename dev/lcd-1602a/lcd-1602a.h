#ifndef __LCD_1602A_H__
#define __LCD_1602A_H__

/*
    LCD Interface Pin - Digital Pin - ATmega328P Pin

    RS  -  3 - PD3
    R/W -  4 - PD4
    E   -  5 - PD5

    DB0 -  6 - PD6
    DB1 -  7 - PD7
    DB2 -  8 - PB0
    DB3 -  9 - PB1
    DB4 - 10 - PB2
    DB5 - 11 - PB3
    DB6 - 12 - PB4
    DB7 - 13 - PB5
*/

void lcd_init (void);
void lcd_clear (void);
void lcd_write_data (uint8_t);
void lcd_print_str (char *);
void lcd_print_int (int);

#endif // __LCD_1602A_H__
