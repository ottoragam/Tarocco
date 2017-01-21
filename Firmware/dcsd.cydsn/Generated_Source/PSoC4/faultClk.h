/*******************************************************************************
* File Name: faultClk.h
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

#if !defined(CY_CLOCK_faultClk_H)
#define CY_CLOCK_faultClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void faultClk_StartEx(uint32 alignClkDiv);
#define faultClk_Start() \
    faultClk_StartEx(faultClk__PA_DIV_ID)

#else

void faultClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void faultClk_Stop(void);

void faultClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 faultClk_GetDividerRegister(void);
uint8  faultClk_GetFractionalDividerRegister(void);

#define faultClk_Enable()                         faultClk_Start()
#define faultClk_Disable()                        faultClk_Stop()
#define faultClk_SetDividerRegister(clkDivider, reset)  \
    faultClk_SetFractionalDividerRegister((clkDivider), 0u)
#define faultClk_SetDivider(clkDivider)           faultClk_SetDividerRegister((clkDivider), 1u)
#define faultClk_SetDividerValue(clkDivider)      faultClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define faultClk_DIV_ID     faultClk__DIV_ID

#define faultClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define faultClk_CTRL_REG   (*(reg32 *)faultClk__CTRL_REGISTER)
#define faultClk_DIV_REG    (*(reg32 *)faultClk__DIV_REGISTER)

#define faultClk_CMD_DIV_SHIFT          (0u)
#define faultClk_CMD_PA_DIV_SHIFT       (8u)
#define faultClk_CMD_DISABLE_SHIFT      (30u)
#define faultClk_CMD_ENABLE_SHIFT       (31u)

#define faultClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << faultClk_CMD_DISABLE_SHIFT))
#define faultClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << faultClk_CMD_ENABLE_SHIFT))

#define faultClk_DIV_FRAC_MASK  (0x000000F8u)
#define faultClk_DIV_FRAC_SHIFT (3u)
#define faultClk_DIV_INT_MASK   (0xFFFFFF00u)
#define faultClk_DIV_INT_SHIFT  (8u)

#else 

#define faultClk_DIV_REG        (*(reg32 *)faultClk__REGISTER)
#define faultClk_ENABLE_REG     faultClk_DIV_REG
#define faultClk_DIV_FRAC_MASK  faultClk__FRAC_MASK
#define faultClk_DIV_FRAC_SHIFT (16u)
#define faultClk_DIV_INT_MASK   faultClk__DIVIDER_MASK
#define faultClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_faultClk_H) */

/* [] END OF FILE */
