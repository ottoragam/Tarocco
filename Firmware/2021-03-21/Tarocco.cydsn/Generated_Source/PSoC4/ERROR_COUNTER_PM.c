/*******************************************************************************
* File Name: ERROR_COUNTER_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
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

static ERROR_COUNTER_backupStruct ERROR_COUNTER_backup;


/*******************************************************************************
* Function Name: ERROR_COUNTER_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ERROR_COUNTER_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void ERROR_COUNTER_SaveConfig(void) 
{
    #if (!ERROR_COUNTER_UsingFixedFunction)

        ERROR_COUNTER_backup.CounterUdb = ERROR_COUNTER_ReadCounter();

        #if(!ERROR_COUNTER_ControlRegRemoved)
            ERROR_COUNTER_backup.CounterControlRegister = ERROR_COUNTER_ReadControlRegister();
        #endif /* (!ERROR_COUNTER_ControlRegRemoved) */

    #endif /* (!ERROR_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERROR_COUNTER_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ERROR_COUNTER_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ERROR_COUNTER_RestoreConfig(void) 
{      
    #if (!ERROR_COUNTER_UsingFixedFunction)

       ERROR_COUNTER_WriteCounter(ERROR_COUNTER_backup.CounterUdb);

        #if(!ERROR_COUNTER_ControlRegRemoved)
            ERROR_COUNTER_WriteControlRegister(ERROR_COUNTER_backup.CounterControlRegister);
        #endif /* (!ERROR_COUNTER_ControlRegRemoved) */

    #endif /* (!ERROR_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERROR_COUNTER_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ERROR_COUNTER_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ERROR_COUNTER_Sleep(void) 
{
    #if(!ERROR_COUNTER_ControlRegRemoved)
        /* Save Counter's enable state */
        if(ERROR_COUNTER_CTRL_ENABLE == (ERROR_COUNTER_CONTROL & ERROR_COUNTER_CTRL_ENABLE))
        {
            /* Counter is enabled */
            ERROR_COUNTER_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            ERROR_COUNTER_backup.CounterEnableState = 0u;
        }
    #else
        ERROR_COUNTER_backup.CounterEnableState = 1u;
        if(ERROR_COUNTER_backup.CounterEnableState != 0u)
        {
            ERROR_COUNTER_backup.CounterEnableState = 0u;
        }
    #endif /* (!ERROR_COUNTER_ControlRegRemoved) */
    
    ERROR_COUNTER_Stop();
    ERROR_COUNTER_SaveConfig();
}


/*******************************************************************************
* Function Name: ERROR_COUNTER_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ERROR_COUNTER_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ERROR_COUNTER_Wakeup(void) 
{
    ERROR_COUNTER_RestoreConfig();
    #if(!ERROR_COUNTER_ControlRegRemoved)
        if(ERROR_COUNTER_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            ERROR_COUNTER_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!ERROR_COUNTER_ControlRegRemoved) */
    
}


/* [] END OF FILE */
