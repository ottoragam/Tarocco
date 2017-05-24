/*******************************************************************************
* File Name: error.h  
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

#if !defined(CY_PINS_error_H) /* Pins error_H */
#define CY_PINS_error_H

#include "cytypes.h"
#include "cyfitter.h"
#include "error_aliases.h"


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
} error_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   error_Read(void);
void    error_Write(uint8 value);
uint8   error_ReadDataReg(void);
#if defined(error__PC) || (CY_PSOC4_4200L) 
    void    error_SetDriveMode(uint8 mode);
#endif
void    error_SetInterruptMode(uint16 position, uint16 mode);
uint8   error_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void error_Sleep(void); 
void error_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(error__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define error_DRIVE_MODE_BITS        (3)
    #define error_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - error_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the error_SetDriveMode() function.
         *  @{
         */
        #define error_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define error_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define error_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define error_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define error_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define error_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define error_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define error_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define error_MASK               error__MASK
#define error_SHIFT              error__SHIFT
#define error_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in error_SetInterruptMode() function.
     *  @{
     */
        #define error_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define error_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define error_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define error_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(error__SIO)
    #define error_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(error__PC) && (CY_PSOC4_4200L)
    #define error_USBIO_ENABLE               ((uint32)0x80000000u)
    #define error_USBIO_DISABLE              ((uint32)(~error_USBIO_ENABLE))
    #define error_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define error_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define error_USBIO_ENTER_SLEEP          ((uint32)((1u << error_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << error_USBIO_SUSPEND_DEL_SHIFT)))
    #define error_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << error_USBIO_SUSPEND_SHIFT)))
    #define error_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << error_USBIO_SUSPEND_DEL_SHIFT)))
    #define error_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(error__PC)
    /* Port Configuration */
    #define error_PC                 (* (reg32 *) error__PC)
#endif
/* Pin State */
#define error_PS                     (* (reg32 *) error__PS)
/* Data Register */
#define error_DR                     (* (reg32 *) error__DR)
/* Input Buffer Disable Override */
#define error_INP_DIS                (* (reg32 *) error__PC2)

/* Interrupt configuration Registers */
#define error_INTCFG                 (* (reg32 *) error__INTCFG)
#define error_INTSTAT                (* (reg32 *) error__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define error_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(error__SIO)
    #define error_SIO_REG            (* (reg32 *) error__SIO)
#endif /* (error__SIO_CFG) */

/* USBIO registers */
#if !defined(error__PC) && (CY_PSOC4_4200L)
    #define error_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define error_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define error_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define error_DRIVE_MODE_SHIFT       (0x00u)
#define error_DRIVE_MODE_MASK        (0x07u << error_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins error_H */


/* [] END OF FILE */
