#ifndef INIT_USART_DMA
#define INIT_USART_DMA

#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"                  // Device header

void Init_USART(int baudRate);//main init usart
void Enable_RCC_AHB(void);//DMA1
//void Enable_RCC_APB1(void);//Usart2
void Enable_RCC_APB2(void);//GpioC pin13 LED, GpioA usart, usart1
void LED(void);//GpioC pin13 LED
void Config_LED(void);//Config GpioC pin13 LED
void Config_GPIO_USART(int baudRate);
void Config_DMA1(void);

int USART1_GetStatus();//status Rx
char USART1_ReadChar();//read DR

void USART1_SetChar(char c);
void USART1_SetString(char* str);

#endif
