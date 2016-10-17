/**
  ******************************************************************************
  * @file      RTXmainUserTimSig.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2  
  * @version   V4.1.0
  * @date      20.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institute 4
  * @brief   Exercise RTX - Part User timer with Signals
  ******************************************************************************
  * @par History:
  *  @details V4.0.0 Ferdinand Englberger
  *           - Initial version
  ******************************************************************************
  */
#include "max_II_configurator.h"  // ETTI4::ETTI4:Embedded laboratory:Configurator


/**
  * @brief Callback function of led1 user timer
  * @param arg : Pointer to parameter variable (not used)
  */
void led1Callback(void const * arg)
{

}

/**
  * @brief Callback function of led2 user timer
  * @param arg : Pointer to parameter variable (not used)
  */
void led2Callback(void const * arg)
{

}


/**
  * @brief  Main thread
  * @details Config signal router and blinks led
  */
int32_t main(void)
{
  
   e4configRTX1();
  
   for(;;)
   {
   }
}
