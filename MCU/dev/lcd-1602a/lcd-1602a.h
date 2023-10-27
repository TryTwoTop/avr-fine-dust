#ifndef __LCD_1602A_H__
#define __LCD_1602A_H__

#include "../../domain/pin/service/pin.h"

#define LCD_HW_INTERFACE_DATA_LENGTH    8

typedef struct
{
    pin_t rs;
    pin_t rw;
    pin_t e;

    pin_t db[LCD_HW_INTERFACE_DATA_LENGTH];
} lcd_pin_t;

void lcd_init (lcd_pin_t *);
void lcd_clear (void);
void lcd_write_data (uint8_t);
void lcd_print_str (char *);
void lcd_print_int (int);
void lcd_new_line (void);

#endif // __LCD_1602A_H__
