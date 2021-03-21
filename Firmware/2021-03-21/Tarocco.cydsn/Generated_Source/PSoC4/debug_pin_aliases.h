/*******************************************************************************
* File Name: debug_pin.h  
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

#if !defined(CY_PINS_debug_pin_ALIASES_H) /* Pins debug_pin_ALIASES_H */
#define CY_PINS_debug_pin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define debug_pin_0			(debug_pin__0__PC)
#define debug_pin_0_PS		(debug_pin__0__PS)
#define debug_pin_0_PC		(debug_pin__0__PC)
#define debug_pin_0_DR		(debug_pin__0__DR)
#define debug_pin_0_SHIFT	(debug_pin__0__SHIFT)
#define debug_pin_0_INTR	((uint16)((uint16)0x0003u << (debug_pin__0__SHIFT*2u)))

#define debug_pin_INTR_ALL	 ((uint16)(debug_pin_0_INTR))


#endif /* End Pins debug_pin_ALIASES_H */


/* [] END OF FILE */
