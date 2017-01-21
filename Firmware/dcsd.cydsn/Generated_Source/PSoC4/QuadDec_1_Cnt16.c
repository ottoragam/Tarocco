/*******************************************************************************
* File Name: QuadDec_1_Cnt16.c  
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

#include "QuadDec_1_Cnt16.h"

uint8 QuadDec_1_Cnt16_initVar = 0u;


/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_Init
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
void QuadDec_1_Cnt16_Init(void) 
{
        #if (!QuadDec_1_Cnt16_UsingFixedFunction && !QuadDec_1_Cnt16_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!QuadDec_1_Cnt16_UsingFixedFunction && !QuadDec_1_Cnt16_ControlRegRemoved) */
        
        #if(!QuadDec_1_Cnt16_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 QuadDec_1_Cnt16_interruptState;
        #endif /* (!QuadDec_1_Cnt16_UsingFixedFunction) */
        
        #if (QuadDec_1_Cnt16_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            QuadDec_1_Cnt16_CONTROL &= QuadDec_1_Cnt16_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                QuadDec_1_Cnt16_CONTROL2 &= ((uint8)(~QuadDec_1_Cnt16_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                QuadDec_1_Cnt16_CONTROL3 &= ((uint8)(~QuadDec_1_Cnt16_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (QuadDec_1_Cnt16_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                QuadDec_1_Cnt16_CONTROL |= QuadDec_1_Cnt16_ONESHOT;
            #endif /* (QuadDec_1_Cnt16_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            QuadDec_1_Cnt16_CONTROL2 |= QuadDec_1_Cnt16_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            QuadDec_1_Cnt16_RT1 &= ((uint8)(~QuadDec_1_Cnt16_RT1_MASK));
            QuadDec_1_Cnt16_RT1 |= QuadDec_1_Cnt16_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            QuadDec_1_Cnt16_RT1 &= ((uint8)(~QuadDec_1_Cnt16_SYNCDSI_MASK));
            QuadDec_1_Cnt16_RT1 |= QuadDec_1_Cnt16_SYNCDSI_EN;

        #else
            #if(!QuadDec_1_Cnt16_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = QuadDec_1_Cnt16_CONTROL & ((uint8)(~QuadDec_1_Cnt16_CTRL_CMPMODE_MASK));
            QuadDec_1_Cnt16_CONTROL = ctrl | QuadDec_1_Cnt16_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = QuadDec_1_Cnt16_CONTROL & ((uint8)(~QuadDec_1_Cnt16_CTRL_CAPMODE_MASK));
            
            #if( 0 != QuadDec_1_Cnt16_CAPTURE_MODE_CONF)
                QuadDec_1_Cnt16_CONTROL = ctrl | QuadDec_1_Cnt16_DEFAULT_CAPTURE_MODE;
            #else
                QuadDec_1_Cnt16_CONTROL = ctrl;
            #endif /* 0 != QuadDec_1_Cnt16_CAPTURE_MODE */ 
            
            #endif /* (!QuadDec_1_Cnt16_ControlRegRemoved) */
        #endif /* (QuadDec_1_Cnt16_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!QuadDec_1_Cnt16_UsingFixedFunction)
            QuadDec_1_Cnt16_ClearFIFO();
        #endif /* (!QuadDec_1_Cnt16_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        QuadDec_1_Cnt16_WritePeriod(QuadDec_1_Cnt16_INIT_PERIOD_VALUE);
        #if (!(QuadDec_1_Cnt16_UsingFixedFunction && (CY_PSOC5A)))
            QuadDec_1_Cnt16_WriteCounter(QuadDec_1_Cnt16_INIT_COUNTER_VALUE);
        #endif /* (!(QuadDec_1_Cnt16_UsingFixedFunction && (CY_PSOC5A))) */
        QuadDec_1_Cnt16_SetInterruptMode(QuadDec_1_Cnt16_INIT_INTERRUPTS_MASK);
        
        #if (!QuadDec_1_Cnt16_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)QuadDec_1_Cnt16_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            QuadDec_1_Cnt16_WriteCompare(QuadDec_1_Cnt16_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            QuadDec_1_Cnt16_interruptState = CyEnterCriticalSection();
            
            QuadDec_1_Cnt16_STATUS_AUX_CTRL |= QuadDec_1_Cnt16_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(QuadDec_1_Cnt16_interruptState);
            
        #endif /* (!QuadDec_1_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_Enable
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
void QuadDec_1_Cnt16_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (QuadDec_1_Cnt16_UsingFixedFunction)
        QuadDec_1_Cnt16_GLOBAL_ENABLE |= QuadDec_1_Cnt16_BLOCK_EN_MASK;
        QuadDec_1_Cnt16_GLOBAL_STBY_ENABLE |= QuadDec_1_Cnt16_BLOCK_STBY_EN_MASK;
    #endif /* (QuadDec_1_Cnt16_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!QuadDec_1_Cnt16_ControlRegRemoved || QuadDec_1_Cnt16_UsingFixedFunction)
        QuadDec_1_Cnt16_CONTROL |= QuadDec_1_Cnt16_CTRL_ENABLE;                
    #endif /* (!QuadDec_1_Cnt16_ControlRegRemoved || QuadDec_1_Cnt16_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_Start
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
*  QuadDec_1_Cnt16_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void QuadDec_1_Cnt16_Start(void) 
{
    if(QuadDec_1_Cnt16_initVar == 0u)
    {
        QuadDec_1_Cnt16_Init();
        
        QuadDec_1_Cnt16_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    QuadDec_1_Cnt16_Enable();        
}


/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_Stop
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
void QuadDec_1_Cnt16_Stop(void) 
{
    /* Disable Counter */
    #if(!QuadDec_1_Cnt16_ControlRegRemoved || QuadDec_1_Cnt16_UsingFixedFunction)
        QuadDec_1_Cnt16_CONTROL &= ((uint8)(~QuadDec_1_Cnt16_CTRL_ENABLE));        
    #endif /* (!QuadDec_1_Cnt16_ControlRegRemoved || QuadDec_1_Cnt16_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (QuadDec_1_Cnt16_UsingFixedFunction)
        QuadDec_1_Cnt16_GLOBAL_ENABLE &= ((uint8)(~QuadDec_1_Cnt16_BLOCK_EN_MASK));
        QuadDec_1_Cnt16_GLOBAL_STBY_ENABLE &= ((uint8)(~QuadDec_1_Cnt16_BLOCK_STBY_EN_MASK));
    #endif /* (QuadDec_1_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_SetInterruptMode
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
void QuadDec_1_Cnt16_SetInterruptMode(uint8 interruptsMask) 
{
    QuadDec_1_Cnt16_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_ReadStatusRegister
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
uint8   QuadDec_1_Cnt16_ReadStatusRegister(void) 
{
    return QuadDec_1_Cnt16_STATUS;
}


#if(!QuadDec_1_Cnt16_ControlRegRemoved)
/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_ReadControlRegister
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
uint8   QuadDec_1_Cnt16_ReadControlRegister(void) 
{
    return QuadDec_1_Cnt16_CONTROL;
}


/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_WriteControlRegister
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
void    QuadDec_1_Cnt16_WriteControlRegister(uint8 control) 
{
    QuadDec_1_Cnt16_CONTROL = control;
}

#endif  /* (!QuadDec_1_Cnt16_ControlRegRemoved) */


#if (!(QuadDec_1_Cnt16_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_WriteCounter
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
void QuadDec_1_Cnt16_WriteCounter(uint16 counter) \
                                   
{
    #if(QuadDec_1_Cnt16_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (QuadDec_1_Cnt16_GLOBAL_ENABLE & QuadDec_1_Cnt16_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        QuadDec_1_Cnt16_GLOBAL_ENABLE |= QuadDec_1_Cnt16_BLOCK_EN_MASK;
        CY_SET_REG16(QuadDec_1_Cnt16_COUNTER_LSB_PTR, (uint16)counter);
        QuadDec_1_Cnt16_GLOBAL_ENABLE &= ((uint8)(~QuadDec_1_Cnt16_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(QuadDec_1_Cnt16_COUNTER_LSB_PTR, counter);
    #endif /* (QuadDec_1_Cnt16_UsingFixedFunction) */
}
#endif /* (!(QuadDec_1_Cnt16_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_ReadCounter
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
uint16 QuadDec_1_Cnt16_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(QuadDec_1_Cnt16_UsingFixedFunction)
		(void)CY_GET_REG16(QuadDec_1_Cnt16_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(QuadDec_1_Cnt16_COUNTER_LSB_PTR_8BIT);
	#endif/* (QuadDec_1_Cnt16_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(QuadDec_1_Cnt16_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(QuadDec_1_Cnt16_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(QuadDec_1_Cnt16_STATICCOUNT_LSB_PTR));
    #endif /* (QuadDec_1_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_ReadCapture
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
uint16 QuadDec_1_Cnt16_ReadCapture(void) 
{
    #if(QuadDec_1_Cnt16_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(QuadDec_1_Cnt16_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(QuadDec_1_Cnt16_STATICCOUNT_LSB_PTR));
    #endif /* (QuadDec_1_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_WritePeriod
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
void QuadDec_1_Cnt16_WritePeriod(uint16 period) 
{
    #if(QuadDec_1_Cnt16_UsingFixedFunction)
        CY_SET_REG16(QuadDec_1_Cnt16_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(QuadDec_1_Cnt16_PERIOD_LSB_PTR, period);
    #endif /* (QuadDec_1_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_ReadPeriod
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
uint16 QuadDec_1_Cnt16_ReadPeriod(void) 
{
    #if(QuadDec_1_Cnt16_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(QuadDec_1_Cnt16_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(QuadDec_1_Cnt16_PERIOD_LSB_PTR));
    #endif /* (QuadDec_1_Cnt16_UsingFixedFunction) */
}


#if (!QuadDec_1_Cnt16_UsingFixedFunction)
/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_WriteCompare
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
void QuadDec_1_Cnt16_WriteCompare(uint16 compare) \
                                   
{
    #if(QuadDec_1_Cnt16_UsingFixedFunction)
        CY_SET_REG16(QuadDec_1_Cnt16_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(QuadDec_1_Cnt16_COMPARE_LSB_PTR, compare);
    #endif /* (QuadDec_1_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_ReadCompare
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
uint16 QuadDec_1_Cnt16_ReadCompare(void) 
{
    return (CY_GET_REG16(QuadDec_1_Cnt16_COMPARE_LSB_PTR));
}


#if (QuadDec_1_Cnt16_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_SetCompareMode
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
void QuadDec_1_Cnt16_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    QuadDec_1_Cnt16_CONTROL &= ((uint8)(~QuadDec_1_Cnt16_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    QuadDec_1_Cnt16_CONTROL |= compareMode;
}
#endif  /* (QuadDec_1_Cnt16_COMPARE_MODE_SOFTWARE) */


#if (QuadDec_1_Cnt16_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_SetCaptureMode
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
void QuadDec_1_Cnt16_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    QuadDec_1_Cnt16_CONTROL &= ((uint8)(~QuadDec_1_Cnt16_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    QuadDec_1_Cnt16_CONTROL |= ((uint8)((uint8)captureMode << QuadDec_1_Cnt16_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (QuadDec_1_Cnt16_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: QuadDec_1_Cnt16_ClearFIFO
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
void QuadDec_1_Cnt16_ClearFIFO(void) 
{

    while(0u != (QuadDec_1_Cnt16_ReadStatusRegister() & QuadDec_1_Cnt16_STATUS_FIFONEMP))
    {
        (void)QuadDec_1_Cnt16_ReadCapture();
    }

}
#endif  /* (!QuadDec_1_Cnt16_UsingFixedFunction) */


/* [] END OF FILE */

