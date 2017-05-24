/*******************************************************************************
* File Name: sleep.c  
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
#include "sleep.h"

static sleep_BACKUP_STRUCT  sleep_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: sleep_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
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
*  \snippet sleep_SUT.c usage_sleep_Sleep_Wakeup
*******************************************************************************/
void sleep_Sleep(void)
{
    #if defined(sleep__PC)
        sleep_backup.pcState = sleep_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            sleep_backup.usbState = sleep_CR1_REG;
            sleep_USB_POWER_REG |= sleep_USBIO_ENTER_SLEEP;
            sleep_CR1_REG &= sleep_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(sleep__SIO)
        sleep_backup.sioState = sleep_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        sleep_SIO_REG &= (uint32)(~sleep_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: sleep_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to sleep_Sleep() for an example usage.
*******************************************************************************/
void sleep_Wakeup(void)
{
    #if defined(sleep__PC)
        sleep_PC = sleep_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            sleep_USB_POWER_REG &= sleep_USBIO_EXIT_SLEEP_PH1;
            sleep_CR1_REG = sleep_backup.usbState;
            sleep_USB_POWER_REG &= sleep_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(sleep__SIO)
        sleep_SIO_REG = sleep_backup.sioState;
    #endif
}


/* [] END OF FILE */
