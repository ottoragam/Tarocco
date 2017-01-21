/*******************************************************************************
* File Name: Timer_1.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the Timer_1
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

#include "Timer_1.h"

uint8 Timer_1_initVar = 0u;


/*******************************************************************************
* Function Name: Timer_1_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default Timer_1 configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (Timer_1__QUAD == Timer_1_CONFIG)
        Timer_1_CONTROL_REG = Timer_1_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Timer_1_TRIG_CONTROL1_REG  = Timer_1_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        Timer_1_SetInterruptMode(Timer_1_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        Timer_1_SetCounterMode(Timer_1_COUNT_DOWN);
        Timer_1_WritePeriod(Timer_1_QUAD_PERIOD_INIT_VALUE);
        Timer_1_WriteCounter(Timer_1_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (Timer_1__QUAD == Timer_1_CONFIG) */

    #if (Timer_1__TIMER == Timer_1_CONFIG)
        Timer_1_CONTROL_REG = Timer_1_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Timer_1_TRIG_CONTROL1_REG  = Timer_1_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Timer_1_SetInterruptMode(Timer_1_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        Timer_1_WritePeriod(Timer_1_TC_PERIOD_VALUE );

        #if (Timer_1__COMPARE == Timer_1_TC_COMP_CAP_MODE)
            Timer_1_WriteCompare(Timer_1_TC_COMPARE_VALUE);

            #if (1u == Timer_1_TC_COMPARE_SWAP)
                Timer_1_SetCompareSwap(1u);
                Timer_1_WriteCompareBuf(Timer_1_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == Timer_1_TC_COMPARE_SWAP) */
        #endif  /* (Timer_1__COMPARE == Timer_1_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (Timer_1_CY_TCPWM_V2 && Timer_1_TIMER_UPDOWN_CNT_USED && !Timer_1_CY_TCPWM_4000)
            Timer_1_WriteCounter(1u);
        #elif(Timer_1__COUNT_DOWN == Timer_1_TC_COUNTER_MODE)
            Timer_1_WriteCounter(Timer_1_TC_PERIOD_VALUE);
        #else
            Timer_1_WriteCounter(0u);
        #endif /* (Timer_1_CY_TCPWM_V2 && Timer_1_TIMER_UPDOWN_CNT_USED && !Timer_1_CY_TCPWM_4000) */
    #endif  /* (Timer_1__TIMER == Timer_1_CONFIG) */

    #if (Timer_1__PWM_SEL == Timer_1_CONFIG)
        Timer_1_CONTROL_REG = Timer_1_CTRL_PWM_BASE_CONFIG;

        #if (Timer_1__PWM_PR == Timer_1_PWM_MODE)
            Timer_1_CONTROL_REG |= Timer_1_CTRL_PWM_RUN_MODE;
            Timer_1_WriteCounter(Timer_1_PWM_PR_INIT_VALUE);
        #else
            Timer_1_CONTROL_REG |= Timer_1_CTRL_PWM_ALIGN | Timer_1_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (Timer_1_CY_TCPWM_V2 && Timer_1_PWM_UPDOWN_CNT_USED && !Timer_1_CY_TCPWM_4000)
                Timer_1_WriteCounter(1u);
            #elif (Timer_1__RIGHT == Timer_1_PWM_ALIGN)
                Timer_1_WriteCounter(Timer_1_PWM_PERIOD_VALUE);
            #else 
                Timer_1_WriteCounter(0u);
            #endif  /* (Timer_1_CY_TCPWM_V2 && Timer_1_PWM_UPDOWN_CNT_USED && !Timer_1_CY_TCPWM_4000) */
        #endif  /* (Timer_1__PWM_PR == Timer_1_PWM_MODE) */

        #if (Timer_1__PWM_DT == Timer_1_PWM_MODE)
            Timer_1_CONTROL_REG |= Timer_1_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (Timer_1__PWM_DT == Timer_1_PWM_MODE) */

        #if (Timer_1__PWM == Timer_1_PWM_MODE)
            Timer_1_CONTROL_REG |= Timer_1_CTRL_PWM_PRESCALER;
        #endif  /* (Timer_1__PWM == Timer_1_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        Timer_1_TRIG_CONTROL1_REG  = Timer_1_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Timer_1_SetInterruptMode(Timer_1_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (Timer_1__PWM_PR == Timer_1_PWM_MODE)
            Timer_1_TRIG_CONTROL2_REG =
                    (Timer_1_CC_MATCH_NO_CHANGE    |
                    Timer_1_OVERLOW_NO_CHANGE      |
                    Timer_1_UNDERFLOW_NO_CHANGE);
        #else
            #if (Timer_1__LEFT == Timer_1_PWM_ALIGN)
                Timer_1_TRIG_CONTROL2_REG = Timer_1_PWM_MODE_LEFT;
            #endif  /* ( Timer_1_PWM_LEFT == Timer_1_PWM_ALIGN) */

            #if (Timer_1__RIGHT == Timer_1_PWM_ALIGN)
                Timer_1_TRIG_CONTROL2_REG = Timer_1_PWM_MODE_RIGHT;
            #endif  /* ( Timer_1_PWM_RIGHT == Timer_1_PWM_ALIGN) */

            #if (Timer_1__CENTER == Timer_1_PWM_ALIGN)
                Timer_1_TRIG_CONTROL2_REG = Timer_1_PWM_MODE_CENTER;
            #endif  /* ( Timer_1_PWM_CENTER == Timer_1_PWM_ALIGN) */

            #if (Timer_1__ASYMMETRIC == Timer_1_PWM_ALIGN)
                Timer_1_TRIG_CONTROL2_REG = Timer_1_PWM_MODE_ASYM;
            #endif  /* (Timer_1__ASYMMETRIC == Timer_1_PWM_ALIGN) */
        #endif  /* (Timer_1__PWM_PR == Timer_1_PWM_MODE) */

        /* Set other values from customizer */
        Timer_1_WritePeriod(Timer_1_PWM_PERIOD_VALUE );
        Timer_1_WriteCompare(Timer_1_PWM_COMPARE_VALUE);

        #if (1u == Timer_1_PWM_COMPARE_SWAP)
            Timer_1_SetCompareSwap(1u);
            Timer_1_WriteCompareBuf(Timer_1_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == Timer_1_PWM_COMPARE_SWAP) */

        #if (1u == Timer_1_PWM_PERIOD_SWAP)
            Timer_1_SetPeriodSwap(1u);
            Timer_1_WritePeriodBuf(Timer_1_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == Timer_1_PWM_PERIOD_SWAP) */
    #endif  /* (Timer_1__PWM_SEL == Timer_1_CONFIG) */
    
}


