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

/**
  * @brief Function to initialize the stepper motor signals
  */
void initStepperMotor(void)
{

}

/**
  * @brief Function to do one step
  * @warning Function is called by an timer IRQ-handler
  */
void stepperCallback(void)
{
  
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
