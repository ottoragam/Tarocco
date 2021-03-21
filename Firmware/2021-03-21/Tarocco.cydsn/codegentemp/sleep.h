/*******************************************************************************
* File Name: sleep.h  
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

#if !defined(CY_PINS_sleep_H) /* Pins sleep_H */
#define CY_PINS_sleep_H

#include "cytypes.h"
#include "cyfitter.h"
#include "sleep_aliases.h"


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
} sleep_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   sleep_Read(void);
void    sleep_Write(uint8 value);
uint8   sleep_ReadDataReg(void);
#if defined(sleep__PC) || (CY_PSOC4_4200L) 
    void    sleep_SetDriveMode(uint8 mode);
#endif
void    sleep_SetInterruptMode(uint16 position, uint16 mode);
uint8   sleep_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void sleep_Sleep(void); 
void sleep_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(sleep__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define sleep_DRIVE_MODE_BITS        (3)
    #define sleep_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - sleep_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the sleep_SetDriveMode() function.
         *  @{
         */
        #define sleep_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define sleep_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define sleep_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define sleep_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define sleep_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define sleep_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define sleep_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define sleep_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define sleep_MASK               sleep__MASK
#define sleep_SHIFT              sleep__SHIFT
#define sleep_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sleep_SetInterruptMode() function.
     *  @{
     */
        #define sleep_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define sleep_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define sleep_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define sleep_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(sleep__SIO)
    #define sleep_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(sleep__PC) && (CY_PSOC4_4200L)
    #define sleep_USBIO_ENABLE               ((uint32)0x80000000u)
    #define sleep_USBIO_DISABLE              ((uint32)(~sleep_USBIO_ENABLE))
    #define sleep_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define sleep_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define sleep_USBIO_ENTER_SLEEP          ((uint32)((1u << sleep_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << sleep_USBIO_SUSPEND_DEL_SHIFT)))
    #define sleep_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << sleep_USBIO_SUSPEND_SHIFT)))
    #define sleep_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << sleep_USBIO_SUSPEND_DEL_SHIFT)))
    #define sleep_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(sleep__PC)
    /* Port Configuration */
    #define sleep_PC                 (* (reg32 *) sleep__PC)
#endif
/* Pin State */
#define sleep_PS                     (* (reg32 *) sleep__PS)
/* Data Register */
#define sleep_DR                     (* (reg32 *) sleep__DR)
/* Input Buffer Disable Override */
#define sleep_INP_DIS                (* (reg32 *) sleep__PC2)

/* Interrupt configuration Registers */
#define sleep_INTCFG                 (* (reg32 *) sleep__INTCFG)
#define sleep_INTSTAT                (* (reg32 *) sleep__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define sleep_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(sleep__SIO)
    #define sleep_SIO_REG            (* (reg32 *) sleep__SIO)
#endif /* (sleep__SIO_CFG) */

/* USBIO registers */
#if !defined(sleep__PC) && (CY_PSOC4_4200L)
    #define sleep_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define sleep_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define sleep_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define sleep_DRIVE_MODE_SHIFT       (0x00u)
#define sleep_DRIVE_MODE_MASK        (0x07u << sleep_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins sleep_H */


/* [] END OF FILE */
