/*******************************************************************************
* File Name: QDEC_FAULT.c  
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

#include "QDEC_FAULT.h"

#if !defined(QDEC_FAULT_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: QDEC_FAULT_Read
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
uint8 QDEC_FAULT_Read(void) 
{ 
    return QDEC_FAULT_Status;
}


/*******************************************************************************
* Function Name: QDEC_FAULT_InterruptEnable
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
void QDEC_FAULT_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    QDEC_FAULT_Status_Aux_Ctrl |= QDEC_FAULT_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: QDEC_FAULT_InterruptDisable
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
void QDEC_FAULT_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    QDEC_FAULT_Status_Aux_Ctrl &= (uint8)(~QDEC_FAULT_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: QDEC_FAULT_WriteMask
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
void QDEC_FAULT_WriteMask(uint8 mask) 
{
    #if(QDEC_FAULT_INPUTS < 8u)
    	mask &= ((uint8)(1u << QDEC_FAULT_INPUTS) - 1u);
	#endif /* End QDEC_FAULT_INPUTS < 8u */
    QDEC_FAULT_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: QDEC_FAULT_ReadMask
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
uint8 QDEC_FAULT_ReadMask(void) 
{
    return QDEC_FAULT_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
