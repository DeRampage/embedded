/**
  ******************************************************************************
  * @file      ea_test6.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.0.0
  * @date      07.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institut 4
  * @brief Template - Program EA6 part stepper motor control
  ******************************************************************************
  * @details signal router setting: \b 01
  ******************************************************************************
  * @par History:
  *  @details V3.0.0 Ferdinand Englberger
  *           - Pack description updated 
  *           - RTOS included 
  *           - Callback  
  *  @details V2.2.0 17.02.2014 Ferdinand Englberger
  *           - Initial version stepper motor control
  ******************************************************************************
  */
#include "cmsis_os.h"             // ARM::CMSIS:RTOS:Keil RTX
#include "max_II_configurator.h"  // ETTI4::ETTI4:Embedded laboratory:Configurator
#include "alarm.h"                      // ETTI4::ETTI4:Embedded laboratory:GPIO-EA
#include "tastenleds.h"                 // ETTI4::ETTI4:Embedded laboratory:GPIO-EA
#include "possensor.h"                  // ETTI4::ETTI4:Embedded laboratory:GPIO-EA
#include "motor.h"                      // ETTI4::ETTI4:Embedded laboratory:GPIO-EA


/**
  * @brief  Main Thread
  */
int32_t main(void)
{
	
  e4configAufzug();
  init_leds_buttons();
	init_position();
	//init_alarm();
	
  initMotorIRQ(); 
	initStepperMotor();
	
	uint32_t button = 0;
	uint32_t position = 0;
	
	for(;;)
  {
		button = getbutton() & 0x0F;
		
		if(button == 0x8){
			button = 0x10;//(button << 1);
		}
		
		if(button != 0){
			
			while(button != position){ 
				
				if(button > position){
					SetMotorDirection(CABINE_UP);
					MotorStart();
				}
		
				if(button < position){
					SetMotorDirection(CABINE_DOWN);
					MotorStart();
				}
			position = get_position();
		}
	}
	MotorStop();
	}
	
}
