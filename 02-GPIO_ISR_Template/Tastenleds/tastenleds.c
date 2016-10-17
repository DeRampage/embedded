/**
  ******************************************************************************
  * @file      tastenleds.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.0.0
  * @date      07.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institut 4
  * @brief Template - Program part to check buttons and control leds
  ******************************************************************************
  * @details signal router adjustment: @b 01
  * @details buttons:
  *          - base frame P0.22 - P0.19
  *          - cabine     P0.27 - P0.24
  *          - emergency stop switch P0.23
  * @details Leds:
  *          - base frame P1.18 - P1.21
  *          - cabine  P1.22 - P1.25 
  ******************************************************************************
  * @par History:
  *  @details V3.0.0 Ferdinand Englberger
  *           - Pack description updated 
  *           - RTOS included  
  *  @details V2.2.0 17.02.2014 Ferdinand Englberger
  *           - copyright clause
  *  @details V2.1.0 23.10.2013 Ferdinand Englberger
  *           - C99 data types  
  *  @details V2.0.0 08.09.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */  
#include "LPC17xx.h"                    // Device header


/**
  * @brief  Function to initialize the pins for leds, buttons and emergency stop switch
  */
void init_leds_buttons(void)
{

}

/**
  * @brief  function to control the leds
  * @details
  * @verbatim
    control word structure
       Bit 7..4 cabine leds     OG3 OG2 OG1 EG
       Bit 3..0 base frame leds OG3 OG2 OG1 EG
    @endverbatim

  * @param  ledson : the lower 8 bit contain the code for the leds.
  *                  @arg Bit = 1 => LED on
  *                  @arg Bit = 0 => LED off
  */
void setLeds(uint32_t ledson)
{

}

/**
  * @brief  Function reads buttons from base frame and cabine.
  * @details
  * @verbatim
    structure of the read information
       Bit 7..4 cabine values     OG3 OG2 OG1 EG
       Bit 3..0 base frame values OG3 OG2 OG1 EG
    @endverbatim
  * @return State of button :
  *         @arg Bit = 1 => button pressed
  *         @arg Bit = 0 => button released
  */
uint32_t getbutton(void)
{

}

/**
  * @brief  Function to read the emergency stop switch
  * @return emergency stop state : can be
  *                        @arg 1 => emergency stop on
  *                        @arg 0 => emergency stop off
  */
uint32_t getNothalt(void)
{

}
