/*******************************************************************************
* File Name: TX_SEND.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the TX_SEND
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

#if !defined(CY_TCPWM_TX_SEND_H)
#define CY_TCPWM_TX_SEND_H


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
} TX_SEND_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  TX_SEND_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define TX_SEND_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define TX_SEND_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define TX_SEND_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define TX_SEND_QUAD_ENCODING_MODES            (0lu)
#define TX_SEND_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define TX_SEND_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define TX_SEND_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define TX_SEND_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define TX_SEND_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define TX_SEND_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define TX_SEND_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define TX_SEND_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define TX_SEND_TC_RUN_MODE                    (0lu)
#define TX_SEND_TC_COUNTER_MODE                (0lu)
#define TX_SEND_TC_COMP_CAP_MODE               (2lu)
#define TX_SEND_TC_PRESCALER                   (7lu)

/* Signal modes */
#define TX_SEND_TC_RELOAD_SIGNAL_MODE          (0lu)
#define TX_SEND_TC_COUNT_SIGNAL_MODE           (3lu)
#define TX_SEND_TC_START_SIGNAL_MODE           (0lu)
#define TX_SEND_TC_STOP_SIGNAL_MODE            (0lu)
#define TX_SEND_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define TX_SEND_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define TX_SEND_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define TX_SEND_TC_START_SIGNAL_PRESENT        (0lu)
#define TX_SEND_TC_STOP_SIGNAL_PRESENT         (0lu)
#define TX_SEND_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TX_SEND_TC_INTERRUPT_MASK              (0lu)

/* PWM Mode */
/* Parameters */
#define TX_SEND_PWM_KILL_EVENT                 (0lu)
#define TX_SEND_PWM_STOP_EVENT                 (0lu)
#define TX_SEND_PWM_MODE                       (4lu)
#define TX_SEND_PWM_OUT_N_INVERT               (0lu)
#define TX_SEND_PWM_OUT_INVERT                 (0lu)
#define TX_SEND_PWM_ALIGN                      (0lu)
#define TX_SEND_PWM_RUN_MODE                   (0lu)
#define TX_SEND_PWM_DEAD_TIME_CYCLE            (0lu)
#define TX_SEND_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define TX_SEND_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define TX_SEND_PWM_COUNT_SIGNAL_MODE          (3lu)
#define TX_SEND_PWM_START_SIGNAL_MODE          (0lu)
#define TX_SEND_PWM_STOP_SIGNAL_MODE           (0lu)
#define TX_SEND_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define TX_SEND_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define TX_SEND_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define TX_SEND_PWM_START_SIGNAL_PRESENT       (0lu)
#define TX_SEND_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define TX_SEND_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TX_SEND_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define TX_SEND_TC_PERIOD_VALUE                (1000lu)
#define TX_SEND_TC_COMPARE_VALUE               (65535lu)
#define TX_SEND_TC_COMPARE_BUF_VALUE           (65535lu)
#define TX_SEND_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define TX_SEND_PWM_PERIOD_VALUE               (65535lu)
#define TX_SEND_PWM_PERIOD_BUF_VALUE           (65535lu)
#define TX_SEND_PWM_PERIOD_SWAP                (0lu)
#define TX_SEND_PWM_COMPARE_VALUE              (65535lu)
#define TX_SEND_PWM_COMPARE_BUF_VALUE          (65535lu)
#define TX_SEND_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define TX_SEND__LEFT 0
#define TX_SEND__RIGHT 1
#define TX_SEND__CENTER 2
#define TX_SEND__ASYMMETRIC 3

#define TX_SEND__X1 0
#define TX_SEND__X2 1
#define TX_SEND__X4 2

#define TX_SEND__PWM 4
#define TX_SEND__PWM_DT 5
#define TX_SEND__PWM_PR 6

#define TX_SEND__INVERSE 1
#define TX_SEND__DIRECT 0

#define TX_SEND__CAPTURE 2
#define TX_SEND__COMPARE 0

#define TX_SEND__TRIG_LEVEL 3
#define TX_SEND__TRIG_RISING 0
#define TX_SEND__TRIG_FALLING 1
#define TX_SEND__TRIG_BOTH 2

#define TX_SEND__INTR_MASK_TC 1
#define TX_SEND__INTR_MASK_CC_MATCH 2
#define TX_SEND__INTR_MASK_NONE 0
#define TX_SEND__INTR_MASK_TC_CC 3

