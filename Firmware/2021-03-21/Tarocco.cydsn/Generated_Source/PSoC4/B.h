/*******************************************************************************
* File Name: B.h  
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

#if !defined(CY_PINS_B_H) /* Pins B_H */
#define CY_PINS_B_H

#include "cytypes.h"
#include "cyfitter.h"
#include "B_aliases.h"


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
} B_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   B_Read(void);
void    B_Write(uint8 value);
uint8   B_ReadDataReg(void);
#if defined(B__PC) || (CY_PSOC4_4200L) 
    void    B_SetDriveMode(uint8 mode);
#endif
void    B_SetInterruptMode(uint16 position, uint16 mode);
uint8   B_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void B_Sleep(void); 
void B_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(B__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define B_DRIVE_MODE_BITS        (3)
    #define B_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - B_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the B_SetDriveMode() function.
         *  @{
         */
        #define B_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define B_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define B_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define B_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define B_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define B_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define B_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define B_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define B_MASK               B__MASK
#define B_SHIFT              B__SHIFT
#define B_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in B_SetInterruptMode() function.
     *  @{
     */
        #define B_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define B_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define B_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define B_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(B__SIO)
    #define B_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(B__PC) && (CY_PSOC4_4200L)
    #define B_USBIO_ENABLE               ((uint32)0x80000000u)
    #define B_USBIO_DISABLE              ((uint32)(~B_USBIO_ENABLE))
    #define B_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define B_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define B_USBIO_ENTER_SLEEP          ((uint32)((1u << B_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << B_USBIO_SUSPEND_DEL_SHIFT)))
    #define B_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << B_USBIO_SUSPEND_SHIFT)))
    #define B_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << B_USBIO_SUSPEND_DEL_SHIFT)))
    #define B_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(B__PC)
    /* Port Configuration */
    #define B_PC                 (* (reg32 *) B__PC)
#endif
/* Pin State */
#define B_PS                     (* (reg32 *) B__PS)
/* Data Register */
#define B_DR                     (* (reg32 *) B__DR)
/* Input Buffer Disable Override */
#define B_INP_DIS                (* (reg32 *) B__PC2)

/* Interrupt configuration Registers */
#define B_INTCFG                 (* (reg32 *) B__INTCFG)
#define B_INTSTAT                (* (reg32 *) B__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define B_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(B__SIO)
    #define B_SIO_REG            (* (reg32 *) B__SIO)
#endif /* (B__SIO_CFG) */

/* USBIO registers */
#if !defined(B__PC) && (CY_PSOC4_4200L)
    #define B_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define B_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define B_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define B_DRIVE_MODE_SHIFT       (0x00u)
#define B_DRIVE_MODE_MASK        (0x07u << B_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins B_H */


/* [] END OF FILE */
