/**
  ******************************************************************************
  * @file      RTXmainTime.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V4.0.0
  * @date      17.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise RTX - Part time management routines
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
#include "cmsis_os.h"
#include "myHW.h"                       // ETTI4::ETTI4:Embedded laboratory:RTX


void ledblink2(void const *argument);
osThreadDef(ledblink2, osPriorityNormal, 1, 0);


/**
  * @brief  Thread - blink LED
  * @param argument : not used
  */
void ledblink2(void const * argument)
{

   for(;;)
   {
		setLED2(1);
		osDelay(750);
		setLED2(0);
		osDelay(750);
   }
}


/**
  * @brief  main thread
  * @details Config signal router and blinks led
  */
int32_t main(void)
{
   e4configRTX1();
   initHW();
	 
	 osThreadCreate(osThread(ledblink2), NULL);
  
   for(;;)
   {
		setLED1(1);
		osDelay(500);
		setLED1(0);
		osDelay(500);
		 
   }
}
