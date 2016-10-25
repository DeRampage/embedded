/**
  ******************************************************************************
  * @file      ea_test7.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.0.0
  * @date      07.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institut 4
  * @brief Template - Program part moving light
  ******************************************************************************
  * @details signal router setting: \b 01
  ******************************************************************************
  *	@par History:
  *  @details V3.0.0 Ferdinand Englberger
  *           - Pack description updated 
  *           - RTOS included    
  *  @details V2.2.0 17.02.2014 Ferdinand Englberger
  *           - copyright clause
  *  @details V2.1.0 02.11.2012 Ferdinand Englberger
  *           - C99 data types   
  *  @details V2.0.0 08.09.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */
#include "alarm.h"                      // ETTI4::ETTI4:Embedded laboratory:GPIO-EA
#include "tastenleds.h"                 // ETTI4::ETTI4:Embedded laboratory:GPIO-EA
#include "possensor.h"                  // ETTI4::ETTI4:Embedded laboratory:GPIO-EA
#include "motor.h"                      // ETTI4::ETTI4:Embedded laboratory:GPIO-EA
#include "alarm.h"                      // ETTI4::ETTI4:Embedded laboratory:GPIO-EA
#include "max_II_configurator.h"        // ETTI4::ETTI4:Embedded laboratory:Configurator


osThreadId IDalarmThread; /*!< Thread Id of alarm key receiption Thread */


void alarmThread(void const *argument);
osThreadDef(alarmThread, osPriorityNormal, 1, 0);

void alarmThread(void const *argument){
	
	osEvent alarm;
	uint32_t alarmButton;
	
	for(;;)
	{
		alarm = osSignalWait(SIG_ALARM_CHANGE, osWaitForever);
		osDelay(20);																							//Nur zum Testen
		alarmButton = getAlarm();
		if(alarm.status == osEventSignal && alarmButton == 1){
			alarmsig(1);
			osDelay(15);
			alarmsig(0);
		}
	}
}

/**
  * @brief  Main Thread
  */
int32_t main(void)
{
	e4configAufzug();
  init_leds_buttons();
	init_alarm();
	NVIC_SetPriorityGrouping(0);

	IDalarmThread = osThreadCreate(osThread(alarmThread), NULL);
	uint32_t button = 1;
	
  for(;;)
  {
		while(getNothalt() != 1){
						
			if(button == 256){
				button = 1;
			}
			osDelay(5);
			setLeds(button);
			button = button << 1;
		}
  }
}



