/**
  ******************************************************************************
  * @file      RTXmainMailQueue.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V4.0.0
  * @date      17.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief     Exercise RTX - Part mail queue routines
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
#include "EmbSysARMDisp.h"              // ETTI4::ETTI4:Embedded laboratory:Displays
#include "stdio.h"
#include "cmsis_os.h"
#include "myHW.h"
#include "LPC17xx.h"                    // Device header


								
	ETTI4disp_t myDisplay = {
	.DispType = USE_TERATERM_UART0,
	.NrLines = 25,
	.NrCols = 80,
};

#define NUMBER 25

osMailQDef(myMail, NUMBER, myMailQ_t);
osMailQId myMail;


/**
  * @brief  main thread
  * @details Config signal router and output thread for PC-terminal
  */
int32_t main(void)
{
  
   e4configRTX1();
	
	 initETTI4display (&myDisplay); 
	 clearETTI4display(&myDisplay);
	 printf("Start of Mail Queue Program\n");
	
	 initSW_IRQ();
	 initHW();
	 osEvent event;
	 myMailQ_t *mailptr; 	 
	
	 myMail = osMailCreate(osMailQ(myMail), NULL);
	
	
   for(;;)
   {
		 printf("==============\n");
		 
		 
		 event = osMailGet(myMail, 100);
		 
			if(event.status == osEventMail){
				
				printf("Mail arrived\n");
		 
		 
				mailptr = event.value.p;		//Enthält den Zeiger zur Nachricht ?? Zur Struktur???
		 
					
				printf("Switch: %d\n", mailptr->SW);
				printf("Value: %d\n", mailptr->value);
				
			 
		 
				if(mailptr->SW == 1){
					printf("SW1  (DIP) -> 0x%02X \n", mailptr->value);
					osMailFree(myMail, mailptr);
				}
				if(mailptr->SW == 2){
					printf("SW2  (HEX) -> 0x%02X \n", mailptr->value);
					osMailFree(myMail, mailptr);
				}
			}else{
				printf("Timeout\n");
			}

   }
}
