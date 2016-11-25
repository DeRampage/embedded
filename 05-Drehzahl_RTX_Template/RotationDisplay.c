/**
  ******************************************************************************
  * @file      RotationDisplay.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.5.0
  * @date      21.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief Exercise engine speed with RTX - display functions
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
#include "drehzahl.h" // ETTI4::ETTI4:Embedded laboratory:Revolution measurement
#include "EmbSysARMDisp.h"  // ETTI4::ETTI4:Embedded laboratory:Displays
#include "stdio.h"
/**
  * @brief  display function
  * @details The display function checks, if the content of "old" and
  *          the "new" object is different. If yes, the new value is displayed and
  *          the content of the new value is copied to the old value object.
  * @param [in, out] pDisp  : Pointer to display desciptor  
  * @param  [in, out] oldStatusPtr : pointer to the "old" motor status object
  * @param  [in] newStatusPtr : pointer to the "new" motor status object
  */
void updateDisplay(ETTI4disp_t * pDisp, 
                   drehzahl_t * oldStatusPtr, drehzahl_t * newStatusPtr)
{
	if(newStatusPtr->direction != oldStatusPtr->direction){
		
		setPosETTI4display(pDisp, 1, 8);
		if(newStatusPtr->direction == Right){
			printf("Right");
		}else{
			printf("Left ");
		}
		oldStatusPtr->direction = newStatusPtr->direction;
	}
	
	if(newStatusPtr->speedstep != oldStatusPtr->speedstep){
		
		setPosETTI4display(pDisp, 2, 12);
		printf("%2d", newStatusPtr->speedstep);
		
		oldStatusPtr->speedstep = newStatusPtr->speedstep;
	}
	
	if(newStatusPtr->status != oldStatusPtr->status){
		
		setPosETTI4display(pDisp, 1, 16);
		if(newStatusPtr->status == Run){
			printf("ON ");
		}else{
			printf("OFF");
		}
		oldStatusPtr->status = newStatusPtr->status;
	}
	
	if(newStatusPtr->drehzahl != oldStatusPtr->drehzahl){
		
		setPosETTI4display(pDisp, 3, 10);
		printf("%2d,%d", newStatusPtr->drehzahl/10, newStatusPtr->drehzahl%10 );
		oldStatusPtr->drehzahl = newStatusPtr->drehzahl;
	}
	setPosETTI4display(pDisp, 0, 0);
}
