#include "init_USART.h"

void Init_USART(int baudRate)//main init usart
{
	Enable_RCC_AHB1();
	Config_LED();
	//
	Enable_RCC_APB2();
	
	Config_GPIO_USART(baudRate);
}

void Enable_RCC_AHB1()//GpioA usart, GpioA pin7 LED
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
}

void Enable_RCC_APB2()//Usart1
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
}

void LED()//GpioA pin7 LED
{
    GPIOA->ODR ^= GPIO_ODR_OD7;
}

void Config_LED()//Config GpioA pin6 pin7 LED
{
		GPIOA->MODER &= ~ (GPIO_MODER_MODER6|GPIO_MODER_MODER7); // сброс
    GPIOA->MODER |= (GPIO_MODER_MODER6_0|GPIO_MODER_MODER7_0);//режим на выход
    GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED6|GPIO_OSPEEDR_OSPEED7); // сброс скорости
    GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED6_0|GPIO_OSPEEDR_OSPEED7_0); // установка средней скорости
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD6|GPIO_PUPDR_PUPD7); // сброс режим подтяжки
    GPIOA->PUPDR |= (GPIO_PUPDR_PUPD6_0|GPIO_PUPDR_PUPD7_0); // установка подтяжки к + (1)  РА0
    GPIOA->OTYPER &= ~ (GPIO_OTYPER_OT6|GPIO_OTYPER_OT7); // сброс режима нагрузки
    GPIOA->OTYPER |= (GPIO_OTYPER_OT6|GPIO_OTYPER_OT7); // установка в режим с открытым коллектором
		GPIOA->ODR |= (GPIO_ODR_OD6|GPIO_ODR_OD7);
}

void Config_GPIO_USART(int baudRate)
{
		GPIOA->MODER &= ~(GPIO_MODER_MODER9 | GPIO_MODER_MODER10);//// Настраиваем пины PA9 (TX) и PA10 (RX)

		GPIOA->MODER |= (GPIO_MODER_MODER9_1) | (GPIO_MODER_MODER10_1); // Установим альтернативный режим
		GPIOA->AFR[1] |= (GPIO_AFRH_AFSEL9_0|GPIO_AFRH_AFSEL9_1|GPIO_AFRH_AFSEL9_2) 
											| (GPIO_AFRH_AFSEL10_0|GPIO_AFRH_AFSEL10_1|GPIO_AFRH_AFSEL10_2); // AF7 для USART1
		
		USART1->BRR = SystemCoreClock/baudRate; // SystemCoreClock/Baudrate 
		USART1->CR1 |= USART_CR1_UE; // Включить USART2
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE; // Включить TX, RX
		USART1->CR1 |= USART_CR1_RXNEIE; // Включить прерывание

		NVIC_EnableIRQ(USART1_IRQn); // Разрешить прерывания для USART2
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

