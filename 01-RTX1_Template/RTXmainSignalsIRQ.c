/**
  ******************************************************************************
  * @file      RTXmainSignalsIRQ.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V4.0.0
  * @date      17.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise RTX - Part events IRQ routines
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

#define SIG_MAIN_SW1 0x0001
#define SIG_MAIN_SW2 0x0002

osThreadId mainThread_ID;

ETTI4disp_t myDisplay = {
		.DispType = USE_TERATERM_UART3_C, 
		.NrLines = 40, 
		.NrCols = 40,
};




/**
  * @brief  main-function
  * @details Config signal router and start of RTOS
  */
int32_t main(void)
{ 
   e4configRTX1();
  
		initETTI4display(&myDisplay);
		clearETTI4display(&myDisplay);
	
		puts("Start of Signal IRQ Program");
		initHW();
		initSW_IRQ();
	
	osEvent signal;
	
	mainThread_ID = osThreadGetId();
	
	 for(;;)
   {
		 signal = osSignalWait(0, 2000);
		// signal = osSignalWait(SIG_MAIN_SW1 | SIG_MAIN_SW2, 2000);
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
