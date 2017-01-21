/*******************************************************************************
* File Name: Cyclk3.h
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

#if !defined(CY_CLOCK_Cyclk3_H)
#define CY_CLOCK_Cyclk3_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Cyclk3_StartEx(uint32 alignClkDiv);
#define Cyclk3_Start() \
    Cyclk3_StartEx(Cyclk3__PA_DIV_ID)

#else

void Cyclk3_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Cyclk3_Stop(void);

void Cyclk3_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Cyclk3_GetDividerRegister(void);
uint8  Cyclk3_GetFractionalDividerRegister(void);

#define Cyclk3_Enable()                         Cyclk3_Start()
#define Cyclk3_Disable()                        Cyclk3_Stop()
#define Cyclk3_SetDividerRegister(clkDivider, reset)  \
    Cyclk3_SetFractionalDividerRegister((clkDivider), 0u)
#define Cyclk3_SetDivider(clkDivider)           Cyclk3_SetDividerRegister((clkDivider), 1u)
#define Cyclk3_SetDividerValue(clkDivider)      Cyclk3_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Cyclk3_DIV_ID     Cyclk3__DIV_ID

#define Cyclk3_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Cyclk3_CTRL_REG   (*(reg32 *)Cyclk3__CTRL_REGISTER)
#define Cyclk3_DIV_REG    (*(reg32 *)Cyclk3__DIV_REGISTER)

#define Cyclk3_CMD_DIV_SHIFT          (0u)
#define Cyclk3_CMD_PA_DIV_SHIFT       (8u)
#define Cyclk3_CMD_DISABLE_SHIFT      (30u)
#define Cyclk3_CMD_ENABLE_SHIFT       (31u)

#define Cyclk3_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Cyclk3_CMD_DISABLE_SHIFT))
#define Cyclk3_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Cyclk3_CMD_ENABLE_SHIFT))

#define Cyclk3_DIV_FRAC_MASK  (0x000000F8u)
#define Cyclk3_DIV_FRAC_SHIFT (3u)
#define Cyclk3_DIV_INT_MASK   (0xFFFFFF00u)
#define Cyclk3_DIV_INT_SHIFT  (8u)

#else 

#define Cyclk3_DIV_REG        (*(reg32 *)Cyclk3__REGISTER)
#define Cyclk3_ENABLE_REG     Cyclk3_DIV_REG
#define Cyclk3_DIV_FRAC_MASK  Cyclk3__FRAC_MASK
#define Cyclk3_DIV_FRAC_SHIFT (16u)
#define Cyclk3_DIV_INT_MASK   Cyclk3__DIVIDER_MASK
#define Cyclk3_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Cyclk3_H) */

/* [] END OF FILE */
