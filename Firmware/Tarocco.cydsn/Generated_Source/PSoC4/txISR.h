/*******************************************************************************
* File Name: txISR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_txISR_H)
#define CY_ISR_txISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void txISR_Start(void);
void txISR_StartEx(cyisraddress address);
void txISR_Stop(void);

CY_ISR_PROTO(txISR_Interrupt);

void txISR_SetVector(cyisraddress address);
cyisraddress txISR_GetVector(void);

void txISR_SetPriority(uint8 priority);
uint8 txISR_GetPriority(void);

void txISR_Enable(void);
uint8 txISR_GetState(void);
void txISR_Disable(void);

void txISR_SetPending(void);
void txISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the txISR ISR. */
#define txISR_INTC_VECTOR            ((reg32 *) txISR__INTC_VECT)

/* Address of the txISR ISR priority. */
#define txISR_INTC_PRIOR             ((reg32 *) txISR__INTC_PRIOR_REG)

/* Priority of the txISR interrupt. */
#define txISR_INTC_PRIOR_NUMBER      txISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable txISR interrupt. */
#define txISR_INTC_SET_EN            ((reg32 *) txISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the txISR interrupt. */
#define txISR_INTC_CLR_EN            ((reg32 *) txISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the txISR interrupt state to pending. */
#define txISR_INTC_SET_PD            ((reg32 *) txISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the txISR interrupt. */
#define txISR_INTC_CLR_PD            ((reg32 *) txISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_txISR_H */


/* [] END OF FILE */
