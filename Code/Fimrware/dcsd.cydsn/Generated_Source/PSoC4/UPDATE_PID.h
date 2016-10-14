/*******************************************************************************
* File Name: UPDATE_PID.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the UPDATE_PID
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_UPDATE_PID_H)
#define CY_TCPWM_UPDATE_PID_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} UPDATE_PID_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  UPDATE_PID_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define UPDATE_PID_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define UPDATE_PID_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define UPDATE_PID_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define UPDATE_PID_QUAD_ENCODING_MODES            (0lu)
#define UPDATE_PID_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define UPDATE_PID_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define UPDATE_PID_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define UPDATE_PID_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define UPDATE_PID_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define UPDATE_PID_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define UPDATE_PID_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define UPDATE_PID_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define UPDATE_PID_TC_RUN_MODE                    (0lu)
#define UPDATE_PID_TC_COUNTER_MODE                (0lu)
#define UPDATE_PID_TC_COMP_CAP_MODE               (2lu)
#define UPDATE_PID_TC_PRESCALER                   (7lu)

/* Signal modes */
#define UPDATE_PID_TC_RELOAD_SIGNAL_MODE          (0lu)
#define UPDATE_PID_TC_COUNT_SIGNAL_MODE           (3lu)
#define UPDATE_PID_TC_START_SIGNAL_MODE           (0lu)
#define UPDATE_PID_TC_STOP_SIGNAL_MODE            (0lu)
#define UPDATE_PID_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define UPDATE_PID_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define UPDATE_PID_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define UPDATE_PID_TC_START_SIGNAL_PRESENT        (0lu)
#define UPDATE_PID_TC_STOP_SIGNAL_PRESENT         (0lu)
#define UPDATE_PID_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define UPDATE_PID_TC_INTERRUPT_MASK              (0lu)

/* PWM Mode */
/* Parameters */
#define UPDATE_PID_PWM_KILL_EVENT                 (0lu)
#define UPDATE_PID_PWM_STOP_EVENT                 (0lu)
#define UPDATE_PID_PWM_MODE                       (4lu)
#define UPDATE_PID_PWM_OUT_N_INVERT               (0lu)
#define UPDATE_PID_PWM_OUT_INVERT                 (0lu)
#define UPDATE_PID_PWM_ALIGN                      (0lu)
#define UPDATE_PID_PWM_RUN_MODE                   (0lu)
#define UPDATE_PID_PWM_DEAD_TIME_CYCLE            (0lu)
#define UPDATE_PID_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define UPDATE_PID_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define UPDATE_PID_PWM_COUNT_SIGNAL_MODE          (3lu)
#define UPDATE_PID_PWM_START_SIGNAL_MODE          (0lu)
#define UPDATE_PID_PWM_STOP_SIGNAL_MODE           (0lu)
#define UPDATE_PID_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define UPDATE_PID_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define UPDATE_PID_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define UPDATE_PID_PWM_START_SIGNAL_PRESENT       (0lu)
#define UPDATE_PID_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define UPDATE_PID_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define UPDATE_PID_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define UPDATE_PID_TC_PERIOD_VALUE                (9lu)
#define UPDATE_PID_TC_COMPARE_VALUE               (65535lu)
#define UPDATE_PID_TC_COMPARE_BUF_VALUE           (65535lu)
#define UPDATE_PID_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define UPDATE_PID_PWM_PERIOD_VALUE               (65535lu)
#define UPDATE_PID_PWM_PERIOD_BUF_VALUE           (65535lu)
#define UPDATE_PID_PWM_PERIOD_SWAP                (0lu)
#define UPDATE_PID_PWM_COMPARE_VALUE              (65535lu)
#define UPDATE_PID_PWM_COMPARE_BUF_VALUE          (65535lu)
#define UPDATE_PID_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define UPDATE_PID__LEFT 0
#define UPDATE_PID__RIGHT 1
#define UPDATE_PID__CENTER 2
#define UPDATE_PID__ASYMMETRIC 3

#define UPDATE_PID__X1 0
#define UPDATE_PID__X2 1
#define UPDATE_PID__X4 2

