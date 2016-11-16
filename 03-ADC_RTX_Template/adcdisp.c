/**
  ******************************************************************************
  * @file      ADCdisp.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  *	@author    Student2  
  * @version   V2.1.0
  * @date      18.12.2015
  * @copyright 2011 - 2015 UniBw M - ETTI - Institute 4
  * @brief   Exercise ADC with RTX - Display function
  ******************************************************************************
  * @par History:
  *  @details V2.1.0 Ferdinand Englberger
  *           - Use new display library V6.0.0    
  *  @details V2.0.0 09.01.2014 Ferdinand Englberger
  *           - Use RTE v1.0.0
  *  @details V1.1.0 18.11.2012 Ferdinand Englberger
  *           - C99 data types   
  *  @details V1.0.0 22.09.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */
#include "adc_RTX.h"             // ETTI4::ETTI4:Embedded laboratory:ADC-RTX
#include "EmbSysARMDisp.h"       // ETTI4::ETTI4:Embedded laboratory:Displays
#include "stdio.h"

extern ETTI4disp_t myDisplay;
/**
  * @brief  output function for ADC results 
  * @param  [in] PtrADCmail : Pointer to result data object
  * @retval None
  */
void adcDisplay(ETTI4disp_t *pDisp, myADCmail_t * PtrADCmail)
{
	setPosETTI4display (pDisp, 0, 0);
	
  printf("P1:%d.%dV->\n", PtrADCmail->ADCresult[0].dVolt / 10, PtrADCmail->ADCresult[0].dVolt % 10);
	horbarETTI4display(&myDisplay, 0, 9, (PtrADCmail->ADCresult[0].adcValue * 2) / 15);
	
	printf("P2:%d.%dV->\n", PtrADCmail->ADCresult[1].dVolt / 10, PtrADCmail->ADCresult[1].dVolt % 10);
	horbarETTI4display(&myDisplay, 1, 9, (PtrADCmail->ADCresult[1].adcValue * 2) / 15);
	
	printf("P3:%d.%dV->\n", PtrADCmail->ADCresult[2].dVolt / 10, PtrADCmail->ADCresult[2].dVolt % 10);
	horbarETTI4display(&myDisplay, 2, 9, (PtrADCmail->ADCresult[2].adcValue * 2) / 15);
	
	printf("P4:%d.%dV->\n", PtrADCmail->ADCresult[3].dVolt / 10, PtrADCmail->ADCresult[3].dVolt % 10);
	horbarETTI4display(&myDisplay, 3, 9, (PtrADCmail->ADCresult[3].adcValue * 2) / 15);
	
}
