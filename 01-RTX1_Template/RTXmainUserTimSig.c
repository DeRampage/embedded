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
#include "cmsis_os.h"
#include "myHW.h"
#include "mySignals.h"                  // ETTI4::ETTI4:Embedded laboratory:RTX

/*Konstanten für die Zeit*/
#define LEDW1 150
#define LEDW2 100

/*Globale Variablen für den Zustand*/
uint32_t SIG_VAR1=0;
uint32_t SIG_VAR2=0;

osThreadId mainID;
void led1Callback(void const * arg);
void led2Callback(void const * arg);

osTimerDef (myPeriodTimer1, led1Callback);
osTimerId myPeriodTimer1;

osTimerDef (myPeriodTimer2, led2Callback);
osTimerId myPeriodTimer2;

/**
  * @brief Callback function of led1 user timer
  * @param arg : Pointer to parameter variable (not used)
  */
void led1Callback(void const * arg)
{
	osSignalSet(mainID,SIG_MAIN_LED1);
}

/**
  * @brief Callback function of led2 user timer
  * @param arg : Pointer to parameter variable (not used)
  */
void led2Callback(void const * arg)
{
	osSignalSet(mainID,SIG_MAIN_LED2);
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
	
	 myPeriodTimer1 = osTimerCreate(osTimer(myPeriodTimer1), osTimerPeriodic, NULL);
	 myPeriodTimer2 = osTimerCreate(osTimer(myPeriodTimer2), osTimerPeriodic, NULL);
	
	 osTimerStart(myPeriodTimer1, LEDW1);
	 osTimerStart(myPeriodTimer2, LEDW2);
   for(;;)
   {
		 event=osSignalWait(NULL, osWaitForever);
		 if(event.value.signals & SIG_MAIN_LED1)
		 {
			 if(SIG_VAR1==0)
			 {
				setLED1(1);
				SIG_VAR1=1;
			 }
			 else
			 {
				setLED1(0);
				SIG_VAR1=0;
			 }
		 }
		 else
		 {
			 if(SIG_VAR2==0)
			 {
				setLED2(1);
				SIG_VAR2=1;
			 }
			 else
			 {
				setLED2(0);
				SIG_VAR2=0;
			 }
		 }
   }
}
