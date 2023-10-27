#include <stdio.h>
#include <avr/io.h>
#include "i2c.h"

/* Status Code */
#define TWI_START           0x08
#define TWI_REPEATED_START  0x10

/* Master Transmitter Mode */
#define TWI_MT_SLA_ACK      0x18
#define TWI_MT_SLA_NACK     0x20
#define TWI_MT_DATA_ACK     0x28
#define TWI_MT_DATA_NACK    0x30
#define TWI_MT_ARB_LOST     0x38

/* Master Receiver Mode */
#define TWI_MR_ARB_LOST     0x38
#define TWI_MR_SLA_ACK      0x40
#define TWI_MR_SLA_NACK     0x48
#define TWI_MR_DATA_ACK     0x50
#define TWI_MR_DATA_NACK    0x58

#define TWI_STATUS_REG_MASK 0xf8

void __print_i2c_registers (void)
{
    uint8_t i2c_status = TWSR & TWI_STATUS_REG_MASK;

    printf("I2C Log\r\n");
    printf("TWSR: %x\r\n", TWSR);
    printf("masked status: %x\r\n", i2c_status);
}

/* SCL frequency: 80KHz */
void i2c_init (void)
{
    // division factor: 92
    TWBR = 92;
    // prescaler value: 1
    TWSR = 0;
}

void i2c_start (uint8_t slave_address, i2c_mode_t mode)
{
    uint8_t i2c_status;

    // Send START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    // wait for TWINT flag set
    while ( (TWCR & (1 << TWINT)) == 0 )
    ;

    // issue: Repeated START 의 경우에도 주소를 전송해야 하나요?
    // Check status
    i2c_status = TWSR & TWI_STATUS_REG_MASK;
    if ( (i2c_status != TWI_START) && (i2c_status != TWI_REPEATED_START) )
        goto bad_i2c_status;

    // Send SLA + W/R
    TWDR = (slave_address << 1) | mode;
    TWCR = (1 << TWINT) | (1 << TWEN);

    // wait for TWINT flag set
    while ( (TWCR & (1 << TWINT)) == 0 )
    ;

    // Check status
    i2c_status = TWSR & TWI_STATUS_REG_MASK;
    if ( (i2c_status != TWI_MT_SLA_ACK) && (i2c_status != TWI_MR_SLA_ACK) )
        goto bad_i2c_status;

    return;

bad_i2c_status:
    __print_i2c_registers();
}

void i2c_stop (void)
{
    // Transmit STOP condition
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

    // wait for TWSTO flag clear
    while ( (TWCR & (1 << TWSTO)) == 1 )
    ;
}

void i2c_repeated_start (uint8_t slave_address, i2c_mode_t mode)
{
    i2c_start(slave_address, mode);
}

void i2c_write (uint8_t data)
{
    uint8_t i2c_status;

    // Transmit data
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);

    // wait for TWINT flag set
    while ( (TWCR & (1 << TWINT)) == 0 )
    ;

    // Check status
    i2c_status = TWSR & TWI_STATUS_REG_MASK;
    if ( i2c_status != TWI_MT_DATA_ACK )
        goto bad_i2c_status;

    return;

bad_i2c_status:
    __print_i2c_registers();
}

/* Receive data and return ack */
uint8_t i2c_read_and_send_ack (void)
{
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);

    // wait for TWINT flag set
    while ( (TWCR & (1 << TWINT)) == 0 )
    ;

    // return received data
    return TWDR;
}

/* Receive data and return not ack */
uint8_t i2c_read_and_send_nack (void)
{
    TWCR = (1 << TWINT) | (1 << TWEN);

    // wait for TWINT flag set
    while ( (TWCR & (1 << TWINT)) == 0 )
    ;

    // return received data
    return TWDR;
}
