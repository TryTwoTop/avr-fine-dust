#ifndef __I2C_H__
#define __I2C_H__

#include <avr/io.h>

typedef enum
{
    I2C_WRITE_MODE,
    I2C_READ_MODE
} i2c_mode_t;

void i2c_init (void);
void i2c_start (uint8_t, i2c_mode_t);
void i2c_stop (void);
void i2c_repeated_start (uint8_t, i2c_mode_t);
void i2c_write (uint8_t);
uint8_t i2c_read_and_send_ack (void);
uint8_t i2c_read_and_send_nack (void);

#endif //__I2C_H__
