/**
  ******************************************************************************
  * @file      terminal.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  * @author    Student2
  * @version   V4.1.0
  * @date      05.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institute 4
  * @brief     Exercise robotic arm  with UART-control
  * @details Template - functions to control the serial terminal
  ******************************************************************************
  * @details resources:
  *          - signal router setting: @b 50
  ******************************************************************************
  * @par History:
  *  @details V4.1.0 Ferdinand Englberger
  *           - Pack description updated  
  *  @details V4.0.0 26.05.2015 Ferdinand Englberger
  *           - Use Compiler pack instead of retarget.c  
  *  @details V3.0.0 17.01.2014 Ferdinand Englberger
  *           - CMSIS RTOS API instead of RLARM  
  *  @details V2.1.0 25.11.2012 Ferdinand Englberger
  *           - C99 data types
  *  @details V2.0.0 06.10.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */


/**
  * @brief  Function to initialize the terminal interface
  * @details UART0, 19200 Baud, 8, n, 1
  */
void TRMinit(void)
{

}

/**
  * @brief  Function to redirect standard output to UART0
  * @param  ch : character to transmit
  * @retval int : transmitted character
  */
int32_t stdout_putchar(int32_t ch)
{

}


/**
  * @brief  Function to clear terminal display
  */
void TRMclearDisplay(void)
{

}


/**
  * @brief Function to set cursor position
  * @details
  * @verbatim
     The terminal itself requires these values
       line   1 -  4
       column 1 - 40
     The parameter value should be different, due to comparability reason 
     with parallel display

     parameter value
       line   0 -  3
       column 0 - 39
    @endverbatim
  * @param  linenr : line position, can be 0 - 3
  * @param  col    : column position, can be 0 - 39
  */
void TRMsetPos (uint32_t linenr, uint32_t col)
{

}

/**
  * @brief  IRQ-Handler for receiving of the terminal key values
  * @details The received values are transferred using the mailbox.
  *          If the mailbox is full the received value is rejected.
  * @retval None
  */
void ___Terminal__IRQHandler(void)
{

}


/**
  * @brief  function to redirect standard input to UART0
  * @details Exchange of the key values y and z is required, to meet the 
  *          requirements of a German keyboard.
  * @retval  "received character"
  */
int32_t stdin_getchar(void)
{

}
