/**
  ******************************************************************************
  * @file      Robterminal.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  * @author    Student2
  * @version   V4.1.0
  * @date      05.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institute 4
  * @brief   Template - Exercise robotic arm with UART-control
  * @details part 1: Control of terminal
  ******************************************************************************
  * @details signal router setting: @b 50
  ******************************************************************************
  * @par History:
  *  @details V4.1.0 Ferdinand Englberger
  *           - Pack description updated  
  *  @details V3.0.0 17.01.2014 Ferdinand Englberger
  *           - CMSIS RTOS API instead of RLARM  
  *  @details V2.1.0 25.11.2012 Ferdinand Englberger
  *           - C99 data types
  *  @details V2.0.0 06.10.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */
#include "cmsis_os.h"             // ARM::CMSIS:RTOS:Keil RTX
#include "max_II_configurator.h"  // ETTI4::ETTI4:Embedded laboratory:Configurator
#include "robterminal.h"                // ETTI4::ETTI4:Embedded laboratory:Robotic arm
#include "stdio.h"

extern osSemaphoreId STDOUTsem;
extern osSemaphoreId STDINsem;
extern osMessageQId STDINmsgQ; //???


//uint32_t i = 0;
//char input[100];		//Für Debugging
/**
  * @brief  Main thread part terminal
  */

int32_t main(void)
{
   e4configRobarm();
	 TRMinit();
	 uint32_t temp;
   //uint32_t i = 0;
   //char input[100];
	 NVIC_SetPriorityGrouping(0);
	
   for(;;)
   {
		 //printf("Bitte Text eingeben:\n");
		 
		 //osSemaphoreWait(STDINsem, osWaitForever);
		 
		 putchar(temp = getchar());
		 
		 fflush(stdout);
		 
		 
		 
		 /*
		 do{
				temp = getchar();
				input[i] = temp;
				i++;
		 //}while(temp != 0x0D);
		 }while(temp != 0);
			
		 //input[i] = 0;
		 input[i] = temp;
		 input[i+1] = '\n';
		 input[i+2] = '\r';
		 i = 0;
		*/
		 //printf("Ihr Text: %s\n", &input[0]);
			
		 //osSemaphoreRelease(STDINsem);
		 
		 //osDelay(30);
		// TRMclearDisplay();
		 
   }
}