#define TX_SEND__UNCONFIG 8
#define TX_SEND__TIMER 1
#define TX_SEND__QUAD 3
#define TX_SEND__PWM_SEL 7

#define TX_SEND__COUNT_UP 0
#define TX_SEND__COUNT_DOWN 1
#define TX_SEND__COUNT_UPDOWN0 2
#define TX_SEND__COUNT_UPDOWN1 3


/* Prescaler */
#define TX_SEND_PRESCALE_DIVBY1                ((uint32)(0u << TX_SEND_PRESCALER_SHIFT))
#define TX_SEND_PRESCALE_DIVBY2                ((uint32)(1u << TX_SEND_PRESCALER_SHIFT))
#define TX_SEND_PRESCALE_DIVBY4                ((uint32)(2u << TX_SEND_PRESCALER_SHIFT))
#define TX_SEND_PRESCALE_DIVBY8                ((uint32)(3u << TX_SEND_PRESCALER_SHIFT))
#define TX_SEND_PRESCALE_DIVBY16               ((uint32)(4u << TX_SEND_PRESCALER_SHIFT))
#define TX_SEND_PRESCALE_DIVBY32               ((uint32)(5u << TX_SEND_PRESCALER_SHIFT))
#define TX_SEND_PRESCALE_DIVBY64               ((uint32)(6u << TX_SEND_PRESCALER_SHIFT))
#define TX_SEND_PRESCALE_DIVBY128              ((uint32)(7u << TX_SEND_PRESCALER_SHIFT))

/* TCPWM set modes */
#define TX_SEND_MODE_TIMER_COMPARE             ((uint32)(TX_SEND__COMPARE         <<  \
                                                                  TX_SEND_MODE_SHIFT))
#define TX_SEND_MODE_TIMER_CAPTURE             ((uint32)(TX_SEND__CAPTURE         <<  \
                                                                  TX_SEND_MODE_SHIFT))
#define TX_SEND_MODE_QUAD                      ((uint32)(TX_SEND__QUAD            <<  \
                                                                  TX_SEND_MODE_SHIFT))
#define TX_SEND_MODE_PWM                       ((uint32)(TX_SEND__PWM             <<  \
                                                                  TX_SEND_MODE_SHIFT))
#define TX_SEND_MODE_PWM_DT                    ((uint32)(TX_SEND__PWM_DT          <<  \
                                                                  TX_SEND_MODE_SHIFT))
#define TX_SEND_MODE_PWM_PR                    ((uint32)(TX_SEND__PWM_PR          <<  \
                                                                  TX_SEND_MODE_SHIFT))

/* Quad Modes */
#define TX_SEND_MODE_X1                        ((uint32)(TX_SEND__X1              <<  \
                                                                  TX_SEND_QUAD_MODE_SHIFT))
#define TX_SEND_MODE_X2                        ((uint32)(TX_SEND__X2              <<  \
                                                                  TX_SEND_QUAD_MODE_SHIFT))
#define TX_SEND_MODE_X4                        ((uint32)(TX_SEND__X4              <<  \
                                                                  TX_SEND_QUAD_MODE_SHIFT))

/* Counter modes */
#define TX_SEND_COUNT_UP                       ((uint32)(TX_SEND__COUNT_UP        <<  \
                                                                  TX_SEND_UPDOWN_SHIFT))
#define TX_SEND_COUNT_DOWN                     ((uint32)(TX_SEND__COUNT_DOWN      <<  \
                                                                  TX_SEND_UPDOWN_SHIFT))
#define TX_SEND_COUNT_UPDOWN0                  ((uint32)(TX_SEND__COUNT_UPDOWN0   <<  \
                                                                  TX_SEND_UPDOWN_SHIFT))
#define TX_SEND_COUNT_UPDOWN1                  ((uint32)(TX_SEND__COUNT_UPDOWN1   <<  \
                                                                  TX_SEND_UPDOWN_SHIFT))

/* PWM output invert */
#define TX_SEND_INVERT_LINE                    ((uint32)(TX_SEND__INVERSE         <<  \
                                                                  TX_SEND_INV_OUT_SHIFT))
#define TX_SEND_INVERT_LINE_N                  ((uint32)(TX_SEND__INVERSE         <<  \
                                                                  TX_SEND_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define TX_SEND_TRIG_RISING                    ((uint32)TX_SEND__TRIG_RISING)
