/*******************************************************************************
* File Name: QDEC.c  
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the Quadrature Decoder
*  component.
*
* Note:
*  None.
*   
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "QDEC.h"

#if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT)
    #include "QDEC_PVT.h"
#endif /* QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT */

uint8 QDEC_initVar = 0u;


/*******************************************************************************
* Function Name: QDEC_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default QuadDec configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QDEC_Init(void) 
{
    #if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT)
        /* Disable Interrupt. */
        CyIntDisable(QDEC_ISR_NUMBER);
        /* Set the ISR to point to the QDEC_isr Interrupt. */
        (void) CyIntSetVector(QDEC_ISR_NUMBER, & QDEC_ISR);
        /* Set the priority. */
        CyIntSetPriority(QDEC_ISR_NUMBER, QDEC_ISR_PRIORITY);
    #endif /* QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: QDEC_Enable
********************************************************************************
*
* Summary:
*  This function enable interrupts from Component and also enable Component's
*  ISR in case of 32-bit counter.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QDEC_Enable(void) 
{
    uint8 enableInterrupts;

    QDEC_SetInterruptMask(QDEC_INIT_INT_MASK);

    /* Clear pending interrupts. */
    (void) QDEC_GetEvents();
    
    enableInterrupts = CyEnterCriticalSection();

    /* Enable interrupts from Statusi register */
    QDEC_SR_AUX_CONTROL |= QDEC_INTERRUPTS_ENABLE;

    CyExitCriticalSection(enableInterrupts);        

    #if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT)
        /* Enable Component interrupts */
        CyIntEnable(QDEC_ISR_NUMBER);
    #endif /* QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: QDEC_Start
********************************************************************************
*
* Summary:
*  Initializes UDBs and other relevant hardware.
*  Resets counter, enables or disables all relevant interrupts.
*  Starts monitoring the inputs and counting.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  QDEC_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QDEC_Start(void) 
{
    #if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT)
        QDEC_Cnt8_Start();
        QDEC_Cnt8_WriteCounter(QDEC_COUNTER_INIT_VALUE);
    #else
        /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_16_BIT) || 
        *  (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT) 
        */
        QDEC_Cnt16_Start();
        QDEC_Cnt16_WriteCounter(QDEC_COUNTER_INIT_VALUE);
    #endif /* QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT */
    
    #if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT)        
       QDEC_count32SoftPart = 0;
    #endif /* QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT */

    if (QDEC_initVar == 0u)
    {
        QDEC_Init();
        QDEC_initVar = 1u;
    }

    QDEC_Enable();
}


/*******************************************************************************
* Function Name: QDEC_Stop
********************************************************************************
*
* Summary:
*  Turns off UDBs and other relevant hardware.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QDEC_Stop(void) 
{
    uint8 enableInterrupts;

    #if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT)
        QDEC_Cnt8_Stop();
    #else 
        /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_16_BIT) ||
        *  (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT)
        */
        QDEC_Cnt16_Stop();    /* counter disable */
    #endif /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT) */
 
    enableInterrupts = CyEnterCriticalSection();

    /* Disable interrupts interrupts from Statusi register */
    QDEC_SR_AUX_CONTROL &= (uint8) (~QDEC_INTERRUPTS_ENABLE);

    CyExitCriticalSection(enableInterrupts);

    #if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT)
        CyIntDisable(QDEC_ISR_NUMBER);    /* interrupt disable */
    #endif /* QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: QDEC_GetCounter
