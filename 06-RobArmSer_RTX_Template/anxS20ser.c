/**
  ******************************************************************************
  * @file      anxS20ser.c
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  * @author    Student2
  * @version   V4.1.0
  * @date      05.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institute 4
  * @brief   Template - functions to control the ANX-S20 (serial)
  ******************************************************************************
  * @details Attention: The control of ANX-S20 using the serial interface is 
  *          not really robust. It es necessary to check a command using 
  *          ACK. It might be necessary to transfer a command several times, 
  *          before the servo controller responds.
  ******************************************************************************
  *	@par History:
  *  @details V4.1.0 Ferdinand Englberger  
  *           - Pack description updated
  *           - Semaphore to protect commands   
  *           - Use only one funtion to update PWM pulse duration    
  *  @details V3.0.0 17.01.2014 Ferdinand Englberger
  *           - CMSIS RTOS API instead of RLARM  
  *  @details V2.1.0 25.11.2012 Ferdinand Englberger
  *           - C99 data types 
  *  @details V2.0.0 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */
#include "anxS20ser.h"

/**
  * @brief  Function to initialize the servo controller-interface
  * @details UART1
  */
void anxS20init(void)
{
    
}

/**
  * @brief  Function to transmit one byte using UART1
  * @param  ch : character to send
  */
void anxS20sendchar(uint32_t ch)
{

}


/**
  * @brief  IRQ-Handler for reception of characters from servo controller
  * @details the received character is transmitted using the mailbox.
  *          If the mailbox is full the received character is rejected.
  */
void __anxS20__IRQHandler(void)
{

}


/**
  * @brief  function to read ACK from servo controller
  * @details the anx-S20-servo controller transmits his
  *          IIC-address to acknowledge, the reception of a valid 
  *          command. The function waits for Acknowledge for 
  *          a maximum time of 20 ms.
  * @retval "Acknowledge status": can be:
  *              @arg 1 ACK received
  *              @arg 0 no ACK received or timeout
  */
int32_t anxS20getAck(void)
{

}


/**
  * @brief  function reads one Byte from servo controller
  * @details Normally this is the firmware version number
  * @retval "read value": can be
  *               @arg read value
  *               @arg 999, if no valid character is received after 5 retries
  */
uint32_t anxS20GetByte(void)
{

}


/**
  * @brief  function to set a servo to a certain position
  * @details The limit parameters are used to simplify the program.
  *          This is, due to that not the first 6 servos are used to 
  *          control the robotic arm.
  *          Usually the limits of all 20 servos should be stored. 
  *          Due to the risk of errors, this is not done here.
  * @param  servo      : servo number1-20
  * @param  positionus : pulse width of servo in us  1500 = 1.5 ms
  * @param  minlimit   : allowed minimum value of pulse width in us
  * @param  maxlimit   : allowed maximum value of pulse width in us
  * @retval Status : can be: 
  *               @arg 1 : ACK received
  *               @arg 0 : no ACK received
  */
int32_t anxS20setservopos(uint32_t servo, uint32_t positionus, 
                          uint32_t minlimit, uint32_t maxlimit)
{

}

/**
  * @brief function to set the speed to position a servo
  * @details speed to position in us/20 ms
  * @param  servo : Servo number 1-20
  * @param  speed : speed to position in us/20 ms
  * @retval Status : can be: 
  *               @arg 1 : ACK received
  *               @arg 0 : no ACK received
  */
int32_t anxS20setservospeed(uint32_t servo, uint32_t speed)
{
    
}

/**
  * @brief Function, which is called to modify the PWM pulse width 
  * @param  [in, out] armsrv_ptr : Pointer to the servo descriptor data
  * @param             direction : Direction of PWM change
  *                                @arg PWMup   : lengthen the PWM pulse
  *                                @arg PWMdown : reduce the PWM pulse
  */
void servotimeUpdate(SrvCtr_t * armsrv_ptr, UpdateDirection direction)
{

}