/*******************************************************************************
* Function Name: Timer_1_Enable
********************************************************************************
*
* Summary:
*  Enables the Timer_1.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    Timer_1_BLOCK_CONTROL_REG |= Timer_1_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (Timer_1__PWM_SEL == Timer_1_CONFIG)
        #if (0u == Timer_1_PWM_START_SIGNAL_PRESENT)
            Timer_1_TriggerCommand(Timer_1_MASK, Timer_1_CMD_START);
        #endif /* (0u == Timer_1_PWM_START_SIGNAL_PRESENT) */
    #endif /* (Timer_1__PWM_SEL == Timer_1_CONFIG) */

    #if (Timer_1__TIMER == Timer_1_CONFIG)
        #if (0u == Timer_1_TC_START_SIGNAL_PRESENT)
            Timer_1_TriggerCommand(Timer_1_MASK, Timer_1_CMD_START);
        #endif /* (0u == Timer_1_TC_START_SIGNAL_PRESENT) */
    #endif /* (Timer_1__TIMER == Timer_1_CONFIG) */
    
    #if (Timer_1__QUAD == Timer_1_CONFIG)
        #if (0u != Timer_1_QUAD_AUTO_START)
            Timer_1_TriggerCommand(Timer_1_MASK, Timer_1_CMD_RELOAD);
        #endif /* (0u != Timer_1_QUAD_AUTO_START) */
    #endif  /* (Timer_1__QUAD == Timer_1_CONFIG) */
}


