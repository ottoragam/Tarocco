/***************************************************************************//**
* \file .h
* \version 3.20
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_UART_H)
#define CY_SCB_PVT_UART_H

#include "UART.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_SetI2CExtClkInterruptMode(interruptMask) UART_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_ClearI2CExtClkInterruptSource(interruptMask) UART_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_GetI2CExtClkInterruptSource()                (UART_INTR_I2C_EC_REG)
#define UART_GetI2CExtClkInterruptMode()                  (UART_INTR_I2C_EC_MASK_REG)
#define UART_GetI2CExtClkInterruptSourceMasked()          (UART_INTR_I2C_EC_MASKED_REG)

#if (!UART_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_GetExtSpiClkInterruptSource()                 (UART_INTR_SPI_EC_REG)
    #define UART_GetExtSpiClkInterruptMode()                   (UART_INTR_SPI_EC_MASK_REG)
    #define UART_GetExtSpiClkInterruptSourceMasked()           (UART_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_CY_SCBIP_V1) */

#if(UART_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UART_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UART_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_CUSTOM_INTR_HANDLER) */
#endif /* (UART_SCB_IRQ_INTERNAL) */

extern UART_BACKUP_STRUCT UART_backup;

#if(UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_scbMode;
    extern uint8 UART_scbEnableWake;
    extern uint8 UART_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_mode;
    extern uint8 UART_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_rxBuffer;
    extern uint8   UART_rxDataBits;
    extern uint32  UART_rxBufferSize;

    extern volatile uint8 * UART_txBuffer;
    extern uint8   UART_txDataBits;
    extern uint32  UART_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_numberOfAddr;
    extern uint8 UART_subAddrSize;
#endif /* (UART_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (UART_SCB_MODE_I2C_CONST_CFG || \
        UART_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 UART_IntrTxMask;
#endif /* (! (UART_SCB_MODE_I2C_CONST_CFG || \
              UART_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_SCB_MODE_I2C_RUNTM_CFG     (UART_SCB_MODE_I2C      == UART_scbMode)
    #define UART_SCB_MODE_SPI_RUNTM_CFG     (UART_SCB_MODE_SPI      == UART_scbMode)
    #define UART_SCB_MODE_UART_RUNTM_CFG    (UART_SCB_MODE_UART     == UART_scbMode)
    #define UART_SCB_MODE_EZI2C_RUNTM_CFG   (UART_SCB_MODE_EZI2C    == UART_scbMode)
    #define UART_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_SCB_MODE_UNCONFIG == UART_scbMode)

    /* Defines wakeup enable */
    #define UART_SCB_WAKE_ENABLE_CHECK       (0u != UART_scbEnableWake)
#endif /* (UART_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_CY_SCBIP_V1)
    #define UART_SCB_PINS_NUMBER    (7u)
#else
    #define UART_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_H) */


/* [] END OF FILE */
