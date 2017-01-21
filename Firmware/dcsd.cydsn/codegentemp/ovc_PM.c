/*******************************************************************************
* File Name: ovc.c  
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
#include "ovc.h"

static ovc_BACKUP_STRUCT  ovc_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: ovc_Sleep
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
*  \snippet ovc_SUT.c usage_ovc_Sleep_Wakeup
*******************************************************************************/
void ovc_Sleep(void)
{
    #if defined(ovc__PC)
        ovc_backup.pcState = ovc_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            ovc_backup.usbState = ovc_CR1_REG;
            ovc_USB_POWER_REG |= ovc_USBIO_ENTER_SLEEP;
            ovc_CR1_REG &= ovc_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ovc__SIO)
        ovc_backup.sioState = ovc_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        ovc_SIO_REG &= (uint32)(~ovc_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: ovc_Wakeup
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
*  Refer to ovc_Sleep() for an example usage.
*******************************************************************************/
void ovc_Wakeup(void)
{
    #if defined(ovc__PC)
        ovc_PC = ovc_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            ovc_USB_POWER_REG &= ovc_USBIO_EXIT_SLEEP_PH1;
            ovc_CR1_REG = ovc_backup.usbState;
            ovc_USB_POWER_REG &= ovc_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ovc__SIO)
        ovc_SIO_REG = ovc_backup.sioState;
    #endif
}


/* [] END OF FILE */
