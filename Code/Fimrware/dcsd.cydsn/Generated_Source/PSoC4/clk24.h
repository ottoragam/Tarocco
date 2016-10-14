/*******************************************************************************
* File Name: clk24.h
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

#if !defined(CY_CLOCK_clk24_H)
#define CY_CLOCK_clk24_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void clk24_StartEx(uint32 alignClkDiv);
#define clk24_Start() \
    clk24_StartEx(clk24__PA_DIV_ID)

#else

void clk24_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void clk24_Stop(void);

void clk24_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 clk24_GetDividerRegister(void);
uint8  clk24_GetFractionalDividerRegister(void);

#define clk24_Enable()                         clk24_Start()
#define clk24_Disable()                        clk24_Stop()
#define clk24_SetDividerRegister(clkDivider, reset)  \
    clk24_SetFractionalDividerRegister((clkDivider), 0u)
#define clk24_SetDivider(clkDivider)           clk24_SetDividerRegister((clkDivider), 1u)
#define clk24_SetDividerValue(clkDivider)      clk24_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define clk24_DIV_ID     clk24__DIV_ID

#define clk24_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define clk24_CTRL_REG   (*(reg32 *)clk24__CTRL_REGISTER)
#define clk24_DIV_REG    (*(reg32 *)clk24__DIV_REGISTER)

#define clk24_CMD_DIV_SHIFT          (0u)
#define clk24_CMD_PA_DIV_SHIFT       (8u)
#define clk24_CMD_DISABLE_SHIFT      (30u)
#define clk24_CMD_ENABLE_SHIFT       (31u)

#define clk24_CMD_DISABLE_MASK       ((uint32)((uint32)1u << clk24_CMD_DISABLE_SHIFT))
#define clk24_CMD_ENABLE_MASK        ((uint32)((uint32)1u << clk24_CMD_ENABLE_SHIFT))

#define clk24_DIV_FRAC_MASK  (0x000000F8u)
#define clk24_DIV_FRAC_SHIFT (3u)
#define clk24_DIV_INT_MASK   (0xFFFFFF00u)
#define clk24_DIV_INT_SHIFT  (8u)

#else 

#define clk24_DIV_REG        (*(reg32 *)clk24__REGISTER)
#define clk24_ENABLE_REG     clk24_DIV_REG
#define clk24_DIV_FRAC_MASK  clk24__FRAC_MASK
#define clk24_DIV_FRAC_SHIFT (16u)
#define clk24_DIV_INT_MASK   clk24__DIVIDER_MASK
#define clk24_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_clk24_H) */

/* [] END OF FILE */
