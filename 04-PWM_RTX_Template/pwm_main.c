/**
  ******************************************************************************
  * @file      pwm_main.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.5.0
  * @date      28.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Template - Exercise PWM-generation with RTX
  ******************************************************************************
  * @par History:
  *  @details V3.5.0 Ferdinand Englberger
  *           - Use display library V6.0.0 and updated pack description      
  *  @details V3.0.0 21.01.2014 Ferdinand Englberger
  *           - CMSIS RTOS API instead of RLARM  
  *  @details V2.1.0 27.11.2012 Ferdinand Englberger
  *           - C99 data types  
  *  @details V2.0.0 20.10.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */
#include "max_II_configurator.h"  // ETTI4::ETTI4:Embedded laboratory:Configurator
#include "pwmRTX.h"                     // ETTI4::ETTI4:Embedded laboratory:PWM and ADC
#include "stdio.h"
#include "EmbSysARMDisp.h"              // ETTI4::ETTI4:Embedded laboratory:Displays
#include "pwmDisplay.h"                 // ETTI4::ETTI4:Embedded laboratory:PWM and ADC
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "pwm_adc.h"                    // ETTI4::ETTI4:Embedded laboratory:PWM and ADC
#include "pwmRTX.h"                     // ETTI4::ETTI4:Embedded laboratory:PWM and ADC
#include "servoPWM.h"                   // ETTI4::ETTI4:Embedded laboratory:PWM and ADC

osThreadId mainThread_ID;

pwm_t pwmControl;

ETTI4disp_t myDisplay = {
													.DispType = USE_ETTI4_PARDISPLAY,
													.NrLines  = 4,
													.NrCols   = 20,
													.enHorbar = true
};

osSemaphoreId access;
osSemaphoreDef(access);

//void adcThread(void const* argument);
osThreadDef(adcThread, osPriorityAboveNormal, 1, NULL);


/**
  * @brief  Main thread
  * @details Thread is used to display the information on LCD
  */
int32_t main(void)
{
  e4configPWM();
  pwm_t	oldPwmCtl;
	pwm_t newPwmCtl;
	
	pwmControl.servo1.advalue = 2048;
	pwmControl.servo1.arc = 0;
	pwmControl.servo1.pw = 1500;
	
	pwmControl.servo2.advalue = 2048;			//////////////////////////////#defines festlegen!!!
	pwmControl.servo2.arc = 0;
	pwmControl.servo2.pw = 1500;
	
	
	
	initETTI4display(&myDisplay);
	clearETTI4display(&myDisplay);
	
	////***Ausgabe Startbildschirm***\\\\
	
	printf("     Laboratory 		\n"
				 "  Embedded Systems	\n"
				 "     Experiment 		\n"
				 "    PWM with RTX 		\n");
	osDelay(20);
	clearETTI4display(&myDisplay);
	
	printf(	"Servo1    ADC: \n"
					"PW:    ms ARC: \n"
					"Servo2    ADC: \n"
					"PW:    ms ARC: \n");
	
	access = osSemaphoreCreate(osSemaphore(access), 1);
	
	osThreadCreate(osThread(adcThread), NULL);
	mainThread_ID = osThreadGetId();
	
	osThreadSetPriority(mainThread_ID, osPriorityIdle);
	
    for(;;)
    {
			newPwmCtl = pwmControl;
			
			//E4updatePWMdisplay(&myDisplay, &oldPwmCtl, &newPwmCtl);		//ggf old and newPwmCtl als Zeiger anlegen...
			updatePWMdisplay(&myDisplay, &oldPwmCtl, &newPwmCtl);
			osDelay(25);
    }
}
