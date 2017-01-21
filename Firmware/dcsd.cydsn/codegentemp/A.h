/*******************************************************************************
* File Name: A.h  
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

#if !defined(CY_PINS_A_H) /* Pins A_H */
#define CY_PINS_A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "A_aliases.h"


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
} A_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   A_Read(void);
void    A_Write(uint8 value);
uint8   A_ReadDataReg(void);
#if defined(A__PC) || (CY_PSOC4_4200L) 
    void    A_SetDriveMode(uint8 mode);
#endif
void    A_SetInterruptMode(uint16 position, uint16 mode);
uint8   A_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void A_Sleep(void); 
void A_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(A__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define A_DRIVE_MODE_BITS        (3)
    #define A_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - A_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the A_SetDriveMode() function.
         *  @{
         */
        #define A_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define A_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define A_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define A_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define A_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define A_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define A_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define A_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define A_MASK               A__MASK
#define A_SHIFT              A__SHIFT
#define A_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in A_SetInterruptMode() function.
     *  @{
     */
        #define A_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define A_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define A_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define A_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(A__SIO)
    #define A_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(A__PC) && (CY_PSOC4_4200L)
    #define A_USBIO_ENABLE               ((uint32)0x80000000u)
    #define A_USBIO_DISABLE              ((uint32)(~A_USBIO_ENABLE))
    #define A_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define A_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define A_USBIO_ENTER_SLEEP          ((uint32)((1u << A_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << A_USBIO_SUSPEND_DEL_SHIFT)))
    #define A_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << A_USBIO_SUSPEND_SHIFT)))
    #define A_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << A_USBIO_SUSPEND_DEL_SHIFT)))
    #define A_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(A__PC)
    /* Port Configuration */
    #define A_PC                 (* (reg32 *) A__PC)
#endif
/* Pin State */
#define A_PS                     (* (reg32 *) A__PS)
/* Data Register */
#define A_DR                     (* (reg32 *) A__DR)
/* Input Buffer Disable Override */
#define A_INP_DIS                (* (reg32 *) A__PC2)

/* Interrupt configuration Registers */
#define A_INTCFG                 (* (reg32 *) A__INTCFG)
#define A_INTSTAT                (* (reg32 *) A__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define A_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(A__SIO)
    #define A_SIO_REG            (* (reg32 *) A__SIO)
#endif /* (A__SIO_CFG) */

/* USBIO registers */
#if !defined(A__PC) && (CY_PSOC4_4200L)
    #define A_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define A_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define A_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define A_DRIVE_MODE_SHIFT       (0x00u)
#define A_DRIVE_MODE_MASK        (0x07u << A_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins A_H */


/* [] END OF FILE */
