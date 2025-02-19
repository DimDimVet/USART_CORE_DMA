#include "app.h"
int rxData0=0;
int rxData=0;

uint8_t dataBufTx[10]="STM32F103";
uint8_t dataBufRx[10];
	int count=0;


void USART2_IRQHandler(void)
{
	 if(USART_GetITStatus(USART2,USART_IT_RXNE) !=RESET)
	 {
			rxData= USART_ReceiveData(USART2);
	 }
}

void DMA1_Channel4_IRQHandler(void) 
{
    if (DMA1->ISR & DMA_ISR_TCIF4) 
		{
        DMA1->IFCR |= DMA_IFCR_CTCIF4; // Очистка флага
			
//			  // Проверка, завершилась ли передача
//        if (DMA_GetCurrDataCounter(DMA1_Channel4) == 0) 
//					{
//            // Перезапуск передачи
//            count++;
//						if(count<3)
//							{
								
//								dataBufTx[count]='3';
//								DMA_SetCurrDataCounter(DMA1_Channel4, 10);
//								DMA_Cmd(DMA1_Channel4, ENABLE);
//								count=0;
//							} 
//					}
//					else{DMA_Cmd(DMA1_Channel4,DISABLE);}
    }
}

void DMA1_Channel5_IRQHandler() 
{
    if (DMA1->ISR & DMA_ISR_TCIF5) 
		{ // Проверка флага завершения передачи
        DMA1->IFCR |= DMA_IFCR_CTCIF5; // Сбрасываем флаг
        // Обработка полученных данных в rxBuffer
		
			// Перезапуск передачи
								
								DMA_Cmd(DMA1_Channel4,DISABLE);
								dataBufTx[0]=dataBufRx[0];
								DMA_SetCurrDataCounter(DMA1_Channel4, 10);
								DMA_Cmd(DMA1_Channel4, ENABLE);
			
			//DMA_Cmd(DMA1_Channel5,DISABLE);//запустим DMA
//			DMA_Cmd(DMA1_Channel5, DISABLE);
//			DMA_GetCurrDataCounter(DMA1_Channel5);
//			DMA_Cmd(DMA1_Channel5, ENABLE);
    }
}

int main()
{
	USART_INIT();

	DMA_UART_Init(dataBufTx,dataBufRx);
	
	while(1)
	{
		 
	}
}

