#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "com/uart/uart.h"
#include "dev/pm2008m/pm2008m.h"
#include "dev/lcd-1602a/lcd-1602a.h"
#include "domain/gpio/service/gpio.h"

int main (void)
{
    pm2008m_data_t dust_data;

    uart_init();
    printf("UART init\r\n");

    pm2008m_init();
    printf("PM2008M init\r\n");

    lcd_init();
    lcd_print_str("LCD-1602A init");
    printf("LCD-1602A init\r\n");
    printf("\r\n");

    _delay_ms(1000);

    while (1)
    {
        dust_data = pm2008m_read();

        lcd_clear();
        lcd_print_str("Fine dust: ");
        lcd_print_int(dust_data.pm_10_grimm);

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
