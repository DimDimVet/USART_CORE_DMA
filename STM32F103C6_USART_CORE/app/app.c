#include "app.h"

char rezultStr [SIZESTR];
char receivedChar;
char* greetingsStr="Prived STM32F103";
char* partingStr="BayBay STM32F103";
char* errorStr="error command";

int main()
{
	Init_USART();

	while(1)
	{

	}
	return 0;
}

void USART2_IRQHandler(void)
{
		LED();
		//
		ExecutorTerminal();
		//
		LED();
}

void ExecutorTerminal()
{
		if (USART2_GetStatus())// Проверка на получение
		{ 
        receivedChar = USART2_ReadChar(); // Читаем
				if(receivedChar==CHAR_COMMAND1)
				{
						snprintf(rezultStr, sizeof rezultStr, "%s command: %c", greetingsStr,receivedChar);
						USART2_SetString(rezultStr);
				}
				else if(receivedChar==CHAR_COMMAND0)
				{
						snprintf(rezultStr, sizeof rezultStr, "%s command: %c", partingStr,receivedChar);
						USART2_SetString(rezultStr);
				}
				else
				{
						snprintf(rezultStr, sizeof rezultStr, "%s: %c", errorStr,receivedChar);
						USART2_SetString(rezultStr);
				}
    }
}
