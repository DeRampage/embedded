/**
  ******************************************************************************
  * @file      ADCmainIRQ.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2  
  * @version   V2.1.0
  * @date      18.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise ADC with RTX (part IRQ and Burst)
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

//osThreadDef(E4heartBeatThread, osPriorityIdle, 1, 0);
osThreadDef(heartBeatThread, osPriorityIdle, 1, 0);

osThreadDef(adcIRQThread, osPriorityAboveNormal, 1, 0);
osThreadId adcIRQThreadId;

//osThreadDef(E4adcIRQThread, osPriorityAboveNormal, 1, 0);
//osThreadId E4adcIRQThreadId;

osMailQDef(ADCmailQ, ANZAHL, myADCmail_t);
osMailQId ADCmailQ;

osMailQDef(ADC_RawMailQ, ANZAHL, ADC_Raw_t);
osMailQId ADC_RawMailQ;

ETTI4disp_t myDisplay = {
													.DispType = USE_ETTI4_PARDISPLAY,
													.NrLines = 4,
													.NrCols = 20,
													.enHorbar = true};

													
/**
  * @brief  Main thread - display of ADC results
  * @retval Errorcode
  */
int32_t main(void)
{
  
   e4configADC();
	 NVIC_SetPriorityGrouping(0);
	
	 initETTI4display(&myDisplay);
	 clearETTI4display(&myDisplay);
	 printf("    Laboratory\n"
				  "  Embedded Systems\n"
				  "   Experiment ADC\n"
				  "    HW-Interrupt\n");
	
   osDelay(2000);
	 clearETTI4display(&myDisplay);
	
	 //E4adcIRQThreadId = osThreadCreate(osThread(E4adcIRQThread), NULL);
	 adcIRQThreadId = osThreadCreate(osThread(adcIRQThread), NULL);
	
	 //osThreadCreate(osThread(E4heartBeatThread), NULL);
	 osThreadCreate(osThread(heartBeatThread), NULL);
	
	
	 osEvent mailEvent;
	 myADCmail_t *mailTemp;
   
	 myADCmail_t temp;
	 ADCmailQ = osMailCreate(osMailQ(ADCmailQ), NULL);
	
	 ADC_RawMailQ = osMailCreate(osMailQ(ADC_RawMailQ), NULL);
	
   for(;;)
   {
		 //osSignalSet(E4adcIRQThreadId, SIG_ADCTHR_START_ADC);
		 osSignalSet(adcIRQThreadId, SIG_ADCTHR_START_ADC);
		 
		 mailEvent = osMailGet(ADCmailQ, osWaitForever);
 
		 if(mailEvent.status == osEventMail){
			 mailTemp = mailEvent.value.p;
			 temp = *mailTemp;
			 osMailFree(ADCmailQ, mailTemp);
			 
			 adcDisplay(&myDisplay, &temp);
			// E4adcDisplay(&myDisplay, &temp);
		 }
   }
}
