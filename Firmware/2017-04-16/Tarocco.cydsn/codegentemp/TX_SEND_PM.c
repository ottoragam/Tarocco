/*******************************************************************************
* File Name: TX_SEND_PM.c
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

#include "TX_SEND.h"

static TX_SEND_BACKUP_STRUCT TX_SEND_backup;


/*******************************************************************************
* Function Name: TX_SEND_SaveConfig
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
void TX_SEND_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: TX_SEND_Sleep
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
void TX_SEND_Sleep(void)
{
    if(0u != (TX_SEND_BLOCK_CONTROL_REG & TX_SEND_MASK))
    {
        TX_SEND_backup.enableState = 1u;
    }
    else
    {
        TX_SEND_backup.enableState = 0u;
    }

    TX_SEND_Stop();
    TX_SEND_SaveConfig();
}


/*******************************************************************************
* Function Name: TX_SEND_RestoreConfig
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
void TX_SEND_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: TX_SEND_Wakeup
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
void TX_SEND_Wakeup(void)
{
    TX_SEND_RestoreConfig();

    if(0u != TX_SEND_backup.enableState)
    {
        TX_SEND_Enable();
    }
}


/* [] END OF FILE */
