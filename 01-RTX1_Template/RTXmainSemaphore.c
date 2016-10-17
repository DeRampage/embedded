/**
  ******************************************************************************
  * @file      RTXmainSemaphore.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V4.0.0
  * @date      17.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise RTX - Part semaphore routines
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
#include "stdio.h"



/**
  * @brief  Thread - send thread
  * @param argument : not used
  */
	
void sendThread(void const *argument);
osThreadDef(sendThread, osPriorityNormal, 1, NULL);

osSemaphoreId display;
osSemaphoreDef(display);


ETTI4disp_t myDisplay = {
	.DispType = USE_TERATERM_UART0,
	.NrLines = 25,
	.NrCols = 80,
};

	
void sendThread(void const * argument)
{
   for(;;)
   {
		osSemaphoreWait(display, osWaitForever); 
		puts("Message from send Thread");
		osSemaphoreRelease(display);
   }
}


/**
  * @brief  main thread
  * @details Config signal router and send messages
  */
int32_t main(void)
{
   e4configRTX1();
	 
   initETTI4display (&myDisplay); 

	 
	
	 display = osSemaphoreCreate(osSemaphore(display), 1);
	 osThreadCreate(osThread(sendThread), NULL);
	
   for(;;)
   {
		osSemaphoreWait(display, osWaitForever); 
		puts("Hello from main Tread");
		osSemaphoreRelease(display); 
   }
}



//CODE OHNE SEMAPHORE
/*

#include "max_II_configurator.h" // ETTI4::ETTI4:Embedded laboratory:Configurator
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX

#include "EmbSysARMDisp.h"              // ETTI4::ETTI4:Embedded laboratory:Displays
#include "stdio.h"




	
void sendThread(void const *argument);
osThreadDef(sendThread, osPriorityNormal, 1, NULL);



ETTI4disp_t myDisplay = {
	.DispType = USE_TERATERM_UART0,
	.NrLines = 25,
	.NrCols = 80,
};

	
void sendThread(void const * argument)
{
   for(;;)
   {
		puts("Message from send Thread");
   }
}



int32_t main(void)
{
   e4configRTX1();
	 
   initETTI4display (&myDisplay); 

	 osThreadCreate(osThread(sendThread), NULL);
	
   for(;;)
   {
		puts("Hello from main Tread");
   }
}
*/