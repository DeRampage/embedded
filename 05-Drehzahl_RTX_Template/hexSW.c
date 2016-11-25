/**
  ******************************************************************************
  * @file      hexSW.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.5.0
  * @date      21.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Control of Hex switches
  ******************************************************************************
  * @details Anschlusspins des Hex-Schalters P0.4 - P0.7
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
#include "hexsw.h" // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "keythread.h"                  // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "LPC17xx.h"                    // Device header

extern osThreadId keyThreadID;
/**
  * @brief Function to initialize HW to read Hex switches
  */
void initHEXSW(void)
{
	LPC_PINCON->PINSEL0 = LPC_PINCON->PINSEL0 & ~((3 << 8) | (3 << 10) | (3 << 12) | (3 << 14));
	LPC_PINCON->PINMODE0 = LPC_PINCON->PINMODE0 & ~((3 << 8) | (3 << 10) | (3 << 12) | (3 << 14));
	LPC_GPIO0->FIODIR = LPC_GPIO0->FIODIR & ~(0xF << 4);
	
	LPC_GPIOINT->IO0IntEnF = LPC_GPIOINT->IO0IntEnF | 0xF0;
	LPC_GPIOINT->IO0IntEnR = LPC_GPIOINT->IO0IntEnR | 0xF0;
	LPC_GPIOINT->IO0IntClr = 0xF0;
	
	NVIC_SetPriority(EINT3_IRQn, 22);
	NVIC_ClearPendingIRQ(EINT3_IRQn);
	NVIC_EnableIRQ(EINT3_IRQn);
}

/**
  * @brief  function to read the value of Hex switch
  * @retval "read value" : can be 0 - 15
  */
uint32_t getHexSW(void)
{
   return (~(LPC_GPIO0->FIOPIN >> 4)) & 0xF;
}

/**
  * @brief IRQ-Handler for value change of Hex switch
  */
void EINT3_IRQHandler(void)
{	
    LPC_GPIOINT->IO0IntClr = 0xF0;
	osSignalSet(keyThreadID, SIG_KEY_NEWHEX);
	
}
