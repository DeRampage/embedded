/**
  ******************************************************************************
  * @file      tastenleds.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.0.0
  * @date      07.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institut 4
  * @brief Template - Program part to check buttons and control leds
  ******************************************************************************
  * @details signal router adjustment: @b 01
  * @details buttons:
  *          - base frame P0.22 - P0.19
  *          - cabine     P0.27 - P0.24
  *          - emergency stop switch P0.23
  * @details Leds:
  *          - base frame P1.18 - P1.21
  *          - cabine  P1.22 - P1.25 
  ******************************************************************************
  * @par History:
  *  @details V3.0.0 Ferdinand Englberger
  *           - Pack description updated 
  *           - RTOS included  
  *  @details V2.2.0 17.02.2014 Ferdinand Englberger
  *           - copyright clause
  *  @details V2.1.0 23.10.2013 Ferdinand Englberger
  *           - C99 data types  
  *  @details V2.0.0 08.09.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */  
#include "LPC17xx.h"                    // Device header


/**
  * @brief  Function to initialize the pins for leds, buttons and emergency stop switch
  */
void init_leds_buttons(void)
{
	//GPIO Port 0 INPUT
	
	/* 
	//INPUT DER SENSOREN
	LPC_PINCON->PINSEL0 = LPC_PINCON->PINSEL0 & ~(0x00000FFC); //0xFFFFF003;
	LPC_PINCON->PINMODE0 = LPC_PINCON->PINMODE0 & ~(0x00000FFC); //0xFFFFF003;
  */
	
	//INPUT DER TASTER
	LPC_PINCON->PINSEL1 = LPC_PINCON->PINSEL1 & ~(0x00FFFFC0); //0xFF00003F; 
	LPC_PINCON->PINMODE1 = LPC_PINCON->PINMODE1 & ~(0x00FFFFC0); //0xFF00003F; 
	LPC_PINCON->PINMODE_OD0 = LPC_PINCON->PINMODE_OD0 & ~(0x0FF80000);//Für alle Eingänge: ~(0x1FF8003E); //0xE007FFC1; 
	
	/*
	//INPUT DES ALARMS
	LPC_PINCON->PINSEL1 = LPC_PINCON->PINSEL1 & ~(0x03000000); //0xFCFFFFFF; 
	LPC_PINCON->PINMODE1 = LPC_PINCON->PINMODE1 & ~(0x03000000); //0xFCFFFFFF; 
	LPC_PINCON->PINMODE_OD0 = LPC_PINCON->PINMODE_OD0 & ~(0x10000000);//Für alle Eingänge: ~(0x1FF8003E); //0xE007FFC1; 
	*/
	
	
	//GPIO Port 1 OUTPUT LED
	LPC_PINCON->PINSEL3 = LPC_PINCON->PINSEL3 & ~(0x000FFFF0);
	LPC_PINCON->PINMODE3 = LPC_PINCON->PINMODE3 & ~(0x000FFFF0);
	LPC_PINCON->PINMODE_OD1 = LPC_PINCON->PINMODE_OD1 & ~(0x03FC0000);
	
	/*
	//GPIO Port 2 OUTPUT MOTOR-CONTROL
	LPC_PINCON->PINSEL4 = LPC_PINCON->PINSEL4 & ~(0x000003FF);
	LPC_PINCON->PINMODE4 = LPC_PINCON->PINMODE4 & ~(0x000003FF);
	LPC_PINCON->PINMODE_OD2 = LPC_PINCON->PINMODE_OD2 & ~(0x00000001F);
	*/
	
	//GPIO Direction & PRESET 
	
	//LPC_GPIO0->FIOCLR = 0x0FF80000; //Für alle Eingänge: 0x1FF8003E;  //Notwendig bei INPUT?
	LPC_GPIO1->FIOCLR = 0x03FC0000; 
	//LPC_GPIO2->FIOCLR = 0x00000001F;
	
		
	LPC_GPIO0->FIODIR = LPC_GPIO0->FIODIR | ~(0x0FF80000);			//Für alle Eingänge: ~(0x1FF8003E)			//INPUT daher 0 erzwingen mit &
	LPC_GPIO1->FIODIR = LPC_GPIO1->FIODIR | 0x03FC0000;   			//OUTPUT daher 1 erzwingen mit |
	//LPC_GPIO2->FIODIR = LPC_GPIO2->FIODIR | (1<<4);				//OUTPUT daher 1 erzwingen mit |
	//LPC_GPIO2->FIODIR = LPC_GPIO2->FIODIR | 0xF;
}

/**
  * @brief  function to control the leds
  * @details
  * @verbatim
    control word structure
       Bit 7..4 cabine leds     OG3 OG2 OG1 EG
       Bit 3..0 base frame leds OG3 OG2 OG1 EG
    @endverbatim

  * @param  ledson : the lower 8 bit contain the code for the leds.
  *                  @arg Bit = 1 => LED on
  *                  @arg Bit = 0 => LED off
  */
void setLeds(uint32_t ledson)
{
	uint32_t leds = (ledson << 18);
	LPC_GPIO1->FIOSET = leds & 0x03FC0000;			//Verhinderung der Ansteuerung "falscher Pins"
	LPC_GPIO1->FIOCLR = ~leds & 0x03FC0000;			// gesetzte Bits ergeben einen geschützten Bereich  
	
	//ZWEITE VLLT BESSERE MÖGLICHKEIT?
	//uint32_t leds = (ledson << 2);
	//LPC_GPIO1->FIOSETU = (leds << 2) & 0x03FC;
	//LPC_GPIO1->FIOCLRU = ~(leds << 2) & 0x03FC;
}

/**
  * @brief  Function reads buttons from base frame and cabine.
  * @details
  * @verbatim
    structure of the read information
       Bit 7..4 cabine values     OG3 OG2 OG1 EG
       Bit 3..0 base frame values OG3 OG2 OG1 EG
    @endverbatim
  * @return State of button :
  *         @arg Bit = 1 => button pressed
  *         @arg Bit = 0 => button released
  */
uint32_t getbutton(void)
{
	uint32_t button;
	uint32_t cabin;
	button = (LPC_GPIO0->FIOPIN2 >> 3) & 0x0F;
	cabin = (LPC_GPIO0->FIOPIN3 & 0x0F) << 4;
	
	button = button + cabin;
	
  return button;
}

/**
  * @brief  Function to read the emergency stop switch
  * @return emergency stop state : can be
  *                        @arg 1 => emergency stop on
  *                        @arg 0 => emergency stop off
  */
uint32_t getNothalt(void)
{
	uint32_t emergency;
	emergency = (LPC_GPIO0->FIOPIN2 >> 7) & 0x01;
	return emergency;
}
