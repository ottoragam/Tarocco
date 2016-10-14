/*******************************************************************************
* File Name: encFault.h
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
#if !defined(CY_ISR_encFault_H)
#define CY_ISR_encFault_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void encFault_Start(void);
void encFault_StartEx(cyisraddress address);
void encFault_Stop(void);

CY_ISR_PROTO(encFault_Interrupt);

void encFault_SetVector(cyisraddress address);
cyisraddress encFault_GetVector(void);

void encFault_SetPriority(uint8 priority);
uint8 encFault_GetPriority(void);

void encFault_Enable(void);
uint8 encFault_GetState(void);
void encFault_Disable(void);

void encFault_SetPending(void);
void encFault_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the encFault ISR. */
#define encFault_INTC_VECTOR            ((reg32 *) encFault__INTC_VECT)

/* Address of the encFault ISR priority. */
#define encFault_INTC_PRIOR             ((reg32 *) encFault__INTC_PRIOR_REG)

/* Priority of the encFault interrupt. */
#define encFault_INTC_PRIOR_NUMBER      encFault__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable encFault interrupt. */
#define encFault_INTC_SET_EN            ((reg32 *) encFault__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the encFault interrupt. */
#define encFault_INTC_CLR_EN            ((reg32 *) encFault__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the encFault interrupt state to pending. */
#define encFault_INTC_SET_PD            ((reg32 *) encFault__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the encFault interrupt. */
#define encFault_INTC_CLR_PD            ((reg32 *) encFault__INTC_CLR_PD_REG)



#endif /* CY_ISR_encFault_H */


/* [] END OF FILE */
