/***************************************************************************//**
* \file UART_SPI_UART.h
* \version 3.20
*
* \brief
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_UART_H)
#define CY_SCB_SPI_UART_UART_H

#include "UART.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define UART_SPI_MODE                   (0u)
#define UART_SPI_SUB_MODE               (0u)
#define UART_SPI_CLOCK_MODE             (0u)
#define UART_SPI_OVS_FACTOR             (16u)
#define UART_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define UART_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define UART_SPI_RX_DATA_BITS_NUM       (8u)
#define UART_SPI_TX_DATA_BITS_NUM       (8u)
#define UART_SPI_WAKE_ENABLE            (0u)
#define UART_SPI_BITS_ORDER             (1u)
#define UART_SPI_TRANSFER_SEPARATION    (1u)
#define UART_SPI_NUMBER_OF_SS_LINES     (1u)
#define UART_SPI_RX_BUFFER_SIZE         (8u)
#define UART_SPI_TX_BUFFER_SIZE         (8u)

#define UART_SPI_INTERRUPT_MODE         (0u)

#define UART_SPI_INTR_RX_MASK           (0u)
#define UART_SPI_INTR_TX_MASK           (0u)

#define UART_SPI_RX_TRIGGER_LEVEL       (7u)
#define UART_SPI_TX_TRIGGER_LEVEL       (0u)

#define UART_SPI_BYTE_MODE_ENABLE       (0u)
#define UART_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define UART_SPI_SS0_POLARITY           (0u)
#define UART_SPI_SS1_POLARITY           (0u)
#define UART_SPI_SS2_POLARITY           (0u)
#define UART_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define UART_UART_SUB_MODE              (0u)
#define UART_UART_DIRECTION             (3u)
#define UART_UART_DATA_BITS_NUM         (8u)
#define UART_UART_PARITY_TYPE           (2u)
#define UART_UART_STOP_BITS_NUM         (2u)
#define UART_UART_OVS_FACTOR            (12u)
#define UART_UART_IRDA_LOW_POWER        (0u)
#define UART_UART_MEDIAN_FILTER_ENABLE  (0u)
#define UART_UART_RETRY_ON_NACK         (0u)
#define UART_UART_IRDA_POLARITY         (0u)
#define UART_UART_DROP_ON_FRAME_ERR     (0u)
#define UART_UART_DROP_ON_PARITY_ERR    (0u)
#define UART_UART_WAKE_ENABLE           (0u)
#define UART_UART_RX_BUFFER_SIZE        (8u)
#define UART_UART_TX_BUFFER_SIZE        (8u)
#define UART_UART_MP_MODE_ENABLE        (0u)
#define UART_UART_MP_ACCEPT_ADDRESS     (0u)
#define UART_UART_MP_RX_ADDRESS         (2u)
#define UART_UART_MP_RX_ADDRESS_MASK    (255u)

#define UART_UART_INTERRUPT_MODE        (2u)

#define UART_UART_INTR_RX_MASK          (4u)
#define UART_UART_INTR_TX_MASK          (0u)

#define UART_UART_RX_TRIGGER_LEVEL      (7u)
#define UART_UART_TX_TRIGGER_LEVEL      (0u)

#define UART_UART_BYTE_MODE_ENABLE      (0u)
#define UART_UART_CTS_ENABLE            (0u)
#define UART_UART_CTS_POLARITY          (0u)
#define UART_UART_RTS_ENABLE            (0u)
#define UART_UART_RTS_POLARITY          (0u)
#define UART_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define UART_SPI_SLAVE  (0u)
#define UART_SPI_MASTER (1u)

/* UART direction enum */
#define UART_UART_RX    (1u)
#define UART_UART_TX    (2u)
#define UART_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(UART_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define UART_SPI_SLAVE_CONST        (1u)
    #define UART_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define UART_RX_DIRECTION           (1u)
    #define UART_TX_DIRECTION           (1u)
    #define UART_UART_RX_DIRECTION      (1u)
    #define UART_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define UART_INTERNAL_RX_SW_BUFFER   (0u)
    #define UART_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define UART_INTERNAL_RX_BUFFER_SIZE    (UART_rxBufferSize + 1u)
    #define UART_RX_BUFFER_SIZE             (UART_rxBufferSize)
    #define UART_TX_BUFFER_SIZE             (UART_txBufferSize)

    /* Return true if buffer is provided */
    #define UART_CHECK_RX_SW_BUFFER (NULL != UART_rxBuffer)
    #define UART_CHECK_TX_SW_BUFFER (NULL != UART_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define UART_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define UART_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define UART_SPI_WAKE_ENABLE_CONST  (1u)
    #define UART_UART_WAKE_ENABLE_CONST (1u)
    #define UART_CHECK_SPI_WAKE_ENABLE  ((0u != UART_scbEnableWake) && UART_SCB_MODE_SPI_RUNTM_CFG)
    #define UART_CHECK_UART_WAKE_ENABLE ((0u != UART_scbEnableWake) && UART_SCB_MODE_UART_RUNTM_CFG)

    /* SPI/UART: TX or RX FIFO size */
    #if (UART_CY_SCBIP_V0 || UART_CY_SCBIP_V1)
        #define UART_SPI_UART_FIFO_SIZE             (UART_FIFO_SIZE)
        #define UART_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define UART_SPI_UART_FIFO_SIZE (UART_GET_FIFO_SIZE(UART_CTRL_REG & \
                                                                                    UART_CTRL_BYTE_MODE))

        #define UART_CHECK_UART_RTS_CONTROL_FLOW \
                    ((UART_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != UART_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(UART_UART_FLOW_CTRL_REG)))
    #endif /* (UART_CY_SCBIP_V0 || UART_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (UART_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define UART_SPI_RX_DIRECTION (1u)
        #define UART_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #define UART_SPI_UART_FIFO_SIZE UART_GET_FIFO_SIZE(UART_SPI_BYTE_MODE_ENABLE)

        /* SPI internal RX and TX buffers */
        #define UART_INTERNAL_SPI_RX_SW_BUFFER  (UART_SPI_RX_BUFFER_SIZE > \
                                                                UART_SPI_UART_FIFO_SIZE)
        #define UART_INTERNAL_SPI_TX_SW_BUFFER  (UART_SPI_TX_BUFFER_SIZE > \
                                                                UART_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define UART_INTERNAL_RX_SW_BUFFER  (UART_INTERNAL_SPI_RX_SW_BUFFER)
        #define UART_INTERNAL_TX_SW_BUFFER  (UART_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define UART_INTERNAL_RX_BUFFER_SIZE    (UART_SPI_RX_BUFFER_SIZE + 1u)
        #define UART_RX_BUFFER_SIZE             (UART_SPI_RX_BUFFER_SIZE)
        #define UART_TX_BUFFER_SIZE             (UART_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define UART_SPI_WAKE_ENABLE_CONST  (0u != UART_SPI_WAKE_ENABLE)
        #define UART_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define UART_UART_RX_DIRECTION (0u != (UART_UART_DIRECTION & UART_UART_RX))
        #define UART_UART_TX_DIRECTION (0u != (UART_UART_DIRECTION & UART_UART_TX))

        /* Get FIFO size */
        #define UART_SPI_UART_FIFO_SIZE UART_GET_FIFO_SIZE(UART_UART_BYTE_MODE_ENABLE)

        /* UART internal RX and TX buffers */
        #define UART_INTERNAL_UART_RX_SW_BUFFER  (UART_UART_RX_BUFFER_SIZE > \
                                                                UART_SPI_UART_FIFO_SIZE)
        #define UART_INTERNAL_UART_TX_SW_BUFFER  (UART_UART_TX_BUFFER_SIZE > \
                                                                    UART_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define UART_INTERNAL_RX_SW_BUFFER  (UART_INTERNAL_UART_RX_SW_BUFFER)
        #define UART_INTERNAL_TX_SW_BUFFER  (UART_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define UART_INTERNAL_RX_BUFFER_SIZE    (UART_UART_RX_BUFFER_SIZE + 1u)
        #define UART_RX_BUFFER_SIZE             (UART_UART_RX_BUFFER_SIZE)
        #define UART_TX_BUFFER_SIZE             (UART_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define UART_SPI_WAKE_ENABLE_CONST  (0u)
        #define UART_UART_WAKE_ENABLE_CONST (0u != UART_UART_WAKE_ENABLE)

    #endif /* (UART_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define UART_SPI_SLAVE_CONST    (UART_SPI_MODE == UART_SPI_SLAVE)
    #define UART_SPI_MASTER_CONST   (UART_SPI_MODE == UART_SPI_MASTER)

    /* Direction */
    #define UART_RX_DIRECTION ((UART_SCB_MODE_SPI_CONST_CFG) ? \
                                            (UART_SPI_RX_DIRECTION) : (UART_UART_RX_DIRECTION))

    #define UART_TX_DIRECTION ((UART_SCB_MODE_SPI_CONST_CFG) ? \
                                            (UART_SPI_TX_DIRECTION) : (UART_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define UART_CHECK_RX_SW_BUFFER (UART_INTERNAL_RX_SW_BUFFER)
    #define UART_CHECK_TX_SW_BUFFER (UART_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define UART_INTERNAL_RX_SW_BUFFER_CONST    (UART_INTERNAL_RX_SW_BUFFER)
    #define UART_INTERNAL_TX_SW_BUFFER_CONST    (UART_INTERNAL_TX_SW_BUFFER)

    /* Wake up enable */
    #define UART_CHECK_SPI_WAKE_ENABLE  (UART_SPI_WAKE_ENABLE_CONST)
    #define UART_CHECK_UART_WAKE_ENABLE (UART_UART_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define UART_CHECK_UART_RTS_CONTROL_FLOW    (UART_SCB_MODE_UART_CONST_CFG && \
                                                             UART_UART_RTS_ENABLE)

