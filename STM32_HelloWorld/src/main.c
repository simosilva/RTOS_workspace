/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h> //for memset
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

//some macros
#define TRUE 1
#define FALSE 0
#define AVAILABLE TRUE
#define NOT_AVAILABLE FALSE

TaskHandle_t xTaskHandle1=NULL;
TaskHandle_t xTaskHandle2=NULL;

//functions prototypes
void vTask1_handler(void *params);
void vTask2_handler(void *params);

static void prvSetupHardware(void);
static void prvSetupUart(void);

void printmsg(char *msg);

//global variable section
char usr_msg[250]={0};
uint8_t UART_ACCESS_KEY = AVAILABLE;


int main(void)
{
	//used for semi-hosting, do not used by default
#ifdef USE_SEMIHOSTING
	extern void initialise_monitor_handles();
	printf("HELLOWORD EXAMPLE CODE\n");
#endif

	DWT -> CTRL |= (1 << 0);//Enable CYCCNT in DWT_CTRL

	// Reset the RCC to 16MHz
	RCC_DeInit();
	//Update the SystemCoreClock variable
	SystemCoreClockUpdate();

	prvSetupHardware();

	sprintf(usr_msg, "This is our first string for the USART2 shoutout\r\n");
	printmsg(usr_msg);

	//Start recording
	SEGGER_SYSVIEW_Conf();
	SEGGER_SYSVIEW_Start();

	//create 2 tasks
	xTaskCreate( vTask1_handler, "Task-1", configMINIMAL_STACK_SIZE, NULL, 2, &xTaskHandle1 );
	xTaskCreate( vTask2_handler, "Task-2", configMINIMAL_STACK_SIZE, NULL, 2, &xTaskHandle2 );

	// Start the scheduler
	vTaskStartScheduler();

	//Scheduler will never return so never fall in these section here

  // Hello Word ADV 16/03/2021
	for(;;);
}

void vTask1_handler(void *params)
{
	while(1)
	{
		if(UART_ACCESS_KEY == AVAILABLE)
		{
			UART_ACCESS_KEY = NOT_AVAILABLE;
			printmsg("Hello Task 1 here!\n\r");
			UART_ACCESS_KEY = AVAILABLE;
			SEGGER_SYSVIEW_Print("Task1 is yelding");
			traceISR_EXIT_TO_SCHEDULER();
			taskYIELD();
		}

	}
}

void vTask2_handler(void *params)
{
	while(1)
	{
		if(UART_ACCESS_KEY == AVAILABLE)
		{
			UART_ACCESS_KEY = NOT_AVAILABLE;
			printmsg("Hello Task 2 here!\n\r");
			UART_ACCESS_KEY = AVAILABLE;
			SEGGER_SYSVIEW_Print("Task1 is yelding");
			traceISR_EXIT_TO_SCHEDULER();
			taskYIELD();
		}
	}
}

static void prvSetupUart(void)
{
	GPIO_InitTypeDef gpio_uart_pins;
	USART_InitTypeDef uart2_init;

	//Enable USART2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE );
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE );

	//PA2 UART2_TX, PA3 UART2_RX
	//zeroing all the data in the structure since are in local variables and can also be garbage if not initialized
	memset(&gpio_uart_pins, 0, sizeof(gpio_uart_pins));
	//Alternate functionality
	gpio_uart_pins.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	gpio_uart_pins.GPIO_Mode = GPIO_Mode_AF;
	gpio_uart_pins.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &gpio_uart_pins);

	//AF (Alternte Functionality) for the pins
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); //PA2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); //PA3

	//zeroeas all the data in the structure since are in local variables and can also be garbage if not initialized
	memset(&uart2_init, 0, sizeof(uart2_init));
	//UART parameter initialization
	uart2_init.USART_BaudRate = 115200;
	uart2_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart2_init.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	uart2_init.USART_Parity = USART_Parity_No;
	uart2_init.USART_StopBits = USART_StopBits_1;
	uart2_init.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &uart2_init);

	//Enable the USART2 Peripheral
	USART_Cmd(USART2, ENABLE);
}

static void prvSetupHardware(void)
{
	prvSetupUart();
}

void printmsg(char *msg)
{
	for(uint32_t i=0; i < strlen(msg); i++ )
	{
		//whait until transmit buffer register is SET
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) != SET );
		//actually send the current char of the msg
		USART_SendData(USART2, msg[i]);
	}

}
