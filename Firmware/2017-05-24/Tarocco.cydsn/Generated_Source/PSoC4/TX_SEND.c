/*******************************************************************************
* File Name: TX_SEND.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the TX_SEND
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

#include "TX_SEND.h"

uint8 TX_SEND_initVar = 0u;


/*******************************************************************************
* Function Name: TX_SEND_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default TX_SEND configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (TX_SEND__QUAD == TX_SEND_CONFIG)
        TX_SEND_CONTROL_REG = TX_SEND_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        TX_SEND_TRIG_CONTROL1_REG  = TX_SEND_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        TX_SEND_SetInterruptMode(TX_SEND_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        TX_SEND_SetCounterMode(TX_SEND_COUNT_DOWN);
        TX_SEND_WritePeriod(TX_SEND_QUAD_PERIOD_INIT_VALUE);
        TX_SEND_WriteCounter(TX_SEND_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (TX_SEND__QUAD == TX_SEND_CONFIG) */

    #if (TX_SEND__TIMER == TX_SEND_CONFIG)
        TX_SEND_CONTROL_REG = TX_SEND_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        TX_SEND_TRIG_CONTROL1_REG  = TX_SEND_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        TX_SEND_SetInterruptMode(TX_SEND_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        TX_SEND_WritePeriod(TX_SEND_TC_PERIOD_VALUE );

        #if (TX_SEND__COMPARE == TX_SEND_TC_COMP_CAP_MODE)
            TX_SEND_WriteCompare(TX_SEND_TC_COMPARE_VALUE);

            #if (1u == TX_SEND_TC_COMPARE_SWAP)
                TX_SEND_SetCompareSwap(1u);
                TX_SEND_WriteCompareBuf(TX_SEND_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == TX_SEND_TC_COMPARE_SWAP) */
        #endif  /* (TX_SEND__COMPARE == TX_SEND_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (TX_SEND_CY_TCPWM_V2 && TX_SEND_TIMER_UPDOWN_CNT_USED && !TX_SEND_CY_TCPWM_4000)
            TX_SEND_WriteCounter(1u);
        #elif(TX_SEND__COUNT_DOWN == TX_SEND_TC_COUNTER_MODE)
            TX_SEND_WriteCounter(TX_SEND_TC_PERIOD_VALUE);
        #else
            TX_SEND_WriteCounter(0u);
        #endif /* (TX_SEND_CY_TCPWM_V2 && TX_SEND_TIMER_UPDOWN_CNT_USED && !TX_SEND_CY_TCPWM_4000) */
    #endif  /* (TX_SEND__TIMER == TX_SEND_CONFIG) */

    #if (TX_SEND__PWM_SEL == TX_SEND_CONFIG)
        TX_SEND_CONTROL_REG = TX_SEND_CTRL_PWM_BASE_CONFIG;

        #if (TX_SEND__PWM_PR == TX_SEND_PWM_MODE)
            TX_SEND_CONTROL_REG |= TX_SEND_CTRL_PWM_RUN_MODE;
            TX_SEND_WriteCounter(TX_SEND_PWM_PR_INIT_VALUE);
        #else
            TX_SEND_CONTROL_REG |= TX_SEND_CTRL_PWM_ALIGN | TX_SEND_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (TX_SEND_CY_TCPWM_V2 && TX_SEND_PWM_UPDOWN_CNT_USED && !TX_SEND_CY_TCPWM_4000)
                TX_SEND_WriteCounter(1u);
            #elif (TX_SEND__RIGHT == TX_SEND_PWM_ALIGN)
                TX_SEND_WriteCounter(TX_SEND_PWM_PERIOD_VALUE);
            #else 
                TX_SEND_WriteCounter(0u);
            #endif  /* (TX_SEND_CY_TCPWM_V2 && TX_SEND_PWM_UPDOWN_CNT_USED && !TX_SEND_CY_TCPWM_4000) */
        #endif  /* (TX_SEND__PWM_PR == TX_SEND_PWM_MODE) */

        #if (TX_SEND__PWM_DT == TX_SEND_PWM_MODE)
            TX_SEND_CONTROL_REG |= TX_SEND_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (TX_SEND__PWM_DT == TX_SEND_PWM_MODE) */

        #if (TX_SEND__PWM == TX_SEND_PWM_MODE)
            TX_SEND_CONTROL_REG |= TX_SEND_CTRL_PWM_PRESCALER;
        #endif  /* (TX_SEND__PWM == TX_SEND_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        TX_SEND_TRIG_CONTROL1_REG  = TX_SEND_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        TX_SEND_SetInterruptMode(TX_SEND_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (TX_SEND__PWM_PR == TX_SEND_PWM_MODE)
            TX_SEND_TRIG_CONTROL2_REG =
                    (TX_SEND_CC_MATCH_NO_CHANGE    |
                    TX_SEND_OVERLOW_NO_CHANGE      |
                    TX_SEND_UNDERFLOW_NO_CHANGE);
        #else
            #if (TX_SEND__LEFT == TX_SEND_PWM_ALIGN)
                TX_SEND_TRIG_CONTROL2_REG = TX_SEND_PWM_MODE_LEFT;
            #endif  /* ( TX_SEND_PWM_LEFT == TX_SEND_PWM_ALIGN) */

            #if (TX_SEND__RIGHT == TX_SEND_PWM_ALIGN)
                TX_SEND_TRIG_CONTROL2_REG = TX_SEND_PWM_MODE_RIGHT;
            #endif  /* ( TX_SEND_PWM_RIGHT == TX_SEND_PWM_ALIGN) */

            #if (TX_SEND__CENTER == TX_SEND_PWM_ALIGN)
                TX_SEND_TRIG_CONTROL2_REG = TX_SEND_PWM_MODE_CENTER;
            #endif  /* ( TX_SEND_PWM_CENTER == TX_SEND_PWM_ALIGN) */

            #if (TX_SEND__ASYMMETRIC == TX_SEND_PWM_ALIGN)
                TX_SEND_TRIG_CONTROL2_REG = TX_SEND_PWM_MODE_ASYM;
            #endif  /* (TX_SEND__ASYMMETRIC == TX_SEND_PWM_ALIGN) */
        #endif  /* (TX_SEND__PWM_PR == TX_SEND_PWM_MODE) */

        /* Set other values from customizer */
        TX_SEND_WritePeriod(TX_SEND_PWM_PERIOD_VALUE );
        TX_SEND_WriteCompare(TX_SEND_PWM_COMPARE_VALUE);

        #if (1u == TX_SEND_PWM_COMPARE_SWAP)
            TX_SEND_SetCompareSwap(1u);
            TX_SEND_WriteCompareBuf(TX_SEND_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == TX_SEND_PWM_COMPARE_SWAP) */

        #if (1u == TX_SEND_PWM_PERIOD_SWAP)
            TX_SEND_SetPeriodSwap(1u);
            TX_SEND_WritePeriodBuf(TX_SEND_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == TX_SEND_PWM_PERIOD_SWAP) */
    #endif  /* (TX_SEND__PWM_SEL == TX_SEND_CONFIG) */
    
}