#define TX_SEND_TRIG_FALLING                   ((uint32)TX_SEND__TRIG_FALLING)
#define TX_SEND_TRIG_BOTH                      ((uint32)TX_SEND__TRIG_BOTH)
#define TX_SEND_TRIG_LEVEL                     ((uint32)TX_SEND__TRIG_LEVEL)

/* Interrupt mask */
#define TX_SEND_INTR_MASK_TC                   ((uint32)TX_SEND__INTR_MASK_TC)
#define TX_SEND_INTR_MASK_CC_MATCH             ((uint32)TX_SEND__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define TX_SEND_CC_MATCH_SET                   (0x00u)
#define TX_SEND_CC_MATCH_CLEAR                 (0x01u)
#define TX_SEND_CC_MATCH_INVERT                (0x02u)
#define TX_SEND_CC_MATCH_NO_CHANGE             (0x03u)
#define TX_SEND_OVERLOW_SET                    (0x00u)
#define TX_SEND_OVERLOW_CLEAR                  (0x04u)
#define TX_SEND_OVERLOW_INVERT                 (0x08u)
#define TX_SEND_OVERLOW_NO_CHANGE              (0x0Cu)
#define TX_SEND_UNDERFLOW_SET                  (0x00u)
#define TX_SEND_UNDERFLOW_CLEAR                (0x10u)
#define TX_SEND_UNDERFLOW_INVERT               (0x20u)
#define TX_SEND_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define TX_SEND_PWM_MODE_LEFT                  (TX_SEND_CC_MATCH_CLEAR        |   \
                                                         TX_SEND_OVERLOW_SET           |   \
                                                         TX_SEND_UNDERFLOW_NO_CHANGE)
#define TX_SEND_PWM_MODE_RIGHT                 (TX_SEND_CC_MATCH_SET          |   \
                                                         TX_SEND_OVERLOW_NO_CHANGE     |   \
                                                         TX_SEND_UNDERFLOW_CLEAR)
#define TX_SEND_PWM_MODE_ASYM                  (TX_SEND_CC_MATCH_INVERT       |   \
                                                         TX_SEND_OVERLOW_SET           |   \
                                                         TX_SEND_UNDERFLOW_CLEAR)

#if (TX_SEND_CY_TCPWM_V2)
    #if(TX_SEND_CY_TCPWM_4000)
        #define TX_SEND_PWM_MODE_CENTER                (TX_SEND_CC_MATCH_INVERT       |   \
                                                                 TX_SEND_OVERLOW_NO_CHANGE     |   \
                                                                 TX_SEND_UNDERFLOW_CLEAR)
    #else
        #define TX_SEND_PWM_MODE_CENTER                (TX_SEND_CC_MATCH_INVERT       |   \
                                                                 TX_SEND_OVERLOW_SET           |   \
                                                                 TX_SEND_UNDERFLOW_CLEAR)
    #endif /* (TX_SEND_CY_TCPWM_4000) */
#else
    #define TX_SEND_PWM_MODE_CENTER                (TX_SEND_CC_MATCH_INVERT       |   \
                                                             TX_SEND_OVERLOW_NO_CHANGE     |   \
                                                             TX_SEND_UNDERFLOW_CLEAR)
#endif /* (TX_SEND_CY_TCPWM_NEW) */

/* Command operations without condition */
#define TX_SEND_CMD_CAPTURE                    (0u)
#define TX_SEND_CMD_RELOAD                     (8u)
#define TX_SEND_CMD_STOP                       (16u)
#define TX_SEND_CMD_START                      (24u)

/* Status */
#define TX_SEND_STATUS_DOWN                    (1u)
#define TX_SEND_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   TX_SEND_Init(void);
void   TX_SEND_Enable(void);
void   TX_SEND_Start(void);
void   TX_SEND_Stop(void);

void   TX_SEND_SetMode(uint32 mode);
void   TX_SEND_SetCounterMode(uint32 counterMode);
void   TX_SEND_SetPWMMode(uint32 modeMask);
void   TX_SEND_SetQDMode(uint32 qdMode);

void   TX_SEND_SetPrescaler(uint32 prescaler);
void   TX_SEND_TriggerCommand(uint32 mask, uint32 command);
void   TX_SEND_SetOneShot(uint32 oneShotEnable);
uint32 TX_SEND_ReadStatus(void);

void   TX_SEND_SetPWMSyncKill(uint32 syncKillEnable);
void   TX_SEND_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   TX_SEND_SetPWMDeadTime(uint32 deadTime);
void   TX_SEND_SetPWMInvert(uint32 mask);

