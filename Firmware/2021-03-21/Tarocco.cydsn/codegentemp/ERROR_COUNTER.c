/*******************************************************************************
* File Name: ERROR_COUNTER.c  
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

#include "ERROR_COUNTER.h"

uint8 ERROR_COUNTER_initVar = 0u;


/*******************************************************************************
* Function Name: ERROR_COUNTER_Init
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
void ERROR_COUNTER_Init(void) 
{
        #if (!ERROR_COUNTER_UsingFixedFunction && !ERROR_COUNTER_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!ERROR_COUNTER_UsingFixedFunction && !ERROR_COUNTER_ControlRegRemoved) */
        
        #if(!ERROR_COUNTER_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 ERROR_COUNTER_interruptState;
        #endif /* (!ERROR_COUNTER_UsingFixedFunction) */
        
        #if (ERROR_COUNTER_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            ERROR_COUNTER_CONTROL &= ERROR_COUNTER_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                ERROR_COUNTER_CONTROL2 &= ((uint8)(~ERROR_COUNTER_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                ERROR_COUNTER_CONTROL3 &= ((uint8)(~ERROR_COUNTER_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (ERROR_COUNTER_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                ERROR_COUNTER_CONTROL |= ERROR_COUNTER_ONESHOT;
            #endif /* (ERROR_COUNTER_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            ERROR_COUNTER_CONTROL2 |= ERROR_COUNTER_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            ERROR_COUNTER_RT1 &= ((uint8)(~ERROR_COUNTER_RT1_MASK));
            ERROR_COUNTER_RT1 |= ERROR_COUNTER_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            ERROR_COUNTER_RT1 &= ((uint8)(~ERROR_COUNTER_SYNCDSI_MASK));
            ERROR_COUNTER_RT1 |= ERROR_COUNTER_SYNCDSI_EN;

        #else
            #if(!ERROR_COUNTER_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = ERROR_COUNTER_CONTROL & ((uint8)(~ERROR_COUNTER_CTRL_CMPMODE_MASK));
            ERROR_COUNTER_CONTROL = ctrl | ERROR_COUNTER_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = ERROR_COUNTER_CONTROL & ((uint8)(~ERROR_COUNTER_CTRL_CAPMODE_MASK));
            
            #if( 0 != ERROR_COUNTER_CAPTURE_MODE_CONF)
                ERROR_COUNTER_CONTROL = ctrl | ERROR_COUNTER_DEFAULT_CAPTURE_MODE;
            #else
                ERROR_COUNTER_CONTROL = ctrl;
            #endif /* 0 != ERROR_COUNTER_CAPTURE_MODE */ 
            
            #endif /* (!ERROR_COUNTER_ControlRegRemoved) */
        #endif /* (ERROR_COUNTER_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!ERROR_COUNTER_UsingFixedFunction)
            ERROR_COUNTER_ClearFIFO();
        #endif /* (!ERROR_COUNTER_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        ERROR_COUNTER_WritePeriod(ERROR_COUNTER_INIT_PERIOD_VALUE);
        #if (!(ERROR_COUNTER_UsingFixedFunction && (CY_PSOC5A)))
            ERROR_COUNTER_WriteCounter(ERROR_COUNTER_INIT_COUNTER_VALUE);
        #endif /* (!(ERROR_COUNTER_UsingFixedFunction && (CY_PSOC5A))) */
        ERROR_COUNTER_SetInterruptMode(ERROR_COUNTER_INIT_INTERRUPTS_MASK);
        
        #if (!ERROR_COUNTER_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)ERROR_COUNTER_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            ERROR_COUNTER_WriteCompare(ERROR_COUNTER_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            ERROR_COUNTER_interruptState = CyEnterCriticalSection();
            
            ERROR_COUNTER_STATUS_AUX_CTRL |= ERROR_COUNTER_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(ERROR_COUNTER_interruptState);
            
        #endif /* (!ERROR_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERROR_COUNTER_Enable
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
void ERROR_COUNTER_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (ERROR_COUNTER_UsingFixedFunction)
        ERROR_COUNTER_GLOBAL_ENABLE |= ERROR_COUNTER_BLOCK_EN_MASK;
        ERROR_COUNTER_GLOBAL_STBY_ENABLE |= ERROR_COUNTER_BLOCK_STBY_EN_MASK;
    #endif /* (ERROR_COUNTER_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!ERROR_COUNTER_ControlRegRemoved || ERROR_COUNTER_UsingFixedFunction)
        ERROR_COUNTER_CONTROL |= ERROR_COUNTER_CTRL_ENABLE;                
    #endif /* (!ERROR_COUNTER_ControlRegRemoved || ERROR_COUNTER_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: ERROR_COUNTER_Start
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
*  ERROR_COUNTER_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void ERROR_COUNTER_Start(void) 
{
    if(ERROR_COUNTER_initVar == 0u)
    {
        ERROR_COUNTER_Init();
        
        ERROR_COUNTER_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    ERROR_COUNTER_Enable();        
}


/*******************************************************************************
* Function Name: ERROR_COUNTER_Stop
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
void ERROR_COUNTER_Stop(void) 
{
    /* Disable Counter */
    #if(!ERROR_COUNTER_ControlRegRemoved || ERROR_COUNTER_UsingFixedFunction)
        ERROR_COUNTER_CONTROL &= ((uint8)(~ERROR_COUNTER_CTRL_ENABLE));        
    #endif /* (!ERROR_COUNTER_ControlRegRemoved || ERROR_COUNTER_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (ERROR_COUNTER_UsingFixedFunction)
        ERROR_COUNTER_GLOBAL_ENABLE &= ((uint8)(~ERROR_COUNTER_BLOCK_EN_MASK));
        ERROR_COUNTER_GLOBAL_STBY_ENABLE &= ((uint8)(~ERROR_COUNTER_BLOCK_STBY_EN_MASK));
    #endif /* (ERROR_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERROR_COUNTER_SetInterruptMode
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
void ERROR_COUNTER_SetInterruptMode(uint8 interruptsMask) 
{
    ERROR_COUNTER_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: ERROR_COUNTER_ReadStatusRegister
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
uint8   ERROR_COUNTER_ReadStatusRegister(void) 
{
    return ERROR_COUNTER_STATUS;
}


#if(!ERROR_COUNTER_ControlRegRemoved)
/*******************************************************************************
* Function Name: ERROR_COUNTER_ReadControlRegister
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
uint8   ERROR_COUNTER_ReadControlRegister(void) 
{
    return ERROR_COUNTER_CONTROL;
}


/*******************************************************************************
* Function Name: ERROR_COUNTER_WriteControlRegister
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
void    ERROR_COUNTER_WriteControlRegister(uint8 control) 
{
    ERROR_COUNTER_CONTROL = control;
}

#endif  /* (!ERROR_COUNTER_ControlRegRemoved) */


#if (!(ERROR_COUNTER_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: ERROR_COUNTER_WriteCounter
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
void ERROR_COUNTER_WriteCounter(uint16 counter) \
                                   
{
    #if(ERROR_COUNTER_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (ERROR_COUNTER_GLOBAL_ENABLE & ERROR_COUNTER_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        ERROR_COUNTER_GLOBAL_ENABLE |= ERROR_COUNTER_BLOCK_EN_MASK;
        CY_SET_REG16(ERROR_COUNTER_COUNTER_LSB_PTR, (uint16)counter);
        ERROR_COUNTER_GLOBAL_ENABLE &= ((uint8)(~ERROR_COUNTER_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(ERROR_COUNTER_COUNTER_LSB_PTR, counter);
    #endif /* (ERROR_COUNTER_UsingFixedFunction) */
}
#endif /* (!(ERROR_COUNTER_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: ERROR_COUNTER_ReadCounter
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
uint16 ERROR_COUNTER_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(ERROR_COUNTER_UsingFixedFunction)
		(void)CY_GET_REG16(ERROR_COUNTER_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(ERROR_COUNTER_COUNTER_LSB_PTR_8BIT);
	#endif/* (ERROR_COUNTER_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(ERROR_COUNTER_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(ERROR_COUNTER_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(ERROR_COUNTER_STATICCOUNT_LSB_PTR));
    #endif /* (ERROR_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERROR_COUNTER_ReadCapture
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
uint16 ERROR_COUNTER_ReadCapture(void) 
{
    #if(ERROR_COUNTER_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(ERROR_COUNTER_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(ERROR_COUNTER_STATICCOUNT_LSB_PTR));
    #endif /* (ERROR_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERROR_COUNTER_WritePeriod
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
void ERROR_COUNTER_WritePeriod(uint16 period) 
{
    #if(ERROR_COUNTER_UsingFixedFunction)
        CY_SET_REG16(ERROR_COUNTER_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(ERROR_COUNTER_PERIOD_LSB_PTR, period);
    #endif /* (ERROR_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERROR_COUNTER_ReadPeriod
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
uint16 ERROR_COUNTER_ReadPeriod(void) 
{
    #if(ERROR_COUNTER_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(ERROR_COUNTER_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(ERROR_COUNTER_PERIOD_LSB_PTR));
    #endif /* (ERROR_COUNTER_UsingFixedFunction) */
}


#if (!ERROR_COUNTER_UsingFixedFunction)
/*******************************************************************************
* Function Name: ERROR_COUNTER_WriteCompare
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
void ERROR_COUNTER_WriteCompare(uint16 compare) \
                                   
{
    #if(ERROR_COUNTER_UsingFixedFunction)
        CY_SET_REG16(ERROR_COUNTER_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(ERROR_COUNTER_COMPARE_LSB_PTR, compare);
    #endif /* (ERROR_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERROR_COUNTER_ReadCompare
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
uint16 ERROR_COUNTER_ReadCompare(void) 
{
    return (CY_GET_REG16(ERROR_COUNTER_COMPARE_LSB_PTR));
}


#if (ERROR_COUNTER_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ERROR_COUNTER_SetCompareMode
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
void ERROR_COUNTER_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    ERROR_COUNTER_CONTROL &= ((uint8)(~ERROR_COUNTER_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    ERROR_COUNTER_CONTROL |= compareMode;
}
#endif  /* (ERROR_COUNTER_COMPARE_MODE_SOFTWARE) */


#if (ERROR_COUNTER_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ERROR_COUNTER_SetCaptureMode
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
void ERROR_COUNTER_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    ERROR_COUNTER_CONTROL &= ((uint8)(~ERROR_COUNTER_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    ERROR_COUNTER_CONTROL |= ((uint8)((uint8)captureMode << ERROR_COUNTER_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (ERROR_COUNTER_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: ERROR_COUNTER_ClearFIFO
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
void ERROR_COUNTER_ClearFIFO(void) 
{

    while(0u != (ERROR_COUNTER_ReadStatusRegister() & ERROR_COUNTER_STATUS_FIFONEMP))
    {
        (void)ERROR_COUNTER_ReadCapture();
    }

}
#endif  /* (!ERROR_COUNTER_UsingFixedFunction) */


/* [] END OF FILE */