/*******************************************************************************
* Function Name: TX_SEND_Enable
********************************************************************************
*
* Summary:
*  Enables the TX_SEND.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    TX_SEND_BLOCK_CONTROL_REG |= TX_SEND_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (TX_SEND__PWM_SEL == TX_SEND_CONFIG)
        #if (0u == TX_SEND_PWM_START_SIGNAL_PRESENT)
            TX_SEND_TriggerCommand(TX_SEND_MASK, TX_SEND_CMD_START);
        #endif /* (0u == TX_SEND_PWM_START_SIGNAL_PRESENT) */
    #endif /* (TX_SEND__PWM_SEL == TX_SEND_CONFIG) */

    #if (TX_SEND__TIMER == TX_SEND_CONFIG)
        #if (0u == TX_SEND_TC_START_SIGNAL_PRESENT)
            TX_SEND_TriggerCommand(TX_SEND_MASK, TX_SEND_CMD_START);
        #endif /* (0u == TX_SEND_TC_START_SIGNAL_PRESENT) */
    #endif /* (TX_SEND__TIMER == TX_SEND_CONFIG) */
    
    #if (TX_SEND__QUAD == TX_SEND_CONFIG)
        #if (0u != TX_SEND_QUAD_AUTO_START)
            TX_SEND_TriggerCommand(TX_SEND_MASK, TX_SEND_CMD_RELOAD);
        #endif /* (0u != TX_SEND_QUAD_AUTO_START) */
    #endif  /* (TX_SEND__QUAD == TX_SEND_CONFIG) */
}


