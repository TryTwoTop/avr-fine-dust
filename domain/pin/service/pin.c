#include "pin.h"

void pin_init (void)
{
    gpio_port_init();
}

void pin_set (pin_t *pin, gpio_port_t gpio_port, uint8_t gpio_pin)
{
    pin->gpio_port = gpio_port;
    pin->gpio_pin = gpio_pin;
}
