/*******************************************************************************
* File Name: QDEC_FAULT.h  
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

#if !defined(CY_STATUS_REG_QDEC_FAULT_H) /* CY_STATUS_REG_QDEC_FAULT_H */
#define CY_STATUS_REG_QDEC_FAULT_H

#include "cytypes.h"
#include "CyLib.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} QDEC_FAULT_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 QDEC_FAULT_Read(void) ;
void QDEC_FAULT_InterruptEnable(void) ;
void QDEC_FAULT_InterruptDisable(void) ;
void QDEC_FAULT_WriteMask(uint8 mask) ;
uint8 QDEC_FAULT_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define QDEC_FAULT_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define QDEC_FAULT_INPUTS              1


/***************************************
*             Registers
***************************************/

/* Status Register */
#define QDEC_FAULT_Status             (* (reg8 *) QDEC_FAULT_sts_sts_reg__STATUS_REG )
#define QDEC_FAULT_Status_PTR         (  (reg8 *) QDEC_FAULT_sts_sts_reg__STATUS_REG )
#define QDEC_FAULT_Status_Mask        (* (reg8 *) QDEC_FAULT_sts_sts_reg__MASK_REG )
#define QDEC_FAULT_Status_Aux_Ctrl    (* (reg8 *) QDEC_FAULT_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_QDEC_FAULT_H */


/* [] END OF FILE */
