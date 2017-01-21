/*******************************************************************************
* File Name: QuadDec_1_Cnt8_PM.c  
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

#include "QuadDec_1_Cnt8.h"

static QuadDec_1_Cnt8_backupStruct QuadDec_1_Cnt8_backup;


/*******************************************************************************
* Function Name: QuadDec_1_Cnt8_SaveConfig
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
*  QuadDec_1_Cnt8_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void QuadDec_1_Cnt8_SaveConfig(void) 
{
    #if (!QuadDec_1_Cnt8_UsingFixedFunction)

        QuadDec_1_Cnt8_backup.CounterUdb = QuadDec_1_Cnt8_ReadCounter();

        #if(!QuadDec_1_Cnt8_ControlRegRemoved)
            QuadDec_1_Cnt8_backup.CounterControlRegister = QuadDec_1_Cnt8_ReadControlRegister();
        #endif /* (!QuadDec_1_Cnt8_ControlRegRemoved) */

    #endif /* (!QuadDec_1_Cnt8_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_1_Cnt8_RestoreConfig
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
*  QuadDec_1_Cnt8_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void QuadDec_1_Cnt8_RestoreConfig(void) 
{      
    #if (!QuadDec_1_Cnt8_UsingFixedFunction)

       QuadDec_1_Cnt8_WriteCounter(QuadDec_1_Cnt8_backup.CounterUdb);

        #if(!QuadDec_1_Cnt8_ControlRegRemoved)
            QuadDec_1_Cnt8_WriteControlRegister(QuadDec_1_Cnt8_backup.CounterControlRegister);
        #endif /* (!QuadDec_1_Cnt8_ControlRegRemoved) */

    #endif /* (!QuadDec_1_Cnt8_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_1_Cnt8_Sleep
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
*  QuadDec_1_Cnt8_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void QuadDec_1_Cnt8_Sleep(void) 
{
    #if(!QuadDec_1_Cnt8_ControlRegRemoved)
        /* Save Counter's enable state */
        if(QuadDec_1_Cnt8_CTRL_ENABLE == (QuadDec_1_Cnt8_CONTROL & QuadDec_1_Cnt8_CTRL_ENABLE))
        {
            /* Counter is enabled */
            QuadDec_1_Cnt8_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            QuadDec_1_Cnt8_backup.CounterEnableState = 0u;
        }
    #else
        QuadDec_1_Cnt8_backup.CounterEnableState = 1u;
        if(QuadDec_1_Cnt8_backup.CounterEnableState != 0u)
        {
            QuadDec_1_Cnt8_backup.CounterEnableState = 0u;
        }
    #endif /* (!QuadDec_1_Cnt8_ControlRegRemoved) */
    
    QuadDec_1_Cnt8_Stop();
    QuadDec_1_Cnt8_SaveConfig();
}


/*******************************************************************************
* Function Name: QuadDec_1_Cnt8_Wakeup
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
*  QuadDec_1_Cnt8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void QuadDec_1_Cnt8_Wakeup(void) 
{
    QuadDec_1_Cnt8_RestoreConfig();
    #if(!QuadDec_1_Cnt8_ControlRegRemoved)
        if(QuadDec_1_Cnt8_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            QuadDec_1_Cnt8_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!QuadDec_1_Cnt8_ControlRegRemoved) */
    
}


/* [] END OF FILE */
