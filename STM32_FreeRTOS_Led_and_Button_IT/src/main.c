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


#define FALSE 0
#define TRUE 1
#define NOT_PRESSED FALSE
#define PRESSED TRUE

//functions prototypes
static void prvSetupHardware(void);
static void prvSetupUart(void);
static void prvSetupGPIO(void);

//task prototypes
void led_task_handler(void *params);
void button_task_handler(void *params);

//global space for some variables
uint8_t button_status_flag = NOT_PRESSED;


int main(void)
{
	DWT -> CTRL |= (1 << 0);//Enable CYCCNT in DWT_CTRL

	// Reset the RCC to 16MHz
	RCC_DeInit();
	//Update the SystemCoreClock variable
	SystemCoreClockUpdate();

	prvSetupHardware();

	//Start recording
	SEGGER_SYSVIEW_Conf();
	SEGGER_SYSVIEW_Start();

	//LED task create
	xTaskCreate(led_task_handler, "LED-TASK", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	//start the scheduler
	vTaskStartScheduler();

	for(;;);
}

void led_task_handler(void *params)
{
	while(1)
	{
		if(button_status_flag == PRESSED)
		{
			//turn on the LED
			GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
		}
		else
		{
			//turn off the LED
			GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
		}
	}
}

void button_handler(void *params)
{
	//making the exor operation with 1 means "toggle status flag"
	button_status_flag ^=1;
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

static void prvSetupGPIO()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	//This function is board specific
	GPIO_InitTypeDef led_init, button_init;

	led_init.GPIO_Mode = GPIO_Mode_OUT;
	led_init.GPIO_OType = GPIO_OType_PP;
	led_init.GPIO_Pin = GPIO_Pin_5;
	led_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	led_init.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOA, &led_init);

	button_init.GPIO_Mode = GPIO_Mode_IN;
	button_init.GPIO_OType = GPIO_OType_PP;
	button_init.GPIO_Pin = GPIO_Pin_13;
	button_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	button_init.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOC, &button_init);

	//Interrupt configuration for the button (PC13)
	//configure the EXTI line (syscfg settings)
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);

	//configure EXTI line 13
	EXTI_InitTypeDef exti_init;
	exti_init.EXTI_Line =  EXTI_Line13 ;
	exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_init.EXTI_Trigger = EXTI_Trigger_Falling;
	exti_init.EXTI_LineCmd = ENABLE ;
	EXTI_Init(&exti_init);

	//NVIC settings (IRQ settings for selected EXTI line(13) wich in STM32F401RE are into EXTI15_10_IRQn group)
	NVIC_SetPriority(EXTI15_10_IRQn, 5);
	NVIC_EnableIRQ(EXTI15_10_IRQn);

}

static void prvSetupHardware(void)
{
	prvSetupGPIO();
	prvSetupUart();
}

//this will overrite the .weak definition that can be found in startup/startup_stm32.s
void EXTI15_10_IRQHandler(void)
{
	//segger systemview command to trace the interrupt visually
	traceISR_ENTER();

	// Clear the interrupt pending bit of the EXTI line (13)
	EXTI_ClearITPendingBit(EXTI_Line13);
	button_handler(NULL);

	//segger systemview command to trace the interrupt visually
	traceISR_EXIT();
}
