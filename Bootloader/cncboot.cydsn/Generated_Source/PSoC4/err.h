/*******************************************************************************
* File Name: err.h  
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

#if !defined(CY_PINS_err_H) /* Pins err_H */
#define CY_PINS_err_H

#include "cytypes.h"
#include "cyfitter.h"
#include "err_aliases.h"


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
} err_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   err_Read(void);
void    err_Write(uint8 value);
uint8   err_ReadDataReg(void);
#if defined(err__PC) || (CY_PSOC4_4200L) 
    void    err_SetDriveMode(uint8 mode);
#endif
void    err_SetInterruptMode(uint16 position, uint16 mode);
uint8   err_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void err_Sleep(void); 
void err_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(err__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define err_DRIVE_MODE_BITS        (3)
    #define err_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - err_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the err_SetDriveMode() function.
         *  @{
         */
        #define err_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define err_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define err_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define err_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define err_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define err_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define err_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define err_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define err_MASK               err__MASK
#define err_SHIFT              err__SHIFT
#define err_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in err_SetInterruptMode() function.
     *  @{
     */
        #define err_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define err_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define err_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define err_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(err__SIO)
    #define err_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(err__PC) && (CY_PSOC4_4200L)
    #define err_USBIO_ENABLE               ((uint32)0x80000000u)
    #define err_USBIO_DISABLE              ((uint32)(~err_USBIO_ENABLE))
    #define err_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define err_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define err_USBIO_ENTER_SLEEP          ((uint32)((1u << err_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << err_USBIO_SUSPEND_DEL_SHIFT)))
    #define err_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << err_USBIO_SUSPEND_SHIFT)))
    #define err_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << err_USBIO_SUSPEND_DEL_SHIFT)))
    #define err_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(err__PC)
    /* Port Configuration */
    #define err_PC                 (* (reg32 *) err__PC)
#endif
/* Pin State */
#define err_PS                     (* (reg32 *) err__PS)
/* Data Register */
#define err_DR                     (* (reg32 *) err__DR)
/* Input Buffer Disable Override */
#define err_INP_DIS                (* (reg32 *) err__PC2)

/* Interrupt configuration Registers */
#define err_INTCFG                 (* (reg32 *) err__INTCFG)
#define err_INTSTAT                (* (reg32 *) err__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define err_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(err__SIO)
    #define err_SIO_REG            (* (reg32 *) err__SIO)
#endif /* (err__SIO_CFG) */

/* USBIO registers */
#if !defined(err__PC) && (CY_PSOC4_4200L)
    #define err_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define err_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define err_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define err_DRIVE_MODE_SHIFT       (0x00u)
#define err_DRIVE_MODE_MASK        (0x07u << err_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins err_H */


/* [] END OF FILE */
