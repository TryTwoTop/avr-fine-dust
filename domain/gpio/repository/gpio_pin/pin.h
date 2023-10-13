#ifndef __GPIO_REPOSITORY_GPIO_PIN_PIN_H__
#define __GPIO_REPOSITORY_GPIO_PIN_PIN_H__

#define GPIO_PIN_0      ((uint8_t)0x01)
#define GPIO_PIN_1      ((uint8_t)0x02)
#define GPIO_PIN_2      ((uint8_t)0x04)
#define GPIO_PIN_3      ((uint8_t)0x08)
#define GPIO_PIN_4      ((uint8_t)0x10)
#define GPIO_PIN_5      ((uint8_t)0x20)
#define GPIO_PIN_6      ((uint8_t)0x40)
#define GPIO_PIN_7      ((uint8_t)0x80)

typedef enum
{
    GPIO_PIN_MODE_INUPT = 0,
    GPIO_PIN_MODE_OUTPUT
} gpio_pin_mode_t;

#endif //__GPIO_REPOSITORY_GPIO_PIN_PIN_H__
