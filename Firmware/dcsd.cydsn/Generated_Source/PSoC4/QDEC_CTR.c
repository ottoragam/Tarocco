/*******************************************************************************
* File Name: QDEC_CTR.c  
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

#include "QDEC_CTR.h"

uint8 QDEC_CTR_initVar = 0u;


/*******************************************************************************
* Function Name: QDEC_CTR_Init
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
void QDEC_CTR_Init(void) 
{
        #if (!QDEC_CTR_UsingFixedFunction && !QDEC_CTR_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!QDEC_CTR_UsingFixedFunction && !QDEC_CTR_ControlRegRemoved) */
        
        #if(!QDEC_CTR_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 QDEC_CTR_interruptState;
        #endif /* (!QDEC_CTR_UsingFixedFunction) */
        
        #if (QDEC_CTR_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            QDEC_CTR_CONTROL &= QDEC_CTR_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                QDEC_CTR_CONTROL2 &= ((uint8)(~QDEC_CTR_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                QDEC_CTR_CONTROL3 &= ((uint8)(~QDEC_CTR_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (QDEC_CTR_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                QDEC_CTR_CONTROL |= QDEC_CTR_ONESHOT;
            #endif /* (QDEC_CTR_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            QDEC_CTR_CONTROL2 |= QDEC_CTR_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            QDEC_CTR_RT1 &= ((uint8)(~QDEC_CTR_RT1_MASK));
            QDEC_CTR_RT1 |= QDEC_CTR_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            QDEC_CTR_RT1 &= ((uint8)(~QDEC_CTR_SYNCDSI_MASK));
            QDEC_CTR_RT1 |= QDEC_CTR_SYNCDSI_EN;

        #else
            #if(!QDEC_CTR_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = QDEC_CTR_CONTROL & ((uint8)(~QDEC_CTR_CTRL_CMPMODE_MASK));
            QDEC_CTR_CONTROL = ctrl | QDEC_CTR_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = QDEC_CTR_CONTROL & ((uint8)(~QDEC_CTR_CTRL_CAPMODE_MASK));
            
            #if( 0 != QDEC_CTR_CAPTURE_MODE_CONF)
                QDEC_CTR_CONTROL = ctrl | QDEC_CTR_DEFAULT_CAPTURE_MODE;
            #else
                QDEC_CTR_CONTROL = ctrl;
            #endif /* 0 != QDEC_CTR_CAPTURE_MODE */ 
            
            #endif /* (!QDEC_CTR_ControlRegRemoved) */
        #endif /* (QDEC_CTR_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!QDEC_CTR_UsingFixedFunction)
            QDEC_CTR_ClearFIFO();
        #endif /* (!QDEC_CTR_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        QDEC_CTR_WritePeriod(QDEC_CTR_INIT_PERIOD_VALUE);
        #if (!(QDEC_CTR_UsingFixedFunction && (CY_PSOC5A)))
            QDEC_CTR_WriteCounter(QDEC_CTR_INIT_COUNTER_VALUE);
        #endif /* (!(QDEC_CTR_UsingFixedFunction && (CY_PSOC5A))) */
        QDEC_CTR_SetInterruptMode(QDEC_CTR_INIT_INTERRUPTS_MASK);
        
        #if (!QDEC_CTR_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)QDEC_CTR_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            QDEC_CTR_WriteCompare(QDEC_CTR_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            QDEC_CTR_interruptState = CyEnterCriticalSection();
            
            QDEC_CTR_STATUS_AUX_CTRL |= QDEC_CTR_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(QDEC_CTR_interruptState);
            
        #endif /* (!QDEC_CTR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QDEC_CTR_Enable
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
void QDEC_CTR_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (QDEC_CTR_UsingFixedFunction)
        QDEC_CTR_GLOBAL_ENABLE |= QDEC_CTR_BLOCK_EN_MASK;
        QDEC_CTR_GLOBAL_STBY_ENABLE |= QDEC_CTR_BLOCK_STBY_EN_MASK;
    #endif /* (QDEC_CTR_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!QDEC_CTR_ControlRegRemoved || QDEC_CTR_UsingFixedFunction)
        QDEC_CTR_CONTROL |= QDEC_CTR_CTRL_ENABLE;                
    #endif /* (!QDEC_CTR_ControlRegRemoved || QDEC_CTR_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: QDEC_CTR_Start
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
*  QDEC_CTR_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void QDEC_CTR_Start(void) 
{
    if(QDEC_CTR_initVar == 0u)
    {
        QDEC_CTR_Init();
        
        QDEC_CTR_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    QDEC_CTR_Enable();        
}


/*******************************************************************************
* Function Name: QDEC_CTR_Stop
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
void QDEC_CTR_Stop(void) 
{
    /* Disable Counter */
    #if(!QDEC_CTR_ControlRegRemoved || QDEC_CTR_UsingFixedFunction)
        QDEC_CTR_CONTROL &= ((uint8)(~QDEC_CTR_CTRL_ENABLE));        
    #endif /* (!QDEC_CTR_ControlRegRemoved || QDEC_CTR_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (QDEC_CTR_UsingFixedFunction)
        QDEC_CTR_GLOBAL_ENABLE &= ((uint8)(~QDEC_CTR_BLOCK_EN_MASK));
        QDEC_CTR_GLOBAL_STBY_ENABLE &= ((uint8)(~QDEC_CTR_BLOCK_STBY_EN_MASK));
    #endif /* (QDEC_CTR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QDEC_CTR_SetInterruptMode
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
void QDEC_CTR_SetInterruptMode(uint8 interruptsMask) 
{
    QDEC_CTR_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: QDEC_CTR_ReadStatusRegister
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
uint8   QDEC_CTR_ReadStatusRegister(void) 
{
    return QDEC_CTR_STATUS;
}


#if(!QDEC_CTR_ControlRegRemoved)
/*******************************************************************************
* Function Name: QDEC_CTR_ReadControlRegister
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
uint8   QDEC_CTR_ReadControlRegister(void) 
{
    return QDEC_CTR_CONTROL;
}


/*******************************************************************************
* Function Name: QDEC_CTR_WriteControlRegister
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
void    QDEC_CTR_WriteControlRegister(uint8 control) 
{
    QDEC_CTR_CONTROL = control;
}

#endif  /* (!QDEC_CTR_ControlRegRemoved) */


#if (!(QDEC_CTR_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: QDEC_CTR_WriteCounter
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
void QDEC_CTR_WriteCounter(uint32 counter) \
                                   
{
    #if(QDEC_CTR_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (QDEC_CTR_GLOBAL_ENABLE & QDEC_CTR_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        QDEC_CTR_GLOBAL_ENABLE |= QDEC_CTR_BLOCK_EN_MASK;
        CY_SET_REG16(QDEC_CTR_COUNTER_LSB_PTR, (uint16)counter);
        QDEC_CTR_GLOBAL_ENABLE &= ((uint8)(~QDEC_CTR_BLOCK_EN_MASK));
    #else
        CY_SET_REG32(QDEC_CTR_COUNTER_LSB_PTR, counter);
    #endif /* (QDEC_CTR_UsingFixedFunction) */
}
#endif /* (!(QDEC_CTR_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: QDEC_CTR_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) The present value of the counter.
*
*******************************************************************************/
uint32 QDEC_CTR_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(QDEC_CTR_UsingFixedFunction)
		(void)CY_GET_REG16(QDEC_CTR_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(QDEC_CTR_COUNTER_LSB_PTR_8BIT);
	#endif/* (QDEC_CTR_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(QDEC_CTR_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(QDEC_CTR_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(QDEC_CTR_STATICCOUNT_LSB_PTR));
    #endif /* (QDEC_CTR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QDEC_CTR_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint32) Present Capture value.
*
*******************************************************************************/
uint32 QDEC_CTR_ReadCapture(void) 
{
    #if(QDEC_CTR_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(QDEC_CTR_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(QDEC_CTR_STATICCOUNT_LSB_PTR));
    #endif /* (QDEC_CTR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QDEC_CTR_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint32) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void QDEC_CTR_WritePeriod(uint32 period) 
{
    #if(QDEC_CTR_UsingFixedFunction)
        CY_SET_REG16(QDEC_CTR_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG32(QDEC_CTR_PERIOD_LSB_PTR, period);
    #endif /* (QDEC_CTR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QDEC_CTR_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) Present period value.
*
*******************************************************************************/
uint32 QDEC_CTR_ReadPeriod(void) 
{
    #if(QDEC_CTR_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(QDEC_CTR_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG32(QDEC_CTR_PERIOD_LSB_PTR));
    #endif /* (QDEC_CTR_UsingFixedFunction) */
}


#if (!QDEC_CTR_UsingFixedFunction)
/*******************************************************************************
* Function Name: QDEC_CTR_WriteCompare
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
void QDEC_CTR_WriteCompare(uint32 compare) \
                                   
{
    #if(QDEC_CTR_UsingFixedFunction)
        CY_SET_REG16(QDEC_CTR_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG32(QDEC_CTR_COMPARE_LSB_PTR, compare);
    #endif /* (QDEC_CTR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QDEC_CTR_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint32) Present compare value.
*
*******************************************************************************/
uint32 QDEC_CTR_ReadCompare(void) 
{
    return (CY_GET_REG32(QDEC_CTR_COMPARE_LSB_PTR));
}


#if (QDEC_CTR_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: QDEC_CTR_SetCompareMode
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
void QDEC_CTR_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    QDEC_CTR_CONTROL &= ((uint8)(~QDEC_CTR_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    QDEC_CTR_CONTROL |= compareMode;
}
#endif  /* (QDEC_CTR_COMPARE_MODE_SOFTWARE) */


#if (QDEC_CTR_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: QDEC_CTR_SetCaptureMode
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
void QDEC_CTR_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    QDEC_CTR_CONTROL &= ((uint8)(~QDEC_CTR_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    QDEC_CTR_CONTROL |= ((uint8)((uint8)captureMode << QDEC_CTR_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (QDEC_CTR_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: QDEC_CTR_ClearFIFO
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
void QDEC_CTR_ClearFIFO(void) 
{

    while(0u != (QDEC_CTR_ReadStatusRegister() & QDEC_CTR_STATUS_FIFONEMP))
    {
        (void)QDEC_CTR_ReadCapture();
    }

}
#endif  /* (!QDEC_CTR_UsingFixedFunction) */


/* [] END OF FILE */

