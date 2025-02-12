#include "INIT_USART_DMA.h"

void Init_USART(int baudRate)//main init usart
{
	//
	Enable_RCC_APB2();
	Config_LED();
	//
	Enable_RCC_AHB();
	Config_GPIO_USART(baudRate);
	Config_DMA1();
}

void Enable_RCC_AHB()//DMA1
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
}

void Enable_RCC_APB1()//Usart2&&&&
{
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
}

void Enable_RCC_APB2()//GpioC pin13 LED, GpioA usart, usart1
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
}

void LED()//GpioC pin13 LED
{
    GPIOC->ODR ^= GPIO_ODR_ODR13;
}

void Config_LED()//Config GpioC pin13 LED
{
		GPIOC->CRH &=~(GPIO_CRH_CNF13|GPIO_CRH_MODE13);
    GPIOC->CRH|=(~GPIO_CRH_CNF13)|GPIO_CRH_MODE13_1;
		GPIOC->BSRR = GPIO_BSRR_BS13;        // Установить
    //GPIOC->BSRR = GPIO_BSRR_BR13;        // Сбросить
}

void Config_GPIO_USART(int baudRate)
{
		GPIOA->CRH |= (GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1); // PA9 на выход, альт режим TX
    GPIOA->CRH |= (GPIO_CRH_CNF10_0); // PA10 на вход RX
		
		USART1->BRR = SystemCoreClock/baudRate; // SystemCoreClock/Baudrate 
		USART1->CR1 |= USART_CR1_UE ; // Включить USART
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE ; // Включить TX, RX
		USART1->CR1 |= USART_CR1_RXNEIE; // Включить прерывание

		NVIC_EnableIRQ(USART1_IRQn); // Разрешить прерывания для USART1
}

void Config_DMA1()
{
		 // Настройки DMA - USART1_RX
		DMA1_Channel5->CCR |= DMA_CCR1_MINC;//включим режим перебора(в данном случае массива)
		DMA1_Channel5->CCR |= DMA_CCR1_DIR;//направления чтение из памяти (в перефирию)
		DMA1_Channel5->CCR |= DMA_CCR1_EN;//включим канал

}

int USART1_GetStatus()//Проверим окончание чтения
{
	if(USART1->SR & USART_SR_RXNE)
	{
		return 1;
	}
		return 0;
}

char USART1_ReadChar()//считываем регистр 
{
	return USART1->DR;
}

void USART1_SetChar(char c)//Установка символа
{
    while (!(USART1->SR & USART_SR_TXE))//Проверим окончание передачи
		{
		}
    USART1->DR = c;
}

void USART1_SetString(char* str)//Установка строки по символьно
{
		int size = strlen(str);
		
		for(int i=0; i<size;i++)
		{
			USART1_SetChar(str[i]);
		}
}

