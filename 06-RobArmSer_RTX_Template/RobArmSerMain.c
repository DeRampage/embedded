/**
  ******************************************************************************
  * @file      Robarmsermain.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @version   V4.1.0
  * @date      05.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institute 4
  * @brief     Template - Exercise robotic arm with UART-control
  * @details Part 2: Test of arm control using terminal keyboard
  *                  and output on terminal display  
  ******************************************************************************
  * @details signal router setting:  @b 50
  ******************************************************************************
  * @par History:
  *  @details V4.1.0 Ferdinand Englberger  
  *           - Pack description updated
  *           - Semaphore to protect commands 
  *           - Use only one funtion to update PWM pulse duration  
  *  @details V4.0.0 26.05.2015 Ferdinand Englberger
  *           - Use Compiler pack instead of retarget.c
  *           - sendchar() calls replaced by putchar()
  *           - getkey() calls replaced by getchar()
  *           - fflush() included to force output    
  *  @details V3.0.0 17.01.2014 Ferdinand Englberger
  *           - CMSIS RTOS API instead of RLARM  
  *  @details V2.1.0 25.11.2012 Ferdinand Englberger
  *           - C99 data types
  *  @details V2.0.0 01.10.2011 Ferdinand Englberger
  *           - Start version LPC1769
  ******************************************************************************
  */
#include <stdio.h>
#include "cmsis_os.h"       // ARM::CMSIS:RTOS:Keil RTX
#include "robterminal.h"    // ETTI4::ETTI4:Embedded laboratory:Robotic arm
#include "anxS20ser.h"
#include "max_II_configurator.h" // ETTI4::ETTI4:Embedded laboratory:Configurator

/** @brief Variable to store servo information
  */
 SrvCtr_t arm_servo[6]= 
 {
   [0].servonr = SRV_BASEROT, [0].servotime = SERVOCENTERTIME,
   [0].servominlimit = SERVOSTARTMIN, [0].servomaxlimit = SERVOSTARTMAX,
   [0].DispLine = 1, [0].DispCol = SRV_TXT_LEFT,
   
   [1].servonr = SRV_BASELIFT, [1].servotime = SERVOCENTERTIME, 
   [1].servominlimit = SERVOSTARTMIN, [1].servomaxlimit = SERVOSTARTMAX,
   [1].DispLine = 1, [1].DispCol = SRV_TXT_RIGHT,
   
   [2].servonr = SRV_SHOULDER, [2].servotime = SERVOCENTERTIME, 
   [2].servominlimit = SERVOSTARTMIN, [2].servomaxlimit = SERVOSTARTMAX,
   [2].DispLine = 2, [2].DispCol = SRV_TXT_LEFT,
   
   [3].servonr = SRV_GRIPPLIFT, [3].servotime = SERVOCENTERTIME, 
   [3].servominlimit = SERVOSTARTMIN, [3].servomaxlimit = SERVOSTARTMAX,
   [3].DispLine = 2, [3].DispCol = SRV_TXT_RIGHT,
   
   [4].servonr = SRV_GRIPPROT, [4].servotime = SERVOCENTERTIME, 
   [4].servominlimit = SERVOSTARTMIN, [4].servomaxlimit = SERVOSTARTMAX,
   [4].DispLine = 3, [4].DispCol = SRV_TXT_LEFT,
   
   [5].servonr = SRV_GRIPPER, [5].servotime = SERVOCENTERTIME, 
   [5].servominlimit = SERVOSTARTMIN+150, 
   [5].servomaxlimit =SERVOSTARTMAX-300, 
   [5].DispLine = 3, [5].DispCol = SRV_TXT_RIGHT
 };
 
/**
  * @brief  Main thread robotic arm
  */
int32_t main(void)
{
  uint32_t temp;
  int32_t i;
  
  e4configRobarm();
  
  TRMinit();
  anxS20init();
  // clear display
  TRMclearDisplay();
  printf("Experiment Robotic Arm   Firmware Vx.xx\n"
         "Base Turn : 1500 us Base Lift : 1500 us\n"
         "Shoulder  : 1500 us Grip Lift : 1500 us\n"
         "Grip Turn : 1500 us Gripper   : 1500 us\n");
  
  // Read Firmware Version
  temp = anxS20GetByte();
  TRMsetPos (0,35);
  printf("%1u.%02u", (temp/100), temp%100);
  fflush(stdout);
  // Center robotic arm servos
  for(i=0;i<6;i++)
  { 
     // Hier den Programmcode zur Einstellung der Centerposition 
     // und zur Einstellung der Servogeschwindigkeit einfügen
  }        
 for(;;)
 {
   temp = getchar();
   switch(temp)
   {
     // base rotation servo
     case 'x':
     case 'X': servotimeUpdate(&arm_servo[0], PWMdown);
               break;
     case 'd':
     case 'D': servotimeUpdate(&arm_servo[0], PWMup);             
               break;

     // base lift servo 
     case 'c':
     case 'C': servotimeUpdate(&arm_servo[1], PWMdown);
               break;
     case 'f':
     case 'F': servotimeUpdate(&arm_servo[1], PWMup);
               break;
     // pin joint 1 servo
     case 'v':
     case 'V': servotimeUpdate(&arm_servo[2], PWMdown);
               break;
     case 'g':
     case 'G': servotimeUpdate(&arm_servo[2], PWMup);
               break;

     // pin joint 2 servo
     case 'b':
     case 'B': servotimeUpdate(&arm_servo[3], PWMdown);
               break;
     case 'h':
     case 'H': servotimeUpdate(&arm_servo[3], PWMup);
               break;

     // grabber rotation servo
     case 'n':
     case 'N': servotimeUpdate(&arm_servo[4], PWMdown);
               break;
     case 'j':
     case 'J': servotimeUpdate(&arm_servo[4], PWMup);
               break;

     // grabber servo 
     case 'm':
     case 'M': servotimeUpdate(&arm_servo[5], PWMdown);
               break;
     case 'k':
     case 'K': servotimeUpdate(&arm_servo[5], PWMup);
               break;
     default: break;
   }  
 }
}
