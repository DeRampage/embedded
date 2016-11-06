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
#include "stdio.h"
/**
  * @brief Function to update LC display
  * @param [in, out]     pDisp : Pointer display descriptor
  * @param [in, out] oldPwmCtl : pointer to servo structure ("old" values)
  * @param [in] newPwmCtl      : pointer to servo structure ("new" values)
  * @retval None
  */
void updatePWMdisplay(ETTI4disp_t * pDisp, pwm_t * oldPwmCtl, pwm_t * newPwmCtl)
{

	if(newPwmCtl->servo1.advalue != oldPwmCtl->servo1.advalue){
		
		setPosETTI4display (pDisp, 0, 15);
		printf(	"%d", newPwmCtl->servo1.advalue);
		
		setPosETTI4display (pDisp, 1, 4);
		printf(	"%d.%d", newPwmCtl->servo1.pw/1000, (newPwmCtl->servo1.pw/100)%10);
		
		setPosETTI4display (pDisp, 1, 15);
		printf(	" %d ", newPwmCtl->servo1.arc);
		
		
		setPosETTI4display (pDisp, 0, 0);
		oldPwmCtl->servo1.advalue = newPwmCtl->servo1.advalue;
		oldPwmCtl->servo1.arc = newPwmCtl->servo1.arc;
		oldPwmCtl->servo1.pw = newPwmCtl->servo1.pw;
	}
	if(newPwmCtl->servo2.advalue != oldPwmCtl->servo2.advalue){
		
		setPosETTI4display (pDisp, 2, 15);
		printf(	"%d", newPwmCtl->servo2.advalue);
		
		setPosETTI4display (pDisp, 3, 4);
		printf(	"%d.%d", newPwmCtl->servo2.pw/1000, (newPwmCtl->servo1.pw/100)%10);
		
		setPosETTI4display (pDisp, 3, 15);
		printf(	" %d ", newPwmCtl->servo2.arc);
		
		setPosETTI4display (pDisp, 0, 0);
		
		oldPwmCtl->servo2.advalue = newPwmCtl->servo2.advalue;
		oldPwmCtl->servo2.arc = newPwmCtl->servo2.arc;
		oldPwmCtl->servo2.pw = newPwmCtl->servo2.pw;
	}
	
}
