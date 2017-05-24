/*******************************************************************************
* File Name: reset.h  
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

#if !defined(CY_PINS_reset_H) /* Pins reset_H */
#define CY_PINS_reset_H

#include "cytypes.h"
#include "cyfitter.h"
#include "reset_aliases.h"


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
} reset_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   reset_Read(void);
void    reset_Write(uint8 value);
uint8   reset_ReadDataReg(void);
#if defined(reset__PC) || (CY_PSOC4_4200L) 
    void    reset_SetDriveMode(uint8 mode);
#endif
void    reset_SetInterruptMode(uint16 position, uint16 mode);
uint8   reset_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void reset_Sleep(void); 
void reset_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(reset__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define reset_DRIVE_MODE_BITS        (3)
    #define reset_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - reset_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the reset_SetDriveMode() function.
         *  @{
         */
        #define reset_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define reset_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define reset_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define reset_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define reset_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define reset_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define reset_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define reset_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define reset_MASK               reset__MASK
#define reset_SHIFT              reset__SHIFT
#define reset_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in reset_SetInterruptMode() function.
     *  @{
     */
        #define reset_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define reset_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define reset_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define reset_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(reset__SIO)
    #define reset_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(reset__PC) && (CY_PSOC4_4200L)
    #define reset_USBIO_ENABLE               ((uint32)0x80000000u)
    #define reset_USBIO_DISABLE              ((uint32)(~reset_USBIO_ENABLE))
    #define reset_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define reset_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define reset_USBIO_ENTER_SLEEP          ((uint32)((1u << reset_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << reset_USBIO_SUSPEND_DEL_SHIFT)))
    #define reset_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << reset_USBIO_SUSPEND_SHIFT)))
    #define reset_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << reset_USBIO_SUSPEND_DEL_SHIFT)))
    #define reset_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(reset__PC)
    /* Port Configuration */
    #define reset_PC                 (* (reg32 *) reset__PC)
#endif
/* Pin State */
#define reset_PS                     (* (reg32 *) reset__PS)
/* Data Register */
#define reset_DR                     (* (reg32 *) reset__DR)
/* Input Buffer Disable Override */
#define reset_INP_DIS                (* (reg32 *) reset__PC2)

/* Interrupt configuration Registers */
#define reset_INTCFG                 (* (reg32 *) reset__INTCFG)
#define reset_INTSTAT                (* (reg32 *) reset__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define reset_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(reset__SIO)
    #define reset_SIO_REG            (* (reg32 *) reset__SIO)
#endif /* (reset__SIO_CFG) */

/* USBIO registers */
#if !defined(reset__PC) && (CY_PSOC4_4200L)
    #define reset_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define reset_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define reset_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define reset_DRIVE_MODE_SHIFT       (0x00u)
#define reset_DRIVE_MODE_MASK        (0x07u << reset_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins reset_H */


/* [] END OF FILE */
