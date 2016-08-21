#include "main.h"

#define leng =40;
char data[11];
char i = 0;
uint8_t nhietdo_c, nhietdo_dv,doam_c,doam_dv;
char id[3],dev1[4],dev2[4];
char i;
uint16_t lux = 364;
char stt1[4] = "1ON";
char stt2[4] = "2OFF";

void delay(uint32_t x)//ham delay
{
 while(x--)
 {};
}
	
	
	
void UART0_IRQHandler()
{  //i = 0; 
	//data = UART0_GetChar();
	//UART0_PutChar(data);	
	data[i] = UART0_GetChar();
	i++;
	if(i==11)
		i=0;
}

int main(void)
{	
	SystemCoreClockUpdate();
	Init_Sys_Tick();
	UART0_PinConf();
	UART0_Init();
	UART0RX_EnableIRQ();
	DHT11_Init();
	Gpio_Init();
	printf("start");
	PTE->PCOR |= 1UL << 2;
	while (1)
	{	
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
			delay_us(2000000);
			printf("%s",data);
		}
}

		


