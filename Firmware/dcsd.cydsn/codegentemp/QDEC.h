/*******************************************************************************
* File Name: QDEC.h  
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the Quadrature
*  Decoder component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_QUADRATURE_DECODER_QDEC_H)
#define CY_QUADRATURE_DECODER_QDEC_H

#include "cyfitter.h"
#include "CyLib.h"
#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component QuadDec_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#define QDEC_COUNTER_SIZE               (32u)
#define QDEC_COUNTER_SIZE_8_BIT         (8u)
#define QDEC_COUNTER_SIZE_16_BIT        (16u)
#define QDEC_COUNTER_SIZE_32_BIT        (32u)

#if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT)
    #include "QDEC_Cnt8.h"
#else 
    /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_16_BIT) || 
    *  (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT) 
    */
    #include "QDEC_Cnt16.h"
#endif /* QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT */

extern uint8 QDEC_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define QDEC_COUNTER_RESOLUTION         (4u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} QDEC_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  QDEC_Init(void) ;
void  QDEC_Start(void) ;
void  QDEC_Stop(void) ;
void  QDEC_Enable(void) ;
uint8 QDEC_GetEvents(void) ;
void  QDEC_SetInterruptMask(uint8 mask) ;
uint8 QDEC_GetInterruptMask(void) ;
int32 QDEC_GetCounter(void) ;
void  QDEC_SetCounter(int32 value)
;
void  QDEC_Sleep(void) ;
void  QDEC_Wakeup(void) ;
void  QDEC_SaveConfig(void) ;
void  QDEC_RestoreConfig(void) ;

#if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT)
    CY_ISR_PROTO(QDEC_ISR);
#endif /* QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT */


/***************************************
*           API Constants
***************************************/

#if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT)
    #define QDEC_ISR_NUMBER             ((uint8) QDEC_isr__INTC_NUMBER)
    #define QDEC_ISR_PRIORITY           ((uint8) QDEC_isr__INTC_PRIOR_NUM)
#endif /* QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT */


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define QDEC_GLITCH_FILTERING           (0u)
#define QDEC_INDEX_INPUT                (0u)


/***************************************
*    Initial Parameter Constants
***************************************/

#if (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT)
    #define QDEC_COUNTER_INIT_VALUE    (0x80u)
#else 
    /* (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_16_BIT) ||
    *  (QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_32_BIT)
    */
    #define QDEC_COUNTER_INIT_VALUE    (0x8000u)
    #define QDEC_COUNTER_MAX_VALUE     (0x7FFFu)
#endif /* QDEC_COUNTER_SIZE == QDEC_COUNTER_SIZE_8_BIT */


/***************************************
*             Registers
***************************************/

#define QDEC_STATUS_REG                 (* (reg8 *) QDEC_bQuadDec_Stsreg__STATUS_REG)
#define QDEC_STATUS_PTR                 (  (reg8 *) QDEC_bQuadDec_Stsreg__STATUS_REG)
#define QDEC_STATUS_MASK                (* (reg8 *) QDEC_bQuadDec_Stsreg__MASK_REG)
#define QDEC_STATUS_MASK_PTR            (  (reg8 *) QDEC_bQuadDec_Stsreg__MASK_REG)
#define QDEC_SR_AUX_CONTROL             (* (reg8 *) QDEC_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)
#define QDEC_SR_AUX_CONTROL_PTR         (  (reg8 *) QDEC_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)


/***************************************
*        Register Constants
***************************************/

#define QDEC_COUNTER_OVERFLOW_SHIFT     (0x00u)
#define QDEC_COUNTER_UNDERFLOW_SHIFT    (0x01u)
#define QDEC_COUNTER_RESET_SHIFT        (0x02u)
#define QDEC_INVALID_IN_SHIFT           (0x03u)
#define QDEC_COUNTER_OVERFLOW           ((uint8) (0x01u << QDEC_COUNTER_OVERFLOW_SHIFT))
#define QDEC_COUNTER_UNDERFLOW          ((uint8) (0x01u << QDEC_COUNTER_UNDERFLOW_SHIFT))
#define QDEC_COUNTER_RESET              ((uint8) (0x01u << QDEC_COUNTER_RESET_SHIFT))
#define QDEC_INVALID_IN                 ((uint8) (0x01u << QDEC_INVALID_IN_SHIFT))

#define QDEC_INTERRUPTS_ENABLE_SHIFT    (0x04u)
#define QDEC_INTERRUPTS_ENABLE          ((uint8)(0x01u << QDEC_INTERRUPTS_ENABLE_SHIFT))
#define QDEC_INIT_INT_MASK              (0x0Fu)


/******************************************************************************************
* Following code are OBSOLETE and must not be used starting from Quadrature Decoder 2.20
******************************************************************************************/
#define QDEC_DISABLE                    (0x00u)


#endif /* CY_QUADRATURE_DECODER_QDEC_H */


/* [] END OF FILE */
