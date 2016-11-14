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
	E4initHEXSW();
	//initHEXSW();
	E4initMotKeysIRQ();
	//initMotKeysIRQ();
	
	
	osEvent signals;
	signals = osSignalWait(0, osWaitForever);
for(;;){
	
	if(signals.status == osEventSignal){
		
		if(signals.value.signals == SIG_KEY_LEFT_RIGHT){
			if(ActMotorStatus.direction == Right){
				//Semaphore
				ActMotorStatus.direction = Left;
				setDirection(Left);
			}else{
			//if(ActMotorStatus.direction == Left){
				//Semaphore
				ActMotorStatus.direction = Right;
				setDirection(Right);
				
			}
			osSignalClear(keyThreadID, SIG_KEY_LEFT_RIGHT); //Notwendig?
		}
		
		if(signals.value.signals == SIG_KEY_RUNSTOP){
			if(ActMotorStatus.status == Stopped){
				//Semaphore
				ActMotorStatus.status = Run;
			}
			
			if(ActMotorStatus.status == Run){
				//Semaphore
				ActMotorStatus.status = Stopped;
				
			}
			//Semaphore
			setRunStop(&ActMotorStatus);
		
		}
		
		if(signals.value.signals == SIG_KEY_NEWHEX){
			//Semaphore
			ActMotorStatus.speedstep = (LPC_GPIO0->FIOPIN >> 4) & 0xFF;
			updateSpeed(&ActMotorStatus);
		}
	}
	
  

  } // end for
}
