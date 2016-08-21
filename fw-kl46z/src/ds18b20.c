#include "ds18b20.h"


void ds18b20_init(void)
{
	//enable port C
	//PTC1 is GPIO, resistor pull up
	//PTC1 is output
	ds18b20_reset();
}

uint16_t ds18b20_reset(void)
{
	
}

void ds18b20_write(uint8_t data)
{
	
}

uint16_t ds18b20_read(void)
{
	
}

