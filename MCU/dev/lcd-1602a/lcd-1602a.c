#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd-1602a.h"

/* LCD Instruction */
#define FUNC_8BIT_2LINE_5M8DOTS     0x38
#define CLEAR_DISPLAY               0x01
#define SET_DISPLAY_NO_CURSOR       0x0c
#define ENTRY_MODE_SET_RIGHT_SHIFT  0x06
#define SET_DDRAM_ADDRESS           0x80

/* Execute time (ms) */
#define EXECUTION_TIME_TO_CLEAR_DISPLAY  2

#define START_DISPLAY_SECOND_LINE_ADDRESS   0x40

#define DIGITS_OF_INT   5

#define BINARY_NUM      2
#define DECIMAL_NUM     10

static lcd_pin_t _lcd_pin;

static void __lcd_e_generate_impulse (void)
{
    // PIN_E HIGH
    pin_write(&_lcd_pin.e, HIGH);
    _delay_ms(1);

    // PIN_E LOW
    pin_write(&_lcd_pin.e, LOW);
    _delay_ms(1);
}

static void __load_data_or_instruction (uint8_t data)
{
    int i;

    for (i = 0; i < LCD_HW_INTERFACE_DATA_LENGTH; i++)
    {
        uint8_t bit = 1 << i;
        pin_write(&_lcd_pin.db[i], (data & bit) ? HIGH : LOW);
    }
}

static void __lcd_write_instruction (uint8_t instruction)
{
    // PIN_RS LOW
    pin_write(&_lcd_pin.rs, LOW);

    __load_data_or_instruction(instruction);

    __lcd_e_generate_impulse();
}

void lcd_new_line (void)
{
    uint8_t instruction = SET_DDRAM_ADDRESS | START_DISPLAY_SECOND_LINE_ADDRESS;

    __lcd_write_instruction(instruction);
}

void lcd_init (lcd_pin_t *lcd_pin)
{
    int i;

    _delay_ms(5);

    pin_init();

    _lcd_pin = *lcd_pin;

    // LCD Control Pin mode init
    pin_set_mode(&_lcd_pin.rs, OUTPUT);
    pin_set_mode(&_lcd_pin.rw, OUTPUT);
    pin_set_mode(&_lcd_pin.e, OUTPUT);

    // LCD Control Pin level init
    pin_write(&_lcd_pin.rs, LOW);
    pin_write(&_lcd_pin.rw, LOW);
    pin_write(&_lcd_pin.e, LOW);

    // LCD Data Pin mode & level init
    for (i = 0; i < LCD_HW_INTERFACE_DATA_LENGTH; i++)
    {
        pin_set_mode(&_lcd_pin.db[i], OUTPUT);
        pin_write(&_lcd_pin.db[i], LOW);
    }

    __lcd_write_instruction(FUNC_8BIT_2LINE_5M8DOTS);

    __lcd_write_instruction(SET_DISPLAY_NO_CURSOR);

    lcd_clear();

    __lcd_write_instruction(ENTRY_MODE_SET_RIGHT_SHIFT);
}

void lcd_clear (void)
{
    __lcd_write_instruction(CLEAR_DISPLAY);
    _delay_ms(EXECUTION_TIME_TO_CLEAR_DISPLAY);
}

void lcd_write_data (uint8_t data)
{
    // PIN_RS HIGH
    pin_write(&_lcd_pin.rs, HIGH);

    __load_data_or_instruction(data);

    __lcd_e_generate_impulse();
}

void lcd_print_str (char *str)
{
    while (*str)
    {
        lcd_write_data(*str);
        str++;
    }
}

void lcd_print_int (int num)
{
    char str[DIGITS_OF_INT + 1];

    itoa(num, str, DECIMAL_NUM);

    lcd_print_str(str);
}
