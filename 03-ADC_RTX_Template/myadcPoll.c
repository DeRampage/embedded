/**
  ******************************************************************************
  * @file      myadcPoll.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2  
  * @version   V2.1.0
  * @date      18.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise ADC with RTX (part polling)
  ******************************************************************************
  * @details
  * @verbatim
    used channel Poti1 <-> AD0.0 (P0.23)
    used channel Poti2 <-> AD0.1 (P0.24)
    used channel Poti3 <-> AD0.2 (P0.25)
    used channel Poti4 <-> AD0.3 (P0.26)
  @endverbatim
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
#include "adc_RTX.h"     // ETTI4::ETTI4:Embedded laboratory:ADC-RTX
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "LPC17xx.h"                    // Device header
#include "stdbool.h"

/**
  * @brief  ADC-initialization polling-solution
  * @details Funtcion initialize the uC-Hardware and the variables
  * @param  [out] ChannelPtr : Pointer to the structure to store the channel 
  *                            select codes
  * @retval None
  */
void adcPollInit(ADC_Channel_t * ChannelPtr)
{
  ChannelPtr->ChanSelect[0] = 0x01;
	ChannelPtr->ChanSelect[1] = 0x02;
	ChannelPtr->ChanSelect[2] = 0x04;
	ChannelPtr->ChanSelect[3] = 0x08;
	
	LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(0xFF << 14)) | (0x55 << 14);
	LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(0xFF << 14)) | (0xAA << 14);
	
	LPC_ADC->ADCR = 0x00200400;
}

/**
  * @brief  function starts ADC
  * @param  adcSel : select-code of the channel, to be converted
  * @retval None
  */
void adcSWstart(uint32_t adcSel)
{
	LPC_ADC->ADCR = ((LPC_ADC->ADCR & ~(0xF)) | adcSel) | (1 << 24);
}

/**
  * @brief  function checks for valid result and reads result from ADC
  * @param  [out] PtrAdvalue : Pointer to the result variable. The result is stored
  *                            as 0-4095.
  * @retval Errorcode : can be,
  *                     @arg 0    : no result available
  *                     @arg else : valid result
  */
uint32_t readADC(uint32_t * PtrAdvalue)
{
	uint32_t temp = LPC_ADC->ADGDR; 
	
	if(temp & 0x80000000){
		*PtrAdvalue = (temp >> 4) & 0xFFF;
		return(true);
	}
	return (false);
}
