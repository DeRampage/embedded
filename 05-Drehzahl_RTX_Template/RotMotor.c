/**
  ******************************************************************************
  * @file      RotMotor.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.5.0
  * @date      21.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise engine speed with RTX - functions to control motor 
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
#include "drehzahl.h"  // ETTI4::ETTI4:Embedded laboratory:Revolution measurement

/**
  * @brief  Function to initialize motor control HW
  * @param  [in] StatusPtr : pointer to motor status object
  */
void initMotor(drehzahl_t * StatusPtr)
{
 
}

/**
  * @brief  Function to control direction pin
  * @param  direction : can be ->  @b Right or @b Left
  */
void setDirection(direction_t direction)
{

}

/**
  * @brief  Function to stop or start motor
  * @param  [in] StatusPtr : Pointer to motor descriptor object. Due to the value of
  *                          the element @b status the motor is started or stopped.
  *                          If the motor is started, the requested speed is set.
  */
void setRunStop(drehzahl_t * StatusPtr)
{

}

/**
  * @brief  Function to set engine speed
  * @param  [in] StatusPtr : Pointer to motor descriptor object. 
  *                          If the motor is in run mode, the requested speed is set.
  */
void updateSpeed(drehzahl_t * StatusPtr)
{
  
}
