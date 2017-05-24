/*******************************************************************************
* File Name: pwmClk.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_pwmClk_H)
#define CY_CLOCK_pwmClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void pwmClk_StartEx(uint32 alignClkDiv);
#define pwmClk_Start() \
    pwmClk_StartEx(pwmClk__PA_DIV_ID)

#else

void pwmClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void pwmClk_Stop(void);

void pwmClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 pwmClk_GetDividerRegister(void);
uint8  pwmClk_GetFractionalDividerRegister(void);

#define pwmClk_Enable()                         pwmClk_Start()
#define pwmClk_Disable()                        pwmClk_Stop()
#define pwmClk_SetDividerRegister(clkDivider, reset)  \
    pwmClk_SetFractionalDividerRegister((clkDivider), 0u)
#define pwmClk_SetDivider(clkDivider)           pwmClk_SetDividerRegister((clkDivider), 1u)
#define pwmClk_SetDividerValue(clkDivider)      pwmClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define pwmClk_DIV_ID     pwmClk__DIV_ID

#define pwmClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define pwmClk_CTRL_REG   (*(reg32 *)pwmClk__CTRL_REGISTER)
#define pwmClk_DIV_REG    (*(reg32 *)pwmClk__DIV_REGISTER)

#define pwmClk_CMD_DIV_SHIFT          (0u)
#define pwmClk_CMD_PA_DIV_SHIFT       (8u)
#define pwmClk_CMD_DISABLE_SHIFT      (30u)
#define pwmClk_CMD_ENABLE_SHIFT       (31u)

#define pwmClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << pwmClk_CMD_DISABLE_SHIFT))
#define pwmClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << pwmClk_CMD_ENABLE_SHIFT))

#define pwmClk_DIV_FRAC_MASK  (0x000000F8u)
#define pwmClk_DIV_FRAC_SHIFT (3u)
#define pwmClk_DIV_INT_MASK   (0xFFFFFF00u)
#define pwmClk_DIV_INT_SHIFT  (8u)

#else 

#define pwmClk_DIV_REG        (*(reg32 *)pwmClk__REGISTER)
#define pwmClk_ENABLE_REG     pwmClk_DIV_REG
#define pwmClk_DIV_FRAC_MASK  pwmClk__FRAC_MASK
#define pwmClk_DIV_FRAC_SHIFT (16u)
#define pwmClk_DIV_INT_MASK   pwmClk__DIVIDER_MASK
#define pwmClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_pwmClk_H) */

/* [] END OF FILE */
