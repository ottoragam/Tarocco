/*******************************************************************************
* File Name: isense.h  
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

#if !defined(CY_PINS_isense_ALIASES_H) /* Pins isense_ALIASES_H */
#define CY_PINS_isense_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define isense_0			(isense__0__PC)
#define isense_0_PS		(isense__0__PS)
#define isense_0_PC		(isense__0__PC)
#define isense_0_DR		(isense__0__DR)
#define isense_0_SHIFT	(isense__0__SHIFT)
#define isense_0_INTR	((uint16)((uint16)0x0003u << (isense__0__SHIFT*2u)))

#define isense_INTR_ALL	 ((uint16)(isense_0_INTR))


#endif /* End Pins isense_ALIASES_H */


/* [] END OF FILE */