#define UPDATE_PID__PWM 4
#define UPDATE_PID__PWM_DT 5
#define UPDATE_PID__PWM_PR 6

#define UPDATE_PID__INVERSE 1
#define UPDATE_PID__DIRECT 0

#define UPDATE_PID__CAPTURE 2
#define UPDATE_PID__COMPARE 0

#define UPDATE_PID__TRIG_LEVEL 3
#define UPDATE_PID__TRIG_RISING 0
#define UPDATE_PID__TRIG_FALLING 1
#define UPDATE_PID__TRIG_BOTH 2

#define UPDATE_PID__INTR_MASK_TC 1
#define UPDATE_PID__INTR_MASK_CC_MATCH 2
#define UPDATE_PID__INTR_MASK_NONE 0
#define UPDATE_PID__INTR_MASK_TC_CC 3

#define UPDATE_PID__UNCONFIG 8
#define UPDATE_PID__TIMER 1
#define UPDATE_PID__QUAD 3
#define UPDATE_PID__PWM_SEL 7

#define UPDATE_PID__COUNT_UP 0
#define UPDATE_PID__COUNT_DOWN 1
#define UPDATE_PID__COUNT_UPDOWN0 2
#define UPDATE_PID__COUNT_UPDOWN1 3


/* Prescaler */
#define UPDATE_PID_PRESCALE_DIVBY1                ((uint32)(0u << UPDATE_PID_PRESCALER_SHIFT))
#define UPDATE_PID_PRESCALE_DIVBY2                ((uint32)(1u << UPDATE_PID_PRESCALER_SHIFT))
#define UPDATE_PID_PRESCALE_DIVBY4                ((uint32)(2u << UPDATE_PID_PRESCALER_SHIFT))
#define UPDATE_PID_PRESCALE_DIVBY8                ((uint32)(3u << UPDATE_PID_PRESCALER_SHIFT))
#define UPDATE_PID_PRESCALE_DIVBY16               ((uint32)(4u << UPDATE_PID_PRESCALER_SHIFT))
#define UPDATE_PID_PRESCALE_DIVBY32               ((uint32)(5u << UPDATE_PID_PRESCALER_SHIFT))
#define UPDATE_PID_PRESCALE_DIVBY64               ((uint32)(6u << UPDATE_PID_PRESCALER_SHIFT))
#define UPDATE_PID_PRESCALE_DIVBY128              ((uint32)(7u << UPDATE_PID_PRESCALER_SHIFT))

/* TCPWM set modes */
#define UPDATE_PID_MODE_TIMER_COMPARE             ((uint32)(UPDATE_PID__COMPARE         <<  \
                                                                  UPDATE_PID_MODE_SHIFT))
#define UPDATE_PID_MODE_TIMER_CAPTURE             ((uint32)(UPDATE_PID__CAPTURE         <<  \
                                                                  UPDATE_PID_MODE_SHIFT))
#define UPDATE_PID_MODE_QUAD                      ((uint32)(UPDATE_PID__QUAD            <<  \
                                                                  UPDATE_PID_MODE_SHIFT))
#define UPDATE_PID_MODE_PWM                       ((uint32)(UPDATE_PID__PWM             <<  \
                                                                  UPDATE_PID_MODE_SHIFT))
#define UPDATE_PID_MODE_PWM_DT                    ((uint32)(UPDATE_PID__PWM_DT          <<  \
                                                                  UPDATE_PID_MODE_SHIFT))
#define UPDATE_PID_MODE_PWM_PR                    ((uint32)(UPDATE_PID__PWM_PR          <<  \
                                                                  UPDATE_PID_MODE_SHIFT))

/* Quad Modes */
#define UPDATE_PID_MODE_X1                        ((uint32)(UPDATE_PID__X1              <<  \
                                                                  UPDATE_PID_QUAD_MODE_SHIFT))
#define UPDATE_PID_MODE_X2                        ((uint32)(UPDATE_PID__X2              <<  \
                                                                  UPDATE_PID_QUAD_MODE_SHIFT))
#define UPDATE_PID_MODE_X4                        ((uint32)(UPDATE_PID__X4              <<  \
                                                                  UPDATE_PID_QUAD_MODE_SHIFT))

