/*******************************************************************************
* File Name: clkenc.h
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

#if !defined(CY_CLOCK_clkenc_H)
#define CY_CLOCK_clkenc_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void clkenc_StartEx(uint32 alignClkDiv);
#define clkenc_Start() \
    clkenc_StartEx(clkenc__PA_DIV_ID)

#else

void clkenc_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void clkenc_Stop(void);

void clkenc_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 clkenc_GetDividerRegister(void);
uint8  clkenc_GetFractionalDividerRegister(void);

#define clkenc_Enable()                         clkenc_Start()
#define clkenc_Disable()                        clkenc_Stop()
#define clkenc_SetDividerRegister(clkDivider, reset)  \
    clkenc_SetFractionalDividerRegister((clkDivider), 0u)
#define clkenc_SetDivider(clkDivider)           clkenc_SetDividerRegister((clkDivider), 1u)
#define clkenc_SetDividerValue(clkDivider)      clkenc_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define clkenc_DIV_ID     clkenc__DIV_ID

#define clkenc_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define clkenc_CTRL_REG   (*(reg32 *)clkenc__CTRL_REGISTER)
#define clkenc_DIV_REG    (*(reg32 *)clkenc__DIV_REGISTER)

#define clkenc_CMD_DIV_SHIFT          (0u)
#define clkenc_CMD_PA_DIV_SHIFT       (8u)
#define clkenc_CMD_DISABLE_SHIFT      (30u)
#define clkenc_CMD_ENABLE_SHIFT       (31u)

#define clkenc_CMD_DISABLE_MASK       ((uint32)((uint32)1u << clkenc_CMD_DISABLE_SHIFT))
#define clkenc_CMD_ENABLE_MASK        ((uint32)((uint32)1u << clkenc_CMD_ENABLE_SHIFT))

#define clkenc_DIV_FRAC_MASK  (0x000000F8u)
#define clkenc_DIV_FRAC_SHIFT (3u)
#define clkenc_DIV_INT_MASK   (0xFFFFFF00u)
#define clkenc_DIV_INT_SHIFT  (8u)

#else 

#define clkenc_DIV_REG        (*(reg32 *)clkenc__REGISTER)
#define clkenc_ENABLE_REG     clkenc_DIV_REG
#define clkenc_DIV_FRAC_MASK  clkenc__FRAC_MASK
#define clkenc_DIV_FRAC_SHIFT (16u)
#define clkenc_DIV_INT_MASK   clkenc__DIVIDER_MASK
#define clkenc_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_clkenc_H) */

/* [] END OF FILE */
