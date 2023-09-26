#include <avr/io.h>
#include "uart/uart.h"

int main (void)
{
    uart_init();
    uart_println("UART init");

    while (1)
    ;

    return 0;
}
