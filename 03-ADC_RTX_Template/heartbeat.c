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

/**
  * @brief  function to initialize the hardware for leds and joystick
  */
void HeartLEDsInit(void)
{

}

/**
  * @brief  function to control the Heartbeat-LEDs
  * @param  leds : control value for the leds Bits 7..0, can be
  *                @arg 1 : LED on
  *                @arg 0 : LED off
  */
void SetHeartLEDs(uint32_t leds)
{

}

/**
  * @brief  Thread - Heartbeat
  * @details The thread generates the moving light on Joystick and LED-modul
  * @param  argument : not used
  */
void heartBeatThread(void const * argument)
{

   for(;;)
   {

   }
}
