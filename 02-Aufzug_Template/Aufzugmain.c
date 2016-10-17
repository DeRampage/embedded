/**
  ******************************************************************************
  * @file      Aufzugmain.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @version   V4.5.0
  * @date      07.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institut 4
  * @brief   main part of the elevator program (LPC1769)
  ******************************************************************************
  * @details signal router setting: \b 01
  ******************************************************************************
  *  @par History:
  *  @details V4.5.0 Ferdinand Englberger
  *           - Use display driver 6.0.0
  *  @details V4.1.0 26.05.2015 Ferdinand Englberger
  *           - retarget.c replaced by Compiler Pack
  *  @details V4.0.1 23.10.2013 Ferdinand Englberger
  *           - Comments corrected
  *  @details V4.0.0 16.07.2013 Ferdinand Englberger
  *           - CMSIS RTOS API instead of RLARM  
  *  @details V2.1.0 02.11.2012 Ferdinand Englberger
  *           - C99 data types
  *  @details V2.0.0 01.09.2011 Ferdinand Englberger
  *           - Start of the  LPC1769-variant
  ******************************************************************************
  */
#include "cmsis_os.h"              // ARM::CMSIS:RTOS:Keil RTX
#include <stdio.h>
#include "max_II_configurator.h"  // ETTI4::ETTI4:Embedded laboratory:Configurator
#include "aufzug_main.h"          // ETTI4::ETTI4:Embedded laboratory:Elevator
#include "motor.h"                // ETTI4::ETTI4:Embedded laboratory:Elevator

void mainThread(void const *argument);

/** @brief Thread definition for mainThread */
osThreadDef(mainThread, osPriorityNormal, 1, 0);

/**
  * @brief  Main-function
  * @details Configures signal router and starts the RTOS
  * @retval Errorcode
  */
int32_t main(void)
{
   e4configAufzug();
   
   osThreadCreate(osThread(mainThread), NULL);
   osThreadTerminate(osThreadGetId());
   for(;;)
   {
   }
}

/**
  * @brief  function initialize all components of the elevator
  * @retval None
  */
void initAufzugHW(void)
{
  init_display( ); // Terminal-Anzeige ETTI 4 Praktikum
  init_leds_buttons();
  init_alarm();
  init_position();
  initStepperMotor();
  init_doorservo();
  init_siebensegment();

  copyToShadow(5, 0, 32, (uint8_t *) "Elevator control LPC1769 - V4.5 ");
  copyToShadow(16, 1, 10,(uint8_t *) "Floor:    ");
  copyToShadow(0, 2, 33, (uint8_t *) "State: Idle       Position: -----");
  copyToShadow(5, 3, 20, (uint8_t *) "Alarm is not running");
}