#endif /* End (UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/ 

/* UART_SPI_INIT_STRUCT */
typedef struct
{   
    /** Mode of operation for SPI. The following defines are available choices:
     *  - UART_SPI_SLAVE 
     *  - UART_SPI_MASTE
    */
    uint32 mode;
    
    /** Submode of operation for SPI. The following defines are available 
     *  choices: 
     *  - UART_SPI_MODE_MOTOROLA 
     *  - UART_SPI_MODE_TI_COINCIDES
     *  - UART_SPI_MODE_TI_PRECEDES
     *  - UART_SPI_MODE_NATIONAL
    */
    uint32 submode;
    
    /** Determines the sclk relationship for Motorola submode. Ignored 
     *  for other submodes. The following defines are available choices:
     *  - UART_SPI_SCLK_CPHA0_CPOL0
     *  - UART_SPI_SCLK_CPHA0_CPOL1
     *  - UART_SPI_SCLK_CPHA1_CPOL0
     *  - UART_SPI_SCLK_CPHA1_CPOL1
    */
    uint32 sclkMode;
    
    /** Oversampling factor for the SPI clock. Ignored for Slave mode operation.
    */
    uint32 oversample;
    
    /** Applies median filter on the input lines: 0 – not applied, 1 – applied.
    */
    uint32 enableMedianFilter;
    
    /** Applies late sampling of MISO line: 0 – not applied, 1 – applied.
     *  Ignored for slave mode.
    */
    uint32 enableLateSampling;
    
    /** Enables wakeup from low power mode: 0 – disable, 1 – enable. 
     *  Ignored for master mode.
    */
    uint32 enableWake;
    
    /** Number of data bits for RX direction.
     *  Different dataBitsRx and dataBitsTx are only allowed for National 
     *  submode.
    */
    uint32 rxDataBits;
    
    /** Number of data bits for TX direction.
     *  Different dataBitsRx and dataBitsTx are only allowed for National 
     *  submode.
    */
    uint32 txDataBits;
    
    /** Determines the bit ordering. The following defines are available 
     *  choices:
     *  - UART_BITS_ORDER_LSB_FIRST
     *  - UART_BITS_ORDER_MSB_FIRST
    */
    uint32 bitOrder;
    
    /** Determines whether transfers are back to back or have SS disabled 
     *  between words. Ignored for slave mode. The following defines are 
     *  available choices: 
     *  - UART_SPI_TRANSFER_CONTINUOUS
     *  - UART_SPI_TRANSFER_SEPARATED
    */
    uint32 transferSeperation;
    
    /** Size of the RX buffer in bytes/words (depends on rxDataBits parameter). 
     *  A value equal to the RX FIFO depth implies the usage of buffering in 
     *  hardware. A value greater than the RX FIFO depth results in a software 
     *  buffer.
     *  The UART_INTR _RX_NOT_EMPTY interrupt has to be enabled to 
     *  transfer data into the software buffer.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words for PSoC 4100 / 
     *    PSoC 4200 devices.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words or 16 
     *    bytes (Byte mode is enabled) for PSoC 4100 BLE / PSoC 4200 BLE / 
     *    PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S / 
     *    PSoC Analog Coprocessor devices.
    */
    uint32 rxBufferSize; 
    
    /** Buffer space provided for a RX software buffer:
     *  - A NULL pointer must be provided to use hardware buffering.
     *  - A pointer to an allocated buffer must be provided to use software 
     *    buffering. The buffer size must equal (rxBufferSize + 1) in bytes if 
     *    dataBitsRx is less or equal to 8, otherwise (2 * (rxBufferSize + 1)) 
     *    in bytes. The software RX buffer always keeps one element empty. 
     *    For correct operation the allocated RX buffer has to be one element 
     *    greater than maximum packet size expected to be received.
    */
    uint8* rxBuffer;
    
    /** Size of the TX buffer in bytes/words(depends on txDataBits parameter). 
     *  A value equal to the TX FIFO depth implies the usage of buffering in 
     *  hardware. A value greater than the TX FIFO depth results in a software 
     *  buffer.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words for PSoC 4100 / 
     *    PSoC 4200 devices.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words or 16 
     *    bytes (Byte mode is enabled) for PSoC 4100 BLE / PSoC 4200 BLE / 
     *    PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S / 
     *    PSoC Analog Coprocessor devices.
    */
    uint32 txBufferSize;
    
    /** Buffer space provided for a TX software buffer:
     *  - A NULL pointer must be provided to use hardware buffering.
     *  - A pointer to an allocated buffer must be provided to use software 
     *    buffering. The buffer size must equal txBufferSize if dataBitsTx is 
     *    less or eqal to 8, otherwise (2* txBufferSize).
    */
    uint8* txBuffer;
    
    /** Enables component interrupt: 0 – disable, 1 – enable.
     *  The interrupt has to be enabled if software buffer is used.
    */
    uint32 enableInterrupt;
    
    /** Mask of enabled interrupt sources for the RX direction. This mask is 
     *  written regardless of the setting of the enable Interrupt field. 
     *  Multiple sources are enabled by providing a value that is the OR of
     *  all of the following sources to enable:
     *  - UART_INTR_RX_FIFO_LEVEL
     *  - UART_INTR_RX_NOT_EMPTY
     *  - UART_INTR_RX_FULL
     *  - UART_INTR_RX_OVERFLOW
     *  - UART_INTR_RX_UNDERFLOW
     *  - UART_INTR_SLAVE_SPI_BUS_ERROR
    */
    uint32 rxInterruptMask;
    
    /** FIFO level for an RX FIFO level interrupt. This value is written 
     *  regardless of whether the RX FIFO level interrupt source is enabled.
    */
    uint32 rxTriggerLevel;
    
    /** Mask of enabled interrupt sources for the TX direction. This mask is 
     *  written regardless of the setting of the enable Interrupt field. 
     *  Multiple sources are enabled by providing a value that is the OR of
     *  all of the following sources to enable:
     *  - UART_INTR_TX_FIFO_LEVEL
     *  - UART_INTR_TX_NOT_FULL
     *  - UART_INTR_TX_EMPTY
     *  - UART_INTR_TX_OVERFLOW
     *  - UART_INTR_TX_UNDERFLOW
     *  - UART_INTR_MASTER_SPI_DONE
    */
    uint32 txInterruptMask;

    /** FIFO level for a TX FIFO level interrupt. This value is written 
     * regardless of whether the TX FIFO level interrupt source is enabled.
    */
    uint32 txTriggerLevel;
    
    /** When enabled the TX and RX FIFO depth is doubled and equal to 
     *  16 bytes: 0 – disable, 1 – enable. This implies that number of 
     *  TX and RX data bits must be less than or equal to 8.
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE / 
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S / 
     *  PSoC Analog Coprocessor.
    */
    uint8 enableByteMode;
    
    /** Enables continuous SCLK generation by the SPI master: 0 – disable, 
     *  1 – enable.
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE / 
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S / 
     *  PSoC Analog Coprocessor.
    */
    uint8 enableFreeRunSclk;
    
    /** Active polarity of slave select lines 0-3. This is bitmask where bit 
     *  UART_SPI_SLAVE_SELECT0 corresponds to slave select 0 
     *  polarity, bit UART_SPI_SLAVE_SELECT1 – slave select 1 
     *  polarity and so on. Polarity constants are: 
     *  - UART_SPI_SS_ACTIVE_LOW 
     *  - UART_SPI_SS_ACTIVE_HIGH
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE / 
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S / 
     *  PSoC Analog Coprocessor.
    */
    uint8 polaritySs;
} UART_SPI_INIT_STRUCT;


