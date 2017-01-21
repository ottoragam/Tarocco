/*******************************************************************************
* File Name: QDECFAULT.h  
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

#if !defined(CY_STATUS_REG_QDECFAULT_H) /* CY_STATUS_REG_QDECFAULT_H */
#define CY_STATUS_REG_QDECFAULT_H

#include "cytypes.h"
#include "CyLib.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} QDECFAULT_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 QDECFAULT_Read(void) ;
void QDECFAULT_InterruptEnable(void) ;
void QDECFAULT_InterruptDisable(void) ;
void QDECFAULT_WriteMask(uint8 mask) ;
uint8 QDECFAULT_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define QDECFAULT_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define QDECFAULT_INPUTS              1


/***************************************
*             Registers
***************************************/

/* Status Register */
#define QDECFAULT_Status             (* (reg8 *) QDECFAULT_sts_sts_reg__STATUS_REG )
#define QDECFAULT_Status_PTR         (  (reg8 *) QDECFAULT_sts_sts_reg__STATUS_REG )
#define QDECFAULT_Status_Mask        (* (reg8 *) QDECFAULT_sts_sts_reg__MASK_REG )
#define QDECFAULT_Status_Aux_Ctrl    (* (reg8 *) QDECFAULT_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_QDECFAULT_H */


/* [] END OF FILE */
