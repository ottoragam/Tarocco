/*******************************************************************************
* File Name: pulseClk.h
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

#if !defined(CY_CLOCK_pulseClk_H)
#define CY_CLOCK_pulseClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void pulseClk_StartEx(uint32 alignClkDiv);
#define pulseClk_Start() \
    pulseClk_StartEx(pulseClk__PA_DIV_ID)

#else

void pulseClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void pulseClk_Stop(void);

void pulseClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 pulseClk_GetDividerRegister(void);
uint8  pulseClk_GetFractionalDividerRegister(void);

#define pulseClk_Enable()                         pulseClk_Start()
#define pulseClk_Disable()                        pulseClk_Stop()
#define pulseClk_SetDividerRegister(clkDivider, reset)  \
    pulseClk_SetFractionalDividerRegister((clkDivider), 0u)
#define pulseClk_SetDivider(clkDivider)           pulseClk_SetDividerRegister((clkDivider), 1u)
#define pulseClk_SetDividerValue(clkDivider)      pulseClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define pulseClk_DIV_ID     pulseClk__DIV_ID

#define pulseClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define pulseClk_CTRL_REG   (*(reg32 *)pulseClk__CTRL_REGISTER)
#define pulseClk_DIV_REG    (*(reg32 *)pulseClk__DIV_REGISTER)

#define pulseClk_CMD_DIV_SHIFT          (0u)
#define pulseClk_CMD_PA_DIV_SHIFT       (8u)
#define pulseClk_CMD_DISABLE_SHIFT      (30u)
#define pulseClk_CMD_ENABLE_SHIFT       (31u)

#define pulseClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << pulseClk_CMD_DISABLE_SHIFT))
#define pulseClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << pulseClk_CMD_ENABLE_SHIFT))

#define pulseClk_DIV_FRAC_MASK  (0x000000F8u)
#define pulseClk_DIV_FRAC_SHIFT (3u)
#define pulseClk_DIV_INT_MASK   (0xFFFFFF00u)
#define pulseClk_DIV_INT_SHIFT  (8u)

#else 

#define pulseClk_DIV_REG        (*(reg32 *)pulseClk__REGISTER)
#define pulseClk_ENABLE_REG     pulseClk_DIV_REG
#define pulseClk_DIV_FRAC_MASK  pulseClk__FRAC_MASK
#define pulseClk_DIV_FRAC_SHIFT (16u)
#define pulseClk_DIV_INT_MASK   pulseClk__DIVIDER_MASK
#define pulseClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_pulseClk_H) */

/* [] END OF FILE */