/* Counter modes */
#define UPDATE_PID_COUNT_UP                       ((uint32)(UPDATE_PID__COUNT_UP        <<  \
                                                                  UPDATE_PID_UPDOWN_SHIFT))
#define UPDATE_PID_COUNT_DOWN                     ((uint32)(UPDATE_PID__COUNT_DOWN      <<  \
                                                                  UPDATE_PID_UPDOWN_SHIFT))
#define UPDATE_PID_COUNT_UPDOWN0                  ((uint32)(UPDATE_PID__COUNT_UPDOWN0   <<  \
                                                                  UPDATE_PID_UPDOWN_SHIFT))
#define UPDATE_PID_COUNT_UPDOWN1                  ((uint32)(UPDATE_PID__COUNT_UPDOWN1   <<  \
                                                                  UPDATE_PID_UPDOWN_SHIFT))

/* PWM output invert */
#define UPDATE_PID_INVERT_LINE                    ((uint32)(UPDATE_PID__INVERSE         <<  \
                                                                  UPDATE_PID_INV_OUT_SHIFT))
#define UPDATE_PID_INVERT_LINE_N                  ((uint32)(UPDATE_PID__INVERSE         <<  \
                                                                  UPDATE_PID_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define UPDATE_PID_TRIG_RISING                    ((uint32)UPDATE_PID__TRIG_RISING)
#define UPDATE_PID_TRIG_FALLING                   ((uint32)UPDATE_PID__TRIG_FALLING)
#define UPDATE_PID_TRIG_BOTH                      ((uint32)UPDATE_PID__TRIG_BOTH)
#define UPDATE_PID_TRIG_LEVEL                     ((uint32)UPDATE_PID__TRIG_LEVEL)

/* Interrupt mask */
#define UPDATE_PID_INTR_MASK_TC                   ((uint32)UPDATE_PID__INTR_MASK_TC)
#define UPDATE_PID_INTR_MASK_CC_MATCH             ((uint32)UPDATE_PID__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define UPDATE_PID_CC_MATCH_SET                   (0x00u)
#define UPDATE_PID_CC_MATCH_CLEAR                 (0x01u)
#define UPDATE_PID_CC_MATCH_INVERT                (0x02u)
#define UPDATE_PID_CC_MATCH_NO_CHANGE             (0x03u)
#define UPDATE_PID_OVERLOW_SET                    (0x00u)
#define UPDATE_PID_OVERLOW_CLEAR                  (0x04u)
#define UPDATE_PID_OVERLOW_INVERT                 (0x08u)
#define UPDATE_PID_OVERLOW_NO_CHANGE              (0x0Cu)
#define UPDATE_PID_UNDERFLOW_SET                  (0x00u)
#define UPDATE_PID_UNDERFLOW_CLEAR                (0x10u)
#define UPDATE_PID_UNDERFLOW_INVERT               (0x20u)
#define UPDATE_PID_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define UPDATE_PID_PWM_MODE_LEFT                  (UPDATE_PID_CC_MATCH_CLEAR        |   \
                                                         UPDATE_PID_OVERLOW_SET           |   \
                                                         UPDATE_PID_UNDERFLOW_NO_CHANGE)
#define UPDATE_PID_PWM_MODE_RIGHT                 (UPDATE_PID_CC_MATCH_SET          |   \
                                                         UPDATE_PID_OVERLOW_NO_CHANGE     |   \
                                                         UPDATE_PID_UNDERFLOW_CLEAR)
#define UPDATE_PID_PWM_MODE_ASYM                  (UPDATE_PID_CC_MATCH_INVERT       |   \
                                                         UPDATE_PID_OVERLOW_SET           |   \
                                                         UPDATE_PID_UNDERFLOW_CLEAR)

#if (UPDATE_PID_CY_TCPWM_V2)
    #if(UPDATE_PID_CY_TCPWM_4000)
        #define UPDATE_PID_PWM_MODE_CENTER                (UPDATE_PID_CC_MATCH_INVERT       |   \
                                                                 UPDATE_PID_OVERLOW_NO_CHANGE     |   \
                                                                 UPDATE_PID_UNDERFLOW_CLEAR)
    #else
        #define UPDATE_PID_PWM_MODE_CENTER                (UPDATE_PID_CC_MATCH_INVERT       |   \
                                                                 UPDATE_PID_OVERLOW_SET           |   \
                                                                 UPDATE_PID_UNDERFLOW_CLEAR)
    #endif /* (UPDATE_PID_CY_TCPWM_4000) */
