#include "main.h"
/**
 * @brief         UART0_PinConf
 * @param[in]     void
 * @param[in,out] void
 * @return        void
 */
void UART0_PinConf(void)
{
	/* PTA1 : UART0_RX */
	PORTA->PCR[1] = 0x00000200UL;
	/* PTA2 : UART0_TX */
	PORTA->PCR[2] = 0x00000200UL;	
}

/**
 * @brief         UART0_Init
 * @param[in]     void
 * @param[in,out] void
 * @return        void
 */
void UART0_Init(void)
{
	char dummy;
	/* Enable clock gate UART0 */
  SIM->SCGC4 |=   1UL << 10; 
  
	/* Choose MCGFLLCLK/2 (48MHz/2) */	
  SIM->SOPT2 |= 1UL << 16;     
	SIM->SOPT2 &= ~(1UL << 27);
	SIM->SOPT2 |=   1UL << 26;

  /* Baudrate = clock/(SBR[12:0] x (OSR + 1))   */
	/* OSR = 15, clock = 24MHz, baudrate = 115200 *///ask: can't config another baund rate.
	/* -> SBR = 13 */
	/* LBKDIE = 0, RXEDGIE = 0, SBNS = 0 */
	UART0->BDH = 0x00;
	UART0->BDL = 0x1A;//26 ???

	/* UART0 control */
	UART0->C1 = 0x00;
	UART0->C2 = 0x00;
	UART0->C3 = 0x00;
	UART0->C4 = 0x0F; /* OSR = 15 */
	UART0->C5 = 0x00;
	
	/* Enable UART0 transmit/receive */
	UART0->C2 |= 0x03 << 2;
	
	/* Dummy read to ensure UART0 
	   receive buffer is empty already */
	dummy = UART0->D;
}	

/**
 * @brief         UART0_PutChar
 * @param[in]     void
 * @param[in,out] void
 * @return        void
 */
void UART0_PutChar(char c)
{
	UART0->D   = c;
  /* Wait for transmition complete */
	while(!(UART0->S1 & (0x01 << 6))) {}
}

/**
 * @brief         UART0_GetChar
 * @param[in]     void
 * @param[in,out] void
 * @return        char
 */
char UART0_GetChar(void)
{
	/* Wait for incomming character */
	while(!(UART0->S1 & (0x01 << 5))) {}
  return UART0->D; 
}

/*
void UART0_GetString(char *s)
{
	*s = UART0_GetChar();
	while(*s!='\0');
	{
		s++;
		*s = UART0_GetChar();
	}
}*/

/**
 * @brief file handle structure
 */
struct __FILE 
{ 
	int handle;
};

FILE __stdout;
FILE __stdin;


/**
 * @brief         fputc
 * @param[in]     void
 * @param[in,out] void
 * @return        char
 */
int fputc(int ch, FILE *f) 
{ 
  UART0_PutChar((char)ch);
  return((int)ch);
}

/**
 * @brief         fgetc
 * @param[in]     void
 * @param[in,out] void
 * @return        char
 */
int fgetc(FILE *f) {
	
	char c;
	/* get key */
	c =  UART0_GetChar();
	/* print echo */
	UART0_PutChar(c);
  return (int)c;
}
/**
 * @brief         UART0RX_GetFlagIRQ
 * @param[in]     void
 * @param[in,out] void
 * @return        uint8_t
 */
uint8_t UART0RX_GetFlagIRQ(void){
	if((UART0->S1 & UART0_S1_RDRF_MASK)==UART0_S1_RDRF_MASK){
		return 1;
	}
	else{
		return 0;
	}
}
/**
 * @brief         UART0RX_ClearFlagIRQ
 * @param[in]     void
 * @param[in,out] void
 * @return        void
 */
void UART0RX_ClearFlagIRQ(void){
	uint8_t Buffer;
	Buffer = UART0->D;
}
/**
 * @brief         UART0RX_EnableIRQ
 * @param[in]     void
 * @param[in,out] void
 * @return        void
 */
void UART0RX_EnableIRQ(void){
	UART0->C2 |= UART0_C2_RIE_MASK;
	NVIC_SetPriority(UART0_IRQn,2);
	NVIC_EnableIRQ(UART0_IRQn);
}
/*********************************************************************/

