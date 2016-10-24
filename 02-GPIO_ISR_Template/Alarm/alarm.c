/**
  ******************************************************************************
  * @file      alarm.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.0.0
  * @date      07.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institut 4
  * @brief Template - Program part to control alarm function
  ******************************************************************************
  * @details signal router adjustment: \b 01
  * @details alarm button  P0.28
  * @details alarm buzzer  P2.4
  ******************************************************************************
  * @par History:
  *  @details V3.0.0 Ferdinand Englberger
  *           - Pack description updated 
  *           - RTOS included 
  *           - Interrupt handler  
  *  @details V2.2.0 17.02.2014 Ferdinand Englberger
  *           - copyright clause  
  *  @details V2.1.0 02.11.2012 Ferdinand Englberger
  *           - C99 data types  
  *  @details V2.0.0 08.09.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */
#include "LPC17xx.h"                    // Device header
#include "cmsis_os.h"

extern osThreadId IDalarmThread;
#define SIG_ALARM_CHANGE 0x0001
/**
  * @brief  Function to initialize alarm capabilities
  */
void init_alarm(void)
{
	
	//GPIO CONFIG ALARM BUTTON
  LPC_PINCON->PINSEL1 = LPC_PINCON->PINSEL1 & ~(0x03000000); 					//0xFCFFFFFF; 
	LPC_PINCON->PINMODE1 = LPC_PINCON->PINMODE1 & ~(0x03000000); 				//0xFCFFFFFF; 
	LPC_PINCON->PINMODE_OD0 = LPC_PINCON->PINMODE_OD0 & ~(0x10000000);	//Für alle Eingänge: ~(0x1FF8003E); //0xE007FFC1; 
	
	
	//GPIO INTERRUPT CONFIG
	LPC_GPIOINT->IO0IntEnR = LPC_GPIOINT->IO0IntEnR | (0x10000000);//~(01<<28); //0x10000000; |= (0x1 << 28);//
	LPC_GPIOINT->IO0IntClr = 01<<28;
	
	LPC_SC->EXTMODE |= (1<<4);
	LPC_SC->EXTINT = 0x08;
	
	NVIC_SetPriority(EINT3_IRQn, 0xA);
	NVIC_ClearPendingIRQ(EINT3_IRQn);
	NVIC_EnableIRQ(EINT3_IRQn);
		
	//GPIO CONFIG ALARM SUMMER
	LPC_PINCON->PINSEL4 = LPC_PINCON->PINSEL4 & ~(0x00000300); 					//Für alles: 0x000003FF
	LPC_PINCON->PINMODE4 = LPC_PINCON->PINMODE4 & ~(0x00000300);				//Für alles: 0x000003FF
	LPC_PINCON->PINMODE_OD2 = LPC_PINCON->PINMODE_OD2 & ~(0x000000010);	//Für alles: 0x0000001F
	
	LPC_GPIO2->FIOSET = 0x000000010;																	//Reset Alarm
	LPC_GPIO0->FIODIR = LPC_GPIO0->FIODIR & ~(1<<28);//| ~(1<<28);//0x10000000);			//Für alle Eingänge: ~(0x1FF8003E)	//INPUT daher 0 erzwingen mit &
	LPC_GPIO2->FIODIR = LPC_GPIO2->FIODIR | (1<<4);
	
}

/**
  * @brief  Function to read alarm button
  * @retval alarmButton : position of alarm button, can be
  *                        @arg 1 = button <b>pressed</b>
  *                        @arg 0 = button <b>released</b>
  */
uint32_t getAlarm(void)
{
	uint32_t alarm;
	alarm = (LPC_GPIO2->FIOPIN1 >>4); //& 0x01;
	return alarm;	
}

/**
  * @brief  IRQ-Handler to detect change of alarm key
  */
void EINT3_IRQHandler(void)
{
	//LPC_SC->EXTINT = 0x08;
	LPC_GPIOINT->IO0IntClr = (1<<28);
	osSignalSet(IDalarmThread, SIG_ALARM_CHANGE);
}


/**
  * @brief  Function to control alarm buzzer
  * @param  alarm : can be
  *                 @arg 1 = buzzer @b on
  *                 @arg 0 = buzzer @b off
  */
void alarmsig(uint32_t alarm)
{
	if(alarm == 1){
		LPC_GPIO2->FIOCLR = 0x000000010;	
	}else{
		LPC_GPIO2->FIOSET = 0x000000010;	
	}
	
}
