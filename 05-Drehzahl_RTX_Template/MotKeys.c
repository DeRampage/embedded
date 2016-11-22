/**
  ******************************************************************************
  * @file      MotKeys.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.5.0
  * @date      21.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   program part : monitoring of keys 
  ******************************************************************************
  * @par History:
  *  @details V3.5.0 Ferdinand Englberger
  *           - Use display library V6.0.0 and updated pack description   
  *  @details V3.0.0 21.01.2014 Ferdinand Englberger
  *           - CMSIS RTOS API instead of RLARM
  *  @details V2.0.0 12.10.2011 Ferdinand Englberger
  *           - Template initial version LPC1769
  ******************************************************************************
  */
#include "LPC17xx.h"                    // Device header
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "keythread.h"                  // ETTI4::ETTI4:Embedded laboratory:Revolution measurement

extern osThreadId keyThreadID;

/**
  * @brief  IRQ handler Run/Stop (EINT1)
  */
void EINT1_IRQHandler(void)
{
	osSignalSet(keyThreadID, SIG_KEY_RUNSTOP);
	LPC_SC->EXTINT = 0x2;
}

/**
  * @brief  IRQ handler Right/Left (EINT2)
  */
void EINT2_IRQHandler(void)
{
	osSignalSet(keyThreadID, SIG_KEY_LEFT_RIGHT);
	LPC_SC->EXTINT = 0x4;
}

/**
  * @brief  Function to initialize the key IRQs
  */
void initMotKeysIRQ(void)
{
	LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~((3 << 22) | (3 << 24))) | ((1 << 22) | (1 << 24));
	LPC_PINCON->PINMODE4 = LPC_PINCON->PINMODE4 & ~((3 << 22) | (3 << 24));
	LPC_SC->EXTMODE = LPC_SC->EXTMODE | (3 << 1);
	LPC_SC->EXTPOLAR = (LPC_SC->EXTPOLAR & ~(3 << 1)) | (1 << 1);
  LPC_SC->EXTINT = 0x6;
	
	NVIC_SetPriority(EINT1_IRQn, 20);
	NVIC_ClearPendingIRQ(EINT1_IRQn);
	
	NVIC_SetPriority(EINT2_IRQn, 21);
	NVIC_ClearPendingIRQ(EINT2_IRQn);
	
	NVIC_EnableIRQ(EINT1_IRQn);
	NVIC_EnableIRQ(EINT2_IRQn);
}
