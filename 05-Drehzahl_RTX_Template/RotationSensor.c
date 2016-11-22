/**
  ******************************************************************************
  * @file      Rotationsensor.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.5.0
  * @date      21.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief Exercise engine speed with RTX - functions engine speed sensor 
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
#include "LPC17xx.h"                    // Device header
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "RotationSensor.h"             // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "drehzahl.h"                   // ETTI4::ETTI4:Embedded laboratory:Revolution measurement


extern drehzahl_t ActMotorStatus;
extern osSemaphoreId MotorStatusSem;

osMessageQDef(dataQ, 4, uint32_t);
osMessageQId dataQ;


/**
  * @brief  Sensor IRQ-Handler
  * @details Acquisition of two complete 2 rotations = 8 measurement values
  */
void TIMER0_IRQHandler(void)
{
	uint32_t neu = LPC_TIM0->CR0;
	static uint32_t old;
	
	osMessagePut(dataQ, neu-old, 0);
	
	LPC_TIM0->IR = 0x3F;
	old = neu;
}

/**
  * @brief  Function to initialize rotation sensor HW
  */
void initSensor(void)
{
	LPC_PINCON->PINSEL3 = LPC_PINCON->PINSEL3 | (0x3 << 20);
	LPC_PINCON->PINMODE3 = LPC_PINCON->PINMODE3 & ~(0x3 << 20);
	
	LPC_TIM0->TCR = 0;
	LPC_TIM0->CTCR = 0;
	LPC_TIM0->PR = 29;
	LPC_TIM0->TC = 0;
	LPC_TIM0->CCR = 05;
	
	LPC_TIM0->MCR = 0;
	LPC_TIM0->EMR = 0;
	
	LPC_TIM0->IR = 0x3F;
	
	NVIC_SetPriority(TIMER0_IRQn, 17);
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
	NVIC_EnableIRQ(TIMER0_IRQn);
	
	LPC_TIM0->TCR = 1;
}

/**
  * @brief  Sensor thread
  * @param  argument : not used
  */


void RotSensorThread(void const *argument)
{
	initSensor();
	
	dataQ = osMessageCreate(osMessageQ(dataQ), NULL);
	
	osEvent incoming;
	
	uint32_t count = 0;
	uint32_t periode = 0;
	uint16_t drehzahl = 0;

   for(;;)
   {
		 incoming = osMessageGet(dataQ, 1000);
		 
		 if(incoming.status == osEventMessage){
			 periode = periode + incoming.value.v;
			 
			 count++;
			 
			 if(count == 8){
				 drehzahl = (20000000/periode); // /2
				 
				 osSemaphoreWait(MotorStatusSem, osWaitForever);
				 ActMotorStatus.drehzahl = drehzahl;
				 osSemaphoreRelease(MotorStatusSem);
				 
				 drehzahl = 0;
				 periode = 0;
				 count = 0;
			 }
		 }/*else{
		osSemaphoreWait(MotorStatusSem, osWaitForever);
		ActMotorStatus.drehzahl = 0;
		osSemaphoreRelease(MotorStatusSem);
		 }*/
		 if(incoming.status == osEventTimeout){
			 osSemaphoreWait(MotorStatusSem, osWaitForever);
		ActMotorStatus.drehzahl = 0;
		osSemaphoreRelease(MotorStatusSem);
		 }
   }
}
