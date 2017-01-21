/*******************************************************************************
* File Name: ENCODER.h  
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

#if !defined(CY_STATUS_REG_ENCODER_H) /* CY_STATUS_REG_ENCODER_H */
#define CY_STATUS_REG_ENCODER_H

#include "cytypes.h"
#include "CyLib.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} ENCODER_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 ENCODER_Read(void) ;
void ENCODER_InterruptEnable(void) ;
void ENCODER_InterruptDisable(void) ;
void ENCODER_WriteMask(uint8 mask) ;
uint8 ENCODER_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define ENCODER_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define ENCODER_INPUTS              2


/***************************************
*             Registers
***************************************/

/* Status Register */
#define ENCODER_Status             (* (reg8 *) ENCODER_sts_sts_reg__STATUS_REG )
#define ENCODER_Status_PTR         (  (reg8 *) ENCODER_sts_sts_reg__STATUS_REG )
#define ENCODER_Status_Mask        (* (reg8 *) ENCODER_sts_sts_reg__MASK_REG )
#define ENCODER_Status_Aux_Ctrl    (* (reg8 *) ENCODER_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_ENCODER_H */


/* [] END OF FILE */