/* UART_UART_INIT_STRUCT */
typedef struct
{
    /** Mode of operation for the UART. The following defines are available 
     *  choices:
     *  - UART_UART_MODE_STD
     *  - UART_UART_MODE_SMARTCARD 
     *  - UART_UART_MODE_IRDA
    */
    uint32 mode;
    
    /** Direction of operation for the UART. The following defines are available
     *  choices:
     *  - UART_UART_TX_RX
     *  - UART_UART_RX
     *  - UART_UART_TX
    */
    uint32 direction;
    
    /** Number of data bits.
    */
    uint32 dataBits;
    
    /** Determines the parity. The following defines are available choices:
     *  - UART_UART_PARITY_EVEN
     *  - UART_UART_PARITY_ODD
     *  - UART_UART_PARITY_NONE
    */
    uint32 parity;
    
    /** Determines the number of stop bits. The following defines are available 
     *  choices:
     *  - UART_UART_STOP_BITS_1
     *  - UART_UART_STOP_BITS_1_5
     *  - UART_UART_STOP_BITS_2
    */
    uint32 stopBits;
    
    /** Oversampling factor for the UART.
     * 
     *  Note The oversampling factor values are changed when enableIrdaLowPower 
     *  is enabled:
     *  - UART_UART_IRDA_LP_OVS16
     *  - UART_UART_IRDA_LP_OVS32
     *  - UART_UART_IRDA_LP_OVS48
     *  - UART_UART_IRDA_LP_OVS96
     *  - UART_UART_IRDA_LP_OVS192
     *  - UART_UART_IRDA_LP_OVS768
     *  - UART_UART_IRDA_LP_OVS1536
    */
    uint32 oversample;
    
    /** Enables IrDA low power RX mode operation: 0 – disable, 1 – enable.
     *  The TX functionality does not work when enabled.
    */
    uint32 enableIrdaLowPower;
    
    /** Applies median filter on the input lines:  0 – not applied, 1 – applied. 
    */
    uint32 enableMedianFilter;
    
    /** Enables retry when NACK response was received: 0 – disable, 1 – enable. 
     *  Only current content of TX FIFO is re-sent.
     *  Ignored for modes other than SmartCard.
    */
    uint32 enableRetryNack;
    
    /** Inverts polarity of RX line: 0 – non-inverting, 1 – inverting. 
     *  Ignored for modes other than IrDA.
    */
    uint32 enableInvertedRx;
    
    /** Drop data from RX FIFO if parity error is detected: 0 – disable, 
     *  1 – enable. 
    */
    uint32 dropOnParityErr;
    
    /** Drop data from RX FIFO if a frame error is detected: 0 – disable, 
     *  1 – enable.
    */
    uint32 dropOnFrameErr;
    
    /** Enables wakeup from low power mode: 0 – disable, 1 – enable. 
     *  Ignored for modes other than standard UART. The RX functionality 
     *  has to be enabled.
    */
    uint32 enableWake;
    
    /** Size of the RX buffer in bytes/words (depends on rxDataBits parameter). 
     *  A value equal to the RX FIFO depth implies the usage of buffering in 
     *  hardware. A value greater than the RX FIFO depth results in a software 
     *  buffer.
     *  The UART_INTR _RX_NOT_EMPTY interrupt has to be enabled to 
     *  transfer data into the software buffer.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words for PSoC 4100 / 
     *    PSoC 4200 devices.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words or 16 
     *    bytes (Byte mode is enabled) for PSoC 4100 BLE / PSoC 4200 BLE / 
     *    PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S / 
     *    PSoC Analog Coprocessor devices.
    */
    uint32 rxBufferSize;
    
    /** Buffer space provided for a RX software buffer:
     *  - A NULL pointer must be provided to use hardware buffering.
     *  - A pointer to an allocated buffer must be provided to use software 
     *    buffering. The buffer size must equal (rxBufferSize + 1) in bytes if 
     *    dataBitsRx is less or equal to 8, otherwise (2 * (rxBufferSize + 1)) 
     *    in bytes. The software RX buffer always keeps one element empty. 
     *    For correct operation the allocated RX buffer has to be one element 
     *    greater than maximum packet size expected to be received.
    */
    uint8* rxBuffer;
    
    /** Size of the TX buffer in bytes/words(depends on txDataBits parameter). 
     *  A value equal to the TX FIFO depth implies the usage of buffering in 
     *  hardware. A value greater than the TX FIFO depth results in a software 
     *  buffer.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words for PSoC 4100 / 
     *    PSoC 4200 devices.
     *  - The RX and TX FIFO depth is equal to 8 bytes/words or 16 
     *    bytes (Byte mode is enabled) for PSoC 4100 BLE / PSoC 4200 BLE / 
     *    PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S / 
     *    PSoC Analog Coprocessor devices.
    */
    uint32 txBufferSize;
    
    /** Buffer space provided for a TX software buffer:
     *  - A NULL pointer must be provided to use hardware buffering.
     *  - A pointer to an allocated buffer must be provided to use software 
     *    buffering. The buffer size must equal txBufferSize if dataBitsTx is 
     *    less or eqal to 8, otherwise (2* txBufferSize).
    */
    uint8* txBuffer;
    
    /** Enables multiprocessor mode: 0 – disable, 1 – enable.
    */
    uint32 enableMultiproc;
    
    /** Enables matched address to be accepted: 0 – disable, 1 – enable.
    */
    uint32 multiprocAcceptAddr;
    
    /** 8 bit address to match in Multiprocessor mode. Ignored for other modes.
    */
    uint32 multiprocAddr;
    
    /** 8 bit mask of address bits that are compared for a Multiprocessor 
     *  address match. Ignored for other modes.
     *  - Bit value 0 – excludes bit from address comparison.
     *  - Bit value 1 – the bit needs to match with the corresponding bit 
     *   of the device address.
    */
    uint32 multiprocAddrMask;
    
    /** Enables component interrupt: 0 – disable, 1 – enable.
     *  The interrupt has to be enabled if software buffer is used.
    */
    uint32 enableInterrupt;
    
    /** Mask of interrupt sources to enable in the RX direction. This mask is 
     *  written regardless of the setting of the enableInterrupt field. 
     *  Multiple sources are enabled by providing a value that is the OR of 
     *  all of the following sources to enable:
     *  - UART_INTR_RX_FIFO_LEVEL
     *  - UART_INTR_RX_NOT_EMPTY
     *  - UART_INTR_RX_FULL
     *  - UART_INTR_RX_OVERFLOW
     *  - UART_INTR_RX_UNDERFLOW
     *  - UART_INTR_RX_FRAME_ERROR
     *  - UART_INTR_RX_PARITY_ERROR
    */
    uint32 rxInterruptMask;
    
    /** FIFO level for an RX FIFO level interrupt. This value is written 
     *  regardless of whether the RX FIFO level interrupt source is enabled.
    */
    uint32 rxTriggerLevel;
    
    /** Mask of interrupt sources to enable in the TX direction. This mask is 
     *  written regardless of the setting of the enableInterrupt field. 
     *  Multiple sources are enabled by providing a value that is the OR of 
     *  all of the following sources to enable:
     *  - UART_INTR_TX_FIFO_LEVEL
     *  - UART_INTR_TX_NOT_FULL
     *  - UART_INTR_TX_EMPTY
     *  - UART_INTR_TX_OVERFLOW
     *  - UART_INTR_TX_UNDERFLOW
     *  - UART_INTR_TX_UART_DONE
     *  - UART_INTR_TX_UART_NACK
     *  - UART_INTR_TX_UART_ARB_LOST
    */
    uint32 txInterruptMask;
    
    /** FIFO level for a TX FIFO level interrupt. This value is written 
     *  regardless of whether the TX FIFO level interrupt source is enabled.
    */
    uint32 txTriggerLevel;
    
    /** When enabled the TX and RX FIFO depth is doubled and equal to 
     *  16 bytes: 0 – disable, 1 – enable. This implies that number of 
     *  Data bits must be less than or equal to 8.
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE / 
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S / 
     *  PSoC Analog Coprocessor.
    */
    uint8 enableByteMode;
    
    /** Enables usage of CTS input signal by the UART transmitter : 0 – disable,
     *  1 – enable.
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE / 
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S / 
     *  PSoC Analog Coprocessor.
    */    
    uint8 enableCts;
    
    /** Sets active polarity of CTS input signal: 
     *  - UART_UART_CTS_ACTIVE_LOW
     *  - UART_UART_CTS_ACTIVE_HIGH
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE / 
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S / 
     *  PSoC Analog Coprocessor.
    */
    uint8 ctsPolarity;
    
    /** RX FIFO level for RTS signal activation. While the RX FIFO has fewer 
     *  entries than the RTS FIFO level value the RTS signal remains active, 
     *  otherwise the RTS signal becomes inactive. By setting this field to 0, 
     *  RTS signal activation is disabled.
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE / 
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S / 
     *  PSoC Analog Coprocessor.
    */
    uint8 rtsRxFifoLevel;

    /** Sets active polarity of RTS output signal: 
     *  - UART_UART_RTS_ ACTIVE_LOW 
     *  - UART_UART_RTS_ACTIVE_HIGH
     *
     *  Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE / 
     *  PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S / 
     *  PSoC Analog Coprocessor.
    */
    uint8 rtsPolarity;
} UART_UART_INIT_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_spi
* @{
*/
/* SPI specific functions */
#if(UART_SCB_MODE_UNCONFIG_CONST_CFG)
    void UART_SpiInit(const UART_SPI_INIT_STRUCT *config);
#endif /* (UART_SCB_MODE_UNCONFIG_CONST_CFG) */


#if(UART_SCB_MODE_SPI_INC)
    /*******************************************************************************
    * Function Name: UART_SpiIsBusBusy
    ****************************************************************************//**
    *
    *  Returns the current status on the bus. The bus status is determined using 
    *  the slave select signal.
    *  - Motorola and National Semiconductor sub-modes: The bus is busy after 
    *    the slave select line is activated and lasts until the slave select line 
    *    is deactivated.
    *  - Texas Instrument sub-modes: The bus is busy at the moment of the initial 
    *    pulse on the slave select line and lasts until the transfer is complete.
    *    If SPI Master is configured to use "Separated transfers" 
    *    (see Continuous versus Separated Transfer Separation), the bus is busy 
    *    during each element transfer and is free between each element transfer. 
    *    The Master does not activate SS line immediately after data has been 
    *    written into the TX FIFO.
    *
    *  \return slaveSelect: Current status on the bus. 
    *   If the returned value is nonzero, the bus is busy. 
    *   If zero is returned, the bus is free. The bus status is determined using 
    *   the slave select signal.
    *
    *******************************************************************************/
    #define UART_SpiIsBusBusy() ((uint32) (0u != (UART_SPI_STATUS_REG & \
                                                              UART_SPI_STATUS_BUS_BUSY)))

    #if (UART_SPI_MASTER_CONST)
        void UART_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(UART_SPI_MASTER_CONST) */

    #if !(UART_CY_SCBIP_V0 || UART_CY_SCBIP_V1)
        void UART_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(UART_CY_SCBIP_V0 || UART_CY_SCBIP_V1) */
