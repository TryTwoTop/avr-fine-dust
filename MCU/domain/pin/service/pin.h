#ifndef __PIN_SERVICE_PIN_H__
#define __PIN_SERVICE_PIN_H__

#include "../../gpio/service/gpio.h"

/* PIN MODE */
#define INPUT   GPIO_PIN_MODE_INUPT
#define OUTPUT  GPIO_PIN_MODE_OUTPUT

/* PIN LEVEL */
#define HIGH    GPIO_PIN_SET
#define LOW     GPIO_PIN_RESET

/* Value Object */
typedef struct
{
    gpio_port_t gpio_port;
    uint8_t gpio_pin;
} pin_t;

/*
    Example

    pin_t led;
    pin_init();
    pin_set(&led, GPIOD, GPIO_PIN_2);
    pin_set_mode(&led, OUTPUT);
    pin_write(&led, HIGH);
*/

void pin_init (void);
void pin_set (pin_t *, gpio_port_t, uint8_t);
void pin_set_mode (pin_t *, uint8_t);
void pin_write (pin_t *, uint8_t);

#endif //__PIN_SERVICE_PIN_H__
