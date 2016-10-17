/**
  ******************************************************************************
  * @file      pwmDisplay.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.5.0
  * @date      28.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Template - Exercise PWM-generation with RTX - display function
  ******************************************************************************
  * @par History:
  *  @details V3.5.0 Ferdinand Englberger
  *           - Use display library V6.0.0 and updated pack description     
  *  @details V3.0.0 Ferdinand Englberger
  *           - CMSIS RTOS API instead of RLARM  
  *  @details V2.1.0 27.11.2012 Ferdinand Englberger
  *           - C99 data types  
  *  @details V2.0.0 20.10.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */
#include "pwmRTX.h"             // ETTI4::ETTI4:Embedded laboratory:PWM and ADC
#include "pwmDisplay.h"         // ETTI4::ETTI4:Embedded laboratory:PWM and ADC

/**
  * @brief Function to update LC display
  * @param [in, out]     pDisp : Pointer display descriptor
  * @param [in, out] oldPwmCtl : pointer to servo structure ("old" values)
  * @param [in] newPwmCtl      : pointer to servo structure ("new" values)
  * @retval None
  */
void updatePWMdisplay(ETTI4disp_t * pDisp, pwm_t * oldPwmCtl, pwm_t * newPwmCtl)
{

}
