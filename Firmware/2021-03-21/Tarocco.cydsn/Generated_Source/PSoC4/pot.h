/*******************************************************************************
* File Name: pot.h  
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

#if !defined(CY_PINS_pot_H) /* Pins pot_H */
#define CY_PINS_pot_H

#include "cytypes.h"
#include "cyfitter.h"
#include "pot_aliases.h"


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
} pot_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   pot_Read(void);
void    pot_Write(uint8 value);
uint8   pot_ReadDataReg(void);
#if defined(pot__PC) || (CY_PSOC4_4200L) 
    void    pot_SetDriveMode(uint8 mode);
#endif
void    pot_SetInterruptMode(uint16 position, uint16 mode);
uint8   pot_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void pot_Sleep(void); 
void pot_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(pot__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define pot_DRIVE_MODE_BITS        (3)
    #define pot_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - pot_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the pot_SetDriveMode() function.
         *  @{
         */
        #define pot_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define pot_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define pot_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define pot_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define pot_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define pot_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define pot_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define pot_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define pot_MASK               pot__MASK
#define pot_SHIFT              pot__SHIFT
#define pot_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pot_SetInterruptMode() function.
     *  @{
     */
        #define pot_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define pot_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define pot_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define pot_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(pot__SIO)
    #define pot_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(pot__PC) && (CY_PSOC4_4200L)
    #define pot_USBIO_ENABLE               ((uint32)0x80000000u)
    #define pot_USBIO_DISABLE              ((uint32)(~pot_USBIO_ENABLE))
    #define pot_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define pot_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define pot_USBIO_ENTER_SLEEP          ((uint32)((1u << pot_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << pot_USBIO_SUSPEND_DEL_SHIFT)))
    #define pot_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << pot_USBIO_SUSPEND_SHIFT)))
    #define pot_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << pot_USBIO_SUSPEND_DEL_SHIFT)))
    #define pot_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(pot__PC)
    /* Port Configuration */
    #define pot_PC                 (* (reg32 *) pot__PC)
#endif
/* Pin State */
#define pot_PS                     (* (reg32 *) pot__PS)
/* Data Register */
#define pot_DR                     (* (reg32 *) pot__DR)
/* Input Buffer Disable Override */
#define pot_INP_DIS                (* (reg32 *) pot__PC2)

/* Interrupt configuration Registers */
#define pot_INTCFG                 (* (reg32 *) pot__INTCFG)
#define pot_INTSTAT                (* (reg32 *) pot__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define pot_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(pot__SIO)
    #define pot_SIO_REG            (* (reg32 *) pot__SIO)
#endif /* (pot__SIO_CFG) */

/* USBIO registers */
#if !defined(pot__PC) && (CY_PSOC4_4200L)
    #define pot_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define pot_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define pot_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define pot_DRIVE_MODE_SHIFT       (0x00u)
#define pot_DRIVE_MODE_MASK        (0x07u << pot_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins pot_H */


/* [] END OF FILE */
