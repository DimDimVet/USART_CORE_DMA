#ifndef APP_H_
#define APP_H_

#include "delay.h"
#include "INIT_USART_DMA.h"

#define BAUND_RATE 9600
#define SIZESTR 30
#define CHAR_COMMAND0 '0'
#define CHAR_COMMAND1 '1'

char rezultStr [SIZESTR];
char receivedChar;
char* greetingsStr="Prived STM32F103";
char* partingStr="BayBay STM32F103";
char* errorStr="error command";

void ExecutorTerminal(void);

#endif
