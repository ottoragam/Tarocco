/*******************************************************************************
* File Name: error.h  
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

#if !defined(CY_PINS_error_ALIASES_H) /* Pins error_ALIASES_H */
#define CY_PINS_error_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define error_0			(error__0__PC)
#define error_0_PS		(error__0__PS)
#define error_0_PC		(error__0__PC)
#define error_0_DR		(error__0__DR)
#define error_0_SHIFT	(error__0__SHIFT)
#define error_0_INTR	((uint16)((uint16)0x0003u << (error__0__SHIFT*2u)))

#define error_INTR_ALL	 ((uint16)(error_0_INTR))


#endif /* End Pins error_ALIASES_H */


/* [] END OF FILE */