#else
    #define UPDATE_PID_PWM_MODE_CENTER                (UPDATE_PID_CC_MATCH_INVERT       |   \
                                                             UPDATE_PID_OVERLOW_NO_CHANGE     |   \
                                                             UPDATE_PID_UNDERFLOW_CLEAR)
#endif /* (UPDATE_PID_CY_TCPWM_NEW) */

/* Command operations without condition */
#define UPDATE_PID_CMD_CAPTURE                    (0u)
#define UPDATE_PID_CMD_RELOAD                     (8u)
#define UPDATE_PID_CMD_STOP                       (16u)
#define UPDATE_PID_CMD_START                      (24u)

/* Status */
#define UPDATE_PID_STATUS_DOWN                    (1u)
#define UPDATE_PID_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   UPDATE_PID_Init(void);
void   UPDATE_PID_Enable(void);
void   UPDATE_PID_Start(void);
void   UPDATE_PID_Stop(void);

void   UPDATE_PID_SetMode(uint32 mode);
void   UPDATE_PID_SetCounterMode(uint32 counterMode);
void   UPDATE_PID_SetPWMMode(uint32 modeMask);
void   UPDATE_PID_SetQDMode(uint32 qdMode);

void   UPDATE_PID_SetPrescaler(uint32 prescaler);
void   UPDATE_PID_TriggerCommand(uint32 mask, uint32 command);
void   UPDATE_PID_SetOneShot(uint32 oneShotEnable);
uint32 UPDATE_PID_ReadStatus(void);

void   UPDATE_PID_SetPWMSyncKill(uint32 syncKillEnable);
void   UPDATE_PID_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   UPDATE_PID_SetPWMDeadTime(uint32 deadTime);
void   UPDATE_PID_SetPWMInvert(uint32 mask);

void   UPDATE_PID_SetInterruptMode(uint32 interruptMask);
uint32 UPDATE_PID_GetInterruptSourceMasked(void);
uint32 UPDATE_PID_GetInterruptSource(void);
void   UPDATE_PID_ClearInterrupt(uint32 interruptMask);
void   UPDATE_PID_SetInterrupt(uint32 interruptMask);

void   UPDATE_PID_WriteCounter(uint32 count);
uint32 UPDATE_PID_ReadCounter(void);

uint32 UPDATE_PID_ReadCapture(void);
uint32 UPDATE_PID_ReadCaptureBuf(void);

void   UPDATE_PID_WritePeriod(uint32 period);
uint32 UPDATE_PID_ReadPeriod(void);
void   UPDATE_PID_WritePeriodBuf(uint32 periodBuf);
uint32 UPDATE_PID_ReadPeriodBuf(void);

void   UPDATE_PID_WriteCompare(uint32 compare);
uint32 UPDATE_PID_ReadCompare(void);
void   UPDATE_PID_WriteCompareBuf(uint32 compareBuf);
uint32 UPDATE_PID_ReadCompareBuf(void);

void   UPDATE_PID_SetPeriodSwap(uint32 swapEnable);
void   UPDATE_PID_SetCompareSwap(uint32 swapEnable);

void   UPDATE_PID_SetCaptureMode(uint32 triggerMode);
void   UPDATE_PID_SetReloadMode(uint32 triggerMode);
void   UPDATE_PID_SetStartMode(uint32 triggerMode);
void   UPDATE_PID_SetStopMode(uint32 triggerMode);
void   UPDATE_PID_SetCountMode(uint32 triggerMode);

