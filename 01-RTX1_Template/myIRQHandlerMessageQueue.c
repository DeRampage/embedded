/**
  ******************************************************************************
  * @file      myIRQHandlerMEssageQueue.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V4.0.0
  * @date      17.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise RTX - IRQ-Handler for interrupts - message queue
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


/**
  * @brief  Callback function for key 1 (message queue)
  * @details The Callback function transfers the content of the DIP-switch 
  *          in the message queue
  */


#include "myHW.h"                       // ETTI4::ETTI4:Embedded laboratory:RTX
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "stdio.h"

extern osMessageQId myMessage; 

	

void key1Callback(void)
{

	myMsgQ_t msg;
	
	msg.content.value = getDIP();
	msg.content.SW = 1;
	
	osMessagePut(myMessage, msg.msgQMsg, 0);
}


/**
  * @brief  Callback function for key 2 (message queue)
  * @details The Callback function transfers the content of the Hex-switch 
  *          in the message queue
  */
void key2Callback(void)
{

	myMsgQ_t msg;
	
	msg.content.value = getHex();
	msg.content.SW = 2;
	
	osMessagePut(myMessage, msg.msgQMsg, 0);
}