#endif /* (UART_SCB_MODE_SPI_INC) */
/** @} spi */

/**
* \addtogroup group_uart
* @{
*/
/* UART specific functions */
#if(UART_SCB_MODE_UNCONFIG_CONST_CFG)
    void UART_UartInit(const UART_UART_INIT_STRUCT *config);
#endif /* (UART_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(UART_SCB_MODE_UART_INC)
    void UART_UartSetRxAddress(uint32 address);
    void UART_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(UART_UART_RX_DIRECTION)
        uint32 UART_UartGetChar(void);
        uint32 UART_UartGetByte(void);

        #if !(UART_CY_SCBIP_V0 || UART_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void UART_UartSetRtsPolarity(uint32 polarity);
            void UART_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(UART_CY_SCBIP_V0 || UART_CY_SCBIP_V1) */
    #endif /* (UART_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(UART_UART_TX_DIRECTION)
        /*******************************************************************************
        * Function Name: UART_UartPutChar
        ****************************************************************************//**
        *
        *  Places a byte of data in the transmit buffer to be sent at the next available
        *  bus time. This function is blocking and waits until there is a space 
        *  available to put requested data in the transmit buffer.
        *  For UART Multi Processor mode this function can send 9-bits data as well. 
        *  Use UART_UART_MP_MARK to add a mark to create an address byte.
        *
        *  \param txDataByte: the data to be transmitted.
        *
        *******************************************************************************/
        #define UART_UartPutChar(ch)    UART_SpiUartWriteTxData((uint32)(ch))
        
        void UART_UartPutString(const char8 string[]);
        void UART_UartPutCRLF(uint32 txDataByte);

        #if !(UART_CY_SCBIP_V0 || UART_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void UART_UartEnableCts(void);
            void UART_UartDisableCts(void);
            void UART_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(UART_CY_SCBIP_V0 || UART_CY_SCBIP_V1) */
    #endif /* (UART_UART_TX_DIRECTION) */
