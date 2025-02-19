#include "init_USART.h"

//DMA_InitTypeDef DMA_InitStruct;
//uint32_t dataBuf[10];//просто массив
/*
USART2_TX PA2
USART2_RX PA3
*/
void USART_INIT()
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//
	USART_DeInit(USART2);
	
	GPIO_InitTypeDef GPIO_USART_TX;
	GPIO_USART_TX.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_USART_TX.GPIO_Pin=GPIO_Pin_2;
	GPIO_USART_TX.GPIO_Speed=GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOA,&GPIO_USART_TX);
	
	GPIO_InitTypeDef GPIO_USART_RX;
	GPIO_USART_RX.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_USART_RX.GPIO_Pin=GPIO_Pin_3;
	GPIO_USART_RX.GPIO_Speed=GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOA,&GPIO_USART_RX);
	//
	USART_InitTypeDef USART2_INIT;
	USART2_INIT.USART_BaudRate=9600;
	USART2_INIT.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART2_INIT.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART2_INIT.USART_Parity=USART_Parity_No;
	USART2_INIT.USART_StopBits=USART_StopBits_1;
	USART2_INIT.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART2,&USART2_INIT);
	USART_Cmd(USART2,ENABLE);
	
	//
    NVIC_InitTypeDef NVIC_USART_InitStr;
    NVIC_USART_InitStr.NVIC_IRQChannel=USART2_IRQn;//ждем прерывание от канала 2
    NVIC_USART_InitStr.NVIC_IRQChannelPreemptionPriority=0; //приоритет самый высокий
    NVIC_USART_InitStr.NVIC_IRQChannelSubPriority=0;//приоритет самый высокий
    NVIC_USART_InitStr.NVIC_IRQChannelCmd=ENABLE;//разрешение прерывания

    NVIC_Init(&NVIC_USART_InitStr);
		
		//
		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		
		NVIC_EnableIRQ(USART2_IRQn);
}

void USART2_SetData(int data)
{
	USART_SendData(USART2,data);
}

void DMA_UART_Init(uint8_t *dataBufTx, uint8_t *dataBufRx)
{
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//
 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
 
// USART_DeInit(USART1);
//	
//	GPIO_InitTypeDef GPIO_USART_TX;
//	GPIO_USART_TX.GPIO_Mode=GPIO_Mode_AF_PP;
//	GPIO_USART_TX.GPIO_Pin=GPIO_Pin_9;
//	GPIO_USART_TX.GPIO_Speed=GPIO_Speed_2MHz;
//	
//	GPIO_Init(GPIOA,&GPIO_USART_TX);
	
	GPIOA->CRH |= (GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1); // TX
    GPIOA->CRH |= (GPIO_CRH_CNF10_0); // RX
	
//	GPIO_InitTypeDef GPIO_USART_RX;
//	GPIO_USART_RX.GPIO_Mode=GPIO_Mode_IN_FLOATING;
//	GPIO_USART_RX.GPIO_Pin=GPIO_Pin_10;
//	GPIO_USART_RX.GPIO_Speed=GPIO_Speed_2MHz;
//	
//	GPIO_Init(GPIOA,&GPIO_USART_RX);
	//
//	USART_InitTypeDef USART1_INIT;
//	USART1_INIT.USART_BaudRate=9600;
//	USART1_INIT.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
//	USART1_INIT.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
//	USART1_INIT.USART_Parity=USART_Parity_No;
//	USART1_INIT.USART_StopBits=USART_StopBits_1;
//	USART1_INIT.USART_WordLength=USART_WordLength_8b;
//	
//	USART_Init(USART1,&USART1_INIT);
//	USART_Cmd(USART1,ENABLE);
USART1->BRR = SystemCoreClock/9600; // SystemCoreClock/Baudrate 
		USART1->CR1 |= USART_CR1_UE ; // Включить USART
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE ; // Включить TX, RX
		USART1->CR1 |= USART_CR1_RXNEIE; // Включить прерывание
	
 /*DMA_InitTypeDef DMA1_UsartInit;
 DMA1_UsartInit.DMA_PeripheralBaseAddr=(uint32_t)&(USART1->DR);//получим адрес usarta
 DMA1_UsartInit.DMA_MemoryBaseAddr=(uint32_t)&dataBuf[0];//получим адрес массива
 DMA1_UsartInit.DMA_DIR=DMA_DIR_PeripheralDST;//направления передачи из памяти в перефирию
 DMA1_UsartInit.DMA_BufferSize=10;//размер буфера = размеру массива
 DMA1_UsartInit.DMA_MemoryInc = DMA_MemoryInc_Enable;//включим режим перебора(в данном случае массива)
 DMA1_UsartInit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;//укажем режим передачи данных в перефирии - байты
 DMA1_UsartInit.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;//укажем режим хранения данных в памяти - байты*/
 
		DMA_InitTypeDef DMA_InitStruct;
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
    DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)dataBufTx; // ваш массив
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStruct.DMA_BufferSize = 10; // длина вашего массива
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;

		DMA1_Channel4->CCR |= DMA_CCR4_TCIE;// разрешение прерывания3
		
    DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
		//DMA_InitStruct.DMA_Mode = DMA_Mode_Circular; // Цикличный режим
		
    DMA_InitStruct.DMA_Priority = DMA_Priority_High;
    DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel4, &DMA_InitStruct);
	
	//
	DMA_Cmd(DMA1_Channel4,ENABLE);//запустим DMA
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);//переключим усарт на работу с дма
		
	DMA1->IFCR |= DMA_IFCR_CTCIF4;//сбрасываем флаг прерывания
	NVIC_EnableIRQ(DMA1_Channel4_IRQn); // Включение прерываний DMA
	
	//
	
