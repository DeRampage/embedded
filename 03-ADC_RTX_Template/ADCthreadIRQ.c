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
  

/**
  * @brief  Thread - ADC interrupt thread
  * @details Thread starts ADC, waits for the ADC result and transfers
  *          the result as mail to main thread
  * @param  argument : not used
  * @retval none
  */
void adcIRQThread(void const * argument)
{
     for(;;)
     {
         
     }
}