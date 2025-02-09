#include "init_USART.h"

void Init_USART()//main init usart
{
	//Led
	Enable_RCC_APB2();
	Config_LED();
	//
	Enable_RCC_APB1();
	Config_GPIO_USART();
}

void Enable_RCC_APB1()//Usart2
{
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
}

void Enable_RCC_APB2()//GpioC pin13 LED, GpioA usart
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
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
    GPIOC->BSRR = GPIO_BSRR_BR13;        // Сбросить
}

void Config_GPIO_USART()
{
		GPIOA->CRL |= (GPIO_CRL_MODE2_1 | GPIO_CRL_CNF2_1); // PA2 на выход, альт режим
    GPIOA->CRL |= (GPIO_CRL_CNF3_0); // PA3 на вход
		
		//USART2->BRR = 0x1D4C; // Baud rate 9600(для 72MHz)
		USART2->BRR = 0xEA6; // Baud rate 9600(для 72MHz)
    USART2->CR1 |= USART2->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE | USART_CR1_RXNEIE; // Включить TX, RX и прерывание

		NVIC_EnableIRQ(USART2_IRQn); // Разрешить прерывания для USART2
}

void USART2_SendChar(char c)
{
    while (!(USART2->SR & USART_SR_TXE))
		{
			
		}
    USART2->DR = c;
}

void USART2_SendString(char* str)
{
    while (*str)
		{
        USART2_SendChar(*str++);
    }
}

char USART2_ReceiveChar(void)
{
    while (!(USART2->SR & USART_SR_RXNE));
    return USART2->DR;
}
