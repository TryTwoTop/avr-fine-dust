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

#define PORT_D_DATA_PIN_MASK    0x3f
#define PORT_B_DATA_PIN_MASK    0xc0

#define START_DISPLAY_SECOND_LINE_ADDRESS   0x40

#define DIGITS_OF_INT           5

#define BINARY_NUM      2
#define DECIMAL_NUM     10

static void __lcd_e_generate_impulse (void)
{
    // PIN_E HIGH
    PORTD |= (1 << PORTD5);
    _delay_ms(1);

    // PIN_E LOW
    PORTD &= ~(1 << PORTD5);
    _delay_ms(1);
}

static void __load_data_or_instruction (uint8_t data)
{
    PORTD = PORTD & PORT_D_DATA_PIN_MASK;
    PORTD |= data << 6;

    PORTB = PORTB & PORT_B_DATA_PIN_MASK;
    PORTB |= data >> 2;
}

static void __lcd_write_instruction (uint8_t instruction)
{
    // PIN_RS LOW
    PORTD &= ~(1 << PORTD3);

    __load_data_or_instruction(instruction);

    __lcd_e_generate_impulse();
}

void lcd_new_line (void)
{
    uint8_t instruction = SET_DDRAM_ADDRESS | START_DISPLAY_SECOND_LINE_ADDRESS;

    __lcd_write_instruction(instruction);
}

void lcd_init (void)
{
    _delay_ms(5);

    // init Control pin
    DDRD |= (1 << DDD5) | (1 << DDD4) | (1 << DDD3);

    // init Data pin
    DDRD |= (1 << DDD7) | (1 << DDD6);

    DDRB |= (1 << DDB5) | (1 << DDB4) | (1 << DDB3) |
            (1 << DDB2) | (1 << DDB1) | (1 << DDB0);

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
    PORTD |= (1 << PORTD3);

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
