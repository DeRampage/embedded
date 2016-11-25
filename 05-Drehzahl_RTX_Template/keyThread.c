/**
  ******************************************************************************
  * @file      keyThread.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.5.0
  * @date      21.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Praktikumsversuch Drehzahlmessung mit RTX  -  Key-Task
  ******************************************************************************
  * @par History:
  *  @details V3.5.0 Ferdinand Englberger
  *           - Use display library V6.0.0 and updated pack description   
  *  @details V3.0.0 21.01.2014 Ferdinand Englberger
  *           - CMSIS RTOS API instead of RLARM
  *  @details V2.0.0 12.10.2011 Ferdinand Englberger
  *           - Template initial version LPC1769
  ******************************************************************************
  */
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "Motkeys.h"                    // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "hexsw.h"                      // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "keythread.h"                  // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "drehzahl.h"                   // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "rotMotor.h"                   // ETTI4::ETTI4:Embedded laboratory:Revolution measurement


extern drehzahl_t ActMotorStatus;
extern osSemaphoreId MotorStatusSem;
/**
  * @brief  Key thread
  * @details Thread controls all keys and switches
  *          - Start/Stop-key
  *          - key for Left/Right rotation
  *          - Hex switch for speed step
  * @param argument : not used
  */
void keyThread(void const *argument)
{
	//E4initHEXSW();
	initHEXSW();
	
	//E4initMotKeysIRQ();
	initMotKeysIRQ();
	
	osEvent signals;
	
  for(;;)
  {
	  
	  signals = osSignalWait(0, osWaitForever);
	  if(signals.status == osEventSignal){
		  if(signals.value.signals & SIG_KEY_LEFT_RIGHT){
			  if(ActMotorStatus.direction == Right){
				osSemaphoreWait(MotorStatusSem, osWaitForever);
				ActMotorStatus.direction = Left;
				osSemaphoreRelease(MotorStatusSem);
				
				setDirection(Left);
				  
			  }else{
				osSemaphoreWait(MotorStatusSem, osWaitForever);
				ActMotorStatus.direction = Right;
				osSemaphoreRelease(MotorStatusSem);
				
				setDirection(Right);
			  }
			  
		  }
		  if(signals.value.signals & SIG_KEY_RUNSTOP){
			  if(ActMotorStatus.status == Stopped){
				osSemaphoreWait(MotorStatusSem, osWaitForever);
				ActMotorStatus.status = Run;
				osSemaphoreRelease(MotorStatusSem); 
			  }else{
				osSemaphoreWait(MotorStatusSem, osWaitForever);
				ActMotorStatus.status = Stopped;
				osSemaphoreRelease(MotorStatusSem);  
			  }
			 
			  
			  setRunStop(&ActMotorStatus);
			  
			  
			  
			  
		  }
		  
		  if(signals.value.signals & SIG_KEY_NEWHEX){
			  
				osSemaphoreWait(MotorStatusSem, osWaitForever);
				//ActMotorStatus.speedstep = E4getHexSW();
			    ActMotorStatus.speedstep = getHexSW();
				osSemaphoreRelease(MotorStatusSem); 
				updateSpeed(&ActMotorStatus);
			  }
	  }

  } // end for
}
