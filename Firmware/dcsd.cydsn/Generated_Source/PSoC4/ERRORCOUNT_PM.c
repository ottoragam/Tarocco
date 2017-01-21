/*******************************************************************************
* File Name: ERRORCOUNT_PM.c  
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

#include "ERRORCOUNT.h"

static ERRORCOUNT_backupStruct ERRORCOUNT_backup;


/*******************************************************************************
* Function Name: ERRORCOUNT_SaveConfig
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
*  ERRORCOUNT_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void ERRORCOUNT_SaveConfig(void) 
{
    #if (!ERRORCOUNT_UsingFixedFunction)

        ERRORCOUNT_backup.CounterUdb = ERRORCOUNT_ReadCounter();

        #if(!ERRORCOUNT_ControlRegRemoved)
            ERRORCOUNT_backup.CounterControlRegister = ERRORCOUNT_ReadControlRegister();
        #endif /* (!ERRORCOUNT_ControlRegRemoved) */

    #endif /* (!ERRORCOUNT_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERRORCOUNT_RestoreConfig
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
*  ERRORCOUNT_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ERRORCOUNT_RestoreConfig(void) 
{      
    #if (!ERRORCOUNT_UsingFixedFunction)

       ERRORCOUNT_WriteCounter(ERRORCOUNT_backup.CounterUdb);

        #if(!ERRORCOUNT_ControlRegRemoved)
            ERRORCOUNT_WriteControlRegister(ERRORCOUNT_backup.CounterControlRegister);
        #endif /* (!ERRORCOUNT_ControlRegRemoved) */

    #endif /* (!ERRORCOUNT_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ERRORCOUNT_Sleep
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
*  ERRORCOUNT_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ERRORCOUNT_Sleep(void) 
{
    #if(!ERRORCOUNT_ControlRegRemoved)
        /* Save Counter's enable state */
        if(ERRORCOUNT_CTRL_ENABLE == (ERRORCOUNT_CONTROL & ERRORCOUNT_CTRL_ENABLE))
        {
            /* Counter is enabled */
            ERRORCOUNT_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            ERRORCOUNT_backup.CounterEnableState = 0u;
        }
    #else
        ERRORCOUNT_backup.CounterEnableState = 1u;
        if(ERRORCOUNT_backup.CounterEnableState != 0u)
        {
            ERRORCOUNT_backup.CounterEnableState = 0u;
        }
    #endif /* (!ERRORCOUNT_ControlRegRemoved) */
    
    ERRORCOUNT_Stop();
    ERRORCOUNT_SaveConfig();
}


/*******************************************************************************
* Function Name: ERRORCOUNT_Wakeup
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
*  ERRORCOUNT_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ERRORCOUNT_Wakeup(void) 
{
    ERRORCOUNT_RestoreConfig();
    #if(!ERRORCOUNT_ControlRegRemoved)
        if(ERRORCOUNT_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            ERRORCOUNT_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!ERRORCOUNT_ControlRegRemoved) */
    
}


/* [] END OF FILE */
