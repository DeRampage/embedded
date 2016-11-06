/**
  ******************************************************************************
  * @file      ADCmainPoll.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2  
  * @version   V2.1.0
  * @date      18.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief     Exercise ADC with RTX (part polling)
  ******************************************************************************
  * @par History:
  *  @details V2.1.0 Ferdinand Englberger
  *           - Use new display library V6.0.0   
  *  @details V2.0.0 09.01.2014 Ferdinand Englberger
  *           - Use RTE v1.0.0
  *  @details V1.1.0 18.11.2012 Ferdinand Englberger
  *           - C99 data types   
  *  @details V1.0.0 22.09.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */

#include "max_II_configurator.h" // ETTI4::ETTI4:Embedded laboratory:Configurator
#include "adc_RTX.h"                    // ETTI4::ETTI4:Embedded laboratory:ADC-RTX
#include "ADCdisp.h"                    // ETTI4::ETTI4:Embedded laboratory:ADC-RTX
#include "stdio.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX

#define ANZAHL 5

osThreadDef(heartBeatThread, osPriorityIdle, 1, 0);

////***Solution for Polling***\\\\

osThreadDef(adcPollThread, osPriorityAboveNormal, 1, 0);
extern osThreadId adcPollThreadId;

////***Solution for Simulation***\\\\

//osThreadDef(adcDummyThread, osPriorityAboveNormal, 1, 0);
//extern osThreadId adcDummyThreadId;


osMailQDef(ADCmailQ, ANZAHL, myADCmail_t);
osMailQId ADCmailQ;

ETTI4disp_t myDisplay = {
													.DispType = USE_ETTI4_PARDISPLAY,
													.NrLines  = 4,
													.NrCols   = 20,
													.enHorbar = true
												};
												
/**
  * @brief  Main thread - display of ADC results
  * @retval Errorcode
  */
												
int32_t main(void)
	{
  e4configADC();
		
	////***Initialisierung Display***\\\\
	
	initETTI4display(&myDisplay);
	clearETTI4display(&myDisplay);
	
	////***Ausgabe Startbildschirm***\\\\
	
	printf("    Laboratory \n  Embedded Systems\n   Experiment ADC\n    SW-Polling\n");
	osDelay(20);
	clearETTI4display(&myDisplay);
	
	////***Start Threads***\\\\

  osThreadCreate(osThread(adcPollThread), NULL);
//	osThreadCreate(osThread(adcDummyThread), NULL);

	osThreadCreate(osThread(heartBeatThread), NULL);
	
		
	osEvent mailEvent;
	myADCmail_t *mailTemp;
	ADCmailQ = osMailCreate(osMailQ(ADCmailQ), NULL);
	
  for(;;)
   {
		 ////***SIGNAL an Dummy-Thread***\\\\
		 
//		 osSignalSet(adcDummyThreadId, SIG_ADCTHR_START_ADC);

		 
		 ////***SIGNAL an Poll-Thread***\\\\

		 osSignalSet(adcPollThreadId, SIG_ADCTHR_START_ADC);
		
		 
		 ////***Warten auf Mail vom Dummy-Thread***\\\\
		 
		 mailEvent = osMailGet(ADCmailQ, osWaitForever);
		 
		 if(mailEvent.status == osEventMail){

			 
			 ////***Kopieren in lokale Variable***\\\\
			
			 mailTemp = mailEvent.value.p;

			 
			 ////***Ausgabe am Display***\\\\

		   E4adcDisplay(&myDisplay, mailTemp);
//		 adcDisplay(&myDisplay, mailTemp);
			
			 
			 ////***Freigeben des Speichers***\\\\
   		 
			 osMailFree(ADCmailQ, mailTemp);
		 }
		 osDelay(15); //soll 150
	 }
}
