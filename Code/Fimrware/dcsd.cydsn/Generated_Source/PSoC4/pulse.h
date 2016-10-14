/*******************************************************************************
* File Name: pulse.h
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
#if !defined(CY_ISR_pulse_H)
#define CY_ISR_pulse_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void pulse_Start(void);
void pulse_StartEx(cyisraddress address);
void pulse_Stop(void);

CY_ISR_PROTO(pulse_Interrupt);

void pulse_SetVector(cyisraddress address);
cyisraddress pulse_GetVector(void);

void pulse_SetPriority(uint8 priority);
uint8 pulse_GetPriority(void);

void pulse_Enable(void);
uint8 pulse_GetState(void);
void pulse_Disable(void);

void pulse_SetPending(void);
void pulse_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the pulse ISR. */
#define pulse_INTC_VECTOR            ((reg32 *) pulse__INTC_VECT)

/* Address of the pulse ISR priority. */
#define pulse_INTC_PRIOR             ((reg32 *) pulse__INTC_PRIOR_REG)

/* Priority of the pulse interrupt. */
#define pulse_INTC_PRIOR_NUMBER      pulse__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable pulse interrupt. */
#define pulse_INTC_SET_EN            ((reg32 *) pulse__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the pulse interrupt. */
#define pulse_INTC_CLR_EN            ((reg32 *) pulse__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the pulse interrupt state to pending. */
#define pulse_INTC_SET_PD            ((reg32 *) pulse__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the pulse interrupt. */
#define pulse_INTC_CLR_PD            ((reg32 *) pulse__INTC_CLR_PD_REG)



#endif /* CY_ISR_pulse_H */


/* [] END OF FILE */
