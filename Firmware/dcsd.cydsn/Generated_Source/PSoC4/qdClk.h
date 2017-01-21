/*******************************************************************************
* File Name: qdClk.h
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

#if !defined(CY_CLOCK_qdClk_H)
#define CY_CLOCK_qdClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void qdClk_StartEx(uint32 alignClkDiv);
#define qdClk_Start() \
    qdClk_StartEx(qdClk__PA_DIV_ID)

#else

void qdClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void qdClk_Stop(void);

void qdClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 qdClk_GetDividerRegister(void);
uint8  qdClk_GetFractionalDividerRegister(void);

#define qdClk_Enable()                         qdClk_Start()
#define qdClk_Disable()                        qdClk_Stop()
#define qdClk_SetDividerRegister(clkDivider, reset)  \
    qdClk_SetFractionalDividerRegister((clkDivider), 0u)
#define qdClk_SetDivider(clkDivider)           qdClk_SetDividerRegister((clkDivider), 1u)
#define qdClk_SetDividerValue(clkDivider)      qdClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define qdClk_DIV_ID     qdClk__DIV_ID

#define qdClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define qdClk_CTRL_REG   (*(reg32 *)qdClk__CTRL_REGISTER)
#define qdClk_DIV_REG    (*(reg32 *)qdClk__DIV_REGISTER)

#define qdClk_CMD_DIV_SHIFT          (0u)
#define qdClk_CMD_PA_DIV_SHIFT       (8u)
#define qdClk_CMD_DISABLE_SHIFT      (30u)
#define qdClk_CMD_ENABLE_SHIFT       (31u)

#define qdClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << qdClk_CMD_DISABLE_SHIFT))
#define qdClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << qdClk_CMD_ENABLE_SHIFT))

#define qdClk_DIV_FRAC_MASK  (0x000000F8u)
#define qdClk_DIV_FRAC_SHIFT (3u)
#define qdClk_DIV_INT_MASK   (0xFFFFFF00u)
#define qdClk_DIV_INT_SHIFT  (8u)

#else 

#define qdClk_DIV_REG        (*(reg32 *)qdClk__REGISTER)
#define qdClk_ENABLE_REG     qdClk_DIV_REG
#define qdClk_DIV_FRAC_MASK  qdClk__FRAC_MASK
#define qdClk_DIV_FRAC_SHIFT (16u)
#define qdClk_DIV_INT_MASK   qdClk__DIVIDER_MASK
#define qdClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_qdClk_H) */

/* [] END OF FILE */
