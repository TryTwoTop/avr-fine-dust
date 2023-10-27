#include "../service/gpio.h"

void gpio_init (void)
{
    gpio_port_init();
}

void gpio_set_pin_mode (gpio_port_t gpio_port, uint8_t gpio_pin, gpio_pin_mode_t pin_mode)
{
    if (pin_mode != GPIO_PIN_MODE_INUPT)
    {
        *(gpio_port.direction_register_address) |= gpio_pin;
    }
    else
    {
        *(gpio_port.direction_register_address) &= ~gpio_pin;
    }
}

void gpio_write_pin (gpio_port_t gpio_port, uint8_t gpio_pin, gpio_pin_state_t gpio_pin_state)
{
    if (gpio_pin_state != GPIO_PIN_RESET)
    {
        *(gpio_port.output_register_address) |= gpio_pin;
    }
    else
    {
        *(gpio_port.output_register_address) &= ~gpio_pin;
    }
}
