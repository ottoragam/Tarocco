/*******************************************************************************
* File Name: sleep.h  
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

#if !defined(CY_PINS_sleep_ALIASES_H) /* Pins sleep_ALIASES_H */
#define CY_PINS_sleep_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define sleep_0			(sleep__0__PC)
#define sleep_0_PS		(sleep__0__PS)
#define sleep_0_PC		(sleep__0__PC)
#define sleep_0_DR		(sleep__0__DR)
#define sleep_0_SHIFT	(sleep__0__SHIFT)
#define sleep_0_INTR	((uint16)((uint16)0x0003u << (sleep__0__SHIFT*2u)))

#define sleep_INTR_ALL	 ((uint16)(sleep_0_INTR))


#endif /* End Pins sleep_ALIASES_H */


/* [] END OF FILE */
