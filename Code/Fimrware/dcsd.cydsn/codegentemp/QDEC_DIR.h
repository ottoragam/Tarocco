/*******************************************************************************
* File Name: QDEC_DIR.h  
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

#if !defined(CY_STATUS_REG_QDEC_DIR_H) /* CY_STATUS_REG_QDEC_DIR_H */
#define CY_STATUS_REG_QDEC_DIR_H

#include "cytypes.h"
#include "CyLib.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} QDEC_DIR_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 QDEC_DIR_Read(void) ;
void QDEC_DIR_InterruptEnable(void) ;
void QDEC_DIR_InterruptDisable(void) ;
void QDEC_DIR_WriteMask(uint8 mask) ;
uint8 QDEC_DIR_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define QDEC_DIR_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define QDEC_DIR_INPUTS              1


/***************************************
*             Registers
***************************************/

/* Status Register */
#define QDEC_DIR_Status             (* (reg8 *) QDEC_DIR_sts_sts_reg__STATUS_REG )
#define QDEC_DIR_Status_PTR         (  (reg8 *) QDEC_DIR_sts_sts_reg__STATUS_REG )
#define QDEC_DIR_Status_Mask        (* (reg8 *) QDEC_DIR_sts_sts_reg__MASK_REG )
#define QDEC_DIR_Status_Aux_Ctrl    (* (reg8 *) QDEC_DIR_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_QDEC_DIR_H */


/* [] END OF FILE */
