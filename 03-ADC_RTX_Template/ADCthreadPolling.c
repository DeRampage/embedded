/**
  ******************************************************************************
  * @file      ADCthreadPolling.c
  * @author    Student1
  *	@author    Student2  
  * @version   V2.1.0
  * @date      18.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief  Exercise ADC with RTX (part polling)
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

osThreadId adcPollThreadId;

myADCmail_t *data;	//Nur für Debugging

ADC_Channel_t Channel;


/**
  * @brief  Thread - ADC polling thread
  * @details Thread starts ADC, waits for the ADC result and transfers
  *          the result as mail to main thread
  * @param  argument : not used
  * @retval none
  */
void adcPollThread(void const * argument)
{	
	uint32_t value = 0;
	myADCmail_t *data;
	
	adcPollThreadId = osThreadGetId();
	adcPollInit(&Channel); 
		
	for(;;)
     {
  		osSignalWait(SIG_ADCTHR_START_ADC, osWaitForever);
			data = osMailAlloc(ADCmailQ, osWaitForever);

			 if(data){

				 for(int i =0; i < 4; i++){					 
					 adcSWstart(Channel.ChanSelect[i]);
					 while(!readADC(&value));
					 data->ADCresult[i].adcValue = value;
					 data->ADCresult[i].dVolt = (data->ADCresult[i].adcValue * 330 + 20475) / 40950;
				 }
				 osMailPut(ADCmailQ, data);
			 }
		 }//FREE FEHLT!
}
