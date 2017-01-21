/*******************************************************************************
* File Name: QDECDIR.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "QDECDIR.h"

#if !defined(QDECDIR_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: QDECDIR_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 QDECDIR_Read(void) 
{ 
    return QDECDIR_Status;
}


/*******************************************************************************
* Function Name: QDECDIR_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QDECDIR_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    QDECDIR_Status_Aux_Ctrl |= QDECDIR_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: QDECDIR_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QDECDIR_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    QDECDIR_Status_Aux_Ctrl &= (uint8)(~QDECDIR_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: QDECDIR_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void QDECDIR_WriteMask(uint8 mask) 
{
    #if(QDECDIR_INPUTS < 8u)
    	mask &= ((uint8)(1u << QDECDIR_INPUTS) - 1u);
	#endif /* End QDECDIR_INPUTS < 8u */
    QDECDIR_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: QDECDIR_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 QDECDIR_ReadMask(void) 
{
    return QDECDIR_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