#endif /* (UART_SCB_MODE_UART_INC) */
/** @} uart */

/**
* \addtogroup group_spi_uart
* @{
*/
#if(UART_RX_DIRECTION)
    uint32 UART_SpiUartReadRxData(void);
    uint32 UART_SpiUartGetRxBufferSize(void);
    void   UART_SpiUartClearRxBuffer(void);
#endif /* (UART_RX_DIRECTION) */

/* Common APIs TX direction */
#if(UART_TX_DIRECTION)
    void   UART_SpiUartWriteTxData(uint32 txData);
    void   UART_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 UART_SpiUartGetTxBufferSize(void);
    void   UART_SpiUartClearTxBuffer(void);
#endif /* (UART_TX_DIRECTION) */
/** @} spi_uart */

CY_ISR_PROTO(UART_SPI_UART_ISR);

#if(UART_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(UART_UART_WAKEUP_ISR);
#endif /* (UART_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   UART_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 UART_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   UART_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 UART_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(UART_INTERNAL_RX_SW_BUFFER_CONST)
        #define UART_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    UART_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define UART_GetWordFromRxBuffer(idx) UART_rxBufferInternal[(idx)]

    #endif /* (UART_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(UART_INTERNAL_TX_SW_BUFFER_CONST)
        #define UART_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        UART_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define UART_GetWordFromTxBuffer(idx) UART_txBufferInternal[(idx)]

    #endif /* (UART_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (UART_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define UART_SPI_MODE_MOTOROLA      (0x00u)
