/*******************************************************************************
* File Name: pidClk.h
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

#if !defined(CY_CLOCK_pidClk_H)
#define CY_CLOCK_pidClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void pidClk_StartEx(uint32 alignClkDiv);
#define pidClk_Start() \
    pidClk_StartEx(pidClk__PA_DIV_ID)

#else

void pidClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void pidClk_Stop(void);

void pidClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 pidClk_GetDividerRegister(void);
uint8  pidClk_GetFractionalDividerRegister(void);

#define pidClk_Enable()                         pidClk_Start()
#define pidClk_Disable()                        pidClk_Stop()
#define pidClk_SetDividerRegister(clkDivider, reset)  \
    pidClk_SetFractionalDividerRegister((clkDivider), 0u)
#define pidClk_SetDivider(clkDivider)           pidClk_SetDividerRegister((clkDivider), 1u)
#define pidClk_SetDividerValue(clkDivider)      pidClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define pidClk_DIV_ID     pidClk__DIV_ID

#define pidClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define pidClk_CTRL_REG   (*(reg32 *)pidClk__CTRL_REGISTER)
#define pidClk_DIV_REG    (*(reg32 *)pidClk__DIV_REGISTER)

#define pidClk_CMD_DIV_SHIFT          (0u)
#define pidClk_CMD_PA_DIV_SHIFT       (8u)
#define pidClk_CMD_DISABLE_SHIFT      (30u)
#define pidClk_CMD_ENABLE_SHIFT       (31u)

#define pidClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << pidClk_CMD_DISABLE_SHIFT))
#define pidClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << pidClk_CMD_ENABLE_SHIFT))

#define pidClk_DIV_FRAC_MASK  (0x000000F8u)
#define pidClk_DIV_FRAC_SHIFT (3u)
#define pidClk_DIV_INT_MASK   (0xFFFFFF00u)
#define pidClk_DIV_INT_SHIFT  (8u)

#else 

#define pidClk_DIV_REG        (*(reg32 *)pidClk__REGISTER)
#define pidClk_ENABLE_REG     pidClk_DIV_REG
#define pidClk_DIV_FRAC_MASK  pidClk__FRAC_MASK
#define pidClk_DIV_FRAC_SHIFT (16u)
#define pidClk_DIV_INT_MASK   pidClk__DIVIDER_MASK
#define pidClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_pidClk_H) */

/* [] END OF FILE */
