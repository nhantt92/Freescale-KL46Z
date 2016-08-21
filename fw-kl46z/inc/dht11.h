 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DHT11_H
#define __DHT11_H

/* Includes ------------------------------------------------------------------*/
#include "utils.h"
#include "MKL46Z4.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "sys-tick.h"

void DHT11_Init();
unsigned char DHT11_Start();
unsigned char DHT11_GetTemHumi(uint8_t *temp_ng, uint8_t *temp_tp, uint8_t *humi_ng, uint8_t *humi_tp);

#endif /* __DHT11_H */