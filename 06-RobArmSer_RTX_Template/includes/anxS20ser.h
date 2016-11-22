/**
  ******************************************************************************
  * @file      anxS20ser.h
  * @author    Prof. Dr.-Ing. Ferdinand Englberger
  * @author    Student1
  * @author    Student2
  * @version   V4.1.0
  * @date      05.01.2016
  * @copyright 2011 - 2016 UniBw M - ETTI - Institute 4
  * @brief   Template - Exercise robotic arm  with UART-control - 
  *                     ANX-S20 header
  ******************************************************************************
  * @par History:
  *  @details V4.1.0 Ferdinand Englberger  
  *           - Pack description updated
  *           - Semaphore to protect commands  
  *           - Use only one funtion to update PWM pulse duration  
  *  @details V3.0.1 23.11.2015 Ferdinand Englberger
  *           - Updated comment in macro definition  
  *  @details V3.0.0 17.01.2014 Ferdinand Englberger
  *           - CMSIS RTOS API instead of RLARM  
  *  @details V2.1.0 25.11.2012 Ferdinand Englberger
  *           - C99 data types
  *  @details V2.0.0 06.10.2011 Ferdinand Englberger
  *           - Template 1769 2011
  ******************************************************************************
  */ 
#ifndef __ANXS20_SER_H__
#define __ANXS20_SER_H__
#include <stdint.h>

#define SERVOCENTERTIME 1500  /*!< Servo center pulse width (us)  */
#define SERVOSTARTMIN   1000  /*!< Servo minimal pulse width (us) */
#define SERVOSTARTMAX   2000  /*!< Servo maximal pulse width (us) */
#define SERVOMODTIME   5  /*!< Servo adjustment step (us)
                                    in up/down-routine  */
#define SRV_BASEROT     17 /*!< Servo-Nr. base rotation servo */
#define SRV_BASELIFT    16  /*!< Servo-Nr. base lift servo */
#define SRV_SHOULDER    15  /*!< Servo-Nr. shoulder servo */
#define SRV_GRIPPLIFT   14  /*!< Servo-Nr. gripper lift servo */
#define SRV_GRIPPROT    13  /*!< Servo-Nr. gripper rotation servo */
#define SRV_GRIPPER     12  /*!< Servo-Nr. gripper servo */

#define SRV_TXT_LEFT    12 /*!< text position left  for servo pulse width */
#define SRV_TXT_RIGHT   32  /*!< text position right for servo pulse width */

#define ANXS20_IIADR  97   /*!< IIC-address of anxS20 servo controller */

/** @brief data type so store servo information
  */
typedef struct { 
     uint16_t servonr;       /*!< servo connection number on servo controller*/
     uint16_t servotime;     /*!< pulse width in us   */
     uint16_t servominlimit; /*!< minimal allowed pulse width in us  */
     uint16_t servomaxlimit; /*!< maximal allowed pulse width in us  */
     uint8_t DispLine;       /*!< pulse width text position - line (0-3) */
     uint8_t DispCol;        /*!< pulse width text position - column (0-39) */
    } SrvCtr_t;

/** @brief Data type to store direction of pwm update */
typedef enum {PWMup, PWMdown} 
                 UpdateDirection; /*!< Direction of PWM update */
    
void anxS20init(void);
void anxS20sendchar(uint32_t ch);
int32_t anxS20getAck(void);
uint32_t anxS20GetByte(void);
int32_t anxS20setservopos(uint32_t servo, uint32_t positionus, 
                          uint32_t minlimit, uint32_t maxlimit);
int32_t anxS20setservospeed(uint32_t servo, uint32_t speed);
void servotimeUpdate(SrvCtr_t * armsrv_ptr, UpdateDirection direction);
#endif