void   TX_SEND_SetInterruptMode(uint32 interruptMask);
uint32 TX_SEND_GetInterruptSourceMasked(void);
uint32 TX_SEND_GetInterruptSource(void);
void   TX_SEND_ClearInterrupt(uint32 interruptMask);
void   TX_SEND_SetInterrupt(uint32 interruptMask);

void   TX_SEND_WriteCounter(uint32 count);
uint32 TX_SEND_ReadCounter(void);

uint32 TX_SEND_ReadCapture(void);
uint32 TX_SEND_ReadCaptureBuf(void);

void   TX_SEND_WritePeriod(uint32 period);
uint32 TX_SEND_ReadPeriod(void);
void   TX_SEND_WritePeriodBuf(uint32 periodBuf);
uint32 TX_SEND_ReadPeriodBuf(void);

void   TX_SEND_WriteCompare(uint32 compare);
uint32 TX_SEND_ReadCompare(void);
void   TX_SEND_WriteCompareBuf(uint32 compareBuf);
uint32 TX_SEND_ReadCompareBuf(void);

void   TX_SEND_SetPeriodSwap(uint32 swapEnable);
void   TX_SEND_SetCompareSwap(uint32 swapEnable);

void   TX_SEND_SetCaptureMode(uint32 triggerMode);
void   TX_SEND_SetReloadMode(uint32 triggerMode);
void   TX_SEND_SetStartMode(uint32 triggerMode);
void   TX_SEND_SetStopMode(uint32 triggerMode);
void   TX_SEND_SetCountMode(uint32 triggerMode);

void   TX_SEND_SaveConfig(void);
void   TX_SEND_RestoreConfig(void);
void   TX_SEND_Sleep(void);
void   TX_SEND_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define TX_SEND_BLOCK_CONTROL_REG              (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TX_SEND_BLOCK_CONTROL_PTR              ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TX_SEND_COMMAND_REG                    (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TX_SEND_COMMAND_PTR                    ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TX_SEND_INTRRUPT_CAUSE_REG             (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TX_SEND_INTRRUPT_CAUSE_PTR             ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TX_SEND_CONTROL_REG                    (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__CTRL )
#define TX_SEND_CONTROL_PTR                    ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__CTRL )
#define TX_SEND_STATUS_REG                     (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__STATUS )
#define TX_SEND_STATUS_PTR                     ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__STATUS )
#define TX_SEND_COUNTER_REG                    (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__COUNTER )
#define TX_SEND_COUNTER_PTR                    ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__COUNTER )
#define TX_SEND_COMP_CAP_REG                   (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__CC )
#define TX_SEND_COMP_CAP_PTR                   ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__CC )
#define TX_SEND_COMP_CAP_BUF_REG               (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__CC_BUFF )
#define TX_SEND_COMP_CAP_BUF_PTR               ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__CC_BUFF )
#define TX_SEND_PERIOD_REG                     (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__PERIOD )
#define TX_SEND_PERIOD_PTR                     ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__PERIOD )
#define TX_SEND_PERIOD_BUF_REG                 (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TX_SEND_PERIOD_BUF_PTR                 ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TX_SEND_TRIG_CONTROL0_REG              (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TX_SEND_TRIG_CONTROL0_PTR              ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TX_SEND_TRIG_CONTROL1_REG              (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TX_SEND_TRIG_CONTROL1_PTR              ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TX_SEND_TRIG_CONTROL2_REG              (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TX_SEND_TRIG_CONTROL2_PTR              ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TX_SEND_INTERRUPT_REQ_REG              (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__INTR )
#define TX_SEND_INTERRUPT_REQ_PTR              ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__INTR )
#define TX_SEND_INTERRUPT_SET_REG              (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__INTR_SET )
#define TX_SEND_INTERRUPT_SET_PTR              ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__INTR_SET )
#define TX_SEND_INTERRUPT_MASK_REG             (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__INTR_MASK )
#define TX_SEND_INTERRUPT_MASK_PTR             ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__INTR_MASK )
#define TX_SEND_INTERRUPT_MASKED_REG           (*(reg32 *) TX_SEND_cy_m0s8_tcpwm_1__INTR_MASKED )
#define TX_SEND_INTERRUPT_MASKED_PTR           ( (reg32 *) TX_SEND_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define TX_SEND_MASK                           ((uint32)TX_SEND_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define TX_SEND_RELOAD_CC_SHIFT                (0u)
#define TX_SEND_RELOAD_PERIOD_SHIFT            (1u)
#define TX_SEND_PWM_SYNC_KILL_SHIFT            (2u)
#define TX_SEND_PWM_STOP_KILL_SHIFT            (3u)
#define TX_SEND_PRESCALER_SHIFT                (8u)
#define TX_SEND_UPDOWN_SHIFT                   (16u)
#define TX_SEND_ONESHOT_SHIFT                  (18u)
#define TX_SEND_QUAD_MODE_SHIFT                (20u)
#define TX_SEND_INV_OUT_SHIFT                  (20u)
#define TX_SEND_INV_COMPL_OUT_SHIFT            (21u)
#define TX_SEND_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define TX_SEND_RELOAD_CC_MASK                 ((uint32)(TX_SEND_1BIT_MASK        <<  \
                                                                            TX_SEND_RELOAD_CC_SHIFT))
#define TX_SEND_RELOAD_PERIOD_MASK             ((uint32)(TX_SEND_1BIT_MASK        <<  \
                                                                            TX_SEND_RELOAD_PERIOD_SHIFT))
