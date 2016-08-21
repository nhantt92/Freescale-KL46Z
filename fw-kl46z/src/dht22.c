#include "dht22.h"
#include "string.h"

void DHT22_Init()
{
	SIM->SCGC5 |= 1ul << 13; //enable gate clock port e 
	PORTE->PCR[2] |= 0x102ul; //PTE2 is GPIO, resistor pullup
}

unsigned char DHT22_Start()
{
	PTE->PDDR |= (uint32_t)0x00000004UL; //set PTE2 is output
	PTE->PSOR |= (uint32_t)0x00000004UL; 
	delay_us(60);
	PTE->PCOR |= (uint32_t)0x00000004UL; //clear PTE2 low level
	delay_us(900);
	PTE->PSOR |= (uint32_t)0x00000004UL; //set PTE2 high level
	delay_us(40);
	PTE->PDDR |= (uint32_t)0x00000000UL; //set PTE2 is input
	delay_us(40);
	if(PTE->PDIR == 0x4ul) //check PTE2 -> 1 ?
		return 1;
	else
		while(PTE->PDIR == 0x0ul); 
	delay_us(80);
	if(PTE->PDIR == 0x4ul)
		return 1;
	else
		return 0;
}

unsigned char DHT22_GetTemHumi(uint8_t *temp, uint8_t *humi)
{
	unsigned char buffer[5]={0,0,0,0,0}; 
  unsigned char j,i,checksum; 
	while(FPTE->PDIR == 0x4ul);
	for(i=0;i<5;i++)
	{	
		for(j=0;j<8;j++)
		{
			while(PTE->PDIR == 0x0ul);
			delay_us(50);
			if(PTE->PDIR == 0x4ul)
			{
				buffer[i] |= (1<<(7-j));
				while(PTE->PDIR == 0x4ul);
			}
		}
	}
	checksum = buffer[0]+buffer[1]+buffer[2]+buffer[3];
	//if(checksum != buffer[4])
		//return 0;
	*temp = (buffer[2]*256 + buffer[3])/10;
	*humi = (buffer[0]*256 + buffer[1])/10;
	return 1;
}
