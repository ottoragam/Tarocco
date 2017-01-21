/*******************************************************************************
* File Name: QDEC_INT.c
* Version 3.0
*
* Description:
*  This file contains the Interrupt Service Routine (ISR) for the Quadrature
*  Decoder component.
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
#include "QDEC_PVT.h"
#include "cyapicallbacks.h"

volatile int32 QDEC_count32SoftPart = 0;


/*******************************************************************************
* FUNCTION NAME: void QDEC_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for Quadrature Decoder Component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  QDEC_count32SoftPart - modified to update hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*  QDEC_swStatus - modified with the updated values of STATUS
*  register.
*
*******************************************************************************/
CY_ISR( QDEC_ISR )
{
   uint8 QDEC_swStatus;

   QDEC_swStatus = QDEC_STATUS_REG;

    #ifdef QDEC_ISR_ENTRY_CALLBACK
        QDEC_ISR_EntryCallback();
    #endif /* QDEC_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START QDEC_ISR_START` */

    /* `#END` */

    if (0u != (QDEC_swStatus & QDEC_COUNTER_OVERFLOW))
    {
        QDEC_count32SoftPart += (int32) QDEC_COUNTER_MAX_VALUE;
    }
    else if (0u != (QDEC_swStatus & QDEC_COUNTER_UNDERFLOW))
    {
        QDEC_count32SoftPart -= (int32) QDEC_COUNTER_INIT_VALUE;
    }
    else
    {
        /* Nothing to do here */
    }
    
    if (0u != (QDEC_swStatus & QDEC_COUNTER_RESET))
    {
        QDEC_count32SoftPart = 0;
    }
    
    /* User code required at end of ISR */
    /* `#START QDEC_ISR_END` */

    /* `#END` */

    #ifdef QDEC_ISR_EXIT_CALLBACK
        QDEC_ISR_ExitCallback();
    #endif /* QDEC_ISR_EXIT_CALLBACK */
}


/* [] END OF FILE */
