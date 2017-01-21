/*******************************************************************************
* File Name: encClk.h
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

#if !defined(CY_CLOCK_encClk_H)
#define CY_CLOCK_encClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void encClk_StartEx(uint32 alignClkDiv);
#define encClk_Start() \
    encClk_StartEx(encClk__PA_DIV_ID)

#else

void encClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void encClk_Stop(void);

void encClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 encClk_GetDividerRegister(void);
uint8  encClk_GetFractionalDividerRegister(void);

#define encClk_Enable()                         encClk_Start()
#define encClk_Disable()                        encClk_Stop()
#define encClk_SetDividerRegister(clkDivider, reset)  \
    encClk_SetFractionalDividerRegister((clkDivider), 0u)
#define encClk_SetDivider(clkDivider)           encClk_SetDividerRegister((clkDivider), 1u)
#define encClk_SetDividerValue(clkDivider)      encClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define encClk_DIV_ID     encClk__DIV_ID

#define encClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define encClk_CTRL_REG   (*(reg32 *)encClk__CTRL_REGISTER)
#define encClk_DIV_REG    (*(reg32 *)encClk__DIV_REGISTER)

#define encClk_CMD_DIV_SHIFT          (0u)
#define encClk_CMD_PA_DIV_SHIFT       (8u)
#define encClk_CMD_DISABLE_SHIFT      (30u)
#define encClk_CMD_ENABLE_SHIFT       (31u)

#define encClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << encClk_CMD_DISABLE_SHIFT))
#define encClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << encClk_CMD_ENABLE_SHIFT))

#define encClk_DIV_FRAC_MASK  (0x000000F8u)
#define encClk_DIV_FRAC_SHIFT (3u)
#define encClk_DIV_INT_MASK   (0xFFFFFF00u)
#define encClk_DIV_INT_SHIFT  (8u)

#else 

#define encClk_DIV_REG        (*(reg32 *)encClk__REGISTER)
#define encClk_ENABLE_REG     encClk_DIV_REG
#define encClk_DIV_FRAC_MASK  encClk__FRAC_MASK
#define encClk_DIV_FRAC_SHIFT (16u)
#define encClk_DIV_INT_MASK   encClk__DIVIDER_MASK
#define encClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_encClk_H) */

/* [] END OF FILE */
