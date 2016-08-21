
#ifndef __I2C_H__
#define __I2C_H__
#include "MKL46Z4.h"
#include "sys-tick.h"
#include "stdint.h"
#include "i2c.h"

#define BH1750_WRITE 0x00
#define BH1750_READ 0xFF

#define BH1750_ADDR_H 0x5C
#define BH1750_ADDR_L 0x23

#define BH1750_POWER_DOWN 0x00
#define BH1750_POWER_ON 0x01
#define BH1750_RESET 0x07
#define BH1750_CONTINUOUS_HIGH_RES_MODE 0x10
#define BH1750_CONTINUOUS_HIGH_RES_MODE_2 0x11
#define BH1750_CONTINUOUS_LOW_RES_MODE_2 0x13
#define BH1750_ONE_TIME_HIGH_RES_MODE 0x20
#define BH1750_ONE_TIME_HIGH_RES_MODE_2 0x21
#define BH1750_ONE_TIME_LOW_RES_MODE 0x23


void BH1750_init();

uint16_t read_bh1750();

#endif