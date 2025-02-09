#include "app.h"

char receivedChar;

void USART2_IRQHandler(void)
{
    if (USART2->SR & USART_SR_RXNE)// Проверка на получение данных
		{ 
        receivedChar = USART2->DR; // Чтение данных
        USART2_SendChar(receivedChar); // Эхо символа
				LED();
    }
}

int main()
{

	Init_USART();

	while(1)
	{
		//LED();
		delay_ms(300);//ждем
		
	}
	return 0;
}

