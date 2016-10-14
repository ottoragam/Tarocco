/***************************************************************************//**
* \file UART_BOOT.h
* \version 3.20
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_UART_H)
#define CY_SCB_BOOT_UART_H

#include "UART_PVT.h"

#if (UART_SCB_MODE_I2C_INC)
    #include "UART_I2C.h"
#endif /* (UART_SCB_MODE_I2C_INC) */

#if (UART_SCB_MODE_EZI2C_INC)
    #include "UART_EZI2C.h"
#endif /* (UART_SCB_MODE_EZI2C_INC) */

#if (UART_SCB_MODE_SPI_INC || UART_SCB_MODE_UART_INC)
    #include "UART_SPI_UART.h"
#endif /* (UART_SCB_MODE_SPI_INC || UART_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define UART_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (UART_SCB_MODE_I2C_INC)
    #define UART_I2C_BTLDR_COMM_ENABLED     (UART_BTLDR_COMM_ENABLED && \
                                                            (UART_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UART_I2C_SLAVE_CONST))
#else
     #define UART_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (UART_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (UART_SCB_MODE_EZI2C_INC)
    #define UART_EZI2C_BTLDR_COMM_ENABLED   (UART_BTLDR_COMM_ENABLED && \
                                                         UART_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define UART_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (UART_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (UART_SCB_MODE_SPI_INC)
    #define UART_SPI_BTLDR_COMM_ENABLED     (UART_BTLDR_COMM_ENABLED && \
                                                            (UART_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UART_SPI_SLAVE_CONST))
#else
        #define UART_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (UART_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (UART_SCB_MODE_UART_INC)
       #define UART_UART_BTLDR_COMM_ENABLED    (UART_BTLDR_COMM_ENABLED && \
                                                            (UART_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (UART_UART_RX_DIRECTION && \
                                                              UART_UART_TX_DIRECTION)))
#else
     #define UART_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (UART_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define UART_BTLDR_COMM_MODE_ENABLED    (UART_I2C_BTLDR_COMM_ENABLED   || \
                                                     UART_SPI_BTLDR_COMM_ENABLED   || \
                                                     UART_EZI2C_BTLDR_COMM_ENABLED || \
                                                     UART_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void UART_I2CCyBtldrCommStart(void);
    void UART_I2CCyBtldrCommStop (void);
    void UART_I2CCyBtldrCommReset(void);
    cystatus UART_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (UART_SCB_MODE_I2C_CONST_CFG)
        #define UART_CyBtldrCommStart   UART_I2CCyBtldrCommStart
        #define UART_CyBtldrCommStop    UART_I2CCyBtldrCommStop
        #define UART_CyBtldrCommReset   UART_I2CCyBtldrCommReset
        #define UART_CyBtldrCommRead    UART_I2CCyBtldrCommRead
        #define UART_CyBtldrCommWrite   UART_I2CCyBtldrCommWrite
    #endif /* (UART_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void UART_EzI2CCyBtldrCommStart(void);
    void UART_EzI2CCyBtldrCommStop (void);
    void UART_EzI2CCyBtldrCommReset(void);
    cystatus UART_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (UART_SCB_MODE_EZI2C_CONST_CFG)
        #define UART_CyBtldrCommStart   UART_EzI2CCyBtldrCommStart
        #define UART_CyBtldrCommStop    UART_EzI2CCyBtldrCommStop
        #define UART_CyBtldrCommReset   UART_EzI2CCyBtldrCommReset
        #define UART_CyBtldrCommRead    UART_EzI2CCyBtldrCommRead
        #define UART_CyBtldrCommWrite   UART_EzI2CCyBtldrCommWrite
    #endif /* (UART_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void UART_SpiCyBtldrCommStart(void);
    void UART_SpiCyBtldrCommStop (void);
    void UART_SpiCyBtldrCommReset(void);
    cystatus UART_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (UART_SCB_MODE_SPI_CONST_CFG)
        #define UART_CyBtldrCommStart   UART_SpiCyBtldrCommStart
        #define UART_CyBtldrCommStop    UART_SpiCyBtldrCommStop
        #define UART_CyBtldrCommReset   UART_SpiCyBtldrCommReset
        #define UART_CyBtldrCommRead    UART_SpiCyBtldrCommRead
        #define UART_CyBtldrCommWrite   UART_SpiCyBtldrCommWrite
    #endif /* (UART_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void UART_UartCyBtldrCommStart(void);
    void UART_UartCyBtldrCommStop (void);
    void UART_UartCyBtldrCommReset(void);
    cystatus UART_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (UART_SCB_MODE_UART_CONST_CFG)
        #define UART_CyBtldrCommStart   UART_UartCyBtldrCommStart
        #define UART_CyBtldrCommStop    UART_UartCyBtldrCommStop
        #define UART_CyBtldrCommReset   UART_UartCyBtldrCommReset
        #define UART_CyBtldrCommRead    UART_UartCyBtldrCommRead
        #define UART_CyBtldrCommWrite   UART_UartCyBtldrCommWrite
    #endif /* (UART_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_BTLDR_COMM_ENABLED)
    #if (UART_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void UART_CyBtldrCommStart(void);
        void UART_CyBtldrCommStop (void);
        void UART_CyBtldrCommReset(void);
        cystatus UART_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (UART_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART)
        #define CyBtldrCommStart    UART_CyBtldrCommStart
        #define CyBtldrCommStop     UART_CyBtldrCommStop
        #define CyBtldrCommReset    UART_CyBtldrCommReset
        #define CyBtldrCommWrite    UART_CyBtldrCommWrite
        #define CyBtldrCommRead     UART_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define UART_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define UART_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define UART_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define UART_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef UART_SPI_BYTE_TO_BYTE
    #define UART_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef UART_UART_BYTE_TO_BYTE
    #define UART_UART_BYTE_TO_BYTE  (175u)
#endif /* UART_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_UART_H) */


/* [] END OF FILE */
