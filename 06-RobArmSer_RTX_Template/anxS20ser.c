/**
  ******************************************************************************
  * @file      anxS20ser.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  * @author    Student2
  * @version   V4.1.0
  * @date      05.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institute 4
  * @brief   Template - functions to control the ANX-S20 (serial)
  ******************************************************************************
  * @details Attention: The control of ANX-S20 using the serial interface is 
  *          not really robust. It es necessary to check a command using 
  *          ACK. It might be necessary to transfer a command several times, 
  *          before the servo controller responds.
  ******************************************************************************
  *	@par History:
  *  @details V4.1.0 Ferdinand Englberger  
  *           - Pack description updated
  *           - Semaphore to protect commands   
  *           - Use only one funtion to update PWM pulse duration    
  *  @details V3.0.0 17.01.2014 Ferdinand Englberger
  *           - CMSIS RTOS API instead of RLARM  
  *  @details V2.1.0 25.11.2012 Ferdinand Englberger
  *           - C99 data types 
  *  @details V2.0.0 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */
#include "anxS20ser.h"
#include "LPC17xx.h"                    // Device header
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "stdio.h"

#define ANZAHL 5
/**
  * @brief  Function to initialize the servo controller-interface
  * @details UART1
  */
osMessageQDef(anxS20MsgQ, ANZAHL, uint32_t);
osMessageQId anxS20MsgQ;
	
void anxS20init(void)
{
	anxS20MsgQ = osMessageCreate(osMessageQ(anxS20MsgQ), NULL);
	
	LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3u<<30))|(1<<30);
	LPC_PINCON->PINMODE0 = LPC_PINCON->PINMODE0 & ~(3u<<30);
	LPC_PINCON->PINMODE_OD0 &= ~(1<<15);
	
	LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~3) | 1;
	LPC_PINCON->PINMODE1 = LPC_PINCON->PINMODE1 & ~3;
	
	
	LPC_UART1->LCR = 0x80;
	LPC_UART1->DLL = 0x87;
	LPC_UART1->DLM = 0x01;
	LPC_UART1->FDR = 0x10;
	LPC_UART1->LCR = 0x03;
	LPC_UART1->FCR = 0x01;
	LPC_UART1->IER = 0x1;
	
	NVIC_SetPriority(UART1_IRQn, 12);
	NVIC_ClearPendingIRQ(UART1_IRQn);
	NVIC_EnableIRQ(UART1_IRQn);
}

/**
  * @brief  Function to transmit one byte using UART1
  * @param  ch : character to send
  */
void anxS20sendchar(uint32_t ch)
{	  
  while((LPC_UART1->LSR & 0x40));
 /*
  {		//Wenn TEMT(Transmitter Empty) 
		
		if (ch == '\n') {									//Input LF?	==> Stringeingabe (Feld, etc.)
	  while(!(LPC_UART1->LSR & 0x20))
		{
     osThreadYield();
    }
	  LPC_UART1->THR = 0x0D; 					//Output CR
  }
  
	
	if (ch == 0x0D) {									//Input CR? ==> Tastatureingeabe
    while(!(LPC_UART1->LSR & 0x20))
		{
     osThreadYield();
    }
		LPC_UART1->THR = 0x0A; 					//Output LF
  }
	
	
	while(!(LPC_UART1->LSR & 0x20))
	{
   osThreadYield();
  }
	*/
	
  LPC_UART1->THR = ch;
	//}
}


/**
  * @brief  IRQ-Handler for reception of characters from servo controller
  * @details the received character is transmitted using the mailbox.
  *          If the mailbox is full the received character is rejected.
  */
void UART1_IRQHandler(void)
{
	uint32_t newdata; 
	newdata = LPC_UART1->RBR;
	osMessagePut(anxS20MsgQ, newdata, 0);
}


/**
  * @brief  function to read ACK from servo controller
  * @details the anx-S20-servo controller transmits his
  *          IIC-address to acknowledge, the reception of a valid 
  *          command. The function waits for Acknowledge for 
  *          a maximum time of 20 ms.
  * @retval "Acknowledge status": can be:
  *              @arg 1 ACK received
  *              @arg 0 no ACK received or timeout
  */
int32_t anxS20getAck(void)
{
	osEvent anxMsg;
	
	anxMsg = osMessageGet(anxS20MsgQ, 10);
	
	if(anxMsg.status == osEventMessage){
		
		if(anxMsg.value.v == 97){
	    return 1;
		}else{
			return 0;
		}
	}
	/* TIMEOUT ist einzige logische Alternative
	
	if(anxMsg.status == osEventTimeout){
		return 0;
	}
	*/
	return 0;
	
}


