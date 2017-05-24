/*******************************************************************************
* File Name: fault.h  
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

#if !defined(CY_PINS_fault_H) /* Pins fault_H */
#define CY_PINS_fault_H

#include "cytypes.h"
#include "cyfitter.h"
#include "fault_aliases.h"


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
} fault_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   fault_Read(void);
void    fault_Write(uint8 value);
uint8   fault_ReadDataReg(void);
#if defined(fault__PC) || (CY_PSOC4_4200L) 
    void    fault_SetDriveMode(uint8 mode);
#endif
void    fault_SetInterruptMode(uint16 position, uint16 mode);
uint8   fault_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void fault_Sleep(void); 
void fault_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(fault__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define fault_DRIVE_MODE_BITS        (3)
    #define fault_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - fault_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the fault_SetDriveMode() function.
         *  @{
         */
        #define fault_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define fault_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define fault_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define fault_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define fault_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define fault_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define fault_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define fault_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define fault_MASK               fault__MASK
#define fault_SHIFT              fault__SHIFT
#define fault_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in fault_SetInterruptMode() function.
     *  @{
     */
        #define fault_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define fault_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define fault_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define fault_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(fault__SIO)
    #define fault_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(fault__PC) && (CY_PSOC4_4200L)
    #define fault_USBIO_ENABLE               ((uint32)0x80000000u)
    #define fault_USBIO_DISABLE              ((uint32)(~fault_USBIO_ENABLE))
    #define fault_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define fault_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define fault_USBIO_ENTER_SLEEP          ((uint32)((1u << fault_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << fault_USBIO_SUSPEND_DEL_SHIFT)))
    #define fault_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << fault_USBIO_SUSPEND_SHIFT)))
    #define fault_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << fault_USBIO_SUSPEND_DEL_SHIFT)))
    #define fault_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(fault__PC)
    /* Port Configuration */
    #define fault_PC                 (* (reg32 *) fault__PC)
#endif
/* Pin State */
#define fault_PS                     (* (reg32 *) fault__PS)
/* Data Register */
#define fault_DR                     (* (reg32 *) fault__DR)
/* Input Buffer Disable Override */
#define fault_INP_DIS                (* (reg32 *) fault__PC2)

/* Interrupt configuration Registers */
#define fault_INTCFG                 (* (reg32 *) fault__INTCFG)
#define fault_INTSTAT                (* (reg32 *) fault__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define fault_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(fault__SIO)
    #define fault_SIO_REG            (* (reg32 *) fault__SIO)
#endif /* (fault__SIO_CFG) */

/* USBIO registers */
#if !defined(fault__PC) && (CY_PSOC4_4200L)
    #define fault_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define fault_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define fault_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define fault_DRIVE_MODE_SHIFT       (0x00u)
#define fault_DRIVE_MODE_MASK        (0x07u << fault_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins fault_H */


/* [] END OF FILE */
