/**
  ******************************************************************************
  * @file      ADCthreadDummy.c
  * @author    Student1
  *	@author    Student2  
  * @version   V2.1.0
  * @date      18.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise ADC - dummy-thread to generate simulated ADC-results
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
#include "stdlib.h" 
/**
  * @brief  Thread - ADC dummy thread
  * @details If the trigger signal is received, the thread transfers test values
  *          using the ADC-mail queue - only the element dVolt is filled with values.
  *          The rest of the elements have no valid content.
  * @param  argument : not used 
  * @retval none
  */
extern osMailQId ADCmailQ;



myADCmail_t *data;
	
void adcDummyThread(void const * argument)
{
   
	
   for(;;)
   {
		 osSignalWait(SIG_ADCTHR_START_ADC, osWaitForever);
		 data = osMailAlloc(ADCmailQ, osWaitForever);
		 if(data){
			 for(int i = 0; i < 4; i++){
				 data->ADCresult[i].dVolt = rand()%33;
			 }
			 osMailPut(ADCmailQ, data);
		 }

   }
}