/**
  * @brief  function reads one Byte from servo controller
  * @details Normally this is the firmware version number
  * @retval "read value": can be
  *               @arg read value
  *               @arg 999, if no valid character is received after 5 retries
  */
uint32_t anxS20GetByte(void)
{
	int32_t count = 0;
	
	
	
	
	
	
	
	int32_t transmission[] = {'a', 'x', 97, 128};
	
	for (int i = 0; i < 4; i++){
		
		for(int j = 0; j < 4; j++){ //ggf i < 5 // transmission[j]
			anxS20sendchar(transmission[j]);
		}
		//fflush(stdout);
		
		if(anxS20getAck() == 1){
			
			osEvent anxMsg;
			anxMsg = osMessageGet(anxS20MsgQ, osWaitForever);
			
			if(anxMsg.status == osEventMessage){
				return anxMsg.value.v;
			}
			i = 4;
		}
		
	}

	return 999;   
	
	
	
	
	
	
	/*
	do{
		if(anxS20getAck() == 1){
			
			osEvent anxMsg;
			anxMsg = osMessageGet(anxS20MsgQ, 0);
			
			if(anxMsg.status == osEventMessage){
				return anxMsg.value.v;
			}
			
		}
		count++;
	}	while(count < 4);

	return 999;
	*/
}


/**
  * @brief  function to set a servo to a certain position
  * @details The limit parameters are used to simplify the program.
  *          This is, due to that not the first 6 servos are used to 
  *          control the robotic arm.
  *          Usually the limits of all 20 servos should be stored. 
  *          Due to the risk of errors, this is not done here.
  * @param  servo      : servo number1-20
  * @param  positionus : pulse width of servo in us  1500 = 1.5 ms
  * @param  minlimit   : allowed minimum value of pulse width in us
  * @param  maxlimit   : allowed maximum value of pulse width in us
  * @retval Status : can be: 
  *               @arg 1 : ACK received
  *               @arg 0 : no ACK received
  */
int32_t anxS20setservopos(uint32_t servo, uint32_t positionus, 
                          uint32_t minlimit, uint32_t maxlimit)
{
	
	
	if(positionus > maxlimit){
		positionus = maxlimit;
	}
	if(positionus < minlimit){
		positionus = minlimit;
	}
	
	int32_t posHigh = (positionus >> 8) & 0xFF;
	int32_t posLow = positionus & 0xFF;
	
	int32_t transmission[] = {'a', 'x', 97, 3, servo, posHigh, posLow};
	
	//do{
	
	for (int i = 0; i < 5; i++){
		
		for(int j = 0; j < transmission[j]; j++){
			anxS20sendchar(transmission[j]);
		}
		
		if(anxS20getAck() == 1){
			i = 5;	//vllt?
			return 1;
		}
		
	}

	return 0;
}

/**
  * @brief function to set the speed to position a servo
  * @details speed to position in us/20 ms
  * @param  servo : Servo number 1-20
  * @param  speed : speed to position in us/20 ms
  * @retval Status : can be: 
  *               @arg 1 : ACK received
  *               @arg 0 : no ACK received
  */
int32_t anxS20setservospeed(uint32_t servo, uint32_t speed)
{
	int32_t transmission[] = {'a', 'x', 97, 2, servo, speed};
	
	for (int i = 0; i < 5; i++){
		
		for(int j = 0; j < transmission[j]; j++){ //ggf i < 5
			anxS20sendchar(transmission[j]);
		}
		
		if(anxS20getAck() == 1){
			i = 5;	//vllt?
			return 1;
		}
		
	}

	return 0;   
}

/**
  * @brief Function, which is called to modify the PWM pulse width 
  * @param  [in, out] armsrv_ptr : Pointer to the servo descriptor data
  * @param             direction : Direction of PWM change
  *                                @arg PWMup   : lengthen the PWM pulse
  *                                @arg PWMdown : reduce the PWM pulse
  */
void servotimeUpdate(SrvCtr_t * armsrv_ptr, UpdateDirection direction)
{
	if(direction == PWMup){
		armsrv_ptr->servotime += 5;
	}else{
		armsrv_ptr->servotime -= 5;
	}
	
	if(armsrv_ptr->servotime > armsrv_ptr->servomaxlimit){
		armsrv_ptr->servotime = armsrv_ptr->servomaxlimit;
	}
	
	if(armsrv_ptr->servotime < armsrv_ptr->servominlimit){
		armsrv_ptr->servotime = armsrv_ptr->servominlimit;
	}
	
	printf("%d", armsrv_ptr->servotime);
	
	anxS20setservopos(armsrv_ptr->servonr, armsrv_ptr->servotime, armsrv_ptr->servominlimit, armsrv_ptr->servomaxlimit);
}
