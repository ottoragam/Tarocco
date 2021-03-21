/*******************************************************************************
* File Name: enable.h  
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

#if !defined(CY_PINS_enable_ALIASES_H) /* Pins enable_ALIASES_H */
#define CY_PINS_enable_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define enable_0			(enable__0__PC)
#define enable_0_PS		(enable__0__PS)
#define enable_0_PC		(enable__0__PC)
#define enable_0_DR		(enable__0__DR)
#define enable_0_SHIFT	(enable__0__SHIFT)
#define enable_0_INTR	((uint16)((uint16)0x0003u << (enable__0__SHIFT*2u)))

#define enable_INTR_ALL	 ((uint16)(enable_0_INTR))


#endif /* End Pins enable_ALIASES_H */


/* [] END OF FILE */