#define TX_SEND_PWM_SYNC_KILL_MASK             ((uint32)(TX_SEND_1BIT_MASK        <<  \
                                                                            TX_SEND_PWM_SYNC_KILL_SHIFT))
#define TX_SEND_PWM_STOP_KILL_MASK             ((uint32)(TX_SEND_1BIT_MASK        <<  \
                                                                            TX_SEND_PWM_STOP_KILL_SHIFT))
#define TX_SEND_PRESCALER_MASK                 ((uint32)(TX_SEND_8BIT_MASK        <<  \
                                                                            TX_SEND_PRESCALER_SHIFT))
#define TX_SEND_UPDOWN_MASK                    ((uint32)(TX_SEND_2BIT_MASK        <<  \
                                                                            TX_SEND_UPDOWN_SHIFT))
#define TX_SEND_ONESHOT_MASK                   ((uint32)(TX_SEND_1BIT_MASK        <<  \
                                                                            TX_SEND_ONESHOT_SHIFT))
#define TX_SEND_QUAD_MODE_MASK                 ((uint32)(TX_SEND_3BIT_MASK        <<  \
                                                                            TX_SEND_QUAD_MODE_SHIFT))
#define TX_SEND_INV_OUT_MASK                   ((uint32)(TX_SEND_2BIT_MASK        <<  \
                                                                            TX_SEND_INV_OUT_SHIFT))
#define TX_SEND_MODE_MASK                      ((uint32)(TX_SEND_3BIT_MASK        <<  \
                                                                            TX_SEND_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define TX_SEND_CAPTURE_SHIFT                  (0u)
#define TX_SEND_COUNT_SHIFT                    (2u)
#define TX_SEND_RELOAD_SHIFT                   (4u)
#define TX_SEND_STOP_SHIFT                     (6u)
#define TX_SEND_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define TX_SEND_CAPTURE_MASK                   ((uint32)(TX_SEND_2BIT_MASK        <<  \
                                                                  TX_SEND_CAPTURE_SHIFT))
#define TX_SEND_COUNT_MASK                     ((uint32)(TX_SEND_2BIT_MASK        <<  \
                                                                  TX_SEND_COUNT_SHIFT))
#define TX_SEND_RELOAD_MASK                    ((uint32)(TX_SEND_2BIT_MASK        <<  \
                                                                  TX_SEND_RELOAD_SHIFT))
#define TX_SEND_STOP_MASK                      ((uint32)(TX_SEND_2BIT_MASK        <<  \
                                                                  TX_SEND_STOP_SHIFT))
#define TX_SEND_START_MASK                     ((uint32)(TX_SEND_2BIT_MASK        <<  \
                                                                  TX_SEND_START_SHIFT))

/* MASK */
#define TX_SEND_1BIT_MASK                      ((uint32)0x01u)
#define TX_SEND_2BIT_MASK                      ((uint32)0x03u)
#define TX_SEND_3BIT_MASK                      ((uint32)0x07u)
#define TX_SEND_6BIT_MASK                      ((uint32)0x3Fu)
#define TX_SEND_8BIT_MASK                      ((uint32)0xFFu)
#define TX_SEND_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define TX_SEND_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define TX_SEND_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(TX_SEND_QUAD_ENCODING_MODES     << TX_SEND_QUAD_MODE_SHIFT))       |\
         ((uint32)(TX_SEND_CONFIG                  << TX_SEND_MODE_SHIFT)))

