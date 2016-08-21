#include "bh1750.h"
#include "i2c.h"
#include "sys-tick.h"


unsigned char _DEVICE_L     = 0x23;// Default device I2C address (ADD = GND)

unsigned char _DEVICE_H     = 0x5C;// Default device I2C address (ADD = VCC)

unsigned char POWER_DOWN = 0x00; // No active state

unsigned char POWER_ON   = 0x01; // Power on

unsigned char RESET      = 0x07; // Reset data register value
 
// Start measurement at 4lx resolution. Time typically 16ms.
unsigned char CONTINUOUS_LOW_RES_MODE = 0x13;
// Start measurement at 1lx resolution. Time typically 120ms
unsigned char CONTINUOUS_HIGH_RES_MODE_1 = 0x10;
// Start measurement at 0.5lx resolution. Time typically 120ms
unsigned char CONTINUOUS_HIGH_RES_MODE_2 = 0x11;
// Start measurement at 1lx resolution. Time typically 120ms
// Device is automatically set to Power Down after measurement.
unsigned char ONE_TIME_HIGH_RES_MODE_1 = 0x20;
// Start measurement at 0.5lx resolution. Time typically 120ms
// Device is automatically set to Power Down after measurement.
unsigned char ONE_TIME_HIGH_RES_MODE_2 = 0x21;
// Start measurement at 1lx resolution. Time typically 120ms
// Device is automatically set to Power Down after measurement.
unsigned char ONE_TIME_LOW_RES_MODE = 0x23;

unsigned char _BYTE_DATA_H = 0x0;

unsigned char _BYTE_DATA_L = 0x0;

uint16_t _DATA=0x0;



void BH1750_init() 
{ 
    delay_us(100000);  
   	I2C_Start(I2C1);
		I2C_Write_Byte(I2C1,0x46);
    I2C_Get_Ack(I2C1);
	  
		I2C_Write_Byte(I2C1,POWER_DOWN);
    I2C_Get_Ack(I2C1);
		I2C_Stop(I2C1);
} 

uint16_t read_bh1750()
{
	
		_DATA=0x0;
	
	  //Chon POWER_ON
	  I2C_Start(I2C1);
		I2C_Write_Byte(I2C1,0x46);
    I2C_Get_Ack(I2C1);
	
		I2C_Write_Byte(I2C1,POWER_ON);
    I2C_Get_Ack(I2C1);
		I2C_Stop(I2C1);
	  delay_us(15000);
	
	  //Chon mode 
		I2C_Start(I2C1);
		I2C_Write_Byte(I2C1,0x46);
    I2C_Get_Ack(I2C1);
	
		I2C_Write_Byte(I2C1,CONTINUOUS_HIGH_RES_MODE_1);
    I2C_Get_Ack(I2C1);
		I2C_Stop(I2C1);
		delay_us(15000);
	
		//Doc du lieu
		I2C_Start(I2C1);
		I2C_Write_Byte(I2C1,0x47);
    I2C_Get_Ack(I2C1);
	
		_BYTE_DATA_H=I2C_Read_Byte(I2C1);
	  I2C_Give_Ack(I2C1);
		_BYTE_DATA_L=I2C_Read_Byte(I2C1);
		I2C_Give_Ack(I2C1);
		I2C_Stop(I2C1);
		delay_us(15000);
		
		_DATA|=_BYTE_DATA_H<<8;
		_DATA|=_BYTE_DATA_L;
		
		
		//RESET
		I2C_Start(I2C1);
		I2C_Write_Byte(I2C1,0x46);
    I2C_Get_Ack(I2C1);
	  
		I2C_Write_Byte(I2C1,RESET);
    I2C_Get_Ack(I2C1);
		I2C_Stop(I2C1);
	  delay_us(15000);
		
		
		//POWER_DOWN
		I2C_Start(I2C1);
		I2C_Write_Byte(I2C1,0x46);
    I2C_Get_Ack(I2C1);
	  
		I2C_Write_Byte(I2C1,POWER_DOWN);
    I2C_Get_Ack(I2C1);
		I2C_Stop(I2C1);
	  delay_us(15000);
		
		return _DATA;
}

