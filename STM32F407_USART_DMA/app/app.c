#include "app.h"


int main()
{
	Init_USART(BAUND_RATE);

	while(1)
	{

	}
	return 0;
}

void USART1_IRQHandler(void)
{
		LED();
		//
		ExecutorTerminal();
		//
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
