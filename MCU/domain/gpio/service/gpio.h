#ifndef __GPIO_SERVICE_GPIO_H__
#define __GPIO_SERVICE_GPIO_H__

#include "../repository/gpio_port/port.h"
#include "../repository/gpio_pin/pin.h"

typedef enum
{
    GPIO_PIN_RESET = 0,
    GPIO_PIN_SET
} gpio_pin_state_t;

extern void gpio_init (void);
extern void gpio_set_pin_mode (gpio_port_t, uint8_t, gpio_pin_mode_t);
/* Exam params: (GPIOD, GPIO_PIN_2, GPIO_PIN_MODE_OUTPUT) */

extern void gpio_write_pin (gpio_port_t, uint8_t, gpio_pin_state_t);
/* Exam params: (GPIOD, GPIO_PIN_2, GPIO_PIN_SET) */

#endif //__GPIO_SERVICE_GPIO_H__
