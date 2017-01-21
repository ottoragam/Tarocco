/*******************************************************************************
* File Name: QDECFAULT.c  
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

#include "QDECFAULT.h"

#if !defined(QDECFAULT_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: QDECFAULT_Read
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
uint8 QDECFAULT_Read(void) 
{ 
    return QDECFAULT_Status;
}


/*******************************************************************************
* Function Name: QDECFAULT_InterruptEnable
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
void QDECFAULT_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    QDECFAULT_Status_Aux_Ctrl |= QDECFAULT_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: QDECFAULT_InterruptDisable
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
void QDECFAULT_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    QDECFAULT_Status_Aux_Ctrl &= (uint8)(~QDECFAULT_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: QDECFAULT_WriteMask
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
void QDECFAULT_WriteMask(uint8 mask) 
{
    #if(QDECFAULT_INPUTS < 8u)
    	mask &= ((uint8)(1u << QDECFAULT_INPUTS) - 1u);
	#endif /* End QDECFAULT_INPUTS < 8u */
    QDECFAULT_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: QDECFAULT_ReadMask
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
uint8 QDECFAULT_ReadMask(void) 
{
    return QDECFAULT_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
