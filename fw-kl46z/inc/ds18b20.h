#ifndef DS18B20_H
#define DS18B20_H
#include "MKL46Z4.h"
#include "stdio.h"
#include "string.h"
#include "sys-tick.h"
#include "stdlib.h"

void ds18b20_init(void);
uint16_t ds18b20_reset(void);
void ds18b20_write(uint8_t data);
uint16_t ds18b20_read(void);
void ds18b20_write_bit(uint8_t bit);
uint16_t ds18b20_read_bit(void);
void ds18b20_write_byte(uint8_t data);
uint8_t ds18b20_read_byte(void);

#endif /* DS18B20_H */
