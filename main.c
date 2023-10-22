#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "com/uart/uart.h"
#include "dev/pm2008m/pm2008m.h"
#include "dev/lcd-1602a/lcd-1602a.h"
#include "domain/gpio/service/gpio.h"

static void mcu_lcd_init (void)
{
    lcd_pin_t lcd_pin;

    pin_init();

    pin_set(&lcd_pin.rs, GPIOD, GPIO_PIN_3);
    pin_set(&lcd_pin.rw, GPIOD, GPIO_PIN_4);
    pin_set(&lcd_pin.e,  GPIOD, GPIO_PIN_5);

    pin_set(&lcd_pin.db[0], GPIOD, GPIO_PIN_6);
    pin_set(&lcd_pin.db[1], GPIOD, GPIO_PIN_7);
    pin_set(&lcd_pin.db[2], GPIOB, GPIO_PIN_0);
    pin_set(&lcd_pin.db[3], GPIOB, GPIO_PIN_1);
    pin_set(&lcd_pin.db[4], GPIOB, GPIO_PIN_2);
    pin_set(&lcd_pin.db[5], GPIOB, GPIO_PIN_3);
    pin_set(&lcd_pin.db[6], GPIOB, GPIO_PIN_4);
    pin_set(&lcd_pin.db[7], GPIOB, GPIO_PIN_5);

    lcd_init(&lcd_pin);
}

int main (void)
{
    pm2008m_data_t dust_data;

    uart_init();
    printf("UART init\r\n");

    pm2008m_init();
    printf("PM2008M init\r\n");

    mcu_lcd_init();
    lcd_print_str("LCD-1602A init");
    printf("LCD-1602A init\r\n");
    printf("\r\n");

    _delay_ms(1000);

    while (1)
    {
        dust_data = pm2008m_read();

        lcd_clear();
        // LCD first line
        lcd_print_str("Sensor dust: ");
        lcd_print_int(dust_data.pm_10_grimm);

        // LCD second line
        lcd_new_line();
        lcd_print_str("API dust: ");

        if (uart_is_received())
        {
            uint8_t api_pm10_value = uart_get_received_data();
            lcd_print_int(api_pm10_value);
        }
        else
        {
            lcd_print_str("no");
        }

        printf("Sensor status: %d\r\n", dust_data.status);
        printf("measuring mode: %d\r\n", dust_data.measuring_mode);
        printf("Calibration coefficient: %d\r\n", dust_data.calib_coefficient);
        printf("\r\n");

        printf("PM-1.0 (GRIMM): %d\r\n", dust_data.pm_1p0_grimm);
        printf("PM-2.5 (GRIMM): %d\r\n", dust_data.pm_2p5_grimm);
        printf("PM-10  (GRIMM): %d\r\n", dust_data.pm_10_grimm);
        printf("PM-1.0   (TSI): %d\r\n", dust_data.pm_1p0_tsi);
        printf("PM-2.5   (TSI): %d\r\n", dust_data.pm_2p5_tsi);
        printf("PM-10    (TSI): %d\r\n", dust_data.pm_10_tsi);
        printf("\r\n");

        printf("Number of  0.3 um: %d\r\n", dust_data.num_of_0p3_um);
        printf("Number of  0.5 um: %d\r\n", dust_data.num_of_0p5_um);
        printf("Number of  1.0 um: %d\r\n", dust_data.num_of_1p0_um);
        printf("Number of  2.5 um: %d\r\n", dust_data.num_of_2p5_um);
        printf("Number of  5.0 um: %d\r\n", dust_data.num_of_5p0_um);
        printf("Number of 10.0 um: %d\r\n", dust_data.num_of_10p0_um);
        printf("\r\n");

        _delay_ms(1000);
    }

    return 0;
}
