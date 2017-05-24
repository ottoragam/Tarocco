/*******************************************************************************
* File Name: step_register.h  
* Version 1.90
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_step_register_H) /* CY_STATUS_REG_step_register_H */
#define CY_STATUS_REG_step_register_H

#include "cytypes.h"
#include "CyLib.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} step_register_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 step_register_Read(void) ;
void step_register_InterruptEnable(void) ;
void step_register_InterruptDisable(void) ;
void step_register_WriteMask(uint8 mask) ;
uint8 step_register_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define step_register_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define step_register_INPUTS              1


/***************************************
*             Registers
***************************************/

/* Status Register */
#define step_register_Status             (* (reg8 *) step_register_sts_sts_reg__STATUS_REG )
#define step_register_Status_PTR         (  (reg8 *) step_register_sts_sts_reg__STATUS_REG )
#define step_register_Status_Mask        (* (reg8 *) step_register_sts_sts_reg__MASK_REG )
#define step_register_Status_Aux_Ctrl    (* (reg8 *) step_register_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_step_register_H */


/* [] END OF FILE */
