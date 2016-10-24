/**
  ******************************************************************************
  * @file      ea_test3.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2
  * @version   V3.0.0
  * @date      07.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institut 4
  * @brief Template - Program part  EA3
  * @details Test of
  *          - init_position()
  *          - get_position()
  ******************************************************************************
  * @details Einstellung Signalverteiler: \b 01
  ******************************************************************************
  *	@par History:
    *  @details V3.0.0 Ferdinand Englberger
  *           - Pack description updated 
  *           - RTOS included  #
  *  @details V2.2.0 17.02.2014 Ferdinand Englberger
  *           - copyright clause
  *  @details V2.1.0 02.11.2012 Ferdinand Englberger
  *           - C99 data types   
  *  @details V2.0.0 08.09.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */
#include "cmsis_os.h"             // ARM::CMSIS:RTOS:Keil RTX
#include "max_II_configurator.h"  // ETTI4::ETTI4:Embedded laboratory:Configurator
#include "tastenleds.h"                 // ETTI4::ETTI4:Embedded laboratory:GPIO-EA
#include "possensor.h"                  // ETTI4::ETTI4:Embedded laboratory:GPIO-EA

/**
  * @brief  Main Thread
  */
int32_t main(void)
{
		e4configAufzug();
    init_leds_buttons();
		init_position();
	
    for(;;)
    {
			
			uint32_t sensor;
			uint32_t button;
			
			osDelay(1);
			
			sensor = get_position();
			setLeds(sensor);
			
			
    }
}
