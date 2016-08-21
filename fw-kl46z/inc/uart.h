#ifndef __UART_H
#define __UART_H

#include "main.h"

typedef void( * CallBack_Type)(uint8_t * buffer, uint8_t len);

void UART0_PinConf(void);
void UART0_Init(void);
void UART0_PutChar(char c);
char UART0_GetChar(void);
//void UART0_GetString(char *s);
void UART0_it(void);
uint8_t UART0RX_GetFlagIRQ(void);
void UART0RX_ClearFlagIRQ(void);
void UART0RX_EnableIRQ(void);
void UART0_AsyncReceive(uint8_t len, uint8_t * buffer, CallBack_Type CallBack);

#endif

