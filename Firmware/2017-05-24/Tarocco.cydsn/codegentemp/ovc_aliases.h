/*******************************************************************************
* File Name: ovc.h  
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

#if !defined(CY_PINS_ovc_ALIASES_H) /* Pins ovc_ALIASES_H */
#define CY_PINS_ovc_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ovc_0			(ovc__0__PC)
#define ovc_0_PS		(ovc__0__PS)
#define ovc_0_PC		(ovc__0__PC)
#define ovc_0_DR		(ovc__0__DR)
#define ovc_0_SHIFT	(ovc__0__SHIFT)
#define ovc_0_INTR	((uint16)((uint16)0x0003u << (ovc__0__SHIFT*2u)))

#define ovc_INTR_ALL	 ((uint16)(ovc_0_INTR))


#endif /* End Pins ovc_ALIASES_H */


/* [] END OF FILE */
