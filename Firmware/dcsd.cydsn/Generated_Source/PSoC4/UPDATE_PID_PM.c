/*******************************************************************************
* File Name: UPDATE_PID_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UPDATE_PID.h"

static UPDATE_PID_BACKUP_STRUCT UPDATE_PID_backup;


/*******************************************************************************
* Function Name: UPDATE_PID_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: UPDATE_PID_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_Sleep(void)
{
    if(0u != (UPDATE_PID_BLOCK_CONTROL_REG & UPDATE_PID_MASK))
    {
        UPDATE_PID_backup.enableState = 1u;
    }
    else
    {
        UPDATE_PID_backup.enableState = 0u;
    }

    UPDATE_PID_Stop();
    UPDATE_PID_SaveConfig();
}


/*******************************************************************************
* Function Name: UPDATE_PID_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: UPDATE_PID_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UPDATE_PID_Wakeup(void)
{
    UPDATE_PID_RestoreConfig();

    if(0u != UPDATE_PID_backup.enableState)
    {
        UPDATE_PID_Enable();
    }
}


/* [] END OF FILE */
