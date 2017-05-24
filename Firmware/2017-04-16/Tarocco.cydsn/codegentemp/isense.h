/*******************************************************************************
* File Name: isense.h  
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

#if !defined(CY_PINS_isense_H) /* Pins isense_H */
#define CY_PINS_isense_H

#include "cytypes.h"
#include "cyfitter.h"
#include "isense_aliases.h"


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
} isense_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   isense_Read(void);
void    isense_Write(uint8 value);
uint8   isense_ReadDataReg(void);
#if defined(isense__PC) || (CY_PSOC4_4200L) 
    void    isense_SetDriveMode(uint8 mode);
#endif
void    isense_SetInterruptMode(uint16 position, uint16 mode);
uint8   isense_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void isense_Sleep(void); 
void isense_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(isense__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define isense_DRIVE_MODE_BITS        (3)
    #define isense_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - isense_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the isense_SetDriveMode() function.
         *  @{
         */
        #define isense_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define isense_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define isense_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define isense_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define isense_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define isense_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define isense_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define isense_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define isense_MASK               isense__MASK
#define isense_SHIFT              isense__SHIFT
#define isense_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in isense_SetInterruptMode() function.
     *  @{
     */
        #define isense_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define isense_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define isense_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define isense_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(isense__SIO)
    #define isense_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(isense__PC) && (CY_PSOC4_4200L)
    #define isense_USBIO_ENABLE               ((uint32)0x80000000u)
    #define isense_USBIO_DISABLE              ((uint32)(~isense_USBIO_ENABLE))
    #define isense_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define isense_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define isense_USBIO_ENTER_SLEEP          ((uint32)((1u << isense_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << isense_USBIO_SUSPEND_DEL_SHIFT)))
    #define isense_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << isense_USBIO_SUSPEND_SHIFT)))
    #define isense_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << isense_USBIO_SUSPEND_DEL_SHIFT)))
    #define isense_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(isense__PC)
    /* Port Configuration */
    #define isense_PC                 (* (reg32 *) isense__PC)
#endif
/* Pin State */
#define isense_PS                     (* (reg32 *) isense__PS)
/* Data Register */
#define isense_DR                     (* (reg32 *) isense__DR)
/* Input Buffer Disable Override */
#define isense_INP_DIS                (* (reg32 *) isense__PC2)

/* Interrupt configuration Registers */
#define isense_INTCFG                 (* (reg32 *) isense__INTCFG)
#define isense_INTSTAT                (* (reg32 *) isense__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define isense_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(isense__SIO)
    #define isense_SIO_REG            (* (reg32 *) isense__SIO)
#endif /* (isense__SIO_CFG) */

/* USBIO registers */
#if !defined(isense__PC) && (CY_PSOC4_4200L)
    #define isense_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define isense_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define isense_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define isense_DRIVE_MODE_SHIFT       (0x00u)
#define isense_DRIVE_MODE_MASK        (0x07u << isense_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins isense_H */


/* [] END OF FILE */
