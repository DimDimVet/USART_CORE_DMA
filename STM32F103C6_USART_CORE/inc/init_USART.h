#ifndef INIT_USART
#define INIT_USART

#include "stm32f10x.h"                  // Device header

void Init_USART(void);//main init usart
void Enable_RCC_APB1(void);//Usart2
void Enable_RCC_APB2(void);//GpioC pin13 LED, GpioA usart
void LED(void);//GpioC pin13 LED
void Config_LED(void);//Config GpioC pin13 LED
void Config_GPIO_USART(void);

void USART2_SendChar(char c);
void USART2_SendString(char* str);
char USART2_ReceiveChar(void);

#endif
