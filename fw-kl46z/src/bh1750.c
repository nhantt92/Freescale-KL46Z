#include "bh1750.h"
#include "i2c.h"

uint_16 BH1750_read(uint8_t addr)
{
	uint16_t aux = 0;
	aux = I2C_
}

//void BH1750_init() 
//{ 
//    delay_us(100000);  
//  	I2C_Start(I2C1);
//		I2C_Write_Byte(I2C1,0x46);
//    I2C_Get_Ack(I2C1);
//	  
//		I2C_Write_Byte(I2C1,POWER_DOWN);
//    I2C_Get_Ack(I2C1);
//		I2C_Stop(I2C1);
//} 

//uint16_t read_bh1750()
//{
//	
//		_DATA=0x0;
//	
//	  //Chon POWER_ON
//	  I2C_Start(I2C1);
//		I2C_Write_Byte(I2C1,0x46);
//    I2C_Get_Ack(I2C1);
//	
//		I2C_Write_Byte(I2C1,POWER_ON);
//    I2C_Get_Ack(I2C1);
//		I2C_Stop(I2C1);
//	  delay_us(15000);
//	
//	  //Chon mode 
//		I2C_Start(I2C1);
//		I2C_Write_Byte(I2C1,0x46);
//    I2C_Get_Ack(I2C1);
//	
//		I2C_Write_Byte(I2C1,CONTINUOUS_HIGH_RES_MODE_1);
//    I2C_Get_Ack(I2C1);
//		I2C_Stop(I2C1);
//		delay_us(15000);
//	
//		//Doc du lieu
//		I2C_Start(I2C1);
//		I2C_Write_Byte(I2C1,0x47);
//    I2C_Get_Ack(I2C1);
//	
//		_BYTE_DATA_H=I2C_Read_Byte(I2C1);
//	  I2C_Give_Ack(I2C1);
//		_BYTE_DATA_L=I2C_Read_Byte(I2C1);
//		I2C_Give_Ack(I2C1);
//		I2C_Stop(I2C1);
//		delay_us(15000);
//		
//		_DATA|=_BYTE_DATA_H<<8;
//		_DATA|=_BYTE_DATA_L;
//		
//		
//		//RESET
//		I2C_Start(I2C1);
//		I2C_Write_Byte(I2C1,0x46);
//    I2C_Get_Ack(I2C1);
//	  
//		I2C_Write_Byte(I2C1,RESET);
//    I2C_Get_Ack(I2C1);
//		I2C_Stop(I2C1);
//	  delay_us(15000);
//		
//		
//		//POWER_DOWN
//		I2C_Start(I2C1);
//		I2C_Write_Byte(I2C1,0x46);
//    I2C_Get_Ack(I2C1);
//	  
//		I2C_Write_Byte(I2C1,POWER_DOWN);
//    I2C_Get_Ack(I2C1);
//		I2C_Stop(I2C1);
//	  delay_us(15000);
//		
//		return _DATA;
//}

