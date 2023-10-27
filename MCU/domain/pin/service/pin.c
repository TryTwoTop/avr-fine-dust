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

void pin_set_mode (pin_t *pin, uint8_t pin_mode)
{
    gpio_set_pin_mode(pin->gpio_port, pin->gpio_pin, pin_mode);
}

void pin_write (pin_t *pin, uint8_t pin_level)
{
    gpio_write_pin(pin->gpio_port, pin->gpio_pin, pin_level);
}