#define UART_SPI_MODE_TI_COINCIDES  (0x01u)
#define UART_SPI_MODE_TI_PRECEDES   (0x11u)
#define UART_SPI_MODE_NATIONAL      (0x02u)
#define UART_SPI_MODE_MASK          (0x03u)
#define UART_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define UART_SPI_MODE_NS_MICROWIRE  (UART_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define UART_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define UART_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define UART_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define UART_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define UART_BITS_ORDER_LSB_FIRST   (0u)
#define UART_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define UART_SPI_TRANSFER_SEPARATED     (0u)
#define UART_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define UART_SPI_SLAVE_SELECT0    (UART_SCB__SS0_POSISTION)
#define UART_SPI_SLAVE_SELECT1    (UART_SCB__SS1_POSISTION)
#define UART_SPI_SLAVE_SELECT2    (UART_SCB__SS2_POSISTION)
#define UART_SPI_SLAVE_SELECT3    (UART_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define UART_SPI_SS_ACTIVE_LOW  (0u)
#define UART_SPI_SS_ACTIVE_HIGH (1u)

#define UART_INTR_SPIM_TX_RESTORE   (UART_INTR_TX_OVERFLOW)

#define UART_INTR_SPIS_TX_RESTORE     (UART_INTR_TX_OVERFLOW | \
                                                 UART_INTR_TX_UNDERFLOW)

/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define UART_UART_MODE_STD          (0u)
#define UART_UART_MODE_SMARTCARD    (1u)
#define UART_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define UART_UART_RX    (1u)
#define UART_UART_TX    (2u)
#define UART_UART_TX_RX (3u)

/* UART parity enum */
#define UART_UART_PARITY_EVEN   (0u)
#define UART_UART_PARITY_ODD    (1u)
#define UART_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define UART_UART_STOP_BITS_1   (2u)
#define UART_UART_STOP_BITS_1_5 (3u)
#define UART_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define UART_UART_IRDA_LP_OVS16     (16u)
#define UART_UART_IRDA_LP_OVS32     (32u)
#define UART_UART_IRDA_LP_OVS48     (48u)
#define UART_UART_IRDA_LP_OVS96     (96u)
#define UART_UART_IRDA_LP_OVS192    (192u)
#define UART_UART_IRDA_LP_OVS768    (768u)
#define UART_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define UART_UART_MP_MARK       (0x100u)
#define UART_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define UART_UART_CTS_ACTIVE_LOW    (0u)
#define UART_UART_CTS_ACTIVE_HIGH   (1u)
#define UART_UART_RTS_ACTIVE_LOW    (0u)
#define UART_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define UART_INTR_RX_ERR        (UART_INTR_RX_OVERFLOW    | \
                                             UART_INTR_RX_UNDERFLOW   | \
                                             UART_INTR_RX_FRAME_ERROR | \
                                             UART_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for UART_UartGetByte() */
#define UART_UART_RX_OVERFLOW       (UART_INTR_RX_OVERFLOW << 8u)
#define UART_UART_RX_UNDERFLOW      (UART_INTR_RX_UNDERFLOW << 8u)
#define UART_UART_RX_FRAME_ERROR    (UART_INTR_RX_FRAME_ERROR << 8u)
#define UART_UART_RX_PARITY_ERROR   (UART_INTR_RX_PARITY_ERROR << 8u)
#define UART_UART_RX_ERROR_MASK     (UART_UART_RX_OVERFLOW    | \
                                                 UART_UART_RX_UNDERFLOW   | \
                                                 UART_UART_RX_FRAME_ERROR | \
                                                 UART_UART_RX_PARITY_ERROR)

#define UART_INTR_UART_TX_RESTORE   (UART_INTR_TX_OVERFLOW  | \
                                                 UART_INTR_TX_UART_NACK | \
                                                 UART_INTR_TX_UART_DONE | \
                                                 UART_INTR_TX_UART_ARB_LOST)


/***************************************
*     Vars with External Linkage
***************************************/