/*******************************************************************************
* Function Name: TX_SEND_Start
********************************************************************************
*
* Summary:
*  Initializes the TX_SEND with default customizer
*  values when called the first time and enables the TX_SEND.
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
*  TX_SEND_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time TX_SEND_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the TX_SEND_Start() routine.
*
*******************************************************************************/
void TX_SEND_Start(void)
{
    if (0u == TX_SEND_initVar)
    {
        TX_SEND_Init();
        TX_SEND_initVar = 1u;
    }

    TX_SEND_Enable();
}


/*******************************************************************************
* Function Name: TX_SEND_Stop
********************************************************************************
*
* Summary:
*  Disables the TX_SEND.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_BLOCK_CONTROL_REG &= (uint32)~TX_SEND_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the TX_SEND. This function is used when
*  configured as a generic TX_SEND and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the TX_SEND to operate in
*   Values:
*   - TX_SEND_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - TX_SEND_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - TX_SEND_MODE_QUAD - Quadrature decoder
*         - TX_SEND_MODE_PWM - PWM
*         - TX_SEND_MODE_PWM_DT - PWM with dead time
*         - TX_SEND_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_CONTROL_REG &= (uint32)~TX_SEND_MODE_MASK;
    TX_SEND_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - TX_SEND_MODE_X1 - Counts on phi 1 rising
*         - TX_SEND_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - TX_SEND_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_CONTROL_REG &= (uint32)~TX_SEND_QUAD_MODE_MASK;
    TX_SEND_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - TX_SEND_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - TX_SEND_PRESCALE_DIVBY2    - Divide by 2
*         - TX_SEND_PRESCALE_DIVBY4    - Divide by 4
*         - TX_SEND_PRESCALE_DIVBY8    - Divide by 8
*         - TX_SEND_PRESCALE_DIVBY16   - Divide by 16
*         - TX_SEND_PRESCALE_DIVBY32   - Divide by 32
*         - TX_SEND_PRESCALE_DIVBY64   - Divide by 64
*         - TX_SEND_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_CONTROL_REG &= (uint32)~TX_SEND_PRESCALER_MASK;
    TX_SEND_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the TX_SEND runs
*  continuously or stops when terminal count is reached.  By default the
*  TX_SEND operates in the continuous mode.
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
void TX_SEND_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_CONTROL_REG &= (uint32)~TX_SEND_ONESHOT_MASK;
    TX_SEND_CONTROL_REG |= ((uint32)((oneShotEnable & TX_SEND_1BIT_MASK) <<
                                                               TX_SEND_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_SetPWMMode
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
void TX_SEND_SetPWMMode(uint32 modeMask)
{
    TX_SEND_TRIG_CONTROL2_REG = (modeMask & TX_SEND_6BIT_MASK);
}



/*******************************************************************************
* Function Name: TX_SEND_SetPWMSyncKill
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
void TX_SEND_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_CONTROL_REG &= (uint32)~TX_SEND_PWM_SYNC_KILL_MASK;
    TX_SEND_CONTROL_REG |= ((uint32)((syncKillEnable & TX_SEND_1BIT_MASK)  <<
                                               TX_SEND_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_SetPWMStopOnKill
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
void TX_SEND_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_CONTROL_REG &= (uint32)~TX_SEND_PWM_STOP_KILL_MASK;
    TX_SEND_CONTROL_REG |= ((uint32)((stopOnKillEnable & TX_SEND_1BIT_MASK)  <<
                                                         TX_SEND_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_SetPWMDeadTime
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
void TX_SEND_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_CONTROL_REG &= (uint32)~TX_SEND_PRESCALER_MASK;
    TX_SEND_CONTROL_REG |= ((uint32)((deadTime & TX_SEND_8BIT_MASK) <<
                                                          TX_SEND_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_SetPWMInvert
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
*         - TX_SEND_INVERT_LINE   - Inverts the line output
*         - TX_SEND_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_CONTROL_REG &= (uint32)~TX_SEND_INV_OUT_MASK;
    TX_SEND_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: TX_SEND_WriteCounter
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
void TX_SEND_WriteCounter(uint32 count)
{
    TX_SEND_COUNTER_REG = (count & TX_SEND_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TX_SEND_ReadCounter
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
uint32 TX_SEND_ReadCounter(void)
{
    return (TX_SEND_COUNTER_REG & TX_SEND_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TX_SEND_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - TX_SEND_COUNT_UP       - Counts up
*     - TX_SEND_COUNT_DOWN     - Counts down
*     - TX_SEND_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - TX_SEND_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_CONTROL_REG &= (uint32)~TX_SEND_UPDOWN_MASK;
    TX_SEND_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_WritePeriod
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
void TX_SEND_WritePeriod(uint32 period)
{
    TX_SEND_PERIOD_REG = (period & TX_SEND_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TX_SEND_ReadPeriod
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
uint32 TX_SEND_ReadPeriod(void)
{
    return (TX_SEND_PERIOD_REG & TX_SEND_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TX_SEND_SetCompareSwap
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
void TX_SEND_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_CONTROL_REG &= (uint32)~TX_SEND_RELOAD_CC_MASK;
    TX_SEND_CONTROL_REG |= (swapEnable & TX_SEND_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_WritePeriodBuf
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
void TX_SEND_WritePeriodBuf(uint32 periodBuf)
{
    TX_SEND_PERIOD_BUF_REG = (periodBuf & TX_SEND_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TX_SEND_ReadPeriodBuf
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
uint32 TX_SEND_ReadPeriodBuf(void)
{
    return (TX_SEND_PERIOD_BUF_REG & TX_SEND_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TX_SEND_SetPeriodSwap
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
void TX_SEND_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_CONTROL_REG &= (uint32)~TX_SEND_RELOAD_PERIOD_MASK;
    TX_SEND_CONTROL_REG |= ((uint32)((swapEnable & TX_SEND_1BIT_MASK) <<
                                                            TX_SEND_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_WriteCompare
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
void TX_SEND_WriteCompare(uint32 compare)
{
    #if (TX_SEND_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (TX_SEND_CY_TCPWM_4000) */

    #if (TX_SEND_CY_TCPWM_4000)
        currentMode = ((TX_SEND_CONTROL_REG & TX_SEND_UPDOWN_MASK) >> TX_SEND_UPDOWN_SHIFT);

        if (((uint32)TX_SEND__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)TX_SEND__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (TX_SEND_CY_TCPWM_4000) */
    
    TX_SEND_COMP_CAP_REG = (compare & TX_SEND_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TX_SEND_ReadCompare
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
uint32 TX_SEND_ReadCompare(void)
{
    #if (TX_SEND_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (TX_SEND_CY_TCPWM_4000) */

    #if (TX_SEND_CY_TCPWM_4000)
        currentMode = ((TX_SEND_CONTROL_REG & TX_SEND_UPDOWN_MASK) >> TX_SEND_UPDOWN_SHIFT);
        
        regVal = TX_SEND_COMP_CAP_REG;
        
        if (((uint32)TX_SEND__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)TX_SEND__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & TX_SEND_16BIT_MASK);
    #else
        return (TX_SEND_COMP_CAP_REG & TX_SEND_16BIT_MASK);
    #endif /* (TX_SEND_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: TX_SEND_WriteCompareBuf
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
void TX_SEND_WriteCompareBuf(uint32 compareBuf)
{
    #if (TX_SEND_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (TX_SEND_CY_TCPWM_4000) */

    #if (TX_SEND_CY_TCPWM_4000)
        currentMode = ((TX_SEND_CONTROL_REG & TX_SEND_UPDOWN_MASK) >> TX_SEND_UPDOWN_SHIFT);

        if (((uint32)TX_SEND__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)TX_SEND__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (TX_SEND_CY_TCPWM_4000) */
    
    TX_SEND_COMP_CAP_BUF_REG = (compareBuf & TX_SEND_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TX_SEND_ReadCompareBuf
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
uint32 TX_SEND_ReadCompareBuf(void)
{
    #if (TX_SEND_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (TX_SEND_CY_TCPWM_4000) */

    #if (TX_SEND_CY_TCPWM_4000)
        currentMode = ((TX_SEND_CONTROL_REG & TX_SEND_UPDOWN_MASK) >> TX_SEND_UPDOWN_SHIFT);

        regVal = TX_SEND_COMP_CAP_BUF_REG;
        
        if (((uint32)TX_SEND__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)TX_SEND__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & TX_SEND_16BIT_MASK);
    #else
        return (TX_SEND_COMP_CAP_BUF_REG & TX_SEND_16BIT_MASK);
    #endif /* (TX_SEND_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: TX_SEND_ReadCapture
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
uint32 TX_SEND_ReadCapture(void)
{
    return (TX_SEND_COMP_CAP_REG & TX_SEND_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TX_SEND_ReadCaptureBuf
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
uint32 TX_SEND_ReadCaptureBuf(void)
{
    return (TX_SEND_COMP_CAP_BUF_REG & TX_SEND_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TX_SEND_SetCaptureMode
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
*     - TX_SEND_TRIG_LEVEL     - Level
*     - TX_SEND_TRIG_RISING    - Rising edge
*     - TX_SEND_TRIG_FALLING   - Falling edge
*     - TX_SEND_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_TRIG_CONTROL1_REG &= (uint32)~TX_SEND_CAPTURE_MASK;
    TX_SEND_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TX_SEND_TRIG_LEVEL     - Level
*     - TX_SEND_TRIG_RISING    - Rising edge
*     - TX_SEND_TRIG_FALLING   - Falling edge
*     - TX_SEND_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_TRIG_CONTROL1_REG &= (uint32)~TX_SEND_RELOAD_MASK;
    TX_SEND_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TX_SEND_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TX_SEND_TRIG_LEVEL     - Level
*     - TX_SEND_TRIG_RISING    - Rising edge
*     - TX_SEND_TRIG_FALLING   - Falling edge
*     - TX_SEND_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_TRIG_CONTROL1_REG &= (uint32)~TX_SEND_START_MASK;
    TX_SEND_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TX_SEND_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TX_SEND_TRIG_LEVEL     - Level
*     - TX_SEND_TRIG_RISING    - Rising edge
*     - TX_SEND_TRIG_FALLING   - Falling edge
*     - TX_SEND_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_TRIG_CONTROL1_REG &= (uint32)~TX_SEND_STOP_MASK;
    TX_SEND_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TX_SEND_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TX_SEND_TRIG_LEVEL     - Level
*     - TX_SEND_TRIG_RISING    - Rising edge
*     - TX_SEND_TRIG_FALLING   - Falling edge
*     - TX_SEND_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_TRIG_CONTROL1_REG &= (uint32)~TX_SEND_COUNT_MASK;
    TX_SEND_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TX_SEND_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_TriggerCommand
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
*     - TX_SEND_CMD_CAPTURE    - Trigger Capture/Switch command
*     - TX_SEND_CMD_RELOAD     - Trigger Reload/Index command
*     - TX_SEND_CMD_STOP       - Trigger Stop/Kill command
*     - TX_SEND_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TX_SEND_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TX_SEND_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the TX_SEND.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - TX_SEND_STATUS_DOWN    - Set if counting down
*     - TX_SEND_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 TX_SEND_ReadStatus(void)
{
    return ((TX_SEND_STATUS_REG >> TX_SEND_RUNNING_STATUS_SHIFT) |
            (TX_SEND_STATUS_REG & TX_SEND_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: TX_SEND_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - TX_SEND_INTR_MASK_TC       - Terminal count mask
*     - TX_SEND_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_SetInterruptMode(uint32 interruptMask)
{
    TX_SEND_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: TX_SEND_GetInterruptSourceMasked
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
*     - TX_SEND_INTR_MASK_TC       - Terminal count mask
*     - TX_SEND_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 TX_SEND_GetInterruptSourceMasked(void)
{
    return (TX_SEND_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: TX_SEND_GetInterruptSource
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
*     - TX_SEND_INTR_MASK_TC       - Terminal count mask
*     - TX_SEND_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 TX_SEND_GetInterruptSource(void)
{
    return (TX_SEND_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: TX_SEND_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - TX_SEND_INTR_MASK_TC       - Terminal count mask
*     - TX_SEND_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_ClearInterrupt(uint32 interruptMask)
{
    TX_SEND_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: TX_SEND_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - TX_SEND_INTR_MASK_TC       - Terminal count mask
*     - TX_SEND_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TX_SEND_SetInterrupt(uint32 interruptMask)
{
    TX_SEND_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
