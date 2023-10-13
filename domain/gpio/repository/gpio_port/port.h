#ifndef __GPIO_REPOSITORY_GPIO_PORT_PORT_H__
#define __GPIO_REPOSITORY_GPIO_PORT_PORT_H__

#include <avr/io.h>

/* Value Object */
typedef struct
{
    uint8_t *direction_register_address;
    uint8_t *output_register_address;
} gpio_port_t;

void gpio_port_init (void);

gpio_port_t GPIOB;
gpio_port_t GPIOC;
gpio_port_t GPIOD;

#endif //__GPIO_REPOSITORY_GPIO_PORT_PORT_H__
