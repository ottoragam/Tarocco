/*******************************************************************************
* File Name: Cyclk12.h
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

#if !defined(CY_CLOCK_Cyclk12_H)
#define CY_CLOCK_Cyclk12_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Cyclk12_StartEx(uint32 alignClkDiv);
#define Cyclk12_Start() \
    Cyclk12_StartEx(Cyclk12__PA_DIV_ID)

#else

void Cyclk12_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Cyclk12_Stop(void);

void Cyclk12_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Cyclk12_GetDividerRegister(void);
uint8  Cyclk12_GetFractionalDividerRegister(void);

#define Cyclk12_Enable()                         Cyclk12_Start()
#define Cyclk12_Disable()                        Cyclk12_Stop()
#define Cyclk12_SetDividerRegister(clkDivider, reset)  \
    Cyclk12_SetFractionalDividerRegister((clkDivider), 0u)
#define Cyclk12_SetDivider(clkDivider)           Cyclk12_SetDividerRegister((clkDivider), 1u)
#define Cyclk12_SetDividerValue(clkDivider)      Cyclk12_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Cyclk12_DIV_ID     Cyclk12__DIV_ID

#define Cyclk12_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Cyclk12_CTRL_REG   (*(reg32 *)Cyclk12__CTRL_REGISTER)
#define Cyclk12_DIV_REG    (*(reg32 *)Cyclk12__DIV_REGISTER)

#define Cyclk12_CMD_DIV_SHIFT          (0u)
#define Cyclk12_CMD_PA_DIV_SHIFT       (8u)
#define Cyclk12_CMD_DISABLE_SHIFT      (30u)
#define Cyclk12_CMD_ENABLE_SHIFT       (31u)

#define Cyclk12_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Cyclk12_CMD_DISABLE_SHIFT))
#define Cyclk12_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Cyclk12_CMD_ENABLE_SHIFT))

#define Cyclk12_DIV_FRAC_MASK  (0x000000F8u)
#define Cyclk12_DIV_FRAC_SHIFT (3u)
#define Cyclk12_DIV_INT_MASK   (0xFFFFFF00u)
#define Cyclk12_DIV_INT_SHIFT  (8u)

#else 

#define Cyclk12_DIV_REG        (*(reg32 *)Cyclk12__REGISTER)
#define Cyclk12_ENABLE_REG     Cyclk12_DIV_REG
#define Cyclk12_DIV_FRAC_MASK  Cyclk12__FRAC_MASK
#define Cyclk12_DIV_FRAC_SHIFT (16u)
#define Cyclk12_DIV_INT_MASK   Cyclk12__DIVIDER_MASK
#define Cyclk12_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Cyclk12_H) */

/* [] END OF FILE */
