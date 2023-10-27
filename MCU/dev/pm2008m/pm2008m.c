#include "pm2008m.h"
#include "../../com/i2c/i2c.h"

#define PM2008M_I2C_ADDRESS         (uint8_t)0x28
#define PM2008M_FRAME_HEADER        0x16

#define PM2008M_WRITE_FRAME_LENGTH  7
#define PM2008M_READ_FRAME_LENGTH   32
#define DATA_BUFFER_LENGTH          PM2008M_READ_FRAME_LENGTH

// Write - Data 1
#define PM2008M_CTRL_CLOSE_MEASUREMENT                  1
#define PM2008M_CTRL_OPEN_SINGLE_MEASUREMENT            2
#define PM2008M_CTRL_SET_UP_CONTINUOUSLY_MEASUREMENT    3
#define PM2008M_CTRL_SET_UP_TIMING_MEASUREMENT          4
#define PM2008M_CTRL_SET_UP_DYNAMIC_MEASUREMENT         5
#define PM2008M_CTRL_SET_UP_CALIB_COEFFICIENT           6

#define PM2008M_CTRL_DEFAULT_MODE                       PM2008M_CTRL_SET_UP_CONTINUOUSLY_MEASUREMENT

#define RESERVED_BYTE   0x00

pm2008m_data_t _pm2008m_data;

uint8_t _data_buffer[DATA_BUFFER_LENGTH];

uint8_t __calc_data_check_code (int frame_length)
{
    int i;
    uint8_t check_code;

    check_code = _data_buffer[0];
    for (i = 1; i < frame_length; i++)
    {
        check_code ^= _data_buffer[i];
    }

    return check_code;
}

void __combine_data_to_pm2008m_data (void)
{
    _pm2008m_data.status            =  _data_buffer[2];
    _pm2008m_data.measuring_mode    = (_data_buffer[3] << 8)  | _data_buffer[4];
    _pm2008m_data.calib_coefficient = (_data_buffer[5] << 8)  | _data_buffer[6];

    _pm2008m_data.pm_1p0_grimm      = (_data_buffer[7] << 8)  | _data_buffer[8];
    _pm2008m_data.pm_2p5_grimm      = (_data_buffer[9] << 8)  | _data_buffer[10];
    _pm2008m_data.pm_10_grimm       = (_data_buffer[11] << 8) | _data_buffer[12];

    _pm2008m_data.pm_1p0_tsi        = (_data_buffer[13] << 8) | _data_buffer[14];
    _pm2008m_data.pm_2p5_tsi        = (_data_buffer[15] << 8) | _data_buffer[16];
    _pm2008m_data.pm_10_tsi         = (_data_buffer[17] << 8) | _data_buffer[18];

    _pm2008m_data.num_of_0p3_um     = (_data_buffer[19] << 8) | _data_buffer[20];
    _pm2008m_data.num_of_0p5_um     = (_data_buffer[21] << 8) | _data_buffer[22];
    _pm2008m_data.num_of_1p0_um     = (_data_buffer[23] << 8) | _data_buffer[24];
    _pm2008m_data.num_of_2p5_um     = (_data_buffer[25] << 8) | _data_buffer[26];
    _pm2008m_data.num_of_5p0_um     = (_data_buffer[27] << 8) | _data_buffer[28];
    _pm2008m_data.num_of_10p0_um    = (_data_buffer[29] << 8) | _data_buffer[30];

    _pm2008m_data.check_code = _data_buffer[31];
}

void pm2008m_init (void)
{
    int i;

    i2c_init();
    i2c_start(PM2008M_I2C_ADDRESS, I2C_WRITE_MODE);

    // P1 ~ P7 Data
    _data_buffer[0] = PM2008M_FRAME_HEADER;
    _data_buffer[1] = PM2008M_WRITE_FRAME_LENGTH;
    _data_buffer[2] = PM2008M_CTRL_DEFAULT_MODE;
    _data_buffer[3] = 0xff;
    _data_buffer[4] = 0xff;
    _data_buffer[5] = RESERVED_BYTE;
    _data_buffer[6] = __calc_data_check_code(PM2008M_WRITE_FRAME_LENGTH);

    for (i = 0; i < PM2008M_WRITE_FRAME_LENGTH; i++)
    {
        i2c_write(_data_buffer[i]);
    }

    i2c_stop();
}

pm2008m_data_t pm2008m_read (void)
{
    int i;

    i2c_start(PM2008M_I2C_ADDRESS, I2C_READ_MODE);

    // P1 ~ P32 Data
    for (i = 0; i < (PM2008M_READ_FRAME_LENGTH - 1); i++)
    {
        _data_buffer[i] = i2c_read_and_send_ack();
    }
    _data_buffer[i] = i2c_read_and_send_nack();

    i2c_stop();

    __combine_data_to_pm2008m_data();

    return _pm2008m_data;
}
