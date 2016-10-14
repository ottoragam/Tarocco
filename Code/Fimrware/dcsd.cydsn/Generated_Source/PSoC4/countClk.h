/*******************************************************************************
* File Name: countClk.h
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

#if !defined(CY_CLOCK_countClk_H)
#define CY_CLOCK_countClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void countClk_StartEx(uint32 alignClkDiv);
#define countClk_Start() \
    countClk_StartEx(countClk__PA_DIV_ID)

#else

void countClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void countClk_Stop(void);

void countClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 countClk_GetDividerRegister(void);
uint8  countClk_GetFractionalDividerRegister(void);

#define countClk_Enable()                         countClk_Start()
#define countClk_Disable()                        countClk_Stop()
#define countClk_SetDividerRegister(clkDivider, reset)  \
    countClk_SetFractionalDividerRegister((clkDivider), 0u)
#define countClk_SetDivider(clkDivider)           countClk_SetDividerRegister((clkDivider), 1u)
#define countClk_SetDividerValue(clkDivider)      countClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define countClk_DIV_ID     countClk__DIV_ID

#define countClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define countClk_CTRL_REG   (*(reg32 *)countClk__CTRL_REGISTER)
#define countClk_DIV_REG    (*(reg32 *)countClk__DIV_REGISTER)

#define countClk_CMD_DIV_SHIFT          (0u)
#define countClk_CMD_PA_DIV_SHIFT       (8u)
#define countClk_CMD_DISABLE_SHIFT      (30u)
#define countClk_CMD_ENABLE_SHIFT       (31u)

#define countClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << countClk_CMD_DISABLE_SHIFT))
#define countClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << countClk_CMD_ENABLE_SHIFT))

#define countClk_DIV_FRAC_MASK  (0x000000F8u)
#define countClk_DIV_FRAC_SHIFT (3u)
#define countClk_DIV_INT_MASK   (0xFFFFFF00u)
#define countClk_DIV_INT_SHIFT  (8u)

#else 

#define countClk_DIV_REG        (*(reg32 *)countClk__REGISTER)
#define countClk_ENABLE_REG     countClk_DIV_REG
#define countClk_DIV_FRAC_MASK  countClk__FRAC_MASK
#define countClk_DIV_FRAC_SHIFT (16u)
#define countClk_DIV_INT_MASK   countClk__DIVIDER_MASK
#define countClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_countClk_H) */

/* [] END OF FILE */
