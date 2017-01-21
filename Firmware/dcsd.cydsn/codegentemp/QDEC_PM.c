/*******************************************************************************
* File Name: QDEC_PM.c
* Version 3.0
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "QDEC.h"

static QDEC_BACKUP_STRUCT QDEC_backup = {0u};


/*******************************************************************************
* Function Name: QDEC_SaveConfig
********************************************************************************
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QDEC_SaveConfig(void) 
{
    #if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT)
        QDEC_Cnt8_SaveConfig();
    #else 
        /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_16_BIT) || 
         * (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT)
         */
        QDEC_Cnt16_SaveConfig();
    #endif /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QDEC_RestoreConfig
********************************************************************************
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QDEC_RestoreConfig(void) 
{
    #if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT)
        QDEC_Cnt8_RestoreConfig();
    #else 
        /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_16_BIT) || 
         * (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT) 
         */
        QDEC_Cnt16_RestoreConfig();
    #endif /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QDEC_Sleep
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QDEC_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QDEC_Sleep(void) 
{
    if (0u != (QDEC_SR_AUX_CONTROL & QDEC_INTERRUPTS_ENABLE))
    {
        QDEC_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        QDEC_backup.enableState = 0u;
    }

    QDEC_Stop();
    QDEC_SaveConfig();
}


/*******************************************************************************
* Function Name: QDEC_Wakeup
********************************************************************************
*
* Summary:
*  Prepare Quadrature Decoder Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QDEC_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void QDEC_Wakeup(void) 
{
    QDEC_RestoreConfig();

    if (QDEC_backup.enableState != 0u)
    {
        #if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT)
            QDEC_Cnt8_Enable();
        #else 
            /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_16_BIT) || 
            *  (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT) 
            */
            QDEC_Cnt16_Enable();
        #endif /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        QDEC_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

