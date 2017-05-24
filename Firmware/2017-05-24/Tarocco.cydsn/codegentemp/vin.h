/*******************************************************************************
* File Name: vin.h  
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

#if !defined(CY_PINS_vin_H) /* Pins vin_H */
#define CY_PINS_vin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "vin_aliases.h"


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
} vin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   vin_Read(void);
void    vin_Write(uint8 value);
uint8   vin_ReadDataReg(void);
#if defined(vin__PC) || (CY_PSOC4_4200L) 
    void    vin_SetDriveMode(uint8 mode);
#endif
void    vin_SetInterruptMode(uint16 position, uint16 mode);
uint8   vin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void vin_Sleep(void); 
void vin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(vin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define vin_DRIVE_MODE_BITS        (3)
    #define vin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - vin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the vin_SetDriveMode() function.
         *  @{
         */
        #define vin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define vin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define vin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define vin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define vin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define vin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define vin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define vin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define vin_MASK               vin__MASK
#define vin_SHIFT              vin__SHIFT
#define vin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in vin_SetInterruptMode() function.
     *  @{
     */
        #define vin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define vin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define vin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define vin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(vin__SIO)
    #define vin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(vin__PC) && (CY_PSOC4_4200L)
    #define vin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define vin_USBIO_DISABLE              ((uint32)(~vin_USBIO_ENABLE))
    #define vin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define vin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define vin_USBIO_ENTER_SLEEP          ((uint32)((1u << vin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << vin_USBIO_SUSPEND_DEL_SHIFT)))
    #define vin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << vin_USBIO_SUSPEND_SHIFT)))
    #define vin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << vin_USBIO_SUSPEND_DEL_SHIFT)))
    #define vin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(vin__PC)
    /* Port Configuration */
    #define vin_PC                 (* (reg32 *) vin__PC)
#endif
/* Pin State */
#define vin_PS                     (* (reg32 *) vin__PS)
/* Data Register */
#define vin_DR                     (* (reg32 *) vin__DR)
/* Input Buffer Disable Override */
#define vin_INP_DIS                (* (reg32 *) vin__PC2)

/* Interrupt configuration Registers */
#define vin_INTCFG                 (* (reg32 *) vin__INTCFG)
#define vin_INTSTAT                (* (reg32 *) vin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define vin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(vin__SIO)
    #define vin_SIO_REG            (* (reg32 *) vin__SIO)
#endif /* (vin__SIO_CFG) */

/* USBIO registers */
#if !defined(vin__PC) && (CY_PSOC4_4200L)
    #define vin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define vin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define vin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define vin_DRIVE_MODE_SHIFT       (0x00u)
#define vin_DRIVE_MODE_MASK        (0x07u << vin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins vin_H */


/* [] END OF FILE */