void   UPDATE_PID_SaveConfig(void);
void   UPDATE_PID_RestoreConfig(void);
void   UPDATE_PID_Sleep(void);
void   UPDATE_PID_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define UPDATE_PID_BLOCK_CONTROL_REG              (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define UPDATE_PID_BLOCK_CONTROL_PTR              ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define UPDATE_PID_COMMAND_REG                    (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define UPDATE_PID_COMMAND_PTR                    ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define UPDATE_PID_INTRRUPT_CAUSE_REG             (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define UPDATE_PID_INTRRUPT_CAUSE_PTR             ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define UPDATE_PID_CONTROL_REG                    (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__CTRL )
#define UPDATE_PID_CONTROL_PTR                    ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__CTRL )
#define UPDATE_PID_STATUS_REG                     (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__STATUS )
#define UPDATE_PID_STATUS_PTR                     ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__STATUS )
#define UPDATE_PID_COUNTER_REG                    (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__COUNTER )
#define UPDATE_PID_COUNTER_PTR                    ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__COUNTER )
#define UPDATE_PID_COMP_CAP_REG                   (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__CC )
#define UPDATE_PID_COMP_CAP_PTR                   ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__CC )
#define UPDATE_PID_COMP_CAP_BUF_REG               (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__CC_BUFF )
#define UPDATE_PID_COMP_CAP_BUF_PTR               ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__CC_BUFF )
#define UPDATE_PID_PERIOD_REG                     (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__PERIOD )
#define UPDATE_PID_PERIOD_PTR                     ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__PERIOD )
#define UPDATE_PID_PERIOD_BUF_REG                 (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define UPDATE_PID_PERIOD_BUF_PTR                 ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define UPDATE_PID_TRIG_CONTROL0_REG              (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define UPDATE_PID_TRIG_CONTROL0_PTR              ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define UPDATE_PID_TRIG_CONTROL1_REG              (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define UPDATE_PID_TRIG_CONTROL1_PTR              ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define UPDATE_PID_TRIG_CONTROL2_REG              (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define UPDATE_PID_TRIG_CONTROL2_PTR              ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define UPDATE_PID_INTERRUPT_REQ_REG              (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__INTR )
#define UPDATE_PID_INTERRUPT_REQ_PTR              ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__INTR )
#define UPDATE_PID_INTERRUPT_SET_REG              (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__INTR_SET )
#define UPDATE_PID_INTERRUPT_SET_PTR              ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__INTR_SET )
#define UPDATE_PID_INTERRUPT_MASK_REG             (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__INTR_MASK )
#define UPDATE_PID_INTERRUPT_MASK_PTR             ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__INTR_MASK )
#define UPDATE_PID_INTERRUPT_MASKED_REG           (*(reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__INTR_MASKED )
#define UPDATE_PID_INTERRUPT_MASKED_PTR           ( (reg32 *) UPDATE_PID_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define UPDATE_PID_MASK                           ((uint32)UPDATE_PID_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define UPDATE_PID_RELOAD_CC_SHIFT                (0u)
#define UPDATE_PID_RELOAD_PERIOD_SHIFT            (1u)
#define UPDATE_PID_PWM_SYNC_KILL_SHIFT            (2u)
#define UPDATE_PID_PWM_STOP_KILL_SHIFT            (3u)
#define UPDATE_PID_PRESCALER_SHIFT                (8u)
#define UPDATE_PID_UPDOWN_SHIFT                   (16u)
#define UPDATE_PID_ONESHOT_SHIFT                  (18u)
#define UPDATE_PID_QUAD_MODE_SHIFT                (20u)
#define UPDATE_PID_INV_OUT_SHIFT                  (20u)
#define UPDATE_PID_INV_COMPL_OUT_SHIFT            (21u)
#define UPDATE_PID_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define UPDATE_PID_RELOAD_CC_MASK                 ((uint32)(UPDATE_PID_1BIT_MASK        <<  \
                                                                            UPDATE_PID_RELOAD_CC_SHIFT))
#define UPDATE_PID_RELOAD_PERIOD_MASK             ((uint32)(UPDATE_PID_1BIT_MASK        <<  \
                                                                            UPDATE_PID_RELOAD_PERIOD_SHIFT))
#define UPDATE_PID_PWM_SYNC_KILL_MASK             ((uint32)(UPDATE_PID_1BIT_MASK        <<  \
                                                                            UPDATE_PID_PWM_SYNC_KILL_SHIFT))
