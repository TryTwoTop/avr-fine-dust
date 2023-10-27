#ifndef __PM2008M_H__
#define __PM2008M_H__

#include <avr/io.h>

typedef struct
{
    uint8_t  status;
    uint16_t measuring_mode;
    uint16_t calib_coefficient;

    uint16_t pm_1p0_grimm;
    uint16_t pm_2p5_grimm;
    uint16_t pm_10_grimm;

    uint16_t pm_1p0_tsi;
    uint16_t pm_2p5_tsi;
    uint16_t pm_10_tsi;

    uint16_t num_of_0p3_um;
    uint16_t num_of_0p5_um;
    uint16_t num_of_1p0_um;
    uint16_t num_of_2p5_um;
    uint16_t num_of_5p0_um;
    uint16_t num_of_10p0_um;

    uint8_t check_code;
} pm2008m_data_t;

void pm2008m_init (void);
pm2008m_data_t pm2008m_read (void);

#endif //__PM2008M_H__
