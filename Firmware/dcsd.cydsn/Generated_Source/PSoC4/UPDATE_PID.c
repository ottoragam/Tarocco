/*******************************************************************************
* File Name: UPDATE_PID.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the UPDATE_PID
*  component
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

#include "UPDATE_PID.h"

uint8 UPDATE_PID_initVar = 0u;


/*******************************************************************************
* Function Name: UPDATE_PID_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default UPDATE_PID configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (UPDATE_PID__QUAD == UPDATE_PID_CONFIG)
        UPDATE_PID_CONTROL_REG = UPDATE_PID_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        UPDATE_PID_TRIG_CONTROL1_REG  = UPDATE_PID_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        UPDATE_PID_SetInterruptMode(UPDATE_PID_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        UPDATE_PID_SetCounterMode(UPDATE_PID_COUNT_DOWN);
        UPDATE_PID_WritePeriod(UPDATE_PID_QUAD_PERIOD_INIT_VALUE);
        UPDATE_PID_WriteCounter(UPDATE_PID_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (UPDATE_PID__QUAD == UPDATE_PID_CONFIG) */

    #if (UPDATE_PID__TIMER == UPDATE_PID_CONFIG)
        UPDATE_PID_CONTROL_REG = UPDATE_PID_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        UPDATE_PID_TRIG_CONTROL1_REG  = UPDATE_PID_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        UPDATE_PID_SetInterruptMode(UPDATE_PID_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        UPDATE_PID_WritePeriod(UPDATE_PID_TC_PERIOD_VALUE );

        #if (UPDATE_PID__COMPARE == UPDATE_PID_TC_COMP_CAP_MODE)
            UPDATE_PID_WriteCompare(UPDATE_PID_TC_COMPARE_VALUE);

            #if (1u == UPDATE_PID_TC_COMPARE_SWAP)
                UPDATE_PID_SetCompareSwap(1u);
                UPDATE_PID_WriteCompareBuf(UPDATE_PID_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == UPDATE_PID_TC_COMPARE_SWAP) */
        #endif  /* (UPDATE_PID__COMPARE == UPDATE_PID_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (UPDATE_PID_CY_TCPWM_V2 && UPDATE_PID_TIMER_UPDOWN_CNT_USED && !UPDATE_PID_CY_TCPWM_4000)
            UPDATE_PID_WriteCounter(1u);
        #elif(UPDATE_PID__COUNT_DOWN == UPDATE_PID_TC_COUNTER_MODE)
            UPDATE_PID_WriteCounter(UPDATE_PID_TC_PERIOD_VALUE);
        #else
            UPDATE_PID_WriteCounter(0u);
        #endif /* (UPDATE_PID_CY_TCPWM_V2 && UPDATE_PID_TIMER_UPDOWN_CNT_USED && !UPDATE_PID_CY_TCPWM_4000) */
    #endif  /* (UPDATE_PID__TIMER == UPDATE_PID_CONFIG) */

    #if (UPDATE_PID__PWM_SEL == UPDATE_PID_CONFIG)
        UPDATE_PID_CONTROL_REG = UPDATE_PID_CTRL_PWM_BASE_CONFIG;

        #if (UPDATE_PID__PWM_PR == UPDATE_PID_PWM_MODE)
            UPDATE_PID_CONTROL_REG |= UPDATE_PID_CTRL_PWM_RUN_MODE;
            UPDATE_PID_WriteCounter(UPDATE_PID_PWM_PR_INIT_VALUE);
        #else
            UPDATE_PID_CONTROL_REG |= UPDATE_PID_CTRL_PWM_ALIGN | UPDATE_PID_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (UPDATE_PID_CY_TCPWM_V2 && UPDATE_PID_PWM_UPDOWN_CNT_USED && !UPDATE_PID_CY_TCPWM_4000)
                UPDATE_PID_WriteCounter(1u);
            #elif (UPDATE_PID__RIGHT == UPDATE_PID_PWM_ALIGN)
                UPDATE_PID_WriteCounter(UPDATE_PID_PWM_PERIOD_VALUE);
            #else 
                UPDATE_PID_WriteCounter(0u);
            #endif  /* (UPDATE_PID_CY_TCPWM_V2 && UPDATE_PID_PWM_UPDOWN_CNT_USED && !UPDATE_PID_CY_TCPWM_4000) */
        #endif  /* (UPDATE_PID__PWM_PR == UPDATE_PID_PWM_MODE) */

        #if (UPDATE_PID__PWM_DT == UPDATE_PID_PWM_MODE)
            UPDATE_PID_CONTROL_REG |= UPDATE_PID_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (UPDATE_PID__PWM_DT == UPDATE_PID_PWM_MODE) */

        #if (UPDATE_PID__PWM == UPDATE_PID_PWM_MODE)
            UPDATE_PID_CONTROL_REG |= UPDATE_PID_CTRL_PWM_PRESCALER;
        #endif  /* (UPDATE_PID__PWM == UPDATE_PID_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        UPDATE_PID_TRIG_CONTROL1_REG  = UPDATE_PID_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        UPDATE_PID_SetInterruptMode(UPDATE_PID_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (UPDATE_PID__PWM_PR == UPDATE_PID_PWM_MODE)
            UPDATE_PID_TRIG_CONTROL2_REG =
                    (UPDATE_PID_CC_MATCH_NO_CHANGE    |
                    UPDATE_PID_OVERLOW_NO_CHANGE      |
                    UPDATE_PID_UNDERFLOW_NO_CHANGE);
        #else
            #if (UPDATE_PID__LEFT == UPDATE_PID_PWM_ALIGN)
                UPDATE_PID_TRIG_CONTROL2_REG = UPDATE_PID_PWM_MODE_LEFT;
            #endif  /* ( UPDATE_PID_PWM_LEFT == UPDATE_PID_PWM_ALIGN) */

            #if (UPDATE_PID__RIGHT == UPDATE_PID_PWM_ALIGN)
                UPDATE_PID_TRIG_CONTROL2_REG = UPDATE_PID_PWM_MODE_RIGHT;
            #endif  /* ( UPDATE_PID_PWM_RIGHT == UPDATE_PID_PWM_ALIGN) */

            #if (UPDATE_PID__CENTER == UPDATE_PID_PWM_ALIGN)
                UPDATE_PID_TRIG_CONTROL2_REG = UPDATE_PID_PWM_MODE_CENTER;
            #endif  /* ( UPDATE_PID_PWM_CENTER == UPDATE_PID_PWM_ALIGN) */

            #if (UPDATE_PID__ASYMMETRIC == UPDATE_PID_PWM_ALIGN)
                UPDATE_PID_TRIG_CONTROL2_REG = UPDATE_PID_PWM_MODE_ASYM;
            #endif  /* (UPDATE_PID__ASYMMETRIC == UPDATE_PID_PWM_ALIGN) */
        #endif  /* (UPDATE_PID__PWM_PR == UPDATE_PID_PWM_MODE) */

        /* Set other values from customizer */
        UPDATE_PID_WritePeriod(UPDATE_PID_PWM_PERIOD_VALUE );
        UPDATE_PID_WriteCompare(UPDATE_PID_PWM_COMPARE_VALUE);

        #if (1u == UPDATE_PID_PWM_COMPARE_SWAP)
            UPDATE_PID_SetCompareSwap(1u);
            UPDATE_PID_WriteCompareBuf(UPDATE_PID_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == UPDATE_PID_PWM_COMPARE_SWAP) */

        #if (1u == UPDATE_PID_PWM_PERIOD_SWAP)
            UPDATE_PID_SetPeriodSwap(1u);
            UPDATE_PID_WritePeriodBuf(UPDATE_PID_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == UPDATE_PID_PWM_PERIOD_SWAP) */
    #endif  /* (UPDATE_PID__PWM_SEL == UPDATE_PID_CONFIG) */
    
}


