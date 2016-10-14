/*******************************************************************************
* File Name: err.h  
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

#if !defined(CY_PINS_err_ALIASES_H) /* Pins err_ALIASES_H */
#define CY_PINS_err_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define err_0			(err__0__PC)
#define err_0_PS		(err__0__PS)
#define err_0_PC		(err__0__PC)
#define err_0_DR		(err__0__DR)
#define err_0_SHIFT	(err__0__SHIFT)
#define err_0_INTR	((uint16)((uint16)0x0003u << (err__0__SHIFT*2u)))

#define err_INTR_ALL	 ((uint16)(err_0_INTR))


#endif /* End Pins err_ALIASES_H */


/* [] END OF FILE */
