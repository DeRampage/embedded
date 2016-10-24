/**
  ******************************************************************************
  * @file      StepperMotor.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.1.0
  * @date      21.09.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institut 4
  * @brief Template - Program part to control stepper motor
  ******************************************************************************
  * @details signal router adjustment: @b 01
  * @details motor pins:
  *          - P2.0 - P2.3
  ******************************************************************************
  * @par History:
  *  @details V3.1.0 Ferdinand Englberger
  *           - Naming error corrected  
  *  @details V3.0.0 07.01.2016 Ferdinand Englberger
  *           - Pack description updated 
  *           - RTOS included  
  *           - Stepper Callback
  *  @details V2.2.0 Ferdinand Englberger
  *           - Initial version
  ******************************************************************************
  */
#include "LPC17xx.h"                    // Device header

/** 
  * @brief Current moving direction of cabine 
  * @details Modified by SetMotorDirection() 
  * @details Used by Elevator control program  
  */
int32_t cabinedirection;  
#define CABINE_UP 1
#define CABINE_DOWN 0


/**
  * @brief Function to initialize the stepper motor signals
  */
void initStepperMotor(void)
{
	//GPIO Port 2 OUTPUT MOTOR-CONTROL
	LPC_PINCON->PINSEL4 = LPC_PINCON->PINSEL4 & ~(0x000003FF);
	LPC_PINCON->PINMODE4 = LPC_PINCON->PINMODE4 & ~(0x000003FF);
	LPC_PINCON->PINMODE_OD2 = LPC_PINCON->PINMODE_OD2 & ~(0x00000001F);
	
	
	LPC_GPIO2->FIOSET |=  (3<<2);
	LPC_GPIO2->FIODIR = LPC_GPIO2->FIODIR | 0xF;
	//initStepperMotor();
}

/**
  * @brief Function to do one step
  * @warning Function is called by an timer IRQ-handler
  */
void stepperCallback(void)
{
  int32_t steps [4] = {0xC, 0x6, 0x3, 0x9};
	static int32_t count = 0;
	
	
	if(cabinedirection == 1){
		if(count == 4){
			count = 0;
		}
		LPC_GPIO2->FIOSET = steps[count] & 0xF;
	  LPC_GPIO2->FIOCLR = ~steps[count] & 0xF;
		count++;
	}else{
		if(count == 0){
			count = 4;
		}
		count--;
		LPC_GPIO2->FIOSET = steps[count] & 0xF;
  	LPC_GPIO2->FIOCLR = ~steps[count] & 0xF;
	}	
}

/**
  * @brief Function controls the rotation direction of the motor
  * @param  direction : can be,
  *                     @arg CABINE_UP
  *                     @arg CABINE_DOWN
  */
void SetMotorDirection(int32_t direction)
{  
	cabinedirection = direction; 
}
