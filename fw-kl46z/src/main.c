#include "main.h"
#define leng =40;
char rev[10];
char i = 0;
char j = 0;
uint8_t nhietdo_c, nhietdo_dv,doam_c,doam_dv;
char id[3],dev1[4],dev2[4];
uint16_t lux;
char *stt1 = "";
char *stt2 = "";

void delay(uint32_t x)//ham delay
{
 while(x--)
 {
		if(rev[2]=='1'&& rev[4]=='N')
		PTE->PCOR |= (1U<<2);
		else if(rev[2] == '1' && rev[4] == 'F')
		PTE->PSOR |= (1U<<2);
		if(rev[6] == '2' && rev[8] == 'N')
		PTE->PCOR |= (1u<<3);
		else if(rev[6] == '2' && rev[8] == 'F')
		PTE->PSOR |= (1u<<3);
 }
}
	
	
void UART0_IRQHandler()
{  //i = 0; 
	//data = UART0_GetChar();
	//UART0_PutChar(data);	
	rev[i] = UART0_GetChar();
	i++;
	if(i==10)
		i=1;
}

int main(void)
{	
	SystemCoreClockUpdate();
	Init_Sys_Tick();
	UART0_PinConf();
	UART0_Init();
	UART0RX_EnableIRQ();
	DHT11_Init();
	I2C_Init(I2C1);
	BH1750_init();
	Gpio_Init();
	printf("start");
	PTE->PSOR |= 1UL << 2;
	PTE->PSOR |= 1UL << 3;
	while (1)
	{	
		//printf("%s\n",rev);
		if((PTE->PDOR&0x4ul) == 0x4ul) //check data output port D
			//printf("DEV1: OFF\n"); //led active level 0 - > level 1 : led off
			stt1 = "1OFF";
		else
			//printf("DEV1: ON\n"); //level 0: led on
			stt1 = "1ON";
		if((PTE->PDOR&0x8ul) == 0x8ul)
			//printf("DEV2: OFF\n");
			stt2 = "2OFF";
		else
			//printf("DEV2: ON\n");
			stt2 = "2ON ";
		lux = read_bh1750();
		if(DHT11_Start())
		{	
			if(DHT11_GetTemHumi(&nhietdo_c,&nhietdo_dv,&doam_c,&doam_dv))
			{
//				printf("readding DHT11\n");
//				printf("%d,%d oC\n",nhietdo_c,nhietdo_dv);
//				printf("%d,%d RH \n",doam_c,doam_dv);
					printf("01,%d,%d,%d,%s,%s\n",nhietdo_c,doam_c,lux,stt1,stt2);
					
			}
			else
				printf("khong do dung\n");
		}
		else
			printf("ERR\n");
			delay(5000000);
		}
}

		


