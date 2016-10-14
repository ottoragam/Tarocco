/*******************************************************************************
* File Name: RESET_FAULT.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_RESET_FAULT_H) /* CY_CONTROL_REG_RESET_FAULT_H */
#define CY_CONTROL_REG_RESET_FAULT_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} RESET_FAULT_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    RESET_FAULT_Write(uint8 control) ;
uint8   RESET_FAULT_Read(void) ;

void RESET_FAULT_SaveConfig(void) ;
void RESET_FAULT_RestoreConfig(void) ;
void RESET_FAULT_Sleep(void) ; 
void RESET_FAULT_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define RESET_FAULT_Control        (* (reg8 *) RESET_FAULT_Sync_ctrl_reg__CONTROL_REG )
#define RESET_FAULT_Control_PTR    (  (reg8 *) RESET_FAULT_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_RESET_FAULT_H */


/* [] END OF FILE */
