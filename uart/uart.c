#include <avr/io.h>
#include "uart.h"

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
    uart_transmit('\n');
}
