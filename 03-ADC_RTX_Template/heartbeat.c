/**
  ******************************************************************************
  * @file      HeartBeat.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2  
  * @version   V2.1.0
  * @date      18.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise ADC - Thread and ISR with moving light function
  ******************************************************************************
  * @details used resources:
  *              - LEDs <-> P2.7 - P2.0
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

#include <stdint.h>
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "LPC17xx.h"                    // Device header
#include "RTE_Device.h"                 // Keil::Device:Startup

/**
  * @brief  function to initialize the hardware for leds and joystick
  */
void HeartLEDsInit(void)
{
	LPC_PINCON->PINSEL4 = LPC_PINCON->PINSEL4 & 0x0000;
	LPC_PINCON->PINMODE4 = LPC_PINCON->PINMODE4 & 0x0000;
	LPC_PINCON->PINMODE_OD2 = LPC_PINCON->PINMODE_OD2  & 0x00;
	
	//LPC_GPIO2->FIOSET = 0x01;
	LPC_GPIO2->FIODIR = LPC_GPIO2->FIODIR | 0xFF;
}

/**
  * @brief  function to control the Heartbeat-LEDs
  * @param  leds : control value for the leds Bits 7..0, can be
  *                @arg 1 : LED on
  *                @arg 0 : LED off
  */
void SetHeartLEDs(uint32_t leds)
{
		LPC_GPIO2->FIOSET = leds;
		LPC_GPIO2->FIOCLR = ~leds;
}

/**
  * @brief  Thread - Heartbeat
  * @details The thread generates the moving light on Joystick and LED-modul
  * @param  argument : not used
  */
void heartBeatThread(void const * argument)
{
	HeartLEDsInit();
	uint16_t shift = 0x1;
	for(;;)
	{
		SetHeartLEDs(shift);
	  shift = shift << 1; 
	 	osDelay(5);
		if(shift == 0x100){
			shift = 0x01;
		}
  }
}
