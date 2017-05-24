/*******************************************************************************
* File Name: ovc.h  
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

#if !defined(CY_PINS_ovc_H) /* Pins ovc_H */
#define CY_PINS_ovc_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ovc_aliases.h"


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
} ovc_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ovc_Read(void);
void    ovc_Write(uint8 value);
uint8   ovc_ReadDataReg(void);
#if defined(ovc__PC) || (CY_PSOC4_4200L) 
    void    ovc_SetDriveMode(uint8 mode);
#endif
void    ovc_SetInterruptMode(uint16 position, uint16 mode);
uint8   ovc_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ovc_Sleep(void); 
void ovc_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ovc__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ovc_DRIVE_MODE_BITS        (3)
    #define ovc_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ovc_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ovc_SetDriveMode() function.
         *  @{
         */
        #define ovc_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ovc_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ovc_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ovc_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ovc_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ovc_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ovc_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ovc_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ovc_MASK               ovc__MASK
#define ovc_SHIFT              ovc__SHIFT
#define ovc_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ovc_SetInterruptMode() function.
     *  @{
     */
        #define ovc_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ovc_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ovc_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ovc_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ovc__SIO)
    #define ovc_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ovc__PC) && (CY_PSOC4_4200L)
    #define ovc_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ovc_USBIO_DISABLE              ((uint32)(~ovc_USBIO_ENABLE))
    #define ovc_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ovc_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ovc_USBIO_ENTER_SLEEP          ((uint32)((1u << ovc_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ovc_USBIO_SUSPEND_DEL_SHIFT)))
    #define ovc_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ovc_USBIO_SUSPEND_SHIFT)))
    #define ovc_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ovc_USBIO_SUSPEND_DEL_SHIFT)))
    #define ovc_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ovc__PC)
    /* Port Configuration */
    #define ovc_PC                 (* (reg32 *) ovc__PC)
#endif
/* Pin State */
#define ovc_PS                     (* (reg32 *) ovc__PS)
/* Data Register */
#define ovc_DR                     (* (reg32 *) ovc__DR)
/* Input Buffer Disable Override */
#define ovc_INP_DIS                (* (reg32 *) ovc__PC2)

/* Interrupt configuration Registers */
#define ovc_INTCFG                 (* (reg32 *) ovc__INTCFG)
#define ovc_INTSTAT                (* (reg32 *) ovc__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ovc_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ovc__SIO)
    #define ovc_SIO_REG            (* (reg32 *) ovc__SIO)
#endif /* (ovc__SIO_CFG) */

/* USBIO registers */
#if !defined(ovc__PC) && (CY_PSOC4_4200L)
    #define ovc_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ovc_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ovc_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ovc_DRIVE_MODE_SHIFT       (0x00u)
#define ovc_DRIVE_MODE_MASK        (0x07u << ovc_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ovc_H */


/* [] END OF FILE */
