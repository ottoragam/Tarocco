/*******************************************************************************
* File Name: clk12.c
* Version 2.20
*
*  Description:
*   Provides system API for the clocking, interrupts and watchdog timer.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <cydevice_trm.h>
#include "clk12.h"

#if defined CYREG_PERI_DIV_CMD

/*******************************************************************************
* Function Name: clk12_StartEx
********************************************************************************
*
* Summary:
*  Starts the clock, aligned to the specified running clock.
*
* Parameters:
*  alignClkDiv:  The divider to which phase alignment is performed when the
*    clock is started.
*
* Returns:
*  None
*
*******************************************************************************/
void clk12_StartEx(uint32 alignClkDiv)
{
    /* Make sure any previous start command has finished. */
    while((clk12_CMD_REG & clk12_CMD_ENABLE_MASK) != 0u)
    {
    }
    
    /* Specify the target divider and it's alignment divider, and enable. */
    clk12_CMD_REG =
        ((uint32)clk12__DIV_ID << clk12_CMD_DIV_SHIFT)|
        (alignClkDiv << clk12_CMD_PA_DIV_SHIFT) |
        (uint32)clk12_CMD_ENABLE_MASK;
}

#else

/*******************************************************************************
* Function Name: clk12_Start
********************************************************************************
*
* Summary:
*  Starts the clock.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/

void clk12_Start(void)
{
    /* Set the bit to enable the clock. */
    clk12_ENABLE_REG |= clk12__ENABLE_MASK;
}

#endif /* CYREG_PERI_DIV_CMD */


/*******************************************************************************
* Function Name: clk12_Stop
********************************************************************************
*
* Summary:
*  Stops the clock and returns immediately. This API does not require the
*  source clock to be running but may return before the hardware is actually
*  disabled.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/
void clk12_Stop(void)
{
#if defined CYREG_PERI_DIV_CMD

    /* Make sure any previous start command has finished. */
    while((clk12_CMD_REG & clk12_CMD_ENABLE_MASK) != 0u)
    {
    }
    
    /* Specify the target divider and it's alignment divider, and disable. */
    clk12_CMD_REG =
        ((uint32)clk12__DIV_ID << clk12_CMD_DIV_SHIFT)|
        ((uint32)clk12_CMD_DISABLE_MASK);

#else

    /* Clear the bit to disable the clock. */
    clk12_ENABLE_REG &= (uint32)(~clk12__ENABLE_MASK);
    
#endif /* CYREG_PERI_DIV_CMD */
}


/*******************************************************************************
* Function Name: clk12_SetFractionalDividerRegister
********************************************************************************
*
* Summary:
*  Modifies the clock divider and the fractional divider.
*
* Parameters:
*  clkDivider:  Divider register value (0-65535). This value is NOT the
*    divider; the clock hardware divides by clkDivider plus one. For example,
*    to divide the clock by 2, this parameter should be set to 1.
*  fracDivider:  Fractional Divider register value (0-31).
* Returns:
*  None
*
*******************************************************************************/
void clk12_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional)
{
    uint32 maskVal;
    uint32 regVal;
    
#if defined (clk12__FRAC_MASK) || defined (CYREG_PERI_DIV_CMD)
    
	/* get all but divider bits */
    maskVal = clk12_DIV_REG & 
                    (uint32)(~(uint32)(clk12_DIV_INT_MASK | clk12_DIV_FRAC_MASK)); 
	/* combine mask and new divider vals into 32-bit value */
    regVal = maskVal |
        ((uint32)((uint32)clkDivider <<  clk12_DIV_INT_SHIFT) & clk12_DIV_INT_MASK) |
        ((uint32)((uint32)clkFractional << clk12_DIV_FRAC_SHIFT) & clk12_DIV_FRAC_MASK);
    
#else
    /* get all but integer divider bits */
    maskVal = clk12_DIV_REG & (uint32)(~(uint32)clk12__DIVIDER_MASK);
    /* combine mask and new divider val into 32-bit value */
    regVal = clkDivider | maskVal;
    
#endif /* clk12__FRAC_MASK || CYREG_PERI_DIV_CMD */

    clk12_DIV_REG = regVal;
}


/*******************************************************************************
* Function Name: clk12_GetDividerRegister
********************************************************************************
*
* Summary:
*  Gets the clock divider register value.
*
* Parameters:
*  None
*
* Returns:
*  Divide value of the clock minus 1. For example, if the clock is set to
*  divide by 2, the return value will be 1.
*
*******************************************************************************/
uint16 clk12_GetDividerRegister(void)
{
    return (uint16)((clk12_DIV_REG & clk12_DIV_INT_MASK)
        >> clk12_DIV_INT_SHIFT);
}


/*******************************************************************************
* Function Name: clk12_GetFractionalDividerRegister
********************************************************************************
*
* Summary:
*  Gets the clock fractional divider register value.
*
* Parameters:
*  None
*
* Returns:
*  Fractional Divide value of the clock
*  0 if the fractional divider is not in use.
*
*******************************************************************************/
uint8 clk12_GetFractionalDividerRegister(void)
{
#if defined (clk12__FRAC_MASK)
    /* return fractional divider bits */
    return (uint8)((clk12_DIV_REG & clk12_DIV_FRAC_MASK)
        >> clk12_DIV_FRAC_SHIFT);
#else
    return 0u;
#endif /* clk12__FRAC_MASK */
}


/* [] END OF FILE */
