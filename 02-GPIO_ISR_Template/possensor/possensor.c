/**
  ******************************************************************************
  * @file      possensor.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.0.0
  * @date      07.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institut 4
  * @brief Template - Program part to read postion sensor values
  ******************************************************************************
  * @details signal router adjustment: \b 01
  * @details position sensors:
  *          - from low to high P0.1 - P0.5
  ******************************************************************************
  * @par History:
  *  @details V3.0.0 Ferdinand Englberger
  *           - Pack description updated 
  *           - RTOS included    
  *  @details V2.2.0 17.02.2014 Ferdinand Englberger
  *           - copyright clause  
  *  @details V2.1.0 02.11.2012 Ferdinand Englberger
  *           - C99 data types  
  *  @details V2.0.0 08.09.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */
#include "LPC17xx.h"                    // Device header


/**
  * @brief  Function to initialize the pins for position sensors
  */
void init_position(void)
{
	LPC_PINCON->PINSEL0 = LPC_PINCON->PINSEL0 & ~(0x00000FFC); //0xFFFFF003;
	LPC_PINCON->PINMODE0 = LPC_PINCON->PINMODE0 & ~(0x00000FFC); //0xFFFFF003;

	LPC_PINCON->PINMODE_OD0 = LPC_PINCON->PINMODE_OD0 & ~(0x0000003E); //0xE007FFC1; 
	
	LPC_GPIO0->FIOCLR = 0x0000003E; //Für alle Eingänge: 0x1FF8003E
	LPC_GPIO0->FIODIR = LPC_GPIO0->FIODIR & ~(0x0000003E);			//Für alle Eingänge: ~(0x1FF8003E)
}

/**
  * @brief  Function to read values from position sensors
  * @details position sensors:
  *          - from low to high P0.1 - P0.5
  * @retval Position information
  */
uint32_t get_position(void)
{
	uint32_t position;
	position = (LPC_GPIO0->FIOPIN0 >> 1) & 0x1F;
	return position;
}
