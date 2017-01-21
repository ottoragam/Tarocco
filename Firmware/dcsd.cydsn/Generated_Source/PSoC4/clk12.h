/*******************************************************************************
* File Name: clk12.h
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

#if !defined(CY_CLOCK_clk12_H)
#define CY_CLOCK_clk12_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void clk12_StartEx(uint32 alignClkDiv);
#define clk12_Start() \
    clk12_StartEx(clk12__PA_DIV_ID)

#else

void clk12_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void clk12_Stop(void);

void clk12_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 clk12_GetDividerRegister(void);
uint8  clk12_GetFractionalDividerRegister(void);

#define clk12_Enable()                         clk12_Start()
#define clk12_Disable()                        clk12_Stop()
#define clk12_SetDividerRegister(clkDivider, reset)  \
    clk12_SetFractionalDividerRegister((clkDivider), 0u)
#define clk12_SetDivider(clkDivider)           clk12_SetDividerRegister((clkDivider), 1u)
#define clk12_SetDividerValue(clkDivider)      clk12_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define clk12_DIV_ID     clk12__DIV_ID

#define clk12_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define clk12_CTRL_REG   (*(reg32 *)clk12__CTRL_REGISTER)
#define clk12_DIV_REG    (*(reg32 *)clk12__DIV_REGISTER)

#define clk12_CMD_DIV_SHIFT          (0u)
#define clk12_CMD_PA_DIV_SHIFT       (8u)
#define clk12_CMD_DISABLE_SHIFT      (30u)
#define clk12_CMD_ENABLE_SHIFT       (31u)

#define clk12_CMD_DISABLE_MASK       ((uint32)((uint32)1u << clk12_CMD_DISABLE_SHIFT))
#define clk12_CMD_ENABLE_MASK        ((uint32)((uint32)1u << clk12_CMD_ENABLE_SHIFT))

#define clk12_DIV_FRAC_MASK  (0x000000F8u)
#define clk12_DIV_FRAC_SHIFT (3u)
#define clk12_DIV_INT_MASK   (0xFFFFFF00u)
#define clk12_DIV_INT_SHIFT  (8u)

#else 

#define clk12_DIV_REG        (*(reg32 *)clk12__REGISTER)
#define clk12_ENABLE_REG     clk12_DIV_REG
#define clk12_DIV_FRAC_MASK  clk12__FRAC_MASK
#define clk12_DIV_FRAC_SHIFT (16u)
#define clk12_DIV_INT_MASK   clk12__DIVIDER_MASK
#define clk12_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_clk12_H) */

/* [] END OF FILE */
