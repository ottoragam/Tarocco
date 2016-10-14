/*******************************************************************************
* File Name: qdecClk.h
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

#if !defined(CY_CLOCK_qdecClk_H)
#define CY_CLOCK_qdecClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void qdecClk_StartEx(uint32 alignClkDiv);
#define qdecClk_Start() \
    qdecClk_StartEx(qdecClk__PA_DIV_ID)

#else

void qdecClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void qdecClk_Stop(void);

void qdecClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 qdecClk_GetDividerRegister(void);
uint8  qdecClk_GetFractionalDividerRegister(void);

#define qdecClk_Enable()                         qdecClk_Start()
#define qdecClk_Disable()                        qdecClk_Stop()
#define qdecClk_SetDividerRegister(clkDivider, reset)  \
    qdecClk_SetFractionalDividerRegister((clkDivider), 0u)
#define qdecClk_SetDivider(clkDivider)           qdecClk_SetDividerRegister((clkDivider), 1u)
#define qdecClk_SetDividerValue(clkDivider)      qdecClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define qdecClk_DIV_ID     qdecClk__DIV_ID

#define qdecClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define qdecClk_CTRL_REG   (*(reg32 *)qdecClk__CTRL_REGISTER)
#define qdecClk_DIV_REG    (*(reg32 *)qdecClk__DIV_REGISTER)

#define qdecClk_CMD_DIV_SHIFT          (0u)
#define qdecClk_CMD_PA_DIV_SHIFT       (8u)
#define qdecClk_CMD_DISABLE_SHIFT      (30u)
#define qdecClk_CMD_ENABLE_SHIFT       (31u)

#define qdecClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << qdecClk_CMD_DISABLE_SHIFT))
#define qdecClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << qdecClk_CMD_ENABLE_SHIFT))

#define qdecClk_DIV_FRAC_MASK  (0x000000F8u)
#define qdecClk_DIV_FRAC_SHIFT (3u)
#define qdecClk_DIV_INT_MASK   (0xFFFFFF00u)
#define qdecClk_DIV_INT_SHIFT  (8u)

#else 

#define qdecClk_DIV_REG        (*(reg32 *)qdecClk__REGISTER)
#define qdecClk_ENABLE_REG     qdecClk_DIV_REG
#define qdecClk_DIV_FRAC_MASK  qdecClk__FRAC_MASK
#define qdecClk_DIV_FRAC_SHIFT (16u)
#define qdecClk_DIV_INT_MASK   qdecClk__DIVIDER_MASK
#define qdecClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_qdecClk_H) */

/* [] END OF FILE */
