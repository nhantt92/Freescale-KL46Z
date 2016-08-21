#include "dht11.h"

void DHT11_Init()
{
	SIM->SCGC5|=SIM_SCGC5_PORTD_MASK;		//CLOCK D
	PORTD->PCR[2] |=PORT_PCR_MUX(1);  	//PD2 is GPIO
}

unsigned char DHT11_Start()
{
	PTD->PDDR |= (uint32_t)0x00000004ul; //PTD2 is output
	PTD->PSOR |= (uint32_t)0x00000004ul; //PTD2 -> logic 1
	delay_us(60);
	PTD->PCOR |= (uint32_t)0x00000004ul; //PTD2 -> logic 0
	delay_us(18000);
	PTD->PSOR |= (uint32_t)0x00000004ul; //PTD2 -> logic 1
	delay_us(40);
	PTD->PDDR = (uint32_t)0x00000000ul; //PTD2 is input
	delay_us(40);
	if(PTD->PDIR == 0x4ul) //check PTD2 -> 1 ?
		return 1;
	else
		while(PTD->PDIR == 0x0ul); 
	delay_us(80);
	if(PTD->PDIR == 0x4ul)
		return 1;
	else
		return 0;
}

unsigned char DHT11_GetTemHumi(uint8_t *temp_ng, uint8_t *temp_tp, uint8_t *humi_ng, uint8_t *humi_tp)
{
	uint8_t buffer[5]={0x00,0x00,0x00,0x00,0x00};
	uint8_t j,i, checksum;
	while(FPTD->PDIR == 0x4ul);
	for(i=0;i<5;i++)
	{	
		for(j=0;j<8;j++)
		{
			while(PTD->PDIR == 0x0ul);
			delay_us(50);
			if(PTD->PDIR == 0x4ul)
			{
				buffer[i] |= (1<<(7-j));
				while(PTD->PDIR == 0x4ul);
			}
		}
	}
	checksum = buffer[0]+buffer[1]+buffer[2]+buffer[3];
	if(checksum != buffer[4])
		return 0;
	*humi_ng = buffer[0];
	*humi_tp = buffer[1];
	*temp_ng = buffer[2];
	*temp_tp = buffer[3];
	return 1;
}