#if(UART_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const UART_SPI_INIT_STRUCT  UART_configSpi;
    extern const UART_UART_INIT_STRUCT UART_configUart;
#endif /* (UART_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (UART_UART_WAKE_ENABLE_CONST && UART_UART_RX_WAKEUP_IRQ)
    extern uint8 UART_skipStart;
#endif /* (UART_UART_WAKE_ENABLE_CONST && UART_UART_RX_WAKEUP_IRQ) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define UART_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & UART_INTR_SLAVE_SPI_BUS_ERROR)
#define UART_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & UART_INTR_MASTER_SPI_DONE)
#define UART_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~UART_INTR_SLAVE_SPI_BUS_ERROR)

#define UART_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~UART_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define UART_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((UART_UART_IRDA_LP_OVS16   == (oversample)) ? UART_CTRL_OVS_IRDA_LP_OVS16 : \
         ((UART_UART_IRDA_LP_OVS32   == (oversample)) ? UART_CTRL_OVS_IRDA_LP_OVS32 : \
          ((UART_UART_IRDA_LP_OVS48   == (oversample)) ? UART_CTRL_OVS_IRDA_LP_OVS48 : \
           ((UART_UART_IRDA_LP_OVS96   == (oversample)) ? UART_CTRL_OVS_IRDA_LP_OVS96 : \
            ((UART_UART_IRDA_LP_OVS192  == (oversample)) ? UART_CTRL_OVS_IRDA_LP_OVS192 : \
             ((UART_UART_IRDA_LP_OVS768  == (oversample)) ? UART_CTRL_OVS_IRDA_LP_OVS768 : \
              ((UART_UART_IRDA_LP_OVS1536 == (oversample)) ? UART_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          UART_CTRL_OVS_IRDA_LP_OVS16)))))))

#define UART_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (UART_UART_RX & (direction))) ? \
                                                                     (UART_RX_CTRL_ENABLED) : (0u))