/*******************************************************************************
* Function Name: UPDATE_PID_Enable
********************************************************************************
*
* Summary:
*  Enables the UPDATE_PID.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    UPDATE_PID_BLOCK_CONTROL_REG |= UPDATE_PID_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (UPDATE_PID__PWM_SEL == UPDATE_PID_CONFIG)
        #if (0u == UPDATE_PID_PWM_START_SIGNAL_PRESENT)
            UPDATE_PID_TriggerCommand(UPDATE_PID_MASK, UPDATE_PID_CMD_START);
        #endif /* (0u == UPDATE_PID_PWM_START_SIGNAL_PRESENT) */
    #endif /* (UPDATE_PID__PWM_SEL == UPDATE_PID_CONFIG) */

    #if (UPDATE_PID__TIMER == UPDATE_PID_CONFIG)
        #if (0u == UPDATE_PID_TC_START_SIGNAL_PRESENT)
            UPDATE_PID_TriggerCommand(UPDATE_PID_MASK, UPDATE_PID_CMD_START);
        #endif /* (0u == UPDATE_PID_TC_START_SIGNAL_PRESENT) */
    #endif /* (UPDATE_PID__TIMER == UPDATE_PID_CONFIG) */
    
    #if (UPDATE_PID__QUAD == UPDATE_PID_CONFIG)
        #if (0u != UPDATE_PID_QUAD_AUTO_START)
            UPDATE_PID_TriggerCommand(UPDATE_PID_MASK, UPDATE_PID_CMD_RELOAD);
        #endif /* (0u != UPDATE_PID_QUAD_AUTO_START) */
    #endif  /* (UPDATE_PID__QUAD == UPDATE_PID_CONFIG) */
}


