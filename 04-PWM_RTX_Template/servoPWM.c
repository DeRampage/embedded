/**
  ******************************************************************************
  * @file      servoPWM.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.5.0
  * @date      28.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Template - Exercise PWM-generation with RTX - part PWM for servo
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
#include "pwmRTX.h"              // ETTI4::ETTI4:Embedded laboratory:PWM and ADC

#define TIME20MS 20000
#define TIMEDEFAULT 1500
/**
  * @brief Function initializes PWM-unit
  */
void initPWM(void)
{
	LPC_PWM1->TCR = 0;
	LPC_PWM1->CTCR = 0;
	LPC_PWM1->PR = 0x1C;
	LPC_PWM1->PC = 0;
	LPC_PWM1->TC = 0;
	
	LPC_PWM1->MR0 = TIME20MS - 1;
	LPC_PWM1->MR2 = TIMEDEFAULT;
	LPC_PWM1->MR5 = TIMEDEFAULT;
	
	LPC_PWM1->MCR = 0x02;
	LPC_PWM1->PCR = 0x2400;
	
	LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~((3 << 8)|(3 << 2))) | ((1 << 8) | (1 << 2));
	LPC_PINCON->PINMODE4 = LPC_PINCON->PINMODE4 | ((3 << 8)|(3 << 2));
	LPC_PINCON->PINMODE_OD2 = LPC_PINCON->PINMODE_OD2 & ~((1 << 4) | (1 << 2));
	
	LPC_PWM1->TCR = 9;
}

/**
  * @brief Function to set pulse width of servos
  * @param [in] pwmPtr : pointer to servo structure
  */
void setServoPWM(pwm_t * pwmPtr)
{
	LPC_PWM1->MR2 = pwmPtr->servo2.pw;
	LPC_PWM1->MR5 = pwmPtr->servo1.pw;
	LPC_PWM1->LER = 0x24;
}
