/**
  ******************************************************************************
  * @file      terminal.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  * @author    Student2
  * @version   V4.1.0
  * @date      05.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institute 4
  * @brief     Exercise robotic arm  with UART-control
  * @details Template - functions to control the serial terminal
  ******************************************************************************
  * @details resources:
  *          - signal router setting: @b 50
  ******************************************************************************
  * @par History:
  *  @details V4.1.0 Ferdinand Englberger
  *           - Pack description updated  
  *  @details V4.0.0 26.05.2015 Ferdinand Englberger
  *           - Use Compiler pack instead of retarget.c  
  *  @details V3.0.0 17.01.2014 Ferdinand Englberger
  *           - CMSIS RTOS API instead of RLARM  
  *  @details V2.1.0 25.11.2012 Ferdinand Englberger
  *           - C99 data types
  *  @details V2.0.0 06.10.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */
#include "stdint.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "LPC17xx.h"                    // Device header
#include "robterminal.h"                // ETTI4::ETTI4:Embedded laboratory:Robotic arm
#include "stdio.h"
#include "stdlib.h"

#define ANZAHL 8

osMessageQDef(STDINmsgQ, ANZAHL, uint32_t);
osMessageQId STDINmsgQ;

osSemaphoreDef(STDOUTsem);
osSemaphoreId STDOUTsem;

osSemaphoreDef(STDINsem);
osSemaphoreId STDINsem;
/**
  * @brief  Function to initialize the terminal interface
  * @details UART0, 19200 Baud, 8, n, 1
  */
void TRMinit(void)
{
	STDINmsgQ = osMessageCreate(osMessageQ(STDINmsgQ), NULL);
	STDOUTsem = osSemaphoreCreate(osSemaphore(STDOUTsem), 1);
	STDINsem = osSemaphoreCreate(osSemaphore(STDINsem), 1);
	
	LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~((3<<6)|(3<<4))) | ((1<<6)|(1<<4));
	LPC_PINCON->PINMODE0 = LPC_PINCON->PINMODE0 & ~((3<<6)|(3<<4));
	LPC_PINCON->PINMODE_OD0 &= ~(1<<2);
	
	LPC_UART0->LCR = 0x80;
	LPC_UART0->DLL = 0xC3;
	LPC_UART0->DLM = 0x00;
	LPC_UART0->FDR = 0x10;
	LPC_UART0->LCR = 0x03;
	LPC_UART0->FCR = 0x01;
	LPC_UART0->IER = 0x1;
	
	NVIC_SetPriority(UART0_IRQn, 14);
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

}

/**
  * @brief  Function to redirect standard output to UART0
  * @param  ch : character to transmit
  * @retval int : transmitted character
  */
int32_t stdout_putchar(int32_t ch)
{	
  if (ch == '\n') {									//Input LF?	==> Stringeingabe (Feld, etc.)
	  while(!(LPC_UART0->LSR & 0x20))
		{
     osThreadYield();
    }
	  LPC_UART0->THR = 0x0D; 					//Output CR
  }
  
	
	if (ch == 0x0D) {									//Input CR? ==> Tastatureingeabe
    while(!(LPC_UART0->LSR & 0x20))
		{
     osThreadYield();
    }
		LPC_UART0->THR = 0x0A; 					//Output LF
  }
	
	
	while(!(LPC_UART0->LSR & 0x20))
	{
   osThreadYield();
  }
	
	
  LPC_UART0->THR = ch;
  return (ch);
}


/**
  * @brief  Function to clear terminal display
  */
void TRMclearDisplay(void)
{
	printf("\x1b[2J"); //\x1b ==> <ESC> KOMMANDO: "<ESC>[2J" löscht Displayinhalt
}


/**
  * @brief Function to set cursor position
  * @details
  * @verbatim
     The terminal itself requires these values
       line   1 -  4
       column 1 - 40
     The parameter value should be different, due to comparability reason 
     with parallel display

     parameter value
       line   0 -  3
       column 0 - 39
    @endverbatim
  * @param  linenr : line position, can be 0 - 3
  * @param  col    : column position, can be 0 - 39
  */
void TRMsetPos (uint32_t linenr, uint32_t col)
{
	printf("\x1b[%d;%df", linenr, col);
}

/**
  * @brief  IRQ-Handler for receiving of the terminal key values
  * @details The received values are transferred using the mailbox.
  *          If the mailbox is full the received value is rejected.
  * @retval None
  */
void UART0_IRQHandler(void)
{
	uint32_t newdata; 
	newdata = LPC_UART0->RBR;
	osMessagePut(STDINmsgQ, newdata, 0);
}


/**
  * @brief  function to redirect standard input to UART0
  * @details Exchange of the key values y and z is required, to meet the 
  *          requirements of a German keyboard.
  * @retval  "received character"
  */

int32_t stdin_getchar(void)
{
	//char input;
	int32_t input;
	osEvent inputMsg = osMessageGet(STDINmsgQ, osWaitForever);
	
	if(inputMsg.status == osEventMessage){
		input = inputMsg.value.v;
	}
		return input;
}
