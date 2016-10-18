/**
  ******************************************************************************
  * @file      RTXmainUserTimSig.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2  
  * @version   V4.1.0
  * @date      20.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institute 4
  * @brief   Exercise RTX - Part User timer with Signals
  ******************************************************************************
  * @par History:
  *  @details V4.0.0 Ferdinand Englberger
  *           - Initial version
  ******************************************************************************
  */
#include "max_II_configurator.h"  // ETTI4::ETTI4:Embedded laboratory:Configurator
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "myHW.h"  
#include "mySignals.h"                  // ETTI4::ETTI4:Embedded laboratory:RTX

#define LEDW1 750
#define LEDW2	500

osThreadId mainID;

void led1Callback(void const * arg);
void led2Callback(void const * arg);
	
osTimerDef(led1Timer, led1Callback);
osTimerId led1Timer;

osTimerDef(led2Timer, led2Callback);
osTimerId led2Timer;

/**
  * @brief Callback function of led1 user timer
  * @param arg : Pointer to parameter variable (not used)
  */
void led1Callback(void const * arg)
{
	osSignalSet(mainID, SIG_MAIN_LED1);
}

/**
  * @brief Callback function of led2 user timer
  * @param arg : Pointer to parameter variable (not used)
  */
void led2Callback(void const * arg)
{
	osSignalSet(mainID, SIG_MAIN_LED2);
}


/**
  * @brief  Main thread
  * @details Config signal router and blinks led
  */
int32_t main(void)
{
  
   e4configRTX1();
	
	initHW();
	
	osEvent event;
	mainID = osThreadGetId();
	
	static uint32_t SIG_VAR1 = 0;
	static uint32_t SIG_VAR2 = 0;
	
	led1Timer = osTimerCreate(osTimer(led1Timer), osTimerPeriodic, NULL);
	led2Timer = osTimerCreate(osTimer(led2Timer), osTimerPeriodic, NULL);
  
	osTimerStart(led1Timer, LEDW1); 
	osTimerStart(led2Timer, LEDW2); 
	
	
   for(;;)
   {
		 event = osSignalWait(0, osWaitForever);
		 
		 if(event.value.signals & SIG_MAIN_LED1){
			 if(SIG_VAR1 == 0){
				 setLED1(1);
				 SIG_VAR1 = 1;
			 }else{
				 setLED1(0);
				 SIG_VAR1 = 0;
			 }
			 			 
		 }
		 if(event.value.signals & SIG_MAIN_LED2){
			 
			 if(SIG_VAR2 == 0){
				 setLED2(1);
				 SIG_VAR2 = 1;
			 }else{
				 setLED2(0);
				 SIG_VAR2 = 0;
			 }
		 } 
   }
}
