/*******************************************************************************
* File Name: phase.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_phase_ALIASES_H) /* Pins phase_ALIASES_H */
#define CY_PINS_phase_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define phase_0			(phase__0__PC)
#define phase_0_PS		(phase__0__PS)
#define phase_0_PC		(phase__0__PC)
#define phase_0_DR		(phase__0__DR)
#define phase_0_SHIFT	(phase__0__SHIFT)
#define phase_0_INTR	((uint16)((uint16)0x0003u << (phase__0__SHIFT*2u)))

#define phase_INTR_ALL	 ((uint16)(phase_0_INTR))


#endif /* End Pins phase_ALIASES_H */


/* [] END OF FILE */
