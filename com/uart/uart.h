#ifndef __UART_H__
#define __UART_H__

void uart_init (void);
void uart_transmit (unsigned char);
void uart_print (char *);
void uart_println (char *);

#endif //__UART_H__