//		DMA_InitTypeDef DMA_InitStructRx;
//    DMA_InitStructRx.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
//    DMA_InitStructRx.DMA_MemoryBaseAddr = (uint32_t)&dataBufRx; // ваш массив
//    DMA_InitStructRx.DMA_DIR = DMA_DIR_PeripheralSRC;
//    DMA_InitStructRx.DMA_BufferSize = 10; // длина вашего массива
//    //DMA_InitStructRx.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//    DMA_InitStructRx.DMA_MemoryInc = DMA_MemoryInc_Enable;
//    DMA_InitStructRx.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//    DMA_InitStructRx.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;

//		DMA1_Channel5->CCR |= DMA_CCR5_TCIE;// разрешение прерывания3

//    DMA_InitStructRx.DMA_Mode = DMA_Mode_Normal;
//		//DMA_InitStructRx.DMA_Mode = DMA_Mode_Circular; // Цикличный режим
//		
//    DMA_InitStructRx.DMA_Priority = DMA_Priority_High;
//    DMA_InitStructRx.DMA_M2M = DMA_M2M_Disable;
//    DMA_Init(DMA1_Channel5, &DMA_InitStructRx);

	  DMA1_Channel5->CCR |= (DMA_CCR5_PL_0 | DMA_CCR5_PSIZE | DMA_CCR5_PINC | DMA_CCR5_CIRC); // Высокий приоритет, инкремент, циклический режим
    DMA1_Channel5->CNDTR = 10; // Количество данных
    DMA1_Channel5->CPAR = (uint32_t)&USART1->DR; // Адрес регистра данных USART
    DMA1_Channel5->CMAR = (uint32_t)dataBufRx; // Адрес буфера
		DMA1_Channel5->CCR |= DMA_CCR5_TCIE;// разрешение прерыван
    DMA1_Channel5->CCR |= DMA_CCR5_EN; // Включение канала DMA

	//
	//DMA_Cmd(DMA1_Channel5,ENABLE);//запустим DMA
	//USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);//переключим усарт на работу с дма
		USART1->CR3 |=USART_CR3_DMAR;
	//
	//DMA1->IFCR |= DMA_IFCR_CTCIF5;//сбрасываем флаг прерывания
	NVIC_EnableIRQ(DMA1_Channel5_IRQn); // Включение прерываний DMA
}


//    DMA1_Channel4->CCR |= (DMA_CCR4_PL_0 | DMA_CCR4_MINC | DMA_CCR4_DIR); // Высокий приоритет, инкремент, направление: память -> перIPHERAL
//    DMA1_Channel4->CNDTR = BUFFER_SIZE; // Количество данных
//    DMA1_Channel4->CPAR = (uint32_t)&USART1->DR; // Адрес регистра данных USART
//    DMA1_Channel4->CMAR = (uint32_t)txBuffer; // Адрес буфера
//    DMA1_Channel4->CCR |= DMA_CCR4_EN; // Включение канала DMA

//		DMA1_Channel5->CCR |= (DMA_CCR5_PL_0 | DMA_CCR5_MINC | DMA_CCR5_CIRC); // Высокий приоритет, инкремент, циклический режим
//    DMA1_Channel5->CNDTR = BUFFER_SIZE; // Количество данных
//    DMA1_Channel5->CPAR = (uint32_t)&USART1->DR; // Адрес регистра данных USART
//    DMA1_Channel5->CMAR = (uint32_t)rxBuffer; // Адрес буфера
//    DMA1_Channel5->CCR |= DMA_CCR5_EN; // Включение канала DMA
