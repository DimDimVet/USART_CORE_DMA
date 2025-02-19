#ifndef INIT_USART
#define INIT_USART

#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"                  // Device header

void Init_USART(int baudRate);//main init usart
void Enable_RCC_AHB1(void);//GpioA usart, GpioA pin7 LED
void Enable_RCC_APB2(void);//Usart1
void LED(void);//GpioA pin7 LED
void Config_LED(void);//Config GpioA pin6 pin7 LED
void Config_GPIO_USART(int baudRate);

int USART1_GetStatus();//status Rx
char USART1_ReadChar();//read DR

void USART1_SetChar(char c);
void USART1_SetString(char* str);

#endif
