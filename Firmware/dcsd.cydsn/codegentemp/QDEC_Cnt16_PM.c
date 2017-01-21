/*******************************************************************************
* File Name: QDEC_Cnt16_PM.c  
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

#include "QDEC_Cnt16.h"

static QDEC_Cnt16_backupStruct QDEC_Cnt16_backup;


/*******************************************************************************
* Function Name: QDEC_Cnt16_SaveConfig
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
*  QDEC_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void QDEC_Cnt16_SaveConfig(void) 
{
    #if (!QDEC_Cnt16_UsingFixedFunction)

        QDEC_Cnt16_backup.CounterUdb = QDEC_Cnt16_ReadCounter();

        #if(!QDEC_Cnt16_ControlRegRemoved)
            QDEC_Cnt16_backup.CounterControlRegister = QDEC_Cnt16_ReadControlRegister();
        #endif /* (!QDEC_Cnt16_ControlRegRemoved) */

    #endif /* (!QDEC_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QDEC_Cnt16_RestoreConfig
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
*  QDEC_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void QDEC_Cnt16_RestoreConfig(void) 
{      
    #if (!QDEC_Cnt16_UsingFixedFunction)

       QDEC_Cnt16_WriteCounter(QDEC_Cnt16_backup.CounterUdb);

        #if(!QDEC_Cnt16_ControlRegRemoved)
            QDEC_Cnt16_WriteControlRegister(QDEC_Cnt16_backup.CounterControlRegister);
        #endif /* (!QDEC_Cnt16_ControlRegRemoved) */

    #endif /* (!QDEC_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QDEC_Cnt16_Sleep
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
*  QDEC_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void QDEC_Cnt16_Sleep(void) 
{
    #if(!QDEC_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(QDEC_Cnt16_CTRL_ENABLE == (QDEC_Cnt16_CONTROL & QDEC_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            QDEC_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            QDEC_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        QDEC_Cnt16_backup.CounterEnableState = 1u;
        if(QDEC_Cnt16_backup.CounterEnableState != 0u)
        {
            QDEC_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!QDEC_Cnt16_ControlRegRemoved) */
    
    QDEC_Cnt16_Stop();
    QDEC_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: QDEC_Cnt16_Wakeup
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
*  QDEC_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void QDEC_Cnt16_Wakeup(void) 
{
    QDEC_Cnt16_RestoreConfig();
    #if(!QDEC_Cnt16_ControlRegRemoved)
        if(QDEC_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            QDEC_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!QDEC_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */
