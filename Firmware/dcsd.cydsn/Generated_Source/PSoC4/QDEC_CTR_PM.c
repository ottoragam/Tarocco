/*******************************************************************************
* File Name: QDEC_CTR_PM.c  
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

#include "QDEC_CTR.h"

static QDEC_CTR_backupStruct QDEC_CTR_backup;


/*******************************************************************************
* Function Name: QDEC_CTR_SaveConfig
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
*  QDEC_CTR_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void QDEC_CTR_SaveConfig(void) 
{
    #if (!QDEC_CTR_UsingFixedFunction)

        QDEC_CTR_backup.CounterUdb = QDEC_CTR_ReadCounter();

        #if(!QDEC_CTR_ControlRegRemoved)
            QDEC_CTR_backup.CounterControlRegister = QDEC_CTR_ReadControlRegister();
        #endif /* (!QDEC_CTR_ControlRegRemoved) */

    #endif /* (!QDEC_CTR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QDEC_CTR_RestoreConfig
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
*  QDEC_CTR_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void QDEC_CTR_RestoreConfig(void) 
{      
    #if (!QDEC_CTR_UsingFixedFunction)

       QDEC_CTR_WriteCounter(QDEC_CTR_backup.CounterUdb);

        #if(!QDEC_CTR_ControlRegRemoved)
            QDEC_CTR_WriteControlRegister(QDEC_CTR_backup.CounterControlRegister);
        #endif /* (!QDEC_CTR_ControlRegRemoved) */

    #endif /* (!QDEC_CTR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QDEC_CTR_Sleep
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
*  QDEC_CTR_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void QDEC_CTR_Sleep(void) 
{
    #if(!QDEC_CTR_ControlRegRemoved)
        /* Save Counter's enable state */
        if(QDEC_CTR_CTRL_ENABLE == (QDEC_CTR_CONTROL & QDEC_CTR_CTRL_ENABLE))
        {
            /* Counter is enabled */
            QDEC_CTR_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            QDEC_CTR_backup.CounterEnableState = 0u;
        }
    #else
        QDEC_CTR_backup.CounterEnableState = 1u;
        if(QDEC_CTR_backup.CounterEnableState != 0u)
        {
            QDEC_CTR_backup.CounterEnableState = 0u;
        }
    #endif /* (!QDEC_CTR_ControlRegRemoved) */
    
    QDEC_CTR_Stop();
    QDEC_CTR_SaveConfig();
}


/*******************************************************************************
* Function Name: QDEC_CTR_Wakeup
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
*  QDEC_CTR_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void QDEC_CTR_Wakeup(void) 
{
    QDEC_CTR_RestoreConfig();
    #if(!QDEC_CTR_ControlRegRemoved)
        if(QDEC_CTR_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            QDEC_CTR_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!QDEC_CTR_ControlRegRemoved) */
    
}


/* [] END OF FILE */
