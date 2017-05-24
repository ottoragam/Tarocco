/*******************************************************************************
* File Name: pwmISR.h
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
#if !defined(CY_ISR_pwmISR_H)
#define CY_ISR_pwmISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void pwmISR_Start(void);
void pwmISR_StartEx(cyisraddress address);
void pwmISR_Stop(void);

CY_ISR_PROTO(pwmISR_Interrupt);

void pwmISR_SetVector(cyisraddress address);
cyisraddress pwmISR_GetVector(void);

void pwmISR_SetPriority(uint8 priority);
uint8 pwmISR_GetPriority(void);

void pwmISR_Enable(void);
uint8 pwmISR_GetState(void);
void pwmISR_Disable(void);

void pwmISR_SetPending(void);
void pwmISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the pwmISR ISR. */
#define pwmISR_INTC_VECTOR            ((reg32 *) pwmISR__INTC_VECT)

/* Address of the pwmISR ISR priority. */
#define pwmISR_INTC_PRIOR             ((reg32 *) pwmISR__INTC_PRIOR_REG)

/* Priority of the pwmISR interrupt. */
#define pwmISR_INTC_PRIOR_NUMBER      pwmISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable pwmISR interrupt. */
#define pwmISR_INTC_SET_EN            ((reg32 *) pwmISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the pwmISR interrupt. */
#define pwmISR_INTC_CLR_EN            ((reg32 *) pwmISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the pwmISR interrupt state to pending. */
#define pwmISR_INTC_SET_PD            ((reg32 *) pwmISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the pwmISR interrupt. */
#define pwmISR_INTC_CLR_PD            ((reg32 *) pwmISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_pwmISR_H */


/* [] END OF FILE */
