/*******************************************************************************
* File Name: B.c  
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
#include "B.h"

static B_BACKUP_STRUCT  B_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: B_Sleep
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
*  \snippet B_SUT.c usage_B_Sleep_Wakeup
*******************************************************************************/
void B_Sleep(void)
{
    #if defined(B__PC)
        B_backup.pcState = B_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            B_backup.usbState = B_CR1_REG;
            B_USB_POWER_REG |= B_USBIO_ENTER_SLEEP;
            B_CR1_REG &= B_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(B__SIO)
        B_backup.sioState = B_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        B_SIO_REG &= (uint32)(~B_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: B_Wakeup
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
*  Refer to B_Sleep() for an example usage.
*******************************************************************************/
void B_Wakeup(void)
{
    #if defined(B__PC)
        B_PC = B_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            B_USB_POWER_REG &= B_USBIO_EXIT_SLEEP_PH1;
            B_CR1_REG = B_backup.usbState;
            B_USB_POWER_REG &= B_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(B__SIO)
        B_SIO_REG = B_backup.sioState;
    #endif
}


/* [] END OF FILE */