#define UART_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (UART_UART_TX & (direction))) ? \
                                                                     (UART_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define UART_CTRL_SPI      (UART_CTRL_MODE_SPI)
#define UART_SPI_RX_CTRL   (UART_RX_CTRL_ENABLED)
#define UART_SPI_TX_CTRL   (UART_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define UART_SPI_SS_POLARITY \
             (((uint32) UART_SPI_SS0_POLARITY << UART_SPI_SLAVE_SELECT0) | \
              ((uint32) UART_SPI_SS1_POLARITY << UART_SPI_SLAVE_SELECT1) | \
              ((uint32) UART_SPI_SS2_POLARITY << UART_SPI_SLAVE_SELECT2) | \
              ((uint32) UART_SPI_SS3_POLARITY << UART_SPI_SLAVE_SELECT3))

#if(UART_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define UART_SPI_DEFAULT_CTRL \
                    (UART_GET_CTRL_OVS(UART_SPI_OVS_FACTOR) | \
                     UART_GET_CTRL_BYTE_MODE (UART_SPI_BYTE_MODE_ENABLE) | \
                     UART_GET_CTRL_EC_AM_MODE(UART_SPI_WAKE_ENABLE)      | \
                     UART_CTRL_SPI)

    #define UART_SPI_DEFAULT_SPI_CTRL \
                    (UART_GET_SPI_CTRL_CONTINUOUS    (UART_SPI_TRANSFER_SEPARATION)       | \
                     UART_GET_SPI_CTRL_SELECT_PRECEDE(UART_SPI_SUB_MODE &                   \
                                                                  UART_SPI_MODE_TI_PRECEDES_MASK)     | \
                     UART_GET_SPI_CTRL_SCLK_MODE     (UART_SPI_CLOCK_MODE)                | \
                     UART_GET_SPI_CTRL_LATE_MISO_SAMPLE(UART_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     UART_GET_SPI_CTRL_SCLK_CONTINUOUS(UART_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     UART_GET_SPI_CTRL_SSEL_POLARITY (UART_SPI_SS_POLARITY)               | \
                     UART_GET_SPI_CTRL_SUB_MODE      (UART_SPI_SUB_MODE)                  | \
                     UART_GET_SPI_CTRL_MASTER_MODE   (UART_SPI_MODE))

    /* RX direction */
    #define UART_SPI_DEFAULT_RX_CTRL \
                    (UART_GET_RX_CTRL_DATA_WIDTH(UART_SPI_RX_DATA_BITS_NUM)     | \
                     UART_GET_RX_CTRL_BIT_ORDER (UART_SPI_BITS_ORDER)           | \
                     UART_GET_RX_CTRL_MEDIAN    (UART_SPI_MEDIAN_FILTER_ENABLE) | \
                     UART_SPI_RX_CTRL)

    #define UART_SPI_DEFAULT_RX_FIFO_CTRL \
                    UART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(UART_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define UART_SPI_DEFAULT_TX_CTRL \
                    (UART_GET_TX_CTRL_DATA_WIDTH(UART_SPI_TX_DATA_BITS_NUM) | \
                     UART_GET_TX_CTRL_BIT_ORDER (UART_SPI_BITS_ORDER)       | \
                     UART_SPI_TX_CTRL)

    #define UART_SPI_DEFAULT_TX_FIFO_CTRL \
                    UART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(UART_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define UART_SPI_DEFAULT_INTR_SPI_EC_MASK   (UART_NO_INTR_SOURCES)

    #define UART_SPI_DEFAULT_INTR_I2C_EC_MASK   (UART_NO_INTR_SOURCES)
    #define UART_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (UART_SPI_INTR_RX_MASK & UART_INTR_SLAVE_SPI_BUS_ERROR)

    #define UART_SPI_DEFAULT_INTR_MASTER_MASK \
                    (UART_SPI_INTR_TX_MASK & UART_INTR_MASTER_SPI_DONE)

    #define UART_SPI_DEFAULT_INTR_RX_MASK \
                    (UART_SPI_INTR_RX_MASK & (uint32) ~UART_INTR_SLAVE_SPI_BUS_ERROR)

    #define UART_SPI_DEFAULT_INTR_TX_MASK \
                    (UART_SPI_INTR_TX_MASK & (uint32) ~UART_INTR_MASTER_SPI_DONE)

#endif /* (UART_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define UART_CTRL_UART      (UART_CTRL_MODE_UART)
#define UART_UART_RX_CTRL   (UART_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define UART_UART_TX_CTRL   (UART_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(UART_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(UART_UART_MODE_IRDA == UART_UART_SUB_MODE)

        #define UART_DEFAULT_CTRL_OVS   ((0u != UART_UART_IRDA_LOW_POWER) ?              \
                                (UART_UART_GET_CTRL_OVS_IRDA_LP(UART_UART_OVS_FACTOR)) : \
                                (UART_CTRL_OVS_IRDA_OVS16))

    #else

        #define UART_DEFAULT_CTRL_OVS   UART_GET_CTRL_OVS(UART_UART_OVS_FACTOR)

    #endif /* (UART_UART_MODE_IRDA == UART_UART_SUB_MODE) */

    #define UART_UART_DEFAULT_CTRL \
                                (UART_GET_CTRL_BYTE_MODE  (UART_UART_BYTE_MODE_ENABLE)  | \
                                 UART_GET_CTRL_ADDR_ACCEPT(UART_UART_MP_ACCEPT_ADDRESS) | \
                                 UART_DEFAULT_CTRL_OVS                                              | \
                                 UART_CTRL_UART)

    #define UART_UART_DEFAULT_UART_CTRL \
                                    (UART_GET_UART_CTRL_MODE(UART_UART_SUB_MODE))

    /* RX direction */
    #define UART_UART_DEFAULT_RX_CTRL_PARITY \
                                ((UART_UART_PARITY_NONE != UART_UART_PARITY_TYPE) ?      \
                                  (UART_GET_UART_RX_CTRL_PARITY(UART_UART_PARITY_TYPE) | \
                                   UART_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define UART_UART_DEFAULT_UART_RX_CTRL \
                    (UART_GET_UART_RX_CTRL_MODE(UART_UART_STOP_BITS_NUM)                    | \
                     UART_GET_UART_RX_CTRL_POLARITY(UART_UART_IRDA_POLARITY)                | \
                     UART_GET_UART_RX_CTRL_MP_MODE(UART_UART_MP_MODE_ENABLE)                | \
                     UART_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(UART_UART_DROP_ON_PARITY_ERR) | \
                     UART_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(UART_UART_DROP_ON_FRAME_ERR)   | \
                     UART_UART_DEFAULT_RX_CTRL_PARITY)

    #define UART_UART_DEFAULT_RX_CTRL \
                                (UART_GET_RX_CTRL_DATA_WIDTH(UART_UART_DATA_BITS_NUM)        | \
                                 UART_GET_RX_CTRL_MEDIAN    (UART_UART_MEDIAN_FILTER_ENABLE) | \
                                 UART_GET_UART_RX_CTRL_ENABLED(UART_UART_DIRECTION))

    #define UART_UART_DEFAULT_RX_FIFO_CTRL \
                                UART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(UART_UART_RX_TRIGGER_LEVEL)

    #define UART_UART_DEFAULT_RX_MATCH_REG  ((0u != UART_UART_MP_MODE_ENABLE) ?          \
                                (UART_GET_RX_MATCH_ADDR(UART_UART_MP_RX_ADDRESS) | \
                                 UART_GET_RX_MATCH_MASK(UART_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define UART_UART_DEFAULT_TX_CTRL_PARITY (UART_UART_DEFAULT_RX_CTRL_PARITY)

    #define UART_UART_DEFAULT_UART_TX_CTRL \
                                (UART_GET_UART_TX_CTRL_MODE(UART_UART_STOP_BITS_NUM)       | \
                                 UART_GET_UART_TX_CTRL_RETRY_NACK(UART_UART_RETRY_ON_NACK) | \
                                 UART_UART_DEFAULT_TX_CTRL_PARITY)

    #define UART_UART_DEFAULT_TX_CTRL \
                                (UART_GET_TX_CTRL_DATA_WIDTH(UART_UART_DATA_BITS_NUM) | \
                                 UART_GET_UART_TX_CTRL_ENABLED(UART_UART_DIRECTION))

    #define UART_UART_DEFAULT_TX_FIFO_CTRL \
                                UART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(UART_UART_TX_TRIGGER_LEVEL)

    #define UART_UART_DEFAULT_FLOW_CTRL \
                        (UART_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(UART_UART_RTS_FIFO_LEVEL) | \
                         UART_GET_UART_FLOW_CTRL_RTS_POLARITY (UART_UART_RTS_POLARITY)   | \
                         UART_GET_UART_FLOW_CTRL_CTS_POLARITY (UART_UART_CTS_POLARITY)   | \
                         UART_GET_UART_FLOW_CTRL_CTS_ENABLE   (UART_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define UART_UART_DEFAULT_INTR_I2C_EC_MASK  (UART_NO_INTR_SOURCES)
    #define UART_UART_DEFAULT_INTR_SPI_EC_MASK  (UART_NO_INTR_SOURCES)
    #define UART_UART_DEFAULT_INTR_SLAVE_MASK   (UART_NO_INTR_SOURCES)
    #define UART_UART_DEFAULT_INTR_MASTER_MASK  (UART_NO_INTR_SOURCES)
    #define UART_UART_DEFAULT_INTR_RX_MASK      (UART_UART_INTR_RX_MASK)
    #define UART_UART_DEFAULT_INTR_TX_MASK      (UART_UART_INTR_TX_MASK)

#endif /* (UART_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define UART_SPIM_ACTIVE_SS0    (UART_SPI_SLAVE_SELECT0)
#define UART_SPIM_ACTIVE_SS1    (UART_SPI_SLAVE_SELECT1)
#define UART_SPIM_ACTIVE_SS2    (UART_SPI_SLAVE_SELECT2)
#define UART_SPIM_ACTIVE_SS3    (UART_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_UART_H */


/* [] END OF FILE */