#define UPDATE_PID_PWM_STOP_KILL_MASK             ((uint32)(UPDATE_PID_1BIT_MASK        <<  \
                                                                            UPDATE_PID_PWM_STOP_KILL_SHIFT))
#define UPDATE_PID_PRESCALER_MASK                 ((uint32)(UPDATE_PID_8BIT_MASK        <<  \
                                                                            UPDATE_PID_PRESCALER_SHIFT))
#define UPDATE_PID_UPDOWN_MASK                    ((uint32)(UPDATE_PID_2BIT_MASK        <<  \
                                                                            UPDATE_PID_UPDOWN_SHIFT))
#define UPDATE_PID_ONESHOT_MASK                   ((uint32)(UPDATE_PID_1BIT_MASK        <<  \
                                                                            UPDATE_PID_ONESHOT_SHIFT))
#define UPDATE_PID_QUAD_MODE_MASK                 ((uint32)(UPDATE_PID_3BIT_MASK        <<  \
                                                                            UPDATE_PID_QUAD_MODE_SHIFT))
#define UPDATE_PID_INV_OUT_MASK                   ((uint32)(UPDATE_PID_2BIT_MASK        <<  \
                                                                            UPDATE_PID_INV_OUT_SHIFT))
#define UPDATE_PID_MODE_MASK                      ((uint32)(UPDATE_PID_3BIT_MASK        <<  \
                                                                            UPDATE_PID_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define UPDATE_PID_CAPTURE_SHIFT                  (0u)
#define UPDATE_PID_COUNT_SHIFT                    (2u)
#define UPDATE_PID_RELOAD_SHIFT                   (4u)
#define UPDATE_PID_STOP_SHIFT                     (6u)
#define UPDATE_PID_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define UPDATE_PID_CAPTURE_MASK                   ((uint32)(UPDATE_PID_2BIT_MASK        <<  \
                                                                  UPDATE_PID_CAPTURE_SHIFT))
#define UPDATE_PID_COUNT_MASK                     ((uint32)(UPDATE_PID_2BIT_MASK        <<  \
                                                                  UPDATE_PID_COUNT_SHIFT))
#define UPDATE_PID_RELOAD_MASK                    ((uint32)(UPDATE_PID_2BIT_MASK        <<  \
                                                                  UPDATE_PID_RELOAD_SHIFT))
#define UPDATE_PID_STOP_MASK                      ((uint32)(UPDATE_PID_2BIT_MASK        <<  \
                                                                  UPDATE_PID_STOP_SHIFT))
#define UPDATE_PID_START_MASK                     ((uint32)(UPDATE_PID_2BIT_MASK        <<  \
                                                                  UPDATE_PID_START_SHIFT))

/* MASK */
#define UPDATE_PID_1BIT_MASK                      ((uint32)0x01u)
#define UPDATE_PID_2BIT_MASK                      ((uint32)0x03u)
#define UPDATE_PID_3BIT_MASK                      ((uint32)0x07u)
#define UPDATE_PID_6BIT_MASK                      ((uint32)0x3Fu)
#define UPDATE_PID_8BIT_MASK                      ((uint32)0xFFu)
#define UPDATE_PID_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define UPDATE_PID_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define UPDATE_PID_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(UPDATE_PID_QUAD_ENCODING_MODES     << UPDATE_PID_QUAD_MODE_SHIFT))       |\
         ((uint32)(UPDATE_PID_CONFIG                  << UPDATE_PID_MODE_SHIFT)))

#define UPDATE_PID_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(UPDATE_PID_PWM_STOP_EVENT          << UPDATE_PID_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(UPDATE_PID_PWM_OUT_INVERT          << UPDATE_PID_INV_OUT_SHIFT))         |\
         ((uint32)(UPDATE_PID_PWM_OUT_N_INVERT        << UPDATE_PID_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(UPDATE_PID_PWM_MODE                << UPDATE_PID_MODE_SHIFT)))

#define UPDATE_PID_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(UPDATE_PID_PWM_RUN_MODE         << UPDATE_PID_ONESHOT_SHIFT))
            
#define UPDATE_PID_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(UPDATE_PID_PWM_ALIGN            << UPDATE_PID_UPDOWN_SHIFT))

