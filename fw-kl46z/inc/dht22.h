#ifndef __DHT22_H
#define __DHT22_H

#include "MKL46Z4.h"
#include "stdio.h"
#include "string.h"
#include "sys-tick.h"


void DHT22_Init();
unsigned char DHT22_Start();
unsigned char DHT22_GetTemHumi(uint8_t *temp, uint8_t *humi);
#endif
