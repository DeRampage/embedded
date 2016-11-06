/**
  ******************************************************************************
  * @file      pwm_adc.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.5.0
  * @date      28.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Template - Exercise PWM-generation with RTX - ADC
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
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "LPC17xx.h"                    // Device header
#include "servoPWM.h"                   // ETTI4::ETTI4:Embedded laboratory:PWM and ADC
#include "pwm_adc.h"                    // ETTI4::ETTI4:Embedded laboratory:PWM and ADC
#include "pwmRTX.h"                     // ETTI4::ETTI4:Embedded laboratory:PWM and ADC

#define SIG_ADC_COMPLETE 0x0001
osThreadId adcThread_ID;
//osThreadDef(adcThread, osPriorityAboveNormal, 1, 0);

extern pwm_t pwmControl;
/**
  * @brief  ADC IRQ-Handler
  */
void ADC_IRQHandler(void)
{
	LPC_ADC->ADCR = LPC_ADC->ADCR & ~(1 << 16); // ADC-Stop
	osSignalSet(adcThread_ID, SIG_ADC_COMPLETE);
	LPC_ADC->ADDR2; //Reset Pending IRQ
}

/**
  * @brief Function to initialize ADC
  */
void initADC(void)
{
	LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~((3<<14)|(3<<18)))|((1<<14)|(1<<18));
	LPC_PINCON->PINMODE1 = (LPC_PINCON->PINSEL1 & ~((3<<14)|(3<<18)))|((1<<14)|(1<<18));
	LPC_ADC->ADCR = 0x00200405;
	LPC_ADC->ADINTEN = (1<<2);
	
	NVIC_SetPriorityGrouping(0);
	NVIC_SetPriority(ADC_IRQn, 24); //STIMMT NICHT WERT ANPASSEN
	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_EnableIRQ(ADC_IRQn);
}

/**
  * @brief Function to start ADC
  */
__inline void startADC(void)
{
	LPC_ADC->ADCR = LPC_ADC->ADCR | (1<<16);
}

/**
  * @brief  ADC thread
  * @param argument : not used
  */
void adcThread(void const *argument)
{
	pwm_t temp;
	uint16_t adcCH0;
	uint16_t adcCH2;
	
	
	adcThread_ID = osThreadGetId();
	initADC();
	
	initPWM();
	
    for(;;)
    {
			startADC();
			osSignalWait(SIG_ADC_COMPLETE, osWaitForever);
			adcCH0 = (LPC_ADC->ADDR0 >> 4) & 0xFFF;
			adcCH2 = (LPC_ADC->ADDR2 >> 4) & 0xFFF;
			
			temp.servo1.advalue = adcCH0;
			temp.servo2.advalue = adcCH2;
			
			temp.servo1.pw = 900 + (adcCH0*1200)/4095;
			temp.servo2.pw = 900 + (adcCH2*1200)/4095;
			
			temp.servo1.arc = -45 + (adcCH0*45)/2047;
			temp.servo2.arc = -45 + (adcCH2*45)/2047;
			
			pwmControl = temp;
			
			setServoPWM(&temp);
			
			osDelay(10);
			
    }
}
