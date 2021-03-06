/**
  ******************************************************************************
  * @file      myIRQHandlerMailQueue.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V4.0.0
  * @date      17.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise RTX - IRQ-Handler for interrupts - mail queue
  ******************************************************************************
  * @par History:
  *  @details V4.0.0 Ferdinand Englberger
  *           - Use Callback instead of direct IRQ-Handler     
  *  @details V3.0.0 08.01.2014 Ferdinand Englberger
  *           - CMSIS RTOS API instead of RLARM
  *  @details V2.1.0 14.11.2012 Ferdinand Englberger
  *           - C99 data types  
  *  @details V2.0.0 16.09.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */

#include "myHW.h"                       // ETTI4::ETTI4:Embedded laboratory:RTX
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "stdio.h"

extern osMailQId myMail;

/**
  * @brief  Callback function for key 1 (mail queue)
  * @details The Callback function transfers the content of the 
  *          DIP-switch in the mail queue
  */  
void key1Callback(void)
{
	myMailQ_t *mailptr;
	mailptr = osMailAlloc(myMail, 0);
	if(mailptr){
	mailptr->value = getDIP();
	mailptr->SW = 1;
	osMailPut(myMail, mailptr);
	}
}


/**
  * @brief  Callback function for key 2 (mail queue)
  * @details The Callback function transfers the content of the 
  *          Hex-switch in the mail queue
  */
void key2Callback(void)
{
	myMailQ_t *mailptr;
	mailptr = osMailAlloc(myMail, 0);
	if(mailptr){
	mailptr->value = getHex();
	mailptr->SW = 2;
	osMailPut(myMail, mailptr);
	}
}