/*******************************************************************************
* Function Name: UPDATE_PID_Start
********************************************************************************
*
* Summary:
*  Initializes the UPDATE_PID with default customizer
*  values when called the first time and enables the UPDATE_PID.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  UPDATE_PID_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time UPDATE_PID_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the UPDATE_PID_Start() routine.
*
*******************************************************************************/
void UPDATE_PID_Start(void)
{
    if (0u == UPDATE_PID_initVar)
    {
        UPDATE_PID_Init();
        UPDATE_PID_initVar = 1u;
    }

    UPDATE_PID_Enable();
}


/*******************************************************************************
* Function Name: UPDATE_PID_Stop
********************************************************************************
*
* Summary:
*  Disables the UPDATE_PID.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_BLOCK_CONTROL_REG &= (uint32)~UPDATE_PID_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the UPDATE_PID. This function is used when
*  configured as a generic UPDATE_PID and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the UPDATE_PID to operate in
*   Values:
*   - UPDATE_PID_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - UPDATE_PID_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - UPDATE_PID_MODE_QUAD - Quadrature decoder
*         - UPDATE_PID_MODE_PWM - PWM
*         - UPDATE_PID_MODE_PWM_DT - PWM with dead time
*         - UPDATE_PID_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_CONTROL_REG &= (uint32)~UPDATE_PID_MODE_MASK;
    UPDATE_PID_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - UPDATE_PID_MODE_X1 - Counts on phi 1 rising
*         - UPDATE_PID_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - UPDATE_PID_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_CONTROL_REG &= (uint32)~UPDATE_PID_QUAD_MODE_MASK;
    UPDATE_PID_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - UPDATE_PID_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - UPDATE_PID_PRESCALE_DIVBY2    - Divide by 2
*         - UPDATE_PID_PRESCALE_DIVBY4    - Divide by 4
*         - UPDATE_PID_PRESCALE_DIVBY8    - Divide by 8
*         - UPDATE_PID_PRESCALE_DIVBY16   - Divide by 16
*         - UPDATE_PID_PRESCALE_DIVBY32   - Divide by 32
*         - UPDATE_PID_PRESCALE_DIVBY64   - Divide by 64
*         - UPDATE_PID_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_CONTROL_REG &= (uint32)~UPDATE_PID_PRESCALER_MASK;
    UPDATE_PID_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the UPDATE_PID runs
*  continuously or stops when terminal count is reached.  By default the
*  UPDATE_PID operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_CONTROL_REG &= (uint32)~UPDATE_PID_ONESHOT_MASK;
    UPDATE_PID_CONTROL_REG |= ((uint32)((oneShotEnable & UPDATE_PID_1BIT_MASK) <<
                                                               UPDATE_PID_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetPWMMode(uint32 modeMask)
{
    UPDATE_PID_TRIG_CONTROL2_REG = (modeMask & UPDATE_PID_6BIT_MASK);
}



/*******************************************************************************
* Function Name: UPDATE_PID_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_CONTROL_REG &= (uint32)~UPDATE_PID_PWM_SYNC_KILL_MASK;
    UPDATE_PID_CONTROL_REG |= ((uint32)((syncKillEnable & UPDATE_PID_1BIT_MASK)  <<
                                               UPDATE_PID_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_CONTROL_REG &= (uint32)~UPDATE_PID_PWM_STOP_KILL_MASK;
    UPDATE_PID_CONTROL_REG |= ((uint32)((stopOnKillEnable & UPDATE_PID_1BIT_MASK)  <<
                                                         UPDATE_PID_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_CONTROL_REG &= (uint32)~UPDATE_PID_PRESCALER_MASK;
    UPDATE_PID_CONTROL_REG |= ((uint32)((deadTime & UPDATE_PID_8BIT_MASK) <<
                                                          UPDATE_PID_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - UPDATE_PID_INVERT_LINE   - Inverts the line output
*         - UPDATE_PID_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_CONTROL_REG &= (uint32)~UPDATE_PID_INV_OUT_MASK;
    UPDATE_PID_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: UPDATE_PID_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_WriteCounter(uint32 count)
{
    UPDATE_PID_COUNTER_REG = (count & UPDATE_PID_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UPDATE_PID_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 UPDATE_PID_ReadCounter(void)
{
    return (UPDATE_PID_COUNTER_REG & UPDATE_PID_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - UPDATE_PID_COUNT_UP       - Counts up
*     - UPDATE_PID_COUNT_DOWN     - Counts down
*     - UPDATE_PID_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - UPDATE_PID_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_CONTROL_REG &= (uint32)~UPDATE_PID_UPDOWN_MASK;
    UPDATE_PID_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_WritePeriod(uint32 period)
{
    UPDATE_PID_PERIOD_REG = (period & UPDATE_PID_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UPDATE_PID_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 UPDATE_PID_ReadPeriod(void)
{
    return (UPDATE_PID_PERIOD_REG & UPDATE_PID_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_CONTROL_REG &= (uint32)~UPDATE_PID_RELOAD_CC_MASK;
    UPDATE_PID_CONTROL_REG |= (swapEnable & UPDATE_PID_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_WritePeriodBuf(uint32 periodBuf)
{
    UPDATE_PID_PERIOD_BUF_REG = (periodBuf & UPDATE_PID_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UPDATE_PID_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 UPDATE_PID_ReadPeriodBuf(void)
{
    return (UPDATE_PID_PERIOD_BUF_REG & UPDATE_PID_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_CONTROL_REG &= (uint32)~UPDATE_PID_RELOAD_PERIOD_MASK;
    UPDATE_PID_CONTROL_REG |= ((uint32)((swapEnable & UPDATE_PID_1BIT_MASK) <<
                                                            UPDATE_PID_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void UPDATE_PID_WriteCompare(uint32 compare)
{
    #if (UPDATE_PID_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (UPDATE_PID_CY_TCPWM_4000) */

    #if (UPDATE_PID_CY_TCPWM_4000)
        currentMode = ((UPDATE_PID_CONTROL_REG & UPDATE_PID_UPDOWN_MASK) >> UPDATE_PID_UPDOWN_SHIFT);

        if (((uint32)UPDATE_PID__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)UPDATE_PID__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (UPDATE_PID_CY_TCPWM_4000) */
    
    UPDATE_PID_COMP_CAP_REG = (compare & UPDATE_PID_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UPDATE_PID_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 UPDATE_PID_ReadCompare(void)
{
    #if (UPDATE_PID_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (UPDATE_PID_CY_TCPWM_4000) */

    #if (UPDATE_PID_CY_TCPWM_4000)
        currentMode = ((UPDATE_PID_CONTROL_REG & UPDATE_PID_UPDOWN_MASK) >> UPDATE_PID_UPDOWN_SHIFT);
        
        regVal = UPDATE_PID_COMP_CAP_REG;
        
        if (((uint32)UPDATE_PID__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)UPDATE_PID__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & UPDATE_PID_16BIT_MASK);
    #else
        return (UPDATE_PID_COMP_CAP_REG & UPDATE_PID_16BIT_MASK);
    #endif /* (UPDATE_PID_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: UPDATE_PID_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void UPDATE_PID_WriteCompareBuf(uint32 compareBuf)
{
    #if (UPDATE_PID_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (UPDATE_PID_CY_TCPWM_4000) */

    #if (UPDATE_PID_CY_TCPWM_4000)
        currentMode = ((UPDATE_PID_CONTROL_REG & UPDATE_PID_UPDOWN_MASK) >> UPDATE_PID_UPDOWN_SHIFT);

        if (((uint32)UPDATE_PID__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)UPDATE_PID__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (UPDATE_PID_CY_TCPWM_4000) */
    
    UPDATE_PID_COMP_CAP_BUF_REG = (compareBuf & UPDATE_PID_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UPDATE_PID_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 UPDATE_PID_ReadCompareBuf(void)
{
    #if (UPDATE_PID_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (UPDATE_PID_CY_TCPWM_4000) */

    #if (UPDATE_PID_CY_TCPWM_4000)
        currentMode = ((UPDATE_PID_CONTROL_REG & UPDATE_PID_UPDOWN_MASK) >> UPDATE_PID_UPDOWN_SHIFT);

        regVal = UPDATE_PID_COMP_CAP_BUF_REG;
        
        if (((uint32)UPDATE_PID__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)UPDATE_PID__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & UPDATE_PID_16BIT_MASK);
    #else
        return (UPDATE_PID_COMP_CAP_BUF_REG & UPDATE_PID_16BIT_MASK);
    #endif /* (UPDATE_PID_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: UPDATE_PID_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 UPDATE_PID_ReadCapture(void)
{
    return (UPDATE_PID_COMP_CAP_REG & UPDATE_PID_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UPDATE_PID_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 UPDATE_PID_ReadCaptureBuf(void)
{
    return (UPDATE_PID_COMP_CAP_BUF_REG & UPDATE_PID_16BIT_MASK);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - UPDATE_PID_TRIG_LEVEL     - Level
*     - UPDATE_PID_TRIG_RISING    - Rising edge
*     - UPDATE_PID_TRIG_FALLING   - Falling edge
*     - UPDATE_PID_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_TRIG_CONTROL1_REG &= (uint32)~UPDATE_PID_CAPTURE_MASK;
    UPDATE_PID_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - UPDATE_PID_TRIG_LEVEL     - Level
*     - UPDATE_PID_TRIG_RISING    - Rising edge
*     - UPDATE_PID_TRIG_FALLING   - Falling edge
*     - UPDATE_PID_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_TRIG_CONTROL1_REG &= (uint32)~UPDATE_PID_RELOAD_MASK;
    UPDATE_PID_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << UPDATE_PID_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - UPDATE_PID_TRIG_LEVEL     - Level
*     - UPDATE_PID_TRIG_RISING    - Rising edge
*     - UPDATE_PID_TRIG_FALLING   - Falling edge
*     - UPDATE_PID_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_TRIG_CONTROL1_REG &= (uint32)~UPDATE_PID_START_MASK;
    UPDATE_PID_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << UPDATE_PID_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - UPDATE_PID_TRIG_LEVEL     - Level
*     - UPDATE_PID_TRIG_RISING    - Rising edge
*     - UPDATE_PID_TRIG_FALLING   - Falling edge
*     - UPDATE_PID_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_TRIG_CONTROL1_REG &= (uint32)~UPDATE_PID_STOP_MASK;
    UPDATE_PID_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << UPDATE_PID_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - UPDATE_PID_TRIG_LEVEL     - Level
*     - UPDATE_PID_TRIG_RISING    - Rising edge
*     - UPDATE_PID_TRIG_FALLING   - Falling edge
*     - UPDATE_PID_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_TRIG_CONTROL1_REG &= (uint32)~UPDATE_PID_COUNT_MASK;
    UPDATE_PID_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << UPDATE_PID_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - UPDATE_PID_CMD_CAPTURE    - Trigger Capture/Switch command
*     - UPDATE_PID_CMD_RELOAD     - Trigger Reload/Index command
*     - UPDATE_PID_CMD_STOP       - Trigger Stop/Kill command
*     - UPDATE_PID_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    UPDATE_PID_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UPDATE_PID_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the UPDATE_PID.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - UPDATE_PID_STATUS_DOWN    - Set if counting down
*     - UPDATE_PID_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 UPDATE_PID_ReadStatus(void)
{
    return ((UPDATE_PID_STATUS_REG >> UPDATE_PID_RUNNING_STATUS_SHIFT) |
            (UPDATE_PID_STATUS_REG & UPDATE_PID_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - UPDATE_PID_INTR_MASK_TC       - Terminal count mask
*     - UPDATE_PID_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetInterruptMode(uint32 interruptMask)
{
    UPDATE_PID_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: UPDATE_PID_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - UPDATE_PID_INTR_MASK_TC       - Terminal count mask
*     - UPDATE_PID_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 UPDATE_PID_GetInterruptSourceMasked(void)
{
    return (UPDATE_PID_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: UPDATE_PID_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - UPDATE_PID_INTR_MASK_TC       - Terminal count mask
*     - UPDATE_PID_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 UPDATE_PID_GetInterruptSource(void)
{
    return (UPDATE_PID_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: UPDATE_PID_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - UPDATE_PID_INTR_MASK_TC       - Terminal count mask
*     - UPDATE_PID_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_ClearInterrupt(uint32 interruptMask)
{
    UPDATE_PID_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: UPDATE_PID_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - UPDATE_PID_INTR_MASK_TC       - Terminal count mask
*     - UPDATE_PID_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SetInterrupt(uint32 interruptMask)
{
    UPDATE_PID_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
