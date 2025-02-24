#ifndef INIT_USART
#define INIT_USART

#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"                  // Device header

void Init_USART(int baudRate);//main init usart
void Enable_RCC_APB1(void);//Usart2
void Enable_RCC_APB2(void);//GpioC pin13 LED, GpioA usart
void LED(void);//GpioC pin13 LED
void Config_LED(void);//Config GpioC pin13 LED
void Config_GPIO_USART(int baudRate);

int USART2_GetStatus();//status Rx
char USART2_ReadChar();//read DR

void USART2_SetChar(char c);
void USART2_SetString(char* str);

#endif
