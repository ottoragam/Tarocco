/*******************************************************************************
* File Name: reset.h  
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

#if !defined(CY_PINS_reset_ALIASES_H) /* Pins reset_ALIASES_H */
#define CY_PINS_reset_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define reset_0			(reset__0__PC)
#define reset_0_PS		(reset__0__PS)
#define reset_0_PC		(reset__0__PC)
#define reset_0_DR		(reset__0__DR)
#define reset_0_SHIFT	(reset__0__SHIFT)
#define reset_0_INTR	((uint16)((uint16)0x0003u << (reset__0__SHIFT*2u)))

#define reset_INTR_ALL	 ((uint16)(reset_0_INTR))


#endif /* End Pins reset_ALIASES_H */


/* [] END OF FILE */
