#include "stm32f10x.h"                  // Device header


#define BUFFER_SIZE 64
uint8_t txBuffer[BUFFER_SIZE] = "Привет, USART!"; // Данные для передачи

void DMA1_Channel4_IRQHandler()
	{
    if (DMA1->ISR & DMA_ISR_TCIF1) { // Проверка флага завершения передачи
        DMA1->IFCR |= DMA_IFCR_CTCIF1; // Сбрасываем флаг
        // Действия по завершению передачи
    }
}

int main() {
    //RCC_Init();
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Включение порта A
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Включение USART1
    RCC->AHBENR |= RCC_AHBENR_DMA1EN; // Включение DMA1
	//
    //USART1_Init();
		GPIOA->CRH |= (GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_0); // TX
    GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10); // RX

    USART1->BRR = SystemCoreClock/9600; // Скорость 9600 Baud
    USART1->CR1 |= USART_CR1_UE; // Включение USART
    USART1->CR1 |= USART_CR1_TE; // TX
	//
    //DMA_Init();
		DMA1_Channel4->CCR |= (DMA_CCR1_PL_0 | DMA_CCR1_MINC | DMA_CCR1_DIR); // Высокий приоритет, инкремент, направление: память -> перIPHERAL
    DMA1_Channel4->CNDTR = BUFFER_SIZE; // Количество данных
    DMA1_Channel4->CPAR = (uint32_t)&USART1->DR; // Адрес регистра данных USART
    DMA1_Channel4->CMAR = (uint32_t)txBuffer; // Адрес буфера
    DMA1_Channel4->CCR |= DMA_CCR1_EN; // Включение канала DMA
	//
    //NVIC_Init();
		NVIC_EnableIRQ(DMA1_Channel4_IRQn); // Разрешение прерывания для DMA
		//
    
    while (1)
		{
        DMA1_Channel4->CCR |= DMA_CCR1_EN; // Запуск передачи данных
        // ваш основной код
    }
}
