#ifndef __UART_H__
#define __UART_H__

void uart_init (void);
void uart_transmit (unsigned char);
void uart_print (char *);
void uart_println (char *);
uint8_t uart_is_received (void);
uint8_t uart_get_received_data (void);

#endif //__UART_H__
