/*******************************************************************************
* File Name: speedClk.h
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

#if !defined(CY_CLOCK_speedClk_H)
#define CY_CLOCK_speedClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void speedClk_StartEx(uint32 alignClkDiv);
#define speedClk_Start() \
    speedClk_StartEx(speedClk__PA_DIV_ID)

#else

void speedClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void speedClk_Stop(void);

void speedClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 speedClk_GetDividerRegister(void);
uint8  speedClk_GetFractionalDividerRegister(void);

#define speedClk_Enable()                         speedClk_Start()
#define speedClk_Disable()                        speedClk_Stop()
#define speedClk_SetDividerRegister(clkDivider, reset)  \
    speedClk_SetFractionalDividerRegister((clkDivider), 0u)
#define speedClk_SetDivider(clkDivider)           speedClk_SetDividerRegister((clkDivider), 1u)
#define speedClk_SetDividerValue(clkDivider)      speedClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define speedClk_DIV_ID     speedClk__DIV_ID

#define speedClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define speedClk_CTRL_REG   (*(reg32 *)speedClk__CTRL_REGISTER)
#define speedClk_DIV_REG    (*(reg32 *)speedClk__DIV_REGISTER)

#define speedClk_CMD_DIV_SHIFT          (0u)
#define speedClk_CMD_PA_DIV_SHIFT       (8u)
#define speedClk_CMD_DISABLE_SHIFT      (30u)
#define speedClk_CMD_ENABLE_SHIFT       (31u)

#define speedClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << speedClk_CMD_DISABLE_SHIFT))
#define speedClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << speedClk_CMD_ENABLE_SHIFT))

#define speedClk_DIV_FRAC_MASK  (0x000000F8u)
#define speedClk_DIV_FRAC_SHIFT (3u)
#define speedClk_DIV_INT_MASK   (0xFFFFFF00u)
#define speedClk_DIV_INT_SHIFT  (8u)

#else 

#define speedClk_DIV_REG        (*(reg32 *)speedClk__REGISTER)
#define speedClk_ENABLE_REG     speedClk_DIV_REG
#define speedClk_DIV_FRAC_MASK  speedClk__FRAC_MASK
#define speedClk_DIV_FRAC_SHIFT (16u)
#define speedClk_DIV_INT_MASK   speedClk__DIVIDER_MASK
#define speedClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_speedClk_H) */

/* [] END OF FILE */
