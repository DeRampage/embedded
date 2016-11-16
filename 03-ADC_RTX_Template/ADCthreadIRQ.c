/**
  ******************************************************************************
  * @file      ADCthreadIRQ.c
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
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "adc_RTX.h"                    // ETTI4::ETTI4:Embedded laboratory:ADC-RTX
#include "LPC17xx.h"                    // Device header

extern osMailQId ADCmailQ;
extern osMailQId ADC_RawMailQ;


/**
  * @brief  Thread - ADC interrupt thread
  * @details Thread starts ADC, waits for the ADC result and transfers
  *          the result as mail to main thread
  * @param  argument : not used
  * @retval none
  */
void adcIRQThread(void const * argument)
{
	osEvent rawEvent;
	ADC_Raw_t *rawData;
	myADCmail_t *data;
	
	adcIRQInit();
	//E4adcIRQInit();
	
     for(;;)
     {
			 osSignalWait(SIG_ADCTHR_START_ADC, osWaitForever);
		   data = osMailAlloc(ADCmailQ, osWaitForever);
			 
			 if(data){
				 adcHwStart();
				 //E4adcHwStart();
				 
				 rawEvent = osMailGet(ADC_RawMailQ, osWaitForever);
				 if(rawEvent.status == osEventMail){
					 rawData = rawEvent.value.p;
					 for(int i = 0; i < 4; i++){
						data->ADCresult[i].adcValue = rawData->advalue[i];
						data->ADCresult[i].dVolt = (data->ADCresult[i].adcValue * 330 + 20475) / 40950;
					 }
					 osMailPut(ADCmailQ, data);
					 osMailFree(ADC_RawMailQ, rawData);
				 }
			 }
      osDelay(250);
     }
}
