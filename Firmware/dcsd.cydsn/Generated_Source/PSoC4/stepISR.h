/*******************************************************************************
* File Name: stepISR.h
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
#if !defined(CY_ISR_stepISR_H)
#define CY_ISR_stepISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void stepISR_Start(void);
void stepISR_StartEx(cyisraddress address);
void stepISR_Stop(void);

CY_ISR_PROTO(stepISR_Interrupt);

void stepISR_SetVector(cyisraddress address);
cyisraddress stepISR_GetVector(void);

void stepISR_SetPriority(uint8 priority);
uint8 stepISR_GetPriority(void);

void stepISR_Enable(void);
uint8 stepISR_GetState(void);
void stepISR_Disable(void);

void stepISR_SetPending(void);
void stepISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the stepISR ISR. */
#define stepISR_INTC_VECTOR            ((reg32 *) stepISR__INTC_VECT)

/* Address of the stepISR ISR priority. */
#define stepISR_INTC_PRIOR             ((reg32 *) stepISR__INTC_PRIOR_REG)

/* Priority of the stepISR interrupt. */
#define stepISR_INTC_PRIOR_NUMBER      stepISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable stepISR interrupt. */
#define stepISR_INTC_SET_EN            ((reg32 *) stepISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the stepISR interrupt. */
#define stepISR_INTC_CLR_EN            ((reg32 *) stepISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the stepISR interrupt state to pending. */
#define stepISR_INTC_SET_PD            ((reg32 *) stepISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the stepISR interrupt. */
#define stepISR_INTC_CLR_PD            ((reg32 *) stepISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_stepISR_H */


/* [] END OF FILE */