/*******************************************************************************
* Function Name: Timer_1_Start
********************************************************************************
*
* Summary:
*  Initializes the Timer_1 with default customizer
*  values when called the first time and enables the Timer_1.
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
*  Timer_1_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time Timer_1_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the Timer_1_Start() routine.
*
*******************************************************************************/
void Timer_1_Start(void)
{
    if (0u == Timer_1_initVar)
    {
        Timer_1_Init();
        Timer_1_initVar = 1u;
    }

    Timer_1_Enable();
}


/*******************************************************************************
* Function Name: Timer_1_Stop
********************************************************************************
*
* Summary:
*  Disables the Timer_1.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_BLOCK_CONTROL_REG &= (uint32)~Timer_1_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the Timer_1. This function is used when
*  configured as a generic Timer_1 and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the Timer_1 to operate in
*   Values:
*   - Timer_1_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - Timer_1_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - Timer_1_MODE_QUAD - Quadrature decoder
*         - Timer_1_MODE_PWM - PWM
*         - Timer_1_MODE_PWM_DT - PWM with dead time
*         - Timer_1_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_CONTROL_REG &= (uint32)~Timer_1_MODE_MASK;
    Timer_1_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - Timer_1_MODE_X1 - Counts on phi 1 rising
*         - Timer_1_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - Timer_1_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_CONTROL_REG &= (uint32)~Timer_1_QUAD_MODE_MASK;
    Timer_1_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - Timer_1_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - Timer_1_PRESCALE_DIVBY2    - Divide by 2
*         - Timer_1_PRESCALE_DIVBY4    - Divide by 4
*         - Timer_1_PRESCALE_DIVBY8    - Divide by 8
*         - Timer_1_PRESCALE_DIVBY16   - Divide by 16
*         - Timer_1_PRESCALE_DIVBY32   - Divide by 32
*         - Timer_1_PRESCALE_DIVBY64   - Divide by 64
*         - Timer_1_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_CONTROL_REG &= (uint32)~Timer_1_PRESCALER_MASK;
    Timer_1_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the Timer_1 runs
*  continuously or stops when terminal count is reached.  By default the
*  Timer_1 operates in the continuous mode.
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
void Timer_1_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_CONTROL_REG &= (uint32)~Timer_1_ONESHOT_MASK;
    Timer_1_CONTROL_REG |= ((uint32)((oneShotEnable & Timer_1_1BIT_MASK) <<
                                                               Timer_1_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_SetPWMMode
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
void Timer_1_SetPWMMode(uint32 modeMask)
{
    Timer_1_TRIG_CONTROL2_REG = (modeMask & Timer_1_6BIT_MASK);
}



/*******************************************************************************
* Function Name: Timer_1_SetPWMSyncKill
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
void Timer_1_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_CONTROL_REG &= (uint32)~Timer_1_PWM_SYNC_KILL_MASK;
    Timer_1_CONTROL_REG |= ((uint32)((syncKillEnable & Timer_1_1BIT_MASK)  <<
                                               Timer_1_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_SetPWMStopOnKill
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
void Timer_1_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_CONTROL_REG &= (uint32)~Timer_1_PWM_STOP_KILL_MASK;
    Timer_1_CONTROL_REG |= ((uint32)((stopOnKillEnable & Timer_1_1BIT_MASK)  <<
                                                         Timer_1_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_SetPWMDeadTime
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
void Timer_1_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_CONTROL_REG &= (uint32)~Timer_1_PRESCALER_MASK;
    Timer_1_CONTROL_REG |= ((uint32)((deadTime & Timer_1_8BIT_MASK) <<
                                                          Timer_1_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_SetPWMInvert
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
*         - Timer_1_INVERT_LINE   - Inverts the line output
*         - Timer_1_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_CONTROL_REG &= (uint32)~Timer_1_INV_OUT_MASK;
    Timer_1_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: Timer_1_WriteCounter
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
void Timer_1_WriteCounter(uint32 count)
{
    Timer_1_COUNTER_REG = (count & Timer_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timer_1_ReadCounter
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
uint32 Timer_1_ReadCounter(void)
{
    return (Timer_1_COUNTER_REG & Timer_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timer_1_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - Timer_1_COUNT_UP       - Counts up
*     - Timer_1_COUNT_DOWN     - Counts down
*     - Timer_1_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - Timer_1_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_CONTROL_REG &= (uint32)~Timer_1_UPDOWN_MASK;
    Timer_1_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_WritePeriod
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
void Timer_1_WritePeriod(uint32 period)
{
    Timer_1_PERIOD_REG = (period & Timer_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timer_1_ReadPeriod
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
uint32 Timer_1_ReadPeriod(void)
{
    return (Timer_1_PERIOD_REG & Timer_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timer_1_SetCompareSwap
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
void Timer_1_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_CONTROL_REG &= (uint32)~Timer_1_RELOAD_CC_MASK;
    Timer_1_CONTROL_REG |= (swapEnable & Timer_1_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_WritePeriodBuf
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
void Timer_1_WritePeriodBuf(uint32 periodBuf)
{
    Timer_1_PERIOD_BUF_REG = (periodBuf & Timer_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timer_1_ReadPeriodBuf
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
uint32 Timer_1_ReadPeriodBuf(void)
{
    return (Timer_1_PERIOD_BUF_REG & Timer_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timer_1_SetPeriodSwap
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
void Timer_1_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_CONTROL_REG &= (uint32)~Timer_1_RELOAD_PERIOD_MASK;
    Timer_1_CONTROL_REG |= ((uint32)((swapEnable & Timer_1_1BIT_MASK) <<
                                                            Timer_1_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_WriteCompare
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
void Timer_1_WriteCompare(uint32 compare)
{
    #if (Timer_1_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Timer_1_CY_TCPWM_4000) */

    #if (Timer_1_CY_TCPWM_4000)
        currentMode = ((Timer_1_CONTROL_REG & Timer_1_UPDOWN_MASK) >> Timer_1_UPDOWN_SHIFT);

        if (((uint32)Timer_1__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)Timer_1__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (Timer_1_CY_TCPWM_4000) */
    
    Timer_1_COMP_CAP_REG = (compare & Timer_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timer_1_ReadCompare
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
uint32 Timer_1_ReadCompare(void)
{
    #if (Timer_1_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Timer_1_CY_TCPWM_4000) */

    #if (Timer_1_CY_TCPWM_4000)
        currentMode = ((Timer_1_CONTROL_REG & Timer_1_UPDOWN_MASK) >> Timer_1_UPDOWN_SHIFT);
        
        regVal = Timer_1_COMP_CAP_REG;
        
        if (((uint32)Timer_1__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Timer_1__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Timer_1_16BIT_MASK);
    #else
        return (Timer_1_COMP_CAP_REG & Timer_1_16BIT_MASK);
    #endif /* (Timer_1_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Timer_1_WriteCompareBuf
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
void Timer_1_WriteCompareBuf(uint32 compareBuf)
{
    #if (Timer_1_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Timer_1_CY_TCPWM_4000) */

    #if (Timer_1_CY_TCPWM_4000)
        currentMode = ((Timer_1_CONTROL_REG & Timer_1_UPDOWN_MASK) >> Timer_1_UPDOWN_SHIFT);

        if (((uint32)Timer_1__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)Timer_1__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (Timer_1_CY_TCPWM_4000) */
    
    Timer_1_COMP_CAP_BUF_REG = (compareBuf & Timer_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timer_1_ReadCompareBuf
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
uint32 Timer_1_ReadCompareBuf(void)
{
    #if (Timer_1_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Timer_1_CY_TCPWM_4000) */

    #if (Timer_1_CY_TCPWM_4000)
        currentMode = ((Timer_1_CONTROL_REG & Timer_1_UPDOWN_MASK) >> Timer_1_UPDOWN_SHIFT);

        regVal = Timer_1_COMP_CAP_BUF_REG;
        
        if (((uint32)Timer_1__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Timer_1__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Timer_1_16BIT_MASK);
    #else
        return (Timer_1_COMP_CAP_BUF_REG & Timer_1_16BIT_MASK);
    #endif /* (Timer_1_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Timer_1_ReadCapture
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
uint32 Timer_1_ReadCapture(void)
{
    return (Timer_1_COMP_CAP_REG & Timer_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timer_1_ReadCaptureBuf
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
uint32 Timer_1_ReadCaptureBuf(void)
{
    return (Timer_1_COMP_CAP_BUF_REG & Timer_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timer_1_SetCaptureMode
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
*     - Timer_1_TRIG_LEVEL     - Level
*     - Timer_1_TRIG_RISING    - Rising edge
*     - Timer_1_TRIG_FALLING   - Falling edge
*     - Timer_1_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_TRIG_CONTROL1_REG &= (uint32)~Timer_1_CAPTURE_MASK;
    Timer_1_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Timer_1_TRIG_LEVEL     - Level
*     - Timer_1_TRIG_RISING    - Rising edge
*     - Timer_1_TRIG_FALLING   - Falling edge
*     - Timer_1_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_TRIG_CONTROL1_REG &= (uint32)~Timer_1_RELOAD_MASK;
    Timer_1_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Timer_1_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Timer_1_TRIG_LEVEL     - Level
*     - Timer_1_TRIG_RISING    - Rising edge
*     - Timer_1_TRIG_FALLING   - Falling edge
*     - Timer_1_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_TRIG_CONTROL1_REG &= (uint32)~Timer_1_START_MASK;
    Timer_1_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Timer_1_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Timer_1_TRIG_LEVEL     - Level
*     - Timer_1_TRIG_RISING    - Rising edge
*     - Timer_1_TRIG_FALLING   - Falling edge
*     - Timer_1_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_TRIG_CONTROL1_REG &= (uint32)~Timer_1_STOP_MASK;
    Timer_1_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Timer_1_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Timer_1_TRIG_LEVEL     - Level
*     - Timer_1_TRIG_RISING    - Rising edge
*     - Timer_1_TRIG_FALLING   - Falling edge
*     - Timer_1_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_TRIG_CONTROL1_REG &= (uint32)~Timer_1_COUNT_MASK;
    Timer_1_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Timer_1_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_TriggerCommand
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
*     - Timer_1_CMD_CAPTURE    - Trigger Capture/Switch command
*     - Timer_1_CMD_RELOAD     - Trigger Reload/Index command
*     - Timer_1_CMD_STOP       - Trigger Stop/Kill command
*     - Timer_1_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timer_1_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timer_1_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the Timer_1.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - Timer_1_STATUS_DOWN    - Set if counting down
*     - Timer_1_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 Timer_1_ReadStatus(void)
{
    return ((Timer_1_STATUS_REG >> Timer_1_RUNNING_STATUS_SHIFT) |
            (Timer_1_STATUS_REG & Timer_1_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: Timer_1_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - Timer_1_INTR_MASK_TC       - Terminal count mask
*     - Timer_1_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_SetInterruptMode(uint32 interruptMask)
{
    Timer_1_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: Timer_1_GetInterruptSourceMasked
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
*     - Timer_1_INTR_MASK_TC       - Terminal count mask
*     - Timer_1_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Timer_1_GetInterruptSourceMasked(void)
{
    return (Timer_1_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: Timer_1_GetInterruptSource
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
*     - Timer_1_INTR_MASK_TC       - Terminal count mask
*     - Timer_1_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Timer_1_GetInterruptSource(void)
{
    return (Timer_1_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: Timer_1_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - Timer_1_INTR_MASK_TC       - Terminal count mask
*     - Timer_1_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_ClearInterrupt(uint32 interruptMask)
{
    Timer_1_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Timer_1_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - Timer_1_INTR_MASK_TC       - Terminal count mask
*     - Timer_1_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Timer_1_SetInterrupt(uint32 interruptMask)
{
    Timer_1_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
