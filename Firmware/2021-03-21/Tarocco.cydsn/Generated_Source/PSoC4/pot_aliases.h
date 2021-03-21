/*******************************************************************************
* File Name: pot.h  
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

#if !defined(CY_PINS_pot_ALIASES_H) /* Pins pot_ALIASES_H */
#define CY_PINS_pot_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pot_0			(pot__0__PC)
#define pot_0_PS		(pot__0__PS)
#define pot_0_PC		(pot__0__PC)
#define pot_0_DR		(pot__0__DR)
#define pot_0_SHIFT	(pot__0__SHIFT)
#define pot_0_INTR	((uint16)((uint16)0x0003u << (pot__0__SHIFT*2u)))

#define pot_INTR_ALL	 ((uint16)(pot_0_INTR))


#endif /* End Pins pot_ALIASES_H */


/* [] END OF FILE */
