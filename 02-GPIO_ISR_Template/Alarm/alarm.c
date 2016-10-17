/**
  ******************************************************************************
  * @file      alarm.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.0.0
  * @date      07.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institut 4
  * @brief Template - Program part to control alarm function
  ******************************************************************************
  * @details signal router adjustment: \b 01
  * @details alarm button  P0.28
  * @details alarm buzzer  P2.4
  ******************************************************************************
  * @par History:
  *  @details V3.0.0 Ferdinand Englberger
  *           - Pack description updated 
  *           - RTOS included 
  *           - Interrupt handler  
  *  @details V2.2.0 17.02.2014 Ferdinand Englberger
  *           - copyright clause  
  *  @details V2.1.0 02.11.2012 Ferdinand Englberger
  *           - C99 data types  
  *  @details V2.0.0 08.09.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */
#include "LPC17xx.h"                    // Device header

/**
  * @brief  Function to initialize alarm capabilities
  */
void init_alarm(void)
{

}

/**
  * @brief  Function to read alarm button
  * @retval alarmButton : position of alarm button, can be
  *                        @arg 1 = button <b>pressed</b>
  *                        @arg 0 = button <b>released</b>
  */
uint32_t getAlarm(void)
{

}

/**
  * @brief  IRQ-Handler to detect change of alarm key
  */
void ???alarmKey??_IRQHandler(void)
{

}


/**
  * @brief  Function to control alarm buzzer
  * @param  alarm : can be
  *                 @arg 1 = buzzer @b on
  *                 @arg 0 = buzzer @b off
  */
void alarmsig(uint32_t alarm)
{

}
