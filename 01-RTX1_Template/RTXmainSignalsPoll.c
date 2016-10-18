/**
  ******************************************************************************
  * @file      RTXmainSignalsPoll.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V4.0.0
  * @date      17.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise RTX - Part events polling routines
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
#include "stdio.h"
#include "EmbSysARMDisp.h"              // ETTI4::ETTI4:Embedded laboratory:Displays
#include "myHW.h"                       // ETTI4::ETTI4:Embedded laboratory:RTX


#define SIG_MAIN_SW1 0x0001
#define SIG_MAIN_SW2 0x0002

osThreadId mainThread_ID;

ETTI4disp_t myDisplay = {
		.DispType = USE_TERATERM_UART3_C, 
		.NrLines = 40, 
		.NrCols = 40,
};


void pollSW1(void const * argument);
osThreadDef(pollSW1, osPriorityNormal, 1, NULL);

void pollSW2(void const * argument);
osThreadDef(pollSW2, osPriorityNormal, 1, NULL);



/**
  * @brief  Polling thread for key 1
  * @param argument : not used
  */
void pollSW1(void const * argument)
{

	uint32_t pushsw1;
	uint32_t sw1;
	
   for(;;)
   {
		sw1 = getSW1();
		 
		if(sw1 == 0){
			pushsw1 = 0;
		}
		if(pushsw1 == 0 && sw1 == 1){
			osSignalSet(mainThread_ID, SIG_MAIN_SW1);
			pushsw1 = sw1;
		}
		
		osDelay(20);
		
   }
}

/**
  * @brief  Polling thread for key 2
  * @param argument : not used
  */


void pollSW2(void const * argument)
{
  uint32_t pushsw2;
	uint32_t sw2;
	
   for(;;)
   {
		sw2 = getSW2();
		if(sw2 == 1){
			pushsw2 = 1;
		}
		if(pushsw2 == 1 && sw2 == 0){
			osSignalSet(mainThread_ID, SIG_MAIN_SW2);
			pushsw2 = sw2;
		}
		
		osDelay(20);
		
   }
}


/**
  * @brief  main thread
  * @details Config signal router and start of RTOS
  */
int32_t main(void)
{
 
   e4configRTX1(); 

		initETTI4display(&myDisplay);
		clearETTI4display(&myDisplay);
	
		puts("Start of Signal Poll Program");
		
		osEvent signal;
		mainThread_ID = osThreadGetId();
		osThreadCreate(osThread(pollSW1), NULL);
	  osThreadCreate(osThread(pollSW2), NULL);
		
   for(;;)
   {
		// signal = osSignalWait(0, 2000);
		 signal = osSignalWait(SIG_MAIN_SW1 | SIG_MAIN_SW2, 2000);
		 if(signal.status == osEventSignal){
			 if(signal.value.signals & SIG_MAIN_SW1){
				 puts("New SW1 Signal");
			 }
			 if(signal.value.signals & SIG_MAIN_SW2){
				 puts("New SW2 Signal");
			 }
			 
		 }else{
			 puts("Timeout 2 seconds");
		 }
		 
   }
}
