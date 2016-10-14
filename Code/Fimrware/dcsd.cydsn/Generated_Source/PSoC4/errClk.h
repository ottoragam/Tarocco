/*******************************************************************************
* File Name: errClk.h
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

#if !defined(CY_CLOCK_errClk_H)
#define CY_CLOCK_errClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void errClk_StartEx(uint32 alignClkDiv);
#define errClk_Start() \
    errClk_StartEx(errClk__PA_DIV_ID)

#else

void errClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void errClk_Stop(void);

void errClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 errClk_GetDividerRegister(void);
uint8  errClk_GetFractionalDividerRegister(void);

#define errClk_Enable()                         errClk_Start()
#define errClk_Disable()                        errClk_Stop()
#define errClk_SetDividerRegister(clkDivider, reset)  \
    errClk_SetFractionalDividerRegister((clkDivider), 0u)
#define errClk_SetDivider(clkDivider)           errClk_SetDividerRegister((clkDivider), 1u)
#define errClk_SetDividerValue(clkDivider)      errClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define errClk_DIV_ID     errClk__DIV_ID

#define errClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define errClk_CTRL_REG   (*(reg32 *)errClk__CTRL_REGISTER)
#define errClk_DIV_REG    (*(reg32 *)errClk__DIV_REGISTER)

#define errClk_CMD_DIV_SHIFT          (0u)
#define errClk_CMD_PA_DIV_SHIFT       (8u)
#define errClk_CMD_DISABLE_SHIFT      (30u)
#define errClk_CMD_ENABLE_SHIFT       (31u)

#define errClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << errClk_CMD_DISABLE_SHIFT))
#define errClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << errClk_CMD_ENABLE_SHIFT))

#define errClk_DIV_FRAC_MASK  (0x000000F8u)
#define errClk_DIV_FRAC_SHIFT (3u)
#define errClk_DIV_INT_MASK   (0xFFFFFF00u)
#define errClk_DIV_INT_SHIFT  (8u)

#else 

#define errClk_DIV_REG        (*(reg32 *)errClk__REGISTER)
#define errClk_ENABLE_REG     errClk_DIV_REG
#define errClk_DIV_FRAC_MASK  errClk__FRAC_MASK
#define errClk_DIV_FRAC_SHIFT (16u)
#define errClk_DIV_INT_MASK   errClk__DIVIDER_MASK
#define errClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_errClk_H) */

/* [] END OF FILE */
