/*******************************************************************************
* File Name: QDECDIR.h  
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

#if !defined(CY_STATUS_REG_QDECDIR_H) /* CY_STATUS_REG_QDECDIR_H */
#define CY_STATUS_REG_QDECDIR_H

#include "cytypes.h"
#include "CyLib.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} QDECDIR_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 QDECDIR_Read(void) ;
void QDECDIR_InterruptEnable(void) ;
void QDECDIR_InterruptDisable(void) ;
void QDECDIR_WriteMask(uint8 mask) ;
uint8 QDECDIR_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define QDECDIR_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define QDECDIR_INPUTS              1


/***************************************
*             Registers
***************************************/

/* Status Register */
#define QDECDIR_Status             (* (reg8 *) QDECDIR_sts_sts_reg__STATUS_REG )
#define QDECDIR_Status_PTR         (  (reg8 *) QDECDIR_sts_sts_reg__STATUS_REG )
#define QDECDIR_Status_Mask        (* (reg8 *) QDECDIR_sts_sts_reg__MASK_REG )
#define QDECDIR_Status_Aux_Ctrl    (* (reg8 *) QDECDIR_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_QDECDIR_H */


/* [] END OF FILE */
