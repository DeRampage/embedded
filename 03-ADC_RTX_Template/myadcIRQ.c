/**
  ******************************************************************************
  * @file      myadcIRQ.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2  
  * @version   V2.1.0
  * @date      18.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise ADC with RTX (part Burst and IRQ)
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


extern osMailQId ADC_RawMailQ;
extern osMailQId ADCmailQ;


/**
  * @brief  ADC-initialization Burst/interrupt-solution
  * @details Function initialize the uC-Hardware
  */
void adcIRQInit(void)
{
  LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(0xFF << 14)) | (0x55 << 14);
	LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(0xFF << 14)) | (0xAA << 14);
	
	LPC_ADC->ADCR = 0x0020040F;
	
	LPC_ADC->ADINTEN = (1 << 3);
	
	
	NVIC_SetPriority(ADC_IRQn, 7);
	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_EnableIRQ(ADC_IRQn);
}

/**
  * @brief  function starts ADC (Burst/HW)
  */
void adcHwStart(void)
{
 LPC_ADC->ADCR = LPC_ADC->ADCR | (1 << 16); 
}

/**
  * @brief  ADC-exception handler
  */
void ADC_IRQHandler(void)
{
  LPC_ADC->ADCR = LPC_ADC->ADCR & ~(1 << 16); 
	
	ADC_Raw_t *raw;
	raw = osMailAlloc(ADC_RawMailQ, 0);
	if(raw){
		raw->advalue[0] = (LPC_ADC->ADDR0 >> 4) & 0xFFF;
		raw->advalue[1] = (LPC_ADC->ADDR1 >> 4) & 0xFFF;
		raw->advalue[2] = (LPC_ADC->ADDR2 >> 4) & 0xFFF;
		raw->advalue[3] = (LPC_ADC->ADDR3 >> 4) & 0xFFF;
		
		osMailPut(ADC_RawMailQ, raw);
	}else{
		LPC_ADC->ADDR3;
	}
  
}
