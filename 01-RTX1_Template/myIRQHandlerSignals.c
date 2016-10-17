/**
  ******************************************************************************
  * @file      myIRQHandlerSignals.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V4.0.0
  * @date      17.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise RTX - IRQ-Handler for interrupt events
  ******************************************************************************
  * @par History:
  *  @details V4.0.0 Ferdinand Englberger
  *           - Use Callback instead of direct IRQ-Handler  
  *  @details V3.0.0 08.01.2014 Ferdinand Englberger
  *           - CMSIS RTOS API instead of RLARM
  *  @details V2.1.0 14.11.2012 Ferdinand Englberger
  *           - C99 data types  
  *  @details V2.0.0 16.09.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */

#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX

#define SIG_MAIN_SW1 0x0001
#define SIG_MAIN_SW2 0x0002

extern osThreadId mainThread_ID; 
/**
  * @brief  Callback functionfor key 1
  * @details The Callback sets a signal for thread main
  */
	
void key1Callback(void)
{
	osSignalSet(mainThread_ID, SIG_MAIN_SW1);
}

/**
  * @brief  Callback functionfor key 2
  * @details The Callback sets a signal for thread main
  */

void key2Callback(void)
{
	osSignalSet(mainThread_ID, SIG_MAIN_SW2);
}
