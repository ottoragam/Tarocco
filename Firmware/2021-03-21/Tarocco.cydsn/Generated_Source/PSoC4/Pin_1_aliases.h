/*******************************************************************************
* File Name: Pin_1.h  
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

#if !defined(CY_PINS_Pin_1_ALIASES_H) /* Pins Pin_1_ALIASES_H */
#define CY_PINS_Pin_1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Pin_1_0			(Pin_1__0__PC)
#define Pin_1_0_PS		(Pin_1__0__PS)
#define Pin_1_0_PC		(Pin_1__0__PC)
#define Pin_1_0_DR		(Pin_1__0__DR)
#define Pin_1_0_SHIFT	(Pin_1__0__SHIFT)
#define Pin_1_0_INTR	((uint16)((uint16)0x0003u << (Pin_1__0__SHIFT*2u)))

#define Pin_1_INTR_ALL	 ((uint16)(Pin_1_0_INTR))


#endif /* End Pins Pin_1_ALIASES_H */


/* [] END OF FILE */