********************************************************************************
*
* Summary:
*  Reports the current value of the counter.
*
* Parameters:
*  None.
*
* Return:
*  The counter value. Return type is signed and per the counter size setting.
*  A positive value indicates clockwise movement (B before A).
*
* Global variables:
*  QDEC_count32SoftPart - used to get hi 16 bit for current value
*  of the 32-bit counter, when Counter size equal 32-bit.
*
*******************************************************************************/
int32 QDEC_GetCounter(void) 
{
    int32 count;
    uint16 tmpCnt;

    #if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT)
        int16 hwCount;

        CyIntDisable(QDEC_ISR_NUMBER);

        tmpCnt = QDEC_Cnt16_ReadCounter();
        hwCount = (int16) ((int32) tmpCnt - (int32) QDEC_COUNTER_INIT_VALUE);
        count = QDEC_count32SoftPart + hwCount;

        CyIntEnable(QDEC_ISR_NUMBER);
    #else 
        /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT) || 
        *  (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_16_BIT)
        */
        #if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT)
            tmpCnt = QDEC_Cnt8_ReadCounter();
        #else /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_16_BIT) */
            tmpCnt = QDEC_Cnt16_ReadCounter();
        #endif  /* QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT */

        count = (int32) ((int32) tmpCnt -
                (int32) QDEC_COUNTER_INIT_VALUE);

    #endif /* QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT */ 

    return (count);
}


/*******************************************************************************
* Function Name: QDEC_SetCounter
********************************************************************************
*
* Summary:
*  Sets the current value of the counter.
*
* Parameters:
*  value:  The new value. Parameter type is signed and per the counter size
*  setting.
*
* Return:
*  None.
*
* Global variables:
*  QDEC_count32SoftPart - modified to set hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QDEC_SetCounter(int32 value) 
{
    #if ((QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT) || \
         (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_16_BIT))
        uint16 count;
        
        if (value >= 0)
        {
            count = (uint16) value + QDEC_COUNTER_INIT_VALUE;
        }
        else
        {
            count = QDEC_COUNTER_INIT_VALUE - (uint16)(-value);
        }
        #if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT)
            QDEC_Cnt8_WriteCounter(count);
        #else /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_16_BIT) */
            QDEC_Cnt16_WriteCounter(count);
        #endif  /* QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT */
    #else /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT) */
        CyIntDisable(QDEC_ISR_NUMBER);

        QDEC_Cnt16_WriteCounter(QDEC_COUNTER_INIT_VALUE);
        QDEC_count32SoftPart = value;

        CyIntEnable(QDEC_ISR_NUMBER);
    #endif  /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT) ||
             * (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_16_BIT)
             */
}


/*******************************************************************************
* Function Name: QDEC_GetEvents
********************************************************************************
* 
* Summary:
*   Reports the current status of events. This function clears the bits of the 
*   status register.
*
* Parameters:
*  None.
*
* Return:
*  The events, as bits in an unsigned 8-bit value:
*    Bit      Description
*     0        Counter overflow.
*     1        Counter underflow.
*     2        Counter reset due to index, if index input is used.
*     3        Invalid A, B inputs state transition.
*
*******************************************************************************/
uint8 QDEC_GetEvents(void) 
{
    return (QDEC_STATUS_REG & QDEC_INIT_INT_MASK);
}


/*******************************************************************************
* Function Name: QDEC_SetInterruptMask
********************************************************************************
*
* Summary:
*  Enables / disables interrupts due to the events.
*  For the 32-bit counter, the overflow, underflow and reset interrupts cannot
*  be disabled, these bits are ignored.
*
* Parameters:
*  mask: Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*
* Return:
*  None.
*
*******************************************************************************/
void QDEC_SetInterruptMask(uint8 mask) 
{
    #if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT)
        /* Underflow, Overflow and Reset interrupts for 32-bit Counter are always enable */
        mask |= (QDEC_COUNTER_OVERFLOW | QDEC_COUNTER_UNDERFLOW |
                 QDEC_COUNTER_RESET);
    #endif /* QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT */

    QDEC_STATUS_MASK = mask;
}


/*******************************************************************************
* Function Name: QDEC_GetInterruptMask
********************************************************************************
*
* Summary:
*  Reports the current interrupt mask settings.
*
* Parameters:
*  None.
*
* Return:
*  Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*  For the 32-bit counter, the overflow, underflow and reset enable bits are
*  always set.
*
*******************************************************************************/
uint8 QDEC_GetInterruptMask(void) 
{
    return (QDEC_STATUS_MASK & QDEC_INIT_INT_MASK);
}


/* [] END OF FILE */
