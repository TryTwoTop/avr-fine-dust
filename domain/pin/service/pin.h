#ifndef __PIN_SERVICE_PIN_H__
#define __PIN_SERVICE_PIN_H__

#include "../../gpio/service/gpio.h"

/* Value Object */
typedef struct
{
    gpio_port_t gpio_port;
    uint8_t gpio_pin;
} pin_t;

void pin_init (void);
void pin_set (pin_t *, gpio_port_t, uint8_t);

#endif //__PIN_SERVICE_PIN_H__
