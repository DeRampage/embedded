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
#include "keythread.h"                  // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "LPC17xx.h"                    // Device header
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX

#define TIMEMAX 12000
#define TIMEMIN 8400
#define TIMESTEP 240


extern drehzahl_t ActMotorStatus;
/**
  * @brief  Function to initialize motor control HW
  * @param  [in] StatusPtr : pointer to motor status object
  */
void initMotor(drehzahl_t * StatusPtr)
{
	
	
	LPC_PWM1->TCR = 0; 	//Timer Stop
	LPC_PWM1->CTCR = 0;	//Select Timer-Mode
	LPC_PWM1->PR = 0;
	LPC_PWM1->PC = 0;
	LPC_PWM1->TC = 0;
	
	
	LPC_PWM1->MR0 = TIMEMAX - 1;	//Period 0.2ms
	//SEMAPHORE?
	LPC_PWM1->MR5 = TIMEMIN + ActMotorStatus.speedstep * TIMESTEP;			//PWM Impulse

	
	LPC_PWM1->MCR = 02; //OKTAL
	LPC_PWM1->PCR = 0x2000;//(LPC_PWM1->PCR & ~(1 << 5)) | (1 << 13);
	
	
	
	
	LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~((3 << 8) | (3 << 6))) | (1 << 8);
	LPC_PINCON->PINMODE4 = LPC_PINCON->PINMODE4 | ((3 << 8) | (3 << 6));
	LPC_PINCON->PINMODE_OD2 = LPC_PINCON->PINMODE_OD2 & ~(1 << 4);
	LPC_GPIO2->FIODIR = LPC_GPIO2->FIODIR | (1<<3);
	
	
	////////////////////NOTWENDIG?//////////////////
	//SEMAPHORE?
	if(ActMotorStatus.direction == Left){
		LPC_GPIO2->FIOSET = (1<<3);
	}else{
		LPC_GPIO2->FIOCLR = (1<<3);
	}
	//SEMAPHORE?
	if(ActMotorStatus.status == Run){
		LPC_PWM1->PCR = 0x2000;
	}else{
		LPC_PWM1->PCR = 0x0000;
	}
	////////////////////NOTWENDIG?//////////////////
	
	
	LPC_PWM1->TCR = 9; //Timer Start
}

/**
  * @brief  Function to control direction pin
  * @param  direction : can be ->  @b Right or @b Left
  */
void setDirection(direction_t direction)
{
	if(direction == Left){
		LPC_GPIO2->FIOSET = (1<<3);
	}else{
		LPC_GPIO2->FIOCLR = (1<<3);
	}
}

/**
  * @brief  Function to stop or start motor
  * @param  [in] StatusPtr : Pointer to motor descriptor object. Due to the value of
  *                          the element @b status the motor is started or stopped.
  *                          If the motor is started, the requested speed is set.
  */
void setRunStop(drehzahl_t * StatusPtr)
{
	if(StatusPtr->status == Run){
		//LPC_PWM1->TCR = 9;
		LPC_PWM1->PCR = 0x2000;
	}else{
		//LPC_PWM1->TCR = 9;
		LPC_PWM1->PCR = 0x0000;
	}
}

/**
  * @brief  Function to set engine speed
  * @param  [in] StatusPtr : Pointer to motor descriptor object. 
  *                          If the motor is in run mode, the requested speed is set.
  */
void updateSpeed(drehzahl_t * StatusPtr)
{
  LPC_PWM1->MR5 = TIMEMIN + StatusPtr->speedstep * TIMESTEP;
	LPC_PWM1->LER = (1 << 5);
}
