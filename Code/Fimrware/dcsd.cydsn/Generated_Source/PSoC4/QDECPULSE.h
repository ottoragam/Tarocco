/*******************************************************************************
* File Name: QDECPULSE.h  
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

#if !defined(CY_STATUS_REG_QDECPULSE_H) /* CY_STATUS_REG_QDECPULSE_H */
#define CY_STATUS_REG_QDECPULSE_H

#include "cytypes.h"
#include "CyLib.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} QDECPULSE_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 QDECPULSE_Read(void) ;
void QDECPULSE_InterruptEnable(void) ;
void QDECPULSE_InterruptDisable(void) ;
void QDECPULSE_WriteMask(uint8 mask) ;
uint8 QDECPULSE_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define QDECPULSE_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define QDECPULSE_INPUTS              1


/***************************************
*             Registers
***************************************/

/* Status Register */
#define QDECPULSE_Status             (* (reg8 *) QDECPULSE_sts_sts_reg__STATUS_REG )
#define QDECPULSE_Status_PTR         (  (reg8 *) QDECPULSE_sts_sts_reg__STATUS_REG )
#define QDECPULSE_Status_Mask        (* (reg8 *) QDECPULSE_sts_sts_reg__MASK_REG )
#define QDECPULSE_Status_Aux_Ctrl    (* (reg8 *) QDECPULSE_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_QDECPULSE_H */


/* [] END OF FILE */
