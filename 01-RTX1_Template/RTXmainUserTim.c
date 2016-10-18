/**
  ******************************************************************************
  * @file      RTXmainUserTim.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2    
  * @version   V4.1.0
  * @date      20.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institute 4
  * @brief   Exercise RTX - Part User timer
  ******************************************************************************
  * @par History:
  *  @details V4.0.0 Ferdinand Englberger
  *           - Initial version
  ******************************************************************************
  */
#include "max_II_configurator.h"  // ETTI4::ETTI4:Embedded laboratory:Configurator
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "myHW.h"                       // ETTI4::ETTI4:Embedded laboratory:RTX

void led1Callback(void const * arg);
void led2Callback(void const * arg);

osTimerDef(led1Timer, led1Callback);
osTimerId led1Timer;
//uint32_t led1 = 0;

osTimerDef(led2Timer, led2Callback);
osTimerId led2Timer;
//uint32_t led2 = 0;


/**
  * @brief Callback function of led1 user timer
  * @param arg : Pointer to parameter variable (not used)
  */
void led1Callback(void const * arg)
{
	static uint32_t led1 = 0;

	if(led1 == 0){
		setLED1(1);
		led1 = 1;
	}else{
		setLED1(0);
		led1 = 0;
	}
}

/**
  * @brief Callback function of led2 user timer
  * @param arg : Pointer to parameter variable (not used)
  */
void led2Callback(void const * arg)
{
	static uint32_t led2 = 0;
	
	if(led2 == 0){
		setLED2(1);
		led2 = 1;
	}else{
		setLED2(0);
		led2 = 0;
	}
}


/**
  * @brief  Main thread
  * @details Config signal router and blinks led
  */
int32_t main(void)
{
   e4configRTX1();
  
	initHW();
	
	led1Timer = osTimerCreate(osTimer(led1Timer), osTimerPeriodic, NULL);
	led2Timer = osTimerCreate(osTimer(led2Timer), osTimerPeriodic, NULL);
	
	osTimerStart(led1Timer, 1000);
	osTimerStart(led2Timer, 1500);
	
   for(;;)
   {
		 osDelay(osWaitForever);
   }
}
