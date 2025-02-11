#include "init_USART.h"

void Init_USART()//main init usart
{
	//Led
	Enable_RCC_APB2();
	Config_LED();
	//
	Enable_RCC_APB1();
	Enable_RCC_AHB1();
	Config_GPIO_USART();
}

void Enable_RCC_AHB1()//GpioA usart
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
}

void Enable_RCC_APB1()//Usart2
{
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
}

void Enable_RCC_APB2()//GpioC pin13 LED, 
{
	//RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	//RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
}

void LED()//GpioC pin13 LED
{
    //GPIOC->ODR ^= GPIO_ODR_ODR13;
}

void Config_LED()//Config GpioC pin13 LED
{
		//GPIOC->CRH &=~(GPIO_CRH_CNF13|GPIO_CRH_MODE13);
    //GPIOC->CRH|=(~GPIO_CRH_CNF13)|GPIO_CRH_MODE13_1;
		//GPIOC->BSRR = GPIO_BSRR_BS13;        // Установить
    ////GPIOC->BSRR = GPIO_BSRR_BR13;        // Сбросить
}

void Config_GPIO_USART()
{
		GPIOA->MODER &= ~(GPIO_MODER_MODER2 | GPIO_MODER_MODER3);//// Настраиваем пины PA2 (TX) и PA3 (RX)
		
		GPIOA->MODER |= (2 << GPIO_MODER_MODER2_Pos) | (2 << GPIO_MODER_MODER3_Pos); // Установим альтернативный режим
		GPIOA->AFR[0] |= (7 << GPIO_AFRL_AFSEL2_Pos) | (7 << GPIO_AFRL_AFSEL3_Pos); // AF7 для USART2
	
		//USART2->BRR = 0x8B; // Baud rate 9600(для 16MHz кварца)
		USART2->BRR = 0x8B; // Baud rate 9600(для 8MHz кварца)??
		USART2->CR1 |= USART_CR1_UE; // Включить USART2
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE; // Включить TX, RX
		USART2->CR1 |= USART_CR1_RXNEIE; // Включить прерывание

		NVIC_EnableIRQ(USART2_IRQn); // Разрешить прерывания для USART2
}

int USART2_GetStatus()//Проверим окончание чтения
{
	if(USART2->SR & USART_SR_RXNE)
	{
		return 1;
	}
		return 0;
}

char USART2_ReadChar()//считываем регистр 
{
	return USART2->DR;
}

void USART2_SetChar(char c)//Установка символа
{
    while (!(USART2->SR & USART_SR_TXE))//Проверим окончание передачи
		{
		}
    USART2->DR = c;
}

void USART2_SetString(char* str)//Установка строки по символьно
{
		int size = strlen(str);
		
		for(int i=0; i<size;i++)
		{
			USART2_SetChar(str[i]);
		}
}