#define UPDATE_PID_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(UPDATE_PID_PWM_KILL_EVENT      << UPDATE_PID_PWM_SYNC_KILL_SHIFT))

#define UPDATE_PID_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(UPDATE_PID_PWM_DEAD_TIME_CYCLE  << UPDATE_PID_PRESCALER_SHIFT))

#define UPDATE_PID_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(UPDATE_PID_PWM_PRESCALER        << UPDATE_PID_PRESCALER_SHIFT))

#define UPDATE_PID_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(UPDATE_PID_TC_PRESCALER            << UPDATE_PID_PRESCALER_SHIFT))       |\
         ((uint32)(UPDATE_PID_TC_COUNTER_MODE         << UPDATE_PID_UPDOWN_SHIFT))          |\
         ((uint32)(UPDATE_PID_TC_RUN_MODE             << UPDATE_PID_ONESHOT_SHIFT))         |\
         ((uint32)(UPDATE_PID_TC_COMP_CAP_MODE        << UPDATE_PID_MODE_SHIFT)))
        
#define UPDATE_PID_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(UPDATE_PID_QUAD_PHIA_SIGNAL_MODE   << UPDATE_PID_COUNT_SHIFT))           |\
         ((uint32)(UPDATE_PID_QUAD_INDEX_SIGNAL_MODE  << UPDATE_PID_RELOAD_SHIFT))          |\
         ((uint32)(UPDATE_PID_QUAD_STOP_SIGNAL_MODE   << UPDATE_PID_STOP_SHIFT))            |\
         ((uint32)(UPDATE_PID_QUAD_PHIB_SIGNAL_MODE   << UPDATE_PID_START_SHIFT)))

#define UPDATE_PID_PWM_SIGNALS_MODES                                                              \
        (((uint32)(UPDATE_PID_PWM_SWITCH_SIGNAL_MODE  << UPDATE_PID_CAPTURE_SHIFT))         |\
         ((uint32)(UPDATE_PID_PWM_COUNT_SIGNAL_MODE   << UPDATE_PID_COUNT_SHIFT))           |\
         ((uint32)(UPDATE_PID_PWM_RELOAD_SIGNAL_MODE  << UPDATE_PID_RELOAD_SHIFT))          |\
         ((uint32)(UPDATE_PID_PWM_STOP_SIGNAL_MODE    << UPDATE_PID_STOP_SHIFT))            |\
         ((uint32)(UPDATE_PID_PWM_START_SIGNAL_MODE   << UPDATE_PID_START_SHIFT)))

#define UPDATE_PID_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(UPDATE_PID_TC_CAPTURE_SIGNAL_MODE  << UPDATE_PID_CAPTURE_SHIFT))         |\
         ((uint32)(UPDATE_PID_TC_COUNT_SIGNAL_MODE    << UPDATE_PID_COUNT_SHIFT))           |\
         ((uint32)(UPDATE_PID_TC_RELOAD_SIGNAL_MODE   << UPDATE_PID_RELOAD_SHIFT))          |\
         ((uint32)(UPDATE_PID_TC_STOP_SIGNAL_MODE     << UPDATE_PID_STOP_SHIFT))            |\
         ((uint32)(UPDATE_PID_TC_START_SIGNAL_MODE    << UPDATE_PID_START_SHIFT)))
        
#define UPDATE_PID_TIMER_UPDOWN_CNT_USED                                                          \
                ((UPDATE_PID__COUNT_UPDOWN0 == UPDATE_PID_TC_COUNTER_MODE)                  ||\
                 (UPDATE_PID__COUNT_UPDOWN1 == UPDATE_PID_TC_COUNTER_MODE))

#define UPDATE_PID_PWM_UPDOWN_CNT_USED                                                            \
                ((UPDATE_PID__CENTER == UPDATE_PID_PWM_ALIGN)                               ||\
                 (UPDATE_PID__ASYMMETRIC == UPDATE_PID_PWM_ALIGN))               
        
#define UPDATE_PID_PWM_PR_INIT_VALUE              (1u)
#define UPDATE_PID_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_UPDATE_PID_H */

/* [] END OF FILE */
