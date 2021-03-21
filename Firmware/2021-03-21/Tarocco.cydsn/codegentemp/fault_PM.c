/*******************************************************************************
* File Name: fault.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "fault.h"

static fault_BACKUP_STRUCT  fault_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: fault_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet fault_SUT.c usage_fault_Sleep_Wakeup
*******************************************************************************/
void fault_Sleep(void)
{
    #if defined(fault__PC)
        fault_backup.pcState = fault_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            fault_backup.usbState = fault_CR1_REG;
            fault_USB_POWER_REG |= fault_USBIO_ENTER_SLEEP;
            fault_CR1_REG &= fault_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(fault__SIO)
        fault_backup.sioState = fault_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        fault_SIO_REG &= (uint32)(~fault_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: fault_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to fault_Sleep() for an example usage.
*******************************************************************************/
void fault_Wakeup(void)
{
    #if defined(fault__PC)
        fault_PC = fault_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            fault_USB_POWER_REG &= fault_USBIO_EXIT_SLEEP_PH1;
            fault_CR1_REG = fault_backup.usbState;
            fault_USB_POWER_REG &= fault_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(fault__SIO)
        fault_SIO_REG = fault_backup.sioState;
    #endif
}


/* [] END OF FILE */
