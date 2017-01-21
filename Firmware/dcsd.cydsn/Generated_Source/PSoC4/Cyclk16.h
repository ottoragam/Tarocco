/*******************************************************************************
* File Name: Cyclk16.h
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

#if !defined(CY_CLOCK_Cyclk16_H)
#define CY_CLOCK_Cyclk16_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Cyclk16_StartEx(uint32 alignClkDiv);
#define Cyclk16_Start() \
    Cyclk16_StartEx(Cyclk16__PA_DIV_ID)

#else

void Cyclk16_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Cyclk16_Stop(void);

void Cyclk16_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Cyclk16_GetDividerRegister(void);
uint8  Cyclk16_GetFractionalDividerRegister(void);

#define Cyclk16_Enable()                         Cyclk16_Start()
#define Cyclk16_Disable()                        Cyclk16_Stop()
#define Cyclk16_SetDividerRegister(clkDivider, reset)  \
    Cyclk16_SetFractionalDividerRegister((clkDivider), 0u)
#define Cyclk16_SetDivider(clkDivider)           Cyclk16_SetDividerRegister((clkDivider), 1u)
#define Cyclk16_SetDividerValue(clkDivider)      Cyclk16_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Cyclk16_DIV_ID     Cyclk16__DIV_ID

#define Cyclk16_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Cyclk16_CTRL_REG   (*(reg32 *)Cyclk16__CTRL_REGISTER)
#define Cyclk16_DIV_REG    (*(reg32 *)Cyclk16__DIV_REGISTER)

#define Cyclk16_CMD_DIV_SHIFT          (0u)
#define Cyclk16_CMD_PA_DIV_SHIFT       (8u)
#define Cyclk16_CMD_DISABLE_SHIFT      (30u)
#define Cyclk16_CMD_ENABLE_SHIFT       (31u)

#define Cyclk16_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Cyclk16_CMD_DISABLE_SHIFT))
#define Cyclk16_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Cyclk16_CMD_ENABLE_SHIFT))

#define Cyclk16_DIV_FRAC_MASK  (0x000000F8u)
#define Cyclk16_DIV_FRAC_SHIFT (3u)
#define Cyclk16_DIV_INT_MASK   (0xFFFFFF00u)
#define Cyclk16_DIV_INT_SHIFT  (8u)

#else 

#define Cyclk16_DIV_REG        (*(reg32 *)Cyclk16__REGISTER)
#define Cyclk16_ENABLE_REG     Cyclk16_DIV_REG
#define Cyclk16_DIV_FRAC_MASK  Cyclk16__FRAC_MASK
#define Cyclk16_DIV_FRAC_SHIFT (16u)
#define Cyclk16_DIV_INT_MASK   Cyclk16__DIVIDER_MASK
#define Cyclk16_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Cyclk16_H) */

/* [] END OF FILE */
