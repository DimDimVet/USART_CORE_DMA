#ifndef INIT_USART
#define INIT_USART

#include "stm32f10x.h"                  // Device header
#include "misc.h"                       // Keil::Device:StdPeriph Drivers:Framework
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "stm32f10x_dma.h"              // Keil::Device:StdPeriph Drivers:DMA


void USART_INIT(void);
void USART2_SetData(int data);
void DMA_UART_Init(uint8_t *dataBufTx, uint8_t *dataBufRx);
//void USART1_SetData(uint8_t dataBuf[10]);

#endif
