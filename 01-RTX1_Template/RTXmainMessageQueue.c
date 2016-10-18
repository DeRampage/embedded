/**
  ******************************************************************************
  * @file      RTXmainMessageQueue.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V4.0.0
  * @date      17.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise RTX - Part message queue
  ******************************************************************************
  * @par History:
  *  @details V4.0.0 Ferdinand Englberger
  *           - Comments updated  
  *  @details V3.0.0 08.01.2014 Ferdinand Englberger
  *           - CMSIS RTOS API instead of RLARM
  *  @details V2.1.0 14.11.2012 Ferdinand Englberger
  *           - C99 data types  
  *  @details V2.0.0 16.09.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */

#include "max_II_configurator.h" // ETTI4::ETTI4:Embedded laboratory:Configurator
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "EmbSysARMDisp.h"              // ETTI4::ETTI4:Embedded laboratory:Displays
#include "myHW.h"                       // ETTI4::ETTI4:Embedded laboratory:RTX
#include "LPC17xx.h"                    // Device header
#include "stdio.h"

ETTI4disp_t myDisplay = {
		.DispType = USE_TERATERM_UART3_C, 
		.NrLines = 40, 
		.NrCols = 40,
};

#define NUMBER 25

osMessageQDef(myMessage, NUMBER, uint32_t);
osMessageQId myMessage;



/**
  * @brief  main thread
  * @details Config signal router and output thread for PC-terminal
  */
int32_t main(void)
{
  
   e4configRTX1();
		
	initHW();
	initSW_IRQ();
	
	initETTI4display(&myDisplay);
	clearETTI4display(&myDisplay);
	printf("Start of Message Program\n");
	
	osEvent event;
	
	myMsgQ_t message;
	
	myMessage = osMessageCreate(osMessageQ(myMessage), NULL); 
	
   for(;;)
   {

		 event = osMessageGet(myMessage, 2000);
		 
		 if(event.status == osEventMessage){
			 
			 message.msgQMsg = event.value.v;
			 
			 if(message.content.SW == 1){
				 printf("SW1 (DIP) -> 0x%02X \n", message.content.value);
			 }
			 
			 if(message.content.SW == 2){
				 printf("SW2 (HEX) -> 0x%02X \n", message.content.value);
			 }
			 
		 }else{
			 printf("Timeout 2 seconds\n");
		 }
		 
   }
}

