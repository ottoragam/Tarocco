/*******************************************************************************
* File Name: rxISR.h
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
#if !defined(CY_ISR_rxISR_H)
#define CY_ISR_rxISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void rxISR_Start(void);
void rxISR_StartEx(cyisraddress address);
void rxISR_Stop(void);

CY_ISR_PROTO(rxISR_Interrupt);

void rxISR_SetVector(cyisraddress address);
cyisraddress rxISR_GetVector(void);

void rxISR_SetPriority(uint8 priority);
uint8 rxISR_GetPriority(void);

void rxISR_Enable(void);
uint8 rxISR_GetState(void);
void rxISR_Disable(void);

void rxISR_SetPending(void);
void rxISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the rxISR ISR. */
#define rxISR_INTC_VECTOR            ((reg32 *) rxISR__INTC_VECT)

/* Address of the rxISR ISR priority. */
#define rxISR_INTC_PRIOR             ((reg32 *) rxISR__INTC_PRIOR_REG)

/* Priority of the rxISR interrupt. */
#define rxISR_INTC_PRIOR_NUMBER      rxISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable rxISR interrupt. */
#define rxISR_INTC_SET_EN            ((reg32 *) rxISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the rxISR interrupt. */
#define rxISR_INTC_CLR_EN            ((reg32 *) rxISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the rxISR interrupt state to pending. */
#define rxISR_INTC_SET_PD            ((reg32 *) rxISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the rxISR interrupt. */
#define rxISR_INTC_CLR_PD            ((reg32 *) rxISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_rxISR_H */


/* [] END OF FILE */
