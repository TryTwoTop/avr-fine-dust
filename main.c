#include <avr/io.h>
#include <stdio.h>
#include "uart/uart.h"

int main (void)
{
    uart_init();
    printf("UART init\r\n");

    while (1)
    ;

    return 0;
}
