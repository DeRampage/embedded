/**
  ******************************************************************************
  * @file      DrehzahlMain.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.5.0
  * @date      21.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise engine speed with RTX
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
#include "max_II_configurator.h"  // ETTI4::ETTI4:Embedded laboratory:Configurator
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "EmbSysARMDisp.h"              // ETTI4::ETTI4:Embedded laboratory:Displays
#include "RotationDisplay.h"            // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "drehzahl.h"                   // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "hexsw.h"                      // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "keythread.h"                  // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "rotMotor.h"                   // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "RotationSensor.h"             // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "Motkeys.h"                    // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "stdio.h"

drehzahl_t ActMotorStatus;

/**
  * @brief  main thread Exercise engine speed with RTX
  * @details Thread is used to display values
  */
	
ETTI4disp_t motDisp = {
													.DispType = USE_ETTI4_PARDISPLAY,
													.NrLines = 4,
													.NrCols = 20,
													.enHorbar = false};
osSemaphoreId MotorStatusSem;
osSemaphoreDef(MotorStatusSem);

osThreadDef(RotSensorThread, osPriorityHigh, 1, 0);
osThreadId RotSensorThreadID;													
													
void keyThread(void const* argument);
//void E4keyThread(void const* argument);

													
osThreadDef(keyThread, osPriorityNormal, 1, 0);
osThreadId keyThreadID;													

//osThreadDef(E4keyThread, osPriorityNormal, 1, 0);
//osThreadId keyThreadID;													
	
int32_t main(void)
{    
	e4configDrehzahl();
	
	drehzahl_t oldStatus;
	drehzahl_t newStatus;
	
	NVIC_SetPriorityGrouping(0);
	
	//E4initHEXSW();
	initHEXSW();
	
	//uint32_t temp = E4getHexSW();
	uint32_t temp = getHexSW();
	
  
	ActMotorStatus.status = Stopped;
	ActMotorStatus.direction = Left;
	ActMotorStatus.speedstep = temp;
	ActMotorStatus.drehzahl = 0;
	
	oldStatus.status = Run;
	oldStatus.direction = Right;
	oldStatus.speedstep = 23;
	oldStatus.drehzahl = 10;
	
	//E4initMotor(&ActMotorStatus); 
	initMotor(&ActMotorStatus); 
	
	initETTI4display(&motDisp);
	clearETTI4display(&motDisp);
	printf("    Laboratory\n"
	    	 "  Embedded Systems\n"
			   "    Experiment \n"
				 "    Motor Test\n");
	
  osDelay(2000);
	
	clearETTI4display(&motDisp);
	
		printf("Rotation Measurement\n"
					 "Status:       -     \n"
					 "Speed Step:         \n"
					 "Rotation:      Hz   \n");
	MotorStatusSem = osSemaphoreCreate(osSemaphore(MotorStatusSem), 1);
	
	keyThreadID = osThreadCreate(osThread(keyThread), NULL);
	//keyThreadID = osThreadCreate(osThread(E4keyThread), NULL);
	
	RotSensorThreadID = osThreadCreate(osThread(RotSensorThread), NULL);
	
	osThreadId mainThreadID = osThreadGetId();
	
	osThreadSetPriority(mainThreadID, osPriorityIdle);
	
    for(;;)
    {
				osDelay(250);
				osSemaphoreWait(MotorStatusSem, osWaitForever);
				newStatus = ActMotorStatus;
				osSemaphoreRelease(MotorStatusSem);
			
				updateDisplay(&motDisp, &oldStatus, &newStatus);
			  //E4updateDisplay(&motDisp, &oldStatus, &newStatus);
    }
}
