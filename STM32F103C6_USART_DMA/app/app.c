#include "app.h"

char rezultStr [SIZESTR];
char receivedChar;
char* greetingsStr="Prived STM32F103";
char* partingStr="BayBay STM32F103";
char* errorStr="error command";

uint8_t dataBuf[10];
char buffer[10];
uint8_t buffer1[100]="FTRYDJJS";
int isRun=1;

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
		//USART1_ReceiveData(buffer, sizeof(buffer));
		//USART1_SendData(buffer, sizeof(buffer));
		//
		LED();
}

void USART1_ReceiveData(char *buffer, uint16_t size)
 {
    DMA1_Channel4->CNDTR = size; // Устанавливаем количество данных
    DMA1_Channel4->CMAR = (uint32_t)buffer; // Указываем адрес буфера
    DMA1_Channel4->CPAR = (uint32_t)&(USART1->DR); // Указываем адрес USART
    DMA1_Channel4->CCR |= DMA_CCR1_EN; // Запуск DMA
}

void USART1_SendData(uint8_t *data, uint16_t size) 
{

		
//				while (!(USART1->SR & USART_SR_TXE))//Проверим окончание передачи
//				{
//				}
				USART1->DR = data[0];
    
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
						snprintf(rezultStr, sizeof rezultStr, "%s: %c", errorStr,buffer[0]);
						USART1_SetString(rezultStr);
				}
    }
}
