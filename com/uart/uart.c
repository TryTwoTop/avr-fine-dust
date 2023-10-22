#include <avr/io.h>
#include <stdio.h>
#include "uart.h"

int __uart_putchar (char, FILE *);

static FILE _my_stdout = FDEV_SETUP_STREAM(__uart_putchar, NULL, _FDEV_SETUP_WRITE);

static void __printf_init (void)
{
    stdout = &_my_stdout;
}

void uart_init (void)
{
    // double uart transmission speed
    UCSR0A |= _BV(U2X0);

    // enable receiver and transmitter
    UCSR0B |= _BV(RXEN0) | _BV(TXEN0);

    // async, no parity, 1 stop bit, 8 data bit
    UCSR0C = 0x06;

    // 9600 baud rate
    UBRR0H = (uint8_t)0;
    UBRR0L = (uint8_t)207;

    // for printf
    __printf_init();
}

void uart_transmit (unsigned char data)
{
    while ((UCSR0A & (1 << UDRE0)) == 0)
    ;

    UDR0 = data;
}

void uart_print (char *str)
{
    while (*str)
    {
        uart_transmit(*str++);
    }
}

void uart_println (char *str)
{
    uart_print(str);
    uart_print("\r\n");
}

uint8_t uart_is_received (void)
{
    uint8_t result = ( UCSR0A & (1 << RXC0) ) ;

    return result;
}

uint8_t uart_get_received_data (void)
{
    return UDR0;
}

int __uart_putchar (char ch, FILE *stream)
{
    uart_transmit(ch);

    return 0;
}
