#include "port.h"

void gpio_port_init (void)
{
    GPIOB.direction_register_address    =   (uint8_t *)&DDRB;
    GPIOB.output_register_address       =   (uint8_t *)&PORTB;

    GPIOC.direction_register_address    =   (uint8_t *)&DDRC;
    GPIOC.output_register_address       =   (uint8_t *)&PORTC;

    GPIOD.direction_register_address    =   (uint8_t *)&DDRD;
    GPIOD.output_register_address       =   (uint8_t *)&PORTD;
}
