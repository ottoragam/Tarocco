/*******************************************************************************
* File Name: step.h  
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

#if !defined(CY_PINS_step_H) /* Pins step_H */
#define CY_PINS_step_H

#include "cytypes.h"
#include "cyfitter.h"
#include "step_aliases.h"


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
} step_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   step_Read(void);
void    step_Write(uint8 value);
uint8   step_ReadDataReg(void);
#if defined(step__PC) || (CY_PSOC4_4200L) 
    void    step_SetDriveMode(uint8 mode);
#endif
void    step_SetInterruptMode(uint16 position, uint16 mode);
uint8   step_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void step_Sleep(void); 
void step_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(step__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define step_DRIVE_MODE_BITS        (3)
    #define step_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - step_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the step_SetDriveMode() function.
         *  @{
         */
        #define step_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define step_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define step_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define step_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define step_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define step_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define step_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define step_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define step_MASK               step__MASK
#define step_SHIFT              step__SHIFT
#define step_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in step_SetInterruptMode() function.
     *  @{
     */
        #define step_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define step_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define step_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define step_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(step__SIO)
    #define step_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(step__PC) && (CY_PSOC4_4200L)
    #define step_USBIO_ENABLE               ((uint32)0x80000000u)
    #define step_USBIO_DISABLE              ((uint32)(~step_USBIO_ENABLE))
    #define step_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define step_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define step_USBIO_ENTER_SLEEP          ((uint32)((1u << step_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << step_USBIO_SUSPEND_DEL_SHIFT)))
    #define step_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << step_USBIO_SUSPEND_SHIFT)))
    #define step_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << step_USBIO_SUSPEND_DEL_SHIFT)))
    #define step_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(step__PC)
    /* Port Configuration */
    #define step_PC                 (* (reg32 *) step__PC)
#endif
/* Pin State */
#define step_PS                     (* (reg32 *) step__PS)
/* Data Register */
#define step_DR                     (* (reg32 *) step__DR)
/* Input Buffer Disable Override */
#define step_INP_DIS                (* (reg32 *) step__PC2)

/* Interrupt configuration Registers */
#define step_INTCFG                 (* (reg32 *) step__INTCFG)
#define step_INTSTAT                (* (reg32 *) step__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define step_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(step__SIO)
    #define step_SIO_REG            (* (reg32 *) step__SIO)
#endif /* (step__SIO_CFG) */

/* USBIO registers */
#if !defined(step__PC) && (CY_PSOC4_4200L)
    #define step_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define step_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define step_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define step_DRIVE_MODE_SHIFT       (0x00u)
#define step_DRIVE_MODE_MASK        (0x07u << step_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins step_H */


/* [] END OF FILE */
