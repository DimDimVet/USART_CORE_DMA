#ifndef APP_H_
#define APP_H_

#include "delay.h"
#include "INIT_USART_DMA.h"

#define BAUND_RATE 9600
#define SIZESTR 30
#define CHAR_COMMAND0 '0'
#define CHAR_COMMAND1 '1'

void ExecutorTerminal(void);

void USART1_ReceiveData(char *buffer, uint16_t size);
void USART1_SendData(uint8_t *data, uint16_t size) ;


#endif
