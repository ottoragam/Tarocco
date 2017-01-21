/*******************************************************************************
* File Name: INVERT_DIR.h  
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

#if !defined(CY_CONTROL_REG_INVERT_DIR_H) /* CY_CONTROL_REG_INVERT_DIR_H */
#define CY_CONTROL_REG_INVERT_DIR_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} INVERT_DIR_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    INVERT_DIR_Write(uint8 control) ;
uint8   INVERT_DIR_Read(void) ;

void INVERT_DIR_SaveConfig(void) ;
void INVERT_DIR_RestoreConfig(void) ;
void INVERT_DIR_Sleep(void) ; 
void INVERT_DIR_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define INVERT_DIR_Control        (* (reg8 *) INVERT_DIR_Sync_ctrl_reg__CONTROL_REG )
#define INVERT_DIR_Control_PTR    (  (reg8 *) INVERT_DIR_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_INVERT_DIR_H */


/* [] END OF FILE */
