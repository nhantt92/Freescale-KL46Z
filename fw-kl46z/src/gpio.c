#include "gpio.h"

void Gpio_Init()
{
	SIM->SCGC5 |= (1UL << 13);   // Mo xung clock PORT E
	PORTE->PCR[2] |= 1UL << 8;  // PTE2 is GPIO 
	PORTE->PCR[3] |= 1UL << 8; // PTE3 is GPIO
	PTE->PDDR |= 1UL << 2;      // PTE2 is output     
	PTE->PDDR |= 1UL << 3;       //PTE3 is output
	PTE->PSOR |= 1UL << 2;      // high level
	PTE->PSOR |= 1UL << 3; //high level
}

