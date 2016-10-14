/*******************************************************************************
* File Name: ffClk.h
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

#if !defined(CY_CLOCK_ffClk_H)
#define CY_CLOCK_ffClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void ffClk_StartEx(uint32 alignClkDiv);
#define ffClk_Start() \
    ffClk_StartEx(ffClk__PA_DIV_ID)

#else

void ffClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void ffClk_Stop(void);

void ffClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 ffClk_GetDividerRegister(void);
uint8  ffClk_GetFractionalDividerRegister(void);

#define ffClk_Enable()                         ffClk_Start()
#define ffClk_Disable()                        ffClk_Stop()
#define ffClk_SetDividerRegister(clkDivider, reset)  \
    ffClk_SetFractionalDividerRegister((clkDivider), 0u)
#define ffClk_SetDivider(clkDivider)           ffClk_SetDividerRegister((clkDivider), 1u)
#define ffClk_SetDividerValue(clkDivider)      ffClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define ffClk_DIV_ID     ffClk__DIV_ID

#define ffClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define ffClk_CTRL_REG   (*(reg32 *)ffClk__CTRL_REGISTER)
#define ffClk_DIV_REG    (*(reg32 *)ffClk__DIV_REGISTER)

#define ffClk_CMD_DIV_SHIFT          (0u)
#define ffClk_CMD_PA_DIV_SHIFT       (8u)
#define ffClk_CMD_DISABLE_SHIFT      (30u)
#define ffClk_CMD_ENABLE_SHIFT       (31u)

#define ffClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << ffClk_CMD_DISABLE_SHIFT))
#define ffClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << ffClk_CMD_ENABLE_SHIFT))

#define ffClk_DIV_FRAC_MASK  (0x000000F8u)
#define ffClk_DIV_FRAC_SHIFT (3u)
#define ffClk_DIV_INT_MASK   (0xFFFFFF00u)
#define ffClk_DIV_INT_SHIFT  (8u)

#else 

#define ffClk_DIV_REG        (*(reg32 *)ffClk__REGISTER)
#define ffClk_ENABLE_REG     ffClk_DIV_REG
#define ffClk_DIV_FRAC_MASK  ffClk__FRAC_MASK
#define ffClk_DIV_FRAC_SHIFT (16u)
#define ffClk_DIV_INT_MASK   ffClk__DIVIDER_MASK
#define ffClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_ffClk_H) */

/* [] END OF FILE */
