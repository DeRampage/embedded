/**
  ******************************************************************************
  * @file      pwm_main.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.5.0
  * @date      28.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Template - Exercise PWM-generation with RTX
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
#include "max_II_configurator.h"  // ETTI4::ETTI4:Embedded laboratory:Configurator


/**
  * @brief  Main thread
  * @details Thread is used to display the information on LCD
  */
int32_t main(void)
{
    e4configPWM();

    for(;;)
    {
    }
}
