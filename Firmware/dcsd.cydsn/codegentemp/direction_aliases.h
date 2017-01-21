/*******************************************************************************
* File Name: direction.h  
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

#if !defined(CY_PINS_direction_ALIASES_H) /* Pins direction_ALIASES_H */
#define CY_PINS_direction_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define direction_0			(direction__0__PC)
#define direction_0_PS		(direction__0__PS)
#define direction_0_PC		(direction__0__PC)
#define direction_0_DR		(direction__0__DR)
#define direction_0_SHIFT	(direction__0__SHIFT)
#define direction_0_INTR	((uint16)((uint16)0x0003u << (direction__0__SHIFT*2u)))

#define direction_INTR_ALL	 ((uint16)(direction_0_INTR))


#endif /* End Pins direction_ALIASES_H */


/* [] END OF FILE */
