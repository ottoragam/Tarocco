/*******************************************************************************
* File Name: QDECPULSE.c  
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

#include "QDECPULSE.h"

#if !defined(QDECPULSE_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: QDECPULSE_Read
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
uint8 QDECPULSE_Read(void) 
{ 
    return QDECPULSE_Status;
}


/*******************************************************************************
* Function Name: QDECPULSE_InterruptEnable
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
void QDECPULSE_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    QDECPULSE_Status_Aux_Ctrl |= QDECPULSE_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: QDECPULSE_InterruptDisable
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
void QDECPULSE_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    QDECPULSE_Status_Aux_Ctrl &= (uint8)(~QDECPULSE_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: QDECPULSE_WriteMask
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
void QDECPULSE_WriteMask(uint8 mask) 
{
    #if(QDECPULSE_INPUTS < 8u)
    	mask &= ((uint8)(1u << QDECPULSE_INPUTS) - 1u);
	#endif /* End QDECPULSE_INPUTS < 8u */
    QDECPULSE_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: QDECPULSE_ReadMask
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
uint8 QDECPULSE_ReadMask(void) 
{
    return QDECPULSE_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
