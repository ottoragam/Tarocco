/*******************************************************************************
* File Name: pulseISR.h
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
#if !defined(CY_ISR_pulseISR_H)
#define CY_ISR_pulseISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void pulseISR_Start(void);
void pulseISR_StartEx(cyisraddress address);
void pulseISR_Stop(void);

CY_ISR_PROTO(pulseISR_Interrupt);

void pulseISR_SetVector(cyisraddress address);
cyisraddress pulseISR_GetVector(void);

void pulseISR_SetPriority(uint8 priority);
uint8 pulseISR_GetPriority(void);

void pulseISR_Enable(void);
uint8 pulseISR_GetState(void);
void pulseISR_Disable(void);

void pulseISR_SetPending(void);
void pulseISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the pulseISR ISR. */
#define pulseISR_INTC_VECTOR            ((reg32 *) pulseISR__INTC_VECT)

/* Address of the pulseISR ISR priority. */
#define pulseISR_INTC_PRIOR             ((reg32 *) pulseISR__INTC_PRIOR_REG)

/* Priority of the pulseISR interrupt. */
#define pulseISR_INTC_PRIOR_NUMBER      pulseISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable pulseISR interrupt. */
#define pulseISR_INTC_SET_EN            ((reg32 *) pulseISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the pulseISR interrupt. */
#define pulseISR_INTC_CLR_EN            ((reg32 *) pulseISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the pulseISR interrupt state to pending. */
#define pulseISR_INTC_SET_PD            ((reg32 *) pulseISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the pulseISR interrupt. */
#define pulseISR_INTC_CLR_PD            ((reg32 *) pulseISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_pulseISR_H */


/* [] END OF FILE */