#define TX_SEND_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(TX_SEND_PWM_STOP_EVENT          << TX_SEND_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(TX_SEND_PWM_OUT_INVERT          << TX_SEND_INV_OUT_SHIFT))         |\
         ((uint32)(TX_SEND_PWM_OUT_N_INVERT        << TX_SEND_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(TX_SEND_PWM_MODE                << TX_SEND_MODE_SHIFT)))

#define TX_SEND_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(TX_SEND_PWM_RUN_MODE         << TX_SEND_ONESHOT_SHIFT))
            
#define TX_SEND_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(TX_SEND_PWM_ALIGN            << TX_SEND_UPDOWN_SHIFT))

#define TX_SEND_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(TX_SEND_PWM_KILL_EVENT      << TX_SEND_PWM_SYNC_KILL_SHIFT))

#define TX_SEND_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(TX_SEND_PWM_DEAD_TIME_CYCLE  << TX_SEND_PRESCALER_SHIFT))

#define TX_SEND_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(TX_SEND_PWM_PRESCALER        << TX_SEND_PRESCALER_SHIFT))

#define TX_SEND_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(TX_SEND_TC_PRESCALER            << TX_SEND_PRESCALER_SHIFT))       |\
         ((uint32)(TX_SEND_TC_COUNTER_MODE         << TX_SEND_UPDOWN_SHIFT))          |\
         ((uint32)(TX_SEND_TC_RUN_MODE             << TX_SEND_ONESHOT_SHIFT))         |\
         ((uint32)(TX_SEND_TC_COMP_CAP_MODE        << TX_SEND_MODE_SHIFT)))
        
#define TX_SEND_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(TX_SEND_QUAD_PHIA_SIGNAL_MODE   << TX_SEND_COUNT_SHIFT))           |\
         ((uint32)(TX_SEND_QUAD_INDEX_SIGNAL_MODE  << TX_SEND_RELOAD_SHIFT))          |\
         ((uint32)(TX_SEND_QUAD_STOP_SIGNAL_MODE   << TX_SEND_STOP_SHIFT))            |\
         ((uint32)(TX_SEND_QUAD_PHIB_SIGNAL_MODE   << TX_SEND_START_SHIFT)))

#define TX_SEND_PWM_SIGNALS_MODES                                                              \
        (((uint32)(TX_SEND_PWM_SWITCH_SIGNAL_MODE  << TX_SEND_CAPTURE_SHIFT))         |\
         ((uint32)(TX_SEND_PWM_COUNT_SIGNAL_MODE   << TX_SEND_COUNT_SHIFT))           |\
         ((uint32)(TX_SEND_PWM_RELOAD_SIGNAL_MODE  << TX_SEND_RELOAD_SHIFT))          |\
         ((uint32)(TX_SEND_PWM_STOP_SIGNAL_MODE    << TX_SEND_STOP_SHIFT))            |\
         ((uint32)(TX_SEND_PWM_START_SIGNAL_MODE   << TX_SEND_START_SHIFT)))

#define TX_SEND_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(TX_SEND_TC_CAPTURE_SIGNAL_MODE  << TX_SEND_CAPTURE_SHIFT))         |\
         ((uint32)(TX_SEND_TC_COUNT_SIGNAL_MODE    << TX_SEND_COUNT_SHIFT))           |\
         ((uint32)(TX_SEND_TC_RELOAD_SIGNAL_MODE   << TX_SEND_RELOAD_SHIFT))          |\
         ((uint32)(TX_SEND_TC_STOP_SIGNAL_MODE     << TX_SEND_STOP_SHIFT))            |\
         ((uint32)(TX_SEND_TC_START_SIGNAL_MODE    << TX_SEND_START_SHIFT)))
        
#define TX_SEND_TIMER_UPDOWN_CNT_USED                                                          \
                ((TX_SEND__COUNT_UPDOWN0 == TX_SEND_TC_COUNTER_MODE)                  ||\
                 (TX_SEND__COUNT_UPDOWN1 == TX_SEND_TC_COUNTER_MODE))

#define TX_SEND_PWM_UPDOWN_CNT_USED                                                            \
                ((TX_SEND__CENTER == TX_SEND_PWM_ALIGN)                               ||\
                 (TX_SEND__ASYMMETRIC == TX_SEND_PWM_ALIGN))               
        
#define TX_SEND_PWM_PR_INIT_VALUE              (1u)
#define TX_SEND_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_TX_SEND_H */

/* [] END OF FILE */
