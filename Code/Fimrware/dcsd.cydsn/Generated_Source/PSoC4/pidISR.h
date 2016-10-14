/*******************************************************************************
* File Name: pidISR.h
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
#if !defined(CY_ISR_pidISR_H)
#define CY_ISR_pidISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void pidISR_Start(void);
void pidISR_StartEx(cyisraddress address);
void pidISR_Stop(void);

CY_ISR_PROTO(pidISR_Interrupt);

void pidISR_SetVector(cyisraddress address);
cyisraddress pidISR_GetVector(void);

void pidISR_SetPriority(uint8 priority);
uint8 pidISR_GetPriority(void);

void pidISR_Enable(void);
uint8 pidISR_GetState(void);
void pidISR_Disable(void);

void pidISR_SetPending(void);
void pidISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the pidISR ISR. */
#define pidISR_INTC_VECTOR            ((reg32 *) pidISR__INTC_VECT)

/* Address of the pidISR ISR priority. */
#define pidISR_INTC_PRIOR             ((reg32 *) pidISR__INTC_PRIOR_REG)

/* Priority of the pidISR interrupt. */
#define pidISR_INTC_PRIOR_NUMBER      pidISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable pidISR interrupt. */
#define pidISR_INTC_SET_EN            ((reg32 *) pidISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the pidISR interrupt. */
#define pidISR_INTC_CLR_EN            ((reg32 *) pidISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the pidISR interrupt state to pending. */
#define pidISR_INTC_SET_PD            ((reg32 *) pidISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the pidISR interrupt. */
#define pidISR_INTC_CLR_PD            ((reg32 *) pidISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_pidISR_H */


/* [] END OF FILE */
