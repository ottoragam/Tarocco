/*******************************************************************************
* File Name: INVERT_DIR_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "INVERT_DIR.h"

/* Check for removal by optimization */
#if !defined(INVERT_DIR_Sync_ctrl_reg__REMOVED)

static INVERT_DIR_BACKUP_STRUCT  INVERT_DIR_backup = {0u};

    
/*******************************************************************************
* Function Name: INVERT_DIR_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void INVERT_DIR_SaveConfig(void) 
{
    INVERT_DIR_backup.controlState = INVERT_DIR_Control;
}


/*******************************************************************************
* Function Name: INVERT_DIR_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void INVERT_DIR_RestoreConfig(void) 
{
     INVERT_DIR_Control = INVERT_DIR_backup.controlState;
}


/*******************************************************************************
* Function Name: INVERT_DIR_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void INVERT_DIR_Sleep(void) 
{
    INVERT_DIR_SaveConfig();
}


/*******************************************************************************
* Function Name: INVERT_DIR_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void INVERT_DIR_Wakeup(void)  
{
    INVERT_DIR_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
