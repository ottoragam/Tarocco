/*******************************************************************************
* File Name: ERRORCOUNT.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "ERRORCOUNT.h"

uint8 ERRORCOUNT_initVar = 0u;


/*******************************************************************************
* Function Name: ERRORCOUNT_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void ERRORCOUNT_Init(void) 
{
        #if (!ERRORCOUNT_UsingFixedFunction && !ERRORCOUNT_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!ERRORCOUNT_UsingFixedFunction && !ERRORCOUNT_ControlRegRemoved) */
        
        #if(!ERRORCOUNT_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 ERRORCOUNT_interruptState;
        #endif /* (!ERRORCOUNT_UsingFixedFunction) */
        
        #if (ERRORCOUNT_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            ERRORCOUNT_CONTROL &= ERRORCOUNT_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                ERRORCOUNT_CONTROL2 &= ((uint8)(~ERRORCOUNT_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                ERRORCOUNT_CONTROL3 &= ((uint8)(~ERRORCOUNT_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (ERRORCOUNT_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                ERRORCOUNT_CONTROL |= ERRORCOUNT_ONESHOT;
            #endif /* (ERRORCOUNT_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            ERRORCOUNT_CONTROL2 |= ERRORCOUNT_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            ERRORCOUNT_RT1 &= ((uint8)(~ERRORCOUNT_RT1_MASK));
            ERRORCOUNT_RT1 |= ERRORCOUNT_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            ERRORCOUNT_RT1 &= ((uint8)(~ERRORCOUNT_SYNCDSI_MASK));
            ERRORCOUNT_RT1 |= ERRORCOUNT_SYNCDSI_EN;

        #else
            #if(!ERRORCOUNT_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = ERRORCOUNT_CONTROL & ((uint8)(~ERRORCOUNT_CTRL_CMPMODE_MASK));
            ERRORCOUNT_CONTROL = ctrl | ERRORCOUNT_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = ERRORCOUNT_CONTROL & ((uint8)(~ERRORCOUNT_CTRL_CAPMODE_MASK));
            
            #if( 0 != ERRORCOUNT_CAPTURE_MODE_CONF)
                ERRORCOUNT_CONTROL = ctrl | ERRORCOUNT_DEFAULT_CAPTURE_MODE;
            #else
                ERRORCOUNT_CONTROL = ctrl;
            #endif /* 0 != ERRORCOUNT_CAPTURE_MODE */ 
            
            #endif /* (!ERRORCOUNT_ControlRegRemoved) */
        #endif /* (ERRORCOUNT_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!ERRORCOUNT_UsingFixedFunction)
            ERRORCOUNT_ClearFIFO();
        #endif /* (!ERRORCOUNT_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        ERRORCOUNT_WritePeriod(ERRORCOUNT_INIT_PERIOD_VALUE);
        #if (!(ERRORCOUNT_UsingFixedFunction && (CY_PSOC5A)))
            ERRORCOUNT_WriteCounter(ERRORCOUNT_INIT_COUNTER_VALUE);
        #endif /* (!(ERRORCOUNT_UsingFixedFunction && (CY_PSOC5A))) */
        ERRORCOUNT_SetInterruptMode(ERRORCOUNT_INIT_INTERRUPTS_MASK);
        
        #if (!ERRORCOUNT_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)ERRORCOUNT_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            ERRORCOUNT_WriteCompare(ERRORCOUNT_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            ERRORCOUNT_interruptState = CyEnterCriticalSection();
            
            ERRORCOUNT_STATUS_AUX_CTRL |= ERRORCOUNT_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(ERRORCOUNT_interruptState);
            
        #endif /* (!ERRORCOUNT_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERRORCOUNT_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void ERRORCOUNT_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (ERRORCOUNT_UsingFixedFunction)
        ERRORCOUNT_GLOBAL_ENABLE |= ERRORCOUNT_BLOCK_EN_MASK;
        ERRORCOUNT_GLOBAL_STBY_ENABLE |= ERRORCOUNT_BLOCK_STBY_EN_MASK;
    #endif /* (ERRORCOUNT_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!ERRORCOUNT_ControlRegRemoved || ERRORCOUNT_UsingFixedFunction)
        ERRORCOUNT_CONTROL |= ERRORCOUNT_CTRL_ENABLE;                
    #endif /* (!ERRORCOUNT_ControlRegRemoved || ERRORCOUNT_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: ERRORCOUNT_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  ERRORCOUNT_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void ERRORCOUNT_Start(void) 
{
    if(ERRORCOUNT_initVar == 0u)
    {
        ERRORCOUNT_Init();
        
        ERRORCOUNT_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    ERRORCOUNT_Enable();        
}


/*******************************************************************************
* Function Name: ERRORCOUNT_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void ERRORCOUNT_Stop(void) 
{
    /* Disable Counter */
    #if(!ERRORCOUNT_ControlRegRemoved || ERRORCOUNT_UsingFixedFunction)
        ERRORCOUNT_CONTROL &= ((uint8)(~ERRORCOUNT_CTRL_ENABLE));        
    #endif /* (!ERRORCOUNT_ControlRegRemoved || ERRORCOUNT_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (ERRORCOUNT_UsingFixedFunction)
        ERRORCOUNT_GLOBAL_ENABLE &= ((uint8)(~ERRORCOUNT_BLOCK_EN_MASK));
        ERRORCOUNT_GLOBAL_STBY_ENABLE &= ((uint8)(~ERRORCOUNT_BLOCK_STBY_EN_MASK));
    #endif /* (ERRORCOUNT_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERRORCOUNT_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void ERRORCOUNT_SetInterruptMode(uint8 interruptsMask) 
{
    ERRORCOUNT_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: ERRORCOUNT_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   ERRORCOUNT_ReadStatusRegister(void) 
{
    return ERRORCOUNT_STATUS;
}


#if(!ERRORCOUNT_ControlRegRemoved)
/*******************************************************************************
* Function Name: ERRORCOUNT_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   ERRORCOUNT_ReadControlRegister(void) 
{
    return ERRORCOUNT_CONTROL;
}


/*******************************************************************************
* Function Name: ERRORCOUNT_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    ERRORCOUNT_WriteControlRegister(uint8 control) 
{
    ERRORCOUNT_CONTROL = control;
}

#endif  /* (!ERRORCOUNT_ControlRegRemoved) */


#if (!(ERRORCOUNT_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: ERRORCOUNT_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void ERRORCOUNT_WriteCounter(uint16 counter) \
                                   
{
    #if(ERRORCOUNT_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (ERRORCOUNT_GLOBAL_ENABLE & ERRORCOUNT_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        ERRORCOUNT_GLOBAL_ENABLE |= ERRORCOUNT_BLOCK_EN_MASK;
        CY_SET_REG16(ERRORCOUNT_COUNTER_LSB_PTR, (uint16)counter);
        ERRORCOUNT_GLOBAL_ENABLE &= ((uint8)(~ERRORCOUNT_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(ERRORCOUNT_COUNTER_LSB_PTR, counter);
    #endif /* (ERRORCOUNT_UsingFixedFunction) */
}
#endif /* (!(ERRORCOUNT_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: ERRORCOUNT_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) The present value of the counter.
*
*******************************************************************************/
uint16 ERRORCOUNT_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(ERRORCOUNT_UsingFixedFunction)
		(void)CY_GET_REG16(ERRORCOUNT_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(ERRORCOUNT_COUNTER_LSB_PTR_8BIT);
	#endif/* (ERRORCOUNT_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(ERRORCOUNT_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(ERRORCOUNT_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(ERRORCOUNT_STATICCOUNT_LSB_PTR));
    #endif /* (ERRORCOUNT_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERRORCOUNT_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint16) Present Capture value.
*
*******************************************************************************/
uint16 ERRORCOUNT_ReadCapture(void) 
{
    #if(ERRORCOUNT_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(ERRORCOUNT_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(ERRORCOUNT_STATICCOUNT_LSB_PTR));
    #endif /* (ERRORCOUNT_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERRORCOUNT_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint16) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void ERRORCOUNT_WritePeriod(uint16 period) 
{
    #if(ERRORCOUNT_UsingFixedFunction)
        CY_SET_REG16(ERRORCOUNT_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(ERRORCOUNT_PERIOD_LSB_PTR, period);
    #endif /* (ERRORCOUNT_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERRORCOUNT_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) Present period value.
*
*******************************************************************************/
uint16 ERRORCOUNT_ReadPeriod(void) 
{
    #if(ERRORCOUNT_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(ERRORCOUNT_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(ERRORCOUNT_PERIOD_LSB_PTR));
    #endif /* (ERRORCOUNT_UsingFixedFunction) */
}


#if (!ERRORCOUNT_UsingFixedFunction)
/*******************************************************************************
* Function Name: ERRORCOUNT_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void ERRORCOUNT_WriteCompare(uint16 compare) \
                                   
{
    #if(ERRORCOUNT_UsingFixedFunction)
        CY_SET_REG16(ERRORCOUNT_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(ERRORCOUNT_COMPARE_LSB_PTR, compare);
    #endif /* (ERRORCOUNT_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERRORCOUNT_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint16) Present compare value.
*
*******************************************************************************/
uint16 ERRORCOUNT_ReadCompare(void) 
{
    return (CY_GET_REG16(ERRORCOUNT_COMPARE_LSB_PTR));
}


#if (ERRORCOUNT_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ERRORCOUNT_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void ERRORCOUNT_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    ERRORCOUNT_CONTROL &= ((uint8)(~ERRORCOUNT_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    ERRORCOUNT_CONTROL |= compareMode;
}
#endif  /* (ERRORCOUNT_COMPARE_MODE_SOFTWARE) */


#if (ERRORCOUNT_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ERRORCOUNT_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void ERRORCOUNT_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    ERRORCOUNT_CONTROL &= ((uint8)(~ERRORCOUNT_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    ERRORCOUNT_CONTROL |= ((uint8)((uint8)captureMode << ERRORCOUNT_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (ERRORCOUNT_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: ERRORCOUNT_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void ERRORCOUNT_ClearFIFO(void) 
{

    while(0u != (ERRORCOUNT_ReadStatusRegister() & ERRORCOUNT_STATUS_FIFONEMP))
    {
        (void)ERRORCOUNT_ReadCapture();
    }

}
#endif  /* (!ERRORCOUNT_UsingFixedFunction) */


/* [] END OF FILE */

