#include "app.h"


char rezultStr [SIZESTR];
char receivedChar;
char* greetingsStr="Prived STM32F103";
char* partingStr="BayBay STM32F103";
char* errorStr="error command";


int main()
{
	int count=0;
	Init_USART(BAUND_RATE);
	
	while(1)
	{
		
		if(count<5)
		{
			
			count++;
		}
			
	}
	return 0;
}

void USART1_IRQHandler(void)
{
		//LED();
		//
		//ExecutorTerminal();
	  //DMA1_Channel4->CCR |= DMA_CCR4_EN; // Запуск передачи данных
	DMA1_Channel5->CPAR = (uint32_t)&USART1->DR;
	DMA1_Channel5->CCR |= DMA_CCR5_EN | DMA_CCR1_DIR;
		//
		//LED();
}

void DMA1_Channel4_IRQHandler() 
	{
		LED();
    if (DMA1->ISR & DMA_ISR_TCIF4)
			{ // Проверка флага завершения передачи
        DMA1->IFCR |= DMA_IFCR_CTCIF4; // Сбрасываем флаг
        // Действия по завершению передачи
      }
		LED();
}

void DMA1_Channel5_IRQHandler() 
{
	LED();
    if (DMA1->ISR & DMA_ISR_TCIF1) 
			{ // Проверяем флаг завершения передачи
        DMA1->IFCR |= DMA_IFCR_CTCIF1; // Сбрасываем флаг
        // Обработка полученных данных
       //ProcessReceivedData(rx_buffer); // Ваш метод обработки
        DMA1_Channel5->CNDTR = 1; // Обновляем количество данных (снова ожидаем 1 байт)
        DMA1_Channel5->CCR |= DMA_CCR1_EN; // Включаем DMA снова
    }
		LED();
}

void ExecutorTerminal()
{
		if (USART1_GetStatus())// Проверка на получение
		{ 
        receivedChar = USART1_ReadChar(); // Читаем

				if(receivedChar==CHAR_COMMAND1)
				{
						snprintf(rezultStr, sizeof rezultStr, "%s command: %c", greetingsStr,receivedChar);
						USART1_SetString(rezultStr);
				}
				else if(receivedChar==CHAR_COMMAND0)
				{
						snprintf(rezultStr, sizeof rezultStr, "%s command: %c", partingStr,receivedChar);
						USART1_SetString(rezultStr);
				}
				else
				{
						snprintf(rezultStr, sizeof rezultStr, "%s: %c", errorStr,receivedChar);
						USART1_SetString(rezultStr);
				}
    }
}
