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
	Config_DMA1();
	
	while(1)
	{

	}
	return 0;
}

void DMA1_Channel4_IRQHandler(void) 
{
    if (DMA1->ISR & DMA_ISR_TCIF4) 
		{
        DMA1->IFCR |= DMA_IFCR_CTCIF4; // Очистка флага
				LED();
    }
}

void DMA1_Channel5_IRQHandler() 
{
		ExecutorTerminal();
	  //
		LED();
}

void ExecutorTerminal()
{
		if (DMA1_GetStatus())// Проверка на получение
		{ 
        receivedChar = DMA1_ReadChar(); // Читаем

				if(receivedChar==CHAR_COMMAND1)
				{
						snprintf(rezultStr, sizeof rezultStr, "%s command: %c", greetingsStr,receivedChar);
						DMA1_SetString(rezultStr);
				}
				else if(receivedChar==CHAR_COMMAND0)
				{
						snprintf(rezultStr, sizeof rezultStr, "%s command: %c", partingStr,receivedChar);
						DMA1_SetString(rezultStr);
				}
				else
				{
						snprintf(rezultStr, sizeof rezultStr, "%s: %c", errorStr,receivedChar);
						DMA1_SetString(rezultStr);
				}
    }
}
