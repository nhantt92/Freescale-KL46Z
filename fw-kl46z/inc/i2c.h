#ifndef __I2C_H__
#define __I2C_H__
#include "MKL46Z4.h"

#define I2C_READ  1
#define I2C_WRITE 0


void I2c_Set_Tx_Mode(I2C_Type* p);
void I2c_Set_Rx_Mode(I2C_Type* p);
void I2C_Set_Slave_mode(I2C_Type* p);
void I2C_Set_Master_mode(I2C_Type* p);
void I2C_Give_Nack(I2C_Type* p);
void I2C_Give_Ack(I2C_Type* p);
void I2C_Repeated_Start(I2C_Type* p);
void I2C_Write_Byte(I2C_Type* p, uint8_t data);
unsigned char I2C_Read_Byte(I2C_Type* p);
void I2C_Start(I2C_Type* p);
void I2C_Stop(I2C_Type* p);
void I2C_Wait(I2C_Type* p);
unsigned char I2C_Get_Ack(I2C_Type* p);
void I2C0_Init(I2C_Type* p); //Acelerometro
void I2C_Deinit(I2C_Type* p);
void I2C_Init(I2C_Type* p);  //Magnetometro
//I2C1_Init(I2C_Type* p) ;
#endif

