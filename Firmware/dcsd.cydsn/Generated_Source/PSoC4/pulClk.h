/*******************************************************************************
* File Name: pulClk.h
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

#if !defined(CY_CLOCK_pulClk_H)
#define CY_CLOCK_pulClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void pulClk_StartEx(uint32 alignClkDiv);
#define pulClk_Start() \
    pulClk_StartEx(pulClk__PA_DIV_ID)

#else

void pulClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void pulClk_Stop(void);

void pulClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 pulClk_GetDividerRegister(void);
uint8  pulClk_GetFractionalDividerRegister(void);

#define pulClk_Enable()                         pulClk_Start()
#define pulClk_Disable()                        pulClk_Stop()
#define pulClk_SetDividerRegister(clkDivider, reset)  \
    pulClk_SetFractionalDividerRegister((clkDivider), 0u)
#define pulClk_SetDivider(clkDivider)           pulClk_SetDividerRegister((clkDivider), 1u)
#define pulClk_SetDividerValue(clkDivider)      pulClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define pulClk_DIV_ID     pulClk__DIV_ID

#define pulClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define pulClk_CTRL_REG   (*(reg32 *)pulClk__CTRL_REGISTER)
#define pulClk_DIV_REG    (*(reg32 *)pulClk__DIV_REGISTER)

#define pulClk_CMD_DIV_SHIFT          (0u)
#define pulClk_CMD_PA_DIV_SHIFT       (8u)
#define pulClk_CMD_DISABLE_SHIFT      (30u)
#define pulClk_CMD_ENABLE_SHIFT       (31u)

#define pulClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << pulClk_CMD_DISABLE_SHIFT))
#define pulClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << pulClk_CMD_ENABLE_SHIFT))

#define pulClk_DIV_FRAC_MASK  (0x000000F8u)
#define pulClk_DIV_FRAC_SHIFT (3u)
#define pulClk_DIV_INT_MASK   (0xFFFFFF00u)
#define pulClk_DIV_INT_SHIFT  (8u)

#else 

#define pulClk_DIV_REG        (*(reg32 *)pulClk__REGISTER)
#define pulClk_ENABLE_REG     pulClk_DIV_REG
#define pulClk_DIV_FRAC_MASK  pulClk__FRAC_MASK
#define pulClk_DIV_FRAC_SHIFT (16u)
#define pulClk_DIV_INT_MASK   pulClk__DIVIDER_MASK
#define pulClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_pulClk_H) */

/* [] END OF FILE */
