/*******************************************************************************
* File Name: phase.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_phase_H) /* Pins phase_H */
#define CY_PINS_phase_H

#include "cytypes.h"
#include "cyfitter.h"
#include "phase_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} phase_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   phase_Read(void);
void    phase_Write(uint8 value);
uint8   phase_ReadDataReg(void);
#if defined(phase__PC) || (CY_PSOC4_4200L) 
    void    phase_SetDriveMode(uint8 mode);
#endif
void    phase_SetInterruptMode(uint16 position, uint16 mode);
uint8   phase_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void phase_Sleep(void); 
void phase_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(phase__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define phase_DRIVE_MODE_BITS        (3)
    #define phase_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - phase_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the phase_SetDriveMode() function.
         *  @{
         */
        #define phase_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define phase_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define phase_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define phase_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define phase_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define phase_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define phase_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define phase_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define phase_MASK               phase__MASK
#define phase_SHIFT              phase__SHIFT
#define phase_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in phase_SetInterruptMode() function.
     *  @{
     */
        #define phase_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define phase_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define phase_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define phase_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(phase__SIO)
    #define phase_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(phase__PC) && (CY_PSOC4_4200L)
    #define phase_USBIO_ENABLE               ((uint32)0x80000000u)
    #define phase_USBIO_DISABLE              ((uint32)(~phase_USBIO_ENABLE))
    #define phase_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define phase_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define phase_USBIO_ENTER_SLEEP          ((uint32)((1u << phase_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << phase_USBIO_SUSPEND_DEL_SHIFT)))
    #define phase_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << phase_USBIO_SUSPEND_SHIFT)))
    #define phase_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << phase_USBIO_SUSPEND_DEL_SHIFT)))
    #define phase_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(phase__PC)
    /* Port Configuration */
    #define phase_PC                 (* (reg32 *) phase__PC)
#endif
/* Pin State */
#define phase_PS                     (* (reg32 *) phase__PS)
/* Data Register */
#define phase_DR                     (* (reg32 *) phase__DR)
/* Input Buffer Disable Override */
#define phase_INP_DIS                (* (reg32 *) phase__PC2)

/* Interrupt configuration Registers */
#define phase_INTCFG                 (* (reg32 *) phase__INTCFG)
#define phase_INTSTAT                (* (reg32 *) phase__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define phase_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(phase__SIO)
    #define phase_SIO_REG            (* (reg32 *) phase__SIO)
#endif /* (phase__SIO_CFG) */

/* USBIO registers */
#if !defined(phase__PC) && (CY_PSOC4_4200L)
    #define phase_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define phase_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define phase_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define phase_DRIVE_MODE_SHIFT       (0x00u)
#define phase_DRIVE_MODE_MASK        (0x07u << phase_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins phase_H */


/* [] END OF FILE */
