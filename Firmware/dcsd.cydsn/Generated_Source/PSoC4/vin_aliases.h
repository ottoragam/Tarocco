/*******************************************************************************
* File Name: vin.h  
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

#if !defined(CY_PINS_vin_ALIASES_H) /* Pins vin_ALIASES_H */
#define CY_PINS_vin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define vin_0			(vin__0__PC)
#define vin_0_PS		(vin__0__PS)
#define vin_0_PC		(vin__0__PC)
#define vin_0_DR		(vin__0__DR)
#define vin_0_SHIFT	(vin__0__SHIFT)
#define vin_0_INTR	((uint16)((uint16)0x0003u << (vin__0__SHIFT*2u)))

#define vin_INTR_ALL	 ((uint16)(vin_0_INTR))


#endif /* End Pins vin_ALIASES_H */


/* [] END OF FILE */
