/*******************************************************************************
* File Name: direction.h  
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

#if !defined(CY_PINS_direction_H) /* Pins direction_H */
#define CY_PINS_direction_H

#include "cytypes.h"
#include "cyfitter.h"
#include "direction_aliases.h"


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
} direction_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   direction_Read(void);
void    direction_Write(uint8 value);
uint8   direction_ReadDataReg(void);
#if defined(direction__PC) || (CY_PSOC4_4200L) 
    void    direction_SetDriveMode(uint8 mode);
#endif
void    direction_SetInterruptMode(uint16 position, uint16 mode);
uint8   direction_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void direction_Sleep(void); 
void direction_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(direction__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define direction_DRIVE_MODE_BITS        (3)
    #define direction_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - direction_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the direction_SetDriveMode() function.
         *  @{
         */
        #define direction_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define direction_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define direction_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define direction_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define direction_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define direction_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define direction_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define direction_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define direction_MASK               direction__MASK
#define direction_SHIFT              direction__SHIFT
#define direction_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in direction_SetInterruptMode() function.
     *  @{
     */
        #define direction_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define direction_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define direction_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define direction_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(direction__SIO)
    #define direction_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(direction__PC) && (CY_PSOC4_4200L)
    #define direction_USBIO_ENABLE               ((uint32)0x80000000u)
    #define direction_USBIO_DISABLE              ((uint32)(~direction_USBIO_ENABLE))
    #define direction_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define direction_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define direction_USBIO_ENTER_SLEEP          ((uint32)((1u << direction_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << direction_USBIO_SUSPEND_DEL_SHIFT)))
    #define direction_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << direction_USBIO_SUSPEND_SHIFT)))
    #define direction_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << direction_USBIO_SUSPEND_DEL_SHIFT)))
    #define direction_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(direction__PC)
    /* Port Configuration */
    #define direction_PC                 (* (reg32 *) direction__PC)
#endif
/* Pin State */
#define direction_PS                     (* (reg32 *) direction__PS)
/* Data Register */
#define direction_DR                     (* (reg32 *) direction__DR)
/* Input Buffer Disable Override */
#define direction_INP_DIS                (* (reg32 *) direction__PC2)

/* Interrupt configuration Registers */
#define direction_INTCFG                 (* (reg32 *) direction__INTCFG)
#define direction_INTSTAT                (* (reg32 *) direction__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define direction_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(direction__SIO)
    #define direction_SIO_REG            (* (reg32 *) direction__SIO)
#endif /* (direction__SIO_CFG) */

/* USBIO registers */
#if !defined(direction__PC) && (CY_PSOC4_4200L)
    #define direction_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define direction_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define direction_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define direction_DRIVE_MODE_SHIFT       (0x00u)
#define direction_DRIVE_MODE_MASK        (0x07u << direction_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins direction_H */


/* [] END OF FILE */
