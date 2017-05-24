/***************************************************************************//**
* \file UART_PINS.h
* \version 3.20
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
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

#if !defined(CY_SCB_PINS_UART_H)
#define CY_SCB_PINS_UART_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define UART_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define UART_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define UART_REMOVE_TX_SDA_MISO_PIN      (1u)
#define UART_REMOVE_SCLK_PIN      (1u)
#define UART_REMOVE_SS0_PIN      (1u)
#define UART_REMOVE_SS1_PIN                 (1u)
#define UART_REMOVE_SS2_PIN                 (1u)
#define UART_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define UART_REMOVE_I2C_PINS                (1u)
#define UART_REMOVE_SPI_MASTER_PINS         (1u)
#define UART_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define UART_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define UART_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define UART_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define UART_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define UART_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define UART_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define UART_REMOVE_SPI_SLAVE_PINS          (1u)
#define UART_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define UART_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define UART_REMOVE_UART_TX_PIN             (0u)
#define UART_REMOVE_UART_RX_TX_PIN          (1u)
#define UART_REMOVE_UART_RX_PIN             (0u)
#define UART_REMOVE_UART_RX_WAKE_PIN        (1u)
#define UART_REMOVE_UART_RTS_PIN            (1u)
#define UART_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define UART_RX_WAKE_SCL_MOSI_PIN (0u == UART_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define UART_RX_SCL_MOSI_PIN     (0u == UART_REMOVE_RX_SCL_MOSI_PIN)
#define UART_TX_SDA_MISO_PIN     (0u == UART_REMOVE_TX_SDA_MISO_PIN)
#define UART_SCLK_PIN     (0u == UART_REMOVE_SCLK_PIN)
#define UART_SS0_PIN     (0u == UART_REMOVE_SS0_PIN)
#define UART_SS1_PIN                (0u == UART_REMOVE_SS1_PIN)
#define UART_SS2_PIN                (0u == UART_REMOVE_SS2_PIN)
#define UART_SS3_PIN                (0u == UART_REMOVE_SS3_PIN)

/* Mode defined pins */
#define UART_I2C_PINS               (0u == UART_REMOVE_I2C_PINS)
#define UART_SPI_MASTER_PINS        (0u == UART_REMOVE_SPI_MASTER_PINS)
#define UART_SPI_MASTER_SCLK_PIN    (0u == UART_REMOVE_SPI_MASTER_SCLK_PIN)
#define UART_SPI_MASTER_MOSI_PIN    (0u == UART_REMOVE_SPI_MASTER_MOSI_PIN)
#define UART_SPI_MASTER_MISO_PIN    (0u == UART_REMOVE_SPI_MASTER_MISO_PIN)
#define UART_SPI_MASTER_SS0_PIN     (0u == UART_REMOVE_SPI_MASTER_SS0_PIN)
#define UART_SPI_MASTER_SS1_PIN     (0u == UART_REMOVE_SPI_MASTER_SS1_PIN)
#define UART_SPI_MASTER_SS2_PIN     (0u == UART_REMOVE_SPI_MASTER_SS2_PIN)
#define UART_SPI_MASTER_SS3_PIN     (0u == UART_REMOVE_SPI_MASTER_SS3_PIN)
#define UART_SPI_SLAVE_PINS         (0u == UART_REMOVE_SPI_SLAVE_PINS)
#define UART_SPI_SLAVE_MOSI_PIN     (0u == UART_REMOVE_SPI_SLAVE_MOSI_PIN)
#define UART_SPI_SLAVE_MISO_PIN     (0u == UART_REMOVE_SPI_SLAVE_MISO_PIN)
#define UART_UART_TX_PIN            (0u == UART_REMOVE_UART_TX_PIN)
#define UART_UART_RX_TX_PIN         (0u == UART_REMOVE_UART_RX_TX_PIN)
#define UART_UART_RX_PIN            (0u == UART_REMOVE_UART_RX_PIN)
#define UART_UART_RX_WAKE_PIN       (0u == UART_REMOVE_UART_RX_WAKE_PIN)
#define UART_UART_RTS_PIN           (0u == UART_REMOVE_UART_RTS_PIN)
#define UART_UART_CTS_PIN           (0u == UART_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (UART_RX_WAKE_SCL_MOSI_PIN)
    #include "UART_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (UART_RX_SCL_MOSI) */

#if (UART_RX_SCL_MOSI_PIN)
    #include "UART_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (UART_RX_SCL_MOSI) */

#if (UART_TX_SDA_MISO_PIN)
    #include "UART_uart_tx_i2c_sda_spi_miso.h"
#endif /* (UART_TX_SDA_MISO) */

#if (UART_SCLK_PIN)
    #include "UART_spi_sclk.h"
#endif /* (UART_SCLK) */

#if (UART_SS0_PIN)
    #include "UART_spi_ss0.h"
#endif /* (UART_SS0_PIN) */

#if (UART_SS1_PIN)
    #include "UART_spi_ss1.h"
#endif /* (UART_SS1_PIN) */

#if (UART_SS2_PIN)
    #include "UART_spi_ss2.h"
#endif /* (UART_SS2_PIN) */

#if (UART_SS3_PIN)
    #include "UART_spi_ss3.h"
#endif /* (UART_SS3_PIN) */

#if (UART_I2C_PINS)
    #include "UART_scl.h"
    #include "UART_sda.h"
#endif /* (UART_I2C_PINS) */

#if (UART_SPI_MASTER_PINS)
#if (UART_SPI_MASTER_SCLK_PIN)
    #include "UART_sclk_m.h"
#endif /* (UART_SPI_MASTER_SCLK_PIN) */

#if (UART_SPI_MASTER_MOSI_PIN)
    #include "UART_mosi_m.h"
#endif /* (UART_SPI_MASTER_MOSI_PIN) */

#if (UART_SPI_MASTER_MISO_PIN)
    #include "UART_miso_m.h"
#endif /*(UART_SPI_MASTER_MISO_PIN) */
#endif /* (UART_SPI_MASTER_PINS) */

#if (UART_SPI_SLAVE_PINS)
    #include "UART_sclk_s.h"
    #include "UART_ss_s.h"

#if (UART_SPI_SLAVE_MOSI_PIN)
    #include "UART_mosi_s.h"
#endif /* (UART_SPI_SLAVE_MOSI_PIN) */

#if (UART_SPI_SLAVE_MISO_PIN)
    #include "UART_miso_s.h"
#endif /*(UART_SPI_SLAVE_MISO_PIN) */
#endif /* (UART_SPI_SLAVE_PINS) */

#if (UART_SPI_MASTER_SS0_PIN)
    #include "UART_ss0_m.h"
#endif /* (UART_SPI_MASTER_SS0_PIN) */

#if (UART_SPI_MASTER_SS1_PIN)
    #include "UART_ss1_m.h"
#endif /* (UART_SPI_MASTER_SS1_PIN) */

#if (UART_SPI_MASTER_SS2_PIN)
    #include "UART_ss2_m.h"
#endif /* (UART_SPI_MASTER_SS2_PIN) */

#if (UART_SPI_MASTER_SS3_PIN)
    #include "UART_ss3_m.h"
#endif /* (UART_SPI_MASTER_SS3_PIN) */

#if (UART_UART_TX_PIN)
    #include "UART_tx.h"
#endif /* (UART_UART_TX_PIN) */

#if (UART_UART_RX_TX_PIN)
    #include "UART_rx_tx.h"
#endif /* (UART_UART_RX_TX_PIN) */

#if (UART_UART_RX_PIN)
    #include "UART_rx.h"
#endif /* (UART_UART_RX_PIN) */

#if (UART_UART_RX_WAKE_PIN)
    #include "UART_rx_wake.h"
#endif /* (UART_UART_RX_WAKE_PIN) */

#if (UART_UART_RTS_PIN)
    #include "UART_rts.h"
#endif /* (UART_UART_RTS_PIN) */

#if (UART_UART_CTS_PIN)
    #include "UART_cts.h"
#endif /* (UART_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (UART_RX_SCL_MOSI_PIN)
    #define UART_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) UART_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define UART_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) UART_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define UART_RX_SCL_MOSI_HSIOM_MASK      (UART_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define UART_RX_SCL_MOSI_HSIOM_POS       (UART_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define UART_RX_SCL_MOSI_HSIOM_SEL_GPIO  (UART_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define UART_RX_SCL_MOSI_HSIOM_SEL_I2C   (UART_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define UART_RX_SCL_MOSI_HSIOM_SEL_SPI   (UART_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define UART_RX_SCL_MOSI_HSIOM_SEL_UART  (UART_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (UART_RX_WAKE_SCL_MOSI_PIN)
    #define UART_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) UART_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define UART_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) UART_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define UART_RX_WAKE_SCL_MOSI_HSIOM_MASK      (UART_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define UART_RX_WAKE_SCL_MOSI_HSIOM_POS       (UART_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define UART_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (UART_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define UART_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (UART_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define UART_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (UART_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define UART_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (UART_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define UART_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) UART_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define UART_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) UART_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define UART_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (UART_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define UART_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) UART_INTCFG_TYPE_MASK << \
                                                                           UART_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins UART_RX_SCL_MOSI_PIN or UART_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (UART_RX_SCL_MOSI_PIN) */

#if (UART_TX_SDA_MISO_PIN)
    #define UART_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) UART_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define UART_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) UART_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define UART_TX_SDA_MISO_HSIOM_MASK      (UART_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define UART_TX_SDA_MISO_HSIOM_POS       (UART_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define UART_TX_SDA_MISO_HSIOM_SEL_GPIO  (UART_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define UART_TX_SDA_MISO_HSIOM_SEL_I2C   (UART_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define UART_TX_SDA_MISO_HSIOM_SEL_SPI   (UART_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define UART_TX_SDA_MISO_HSIOM_SEL_UART  (UART_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (UART_TX_SDA_MISO_PIN) */

#if (UART_SCLK_PIN)
    #define UART_SCLK_HSIOM_REG   (*(reg32 *) UART_spi_sclk__0__HSIOM)
    #define UART_SCLK_HSIOM_PTR   ( (reg32 *) UART_spi_sclk__0__HSIOM)
    
    #define UART_SCLK_HSIOM_MASK      (UART_spi_sclk__0__HSIOM_MASK)
    #define UART_SCLK_HSIOM_POS       (UART_spi_sclk__0__HSIOM_SHIFT)
    #define UART_SCLK_HSIOM_SEL_GPIO  (UART_spi_sclk__0__HSIOM_GPIO)
    #define UART_SCLK_HSIOM_SEL_I2C   (UART_spi_sclk__0__HSIOM_I2C)
    #define UART_SCLK_HSIOM_SEL_SPI   (UART_spi_sclk__0__HSIOM_SPI)
    #define UART_SCLK_HSIOM_SEL_UART  (UART_spi_sclk__0__HSIOM_UART)
#endif /* (UART_SCLK_PIN) */

#if (UART_SS0_PIN)
    #define UART_SS0_HSIOM_REG   (*(reg32 *) UART_spi_ss0__0__HSIOM)
    #define UART_SS0_HSIOM_PTR   ( (reg32 *) UART_spi_ss0__0__HSIOM)
    
    #define UART_SS0_HSIOM_MASK      (UART_spi_ss0__0__HSIOM_MASK)
    #define UART_SS0_HSIOM_POS       (UART_spi_ss0__0__HSIOM_SHIFT)
    #define UART_SS0_HSIOM_SEL_GPIO  (UART_spi_ss0__0__HSIOM_GPIO)
    #define UART_SS0_HSIOM_SEL_I2C   (UART_spi_ss0__0__HSIOM_I2C)
    #define UART_SS0_HSIOM_SEL_SPI   (UART_spi_ss0__0__HSIOM_SPI)
#if !(UART_CY_SCBIP_V0 || UART_CY_SCBIP_V1)
    #define UART_SS0_HSIOM_SEL_UART  (UART_spi_ss0__0__HSIOM_UART)
#endif /* !(UART_CY_SCBIP_V0 || UART_CY_SCBIP_V1) */
#endif /* (UART_SS0_PIN) */

#if (UART_SS1_PIN)
    #define UART_SS1_HSIOM_REG  (*(reg32 *) UART_spi_ss1__0__HSIOM)
    #define UART_SS1_HSIOM_PTR  ( (reg32 *) UART_spi_ss1__0__HSIOM)
    
    #define UART_SS1_HSIOM_MASK     (UART_spi_ss1__0__HSIOM_MASK)
    #define UART_SS1_HSIOM_POS      (UART_spi_ss1__0__HSIOM_SHIFT)
    #define UART_SS1_HSIOM_SEL_GPIO (UART_spi_ss1__0__HSIOM_GPIO)
    #define UART_SS1_HSIOM_SEL_I2C  (UART_spi_ss1__0__HSIOM_I2C)
    #define UART_SS1_HSIOM_SEL_SPI  (UART_spi_ss1__0__HSIOM_SPI)
#endif /* (UART_SS1_PIN) */

#if (UART_SS2_PIN)
    #define UART_SS2_HSIOM_REG     (*(reg32 *) UART_spi_ss2__0__HSIOM)
    #define UART_SS2_HSIOM_PTR     ( (reg32 *) UART_spi_ss2__0__HSIOM)
    
    #define UART_SS2_HSIOM_MASK     (UART_spi_ss2__0__HSIOM_MASK)
    #define UART_SS2_HSIOM_POS      (UART_spi_ss2__0__HSIOM_SHIFT)
    #define UART_SS2_HSIOM_SEL_GPIO (UART_spi_ss2__0__HSIOM_GPIO)
    #define UART_SS2_HSIOM_SEL_I2C  (UART_spi_ss2__0__HSIOM_I2C)
    #define UART_SS2_HSIOM_SEL_SPI  (UART_spi_ss2__0__HSIOM_SPI)
#endif /* (UART_SS2_PIN) */

#if (UART_SS3_PIN)
    #define UART_SS3_HSIOM_REG     (*(reg32 *) UART_spi_ss3__0__HSIOM)
    #define UART_SS3_HSIOM_PTR     ( (reg32 *) UART_spi_ss3__0__HSIOM)
    
    #define UART_SS3_HSIOM_MASK     (UART_spi_ss3__0__HSIOM_MASK)
    #define UART_SS3_HSIOM_POS      (UART_spi_ss3__0__HSIOM_SHIFT)
    #define UART_SS3_HSIOM_SEL_GPIO (UART_spi_ss3__0__HSIOM_GPIO)
    #define UART_SS3_HSIOM_SEL_I2C  (UART_spi_ss3__0__HSIOM_I2C)
    #define UART_SS3_HSIOM_SEL_SPI  (UART_spi_ss3__0__HSIOM_SPI)
#endif /* (UART_SS3_PIN) */

#if (UART_I2C_PINS)
    #define UART_SCL_HSIOM_REG  (*(reg32 *) UART_scl__0__HSIOM)
    #define UART_SCL_HSIOM_PTR  ( (reg32 *) UART_scl__0__HSIOM)
    
    #define UART_SCL_HSIOM_MASK     (UART_scl__0__HSIOM_MASK)
    #define UART_SCL_HSIOM_POS      (UART_scl__0__HSIOM_SHIFT)
    #define UART_SCL_HSIOM_SEL_GPIO (UART_sda__0__HSIOM_GPIO)
    #define UART_SCL_HSIOM_SEL_I2C  (UART_sda__0__HSIOM_I2C)
    
    #define UART_SDA_HSIOM_REG  (*(reg32 *) UART_sda__0__HSIOM)
    #define UART_SDA_HSIOM_PTR  ( (reg32 *) UART_sda__0__HSIOM)
    
    #define UART_SDA_HSIOM_MASK     (UART_sda__0__HSIOM_MASK)
    #define UART_SDA_HSIOM_POS      (UART_sda__0__HSIOM_SHIFT)
    #define UART_SDA_HSIOM_SEL_GPIO (UART_sda__0__HSIOM_GPIO)
    #define UART_SDA_HSIOM_SEL_I2C  (UART_sda__0__HSIOM_I2C)
#endif /* (UART_I2C_PINS) */

#if (UART_SPI_SLAVE_PINS)
    #define UART_SCLK_S_HSIOM_REG   (*(reg32 *) UART_sclk_s__0__HSIOM)
    #define UART_SCLK_S_HSIOM_PTR   ( (reg32 *) UART_sclk_s__0__HSIOM)
    
    #define UART_SCLK_S_HSIOM_MASK      (UART_sclk_s__0__HSIOM_MASK)
    #define UART_SCLK_S_HSIOM_POS       (UART_sclk_s__0__HSIOM_SHIFT)
    #define UART_SCLK_S_HSIOM_SEL_GPIO  (UART_sclk_s__0__HSIOM_GPIO)
    #define UART_SCLK_S_HSIOM_SEL_SPI   (UART_sclk_s__0__HSIOM_SPI)
    
    #define UART_SS0_S_HSIOM_REG    (*(reg32 *) UART_ss0_s__0__HSIOM)
    #define UART_SS0_S_HSIOM_PTR    ( (reg32 *) UART_ss0_s__0__HSIOM)
    
    #define UART_SS0_S_HSIOM_MASK       (UART_ss0_s__0__HSIOM_MASK)
    #define UART_SS0_S_HSIOM_POS        (UART_ss0_s__0__HSIOM_SHIFT)
    #define UART_SS0_S_HSIOM_SEL_GPIO   (UART_ss0_s__0__HSIOM_GPIO)  
    #define UART_SS0_S_HSIOM_SEL_SPI    (UART_ss0_s__0__HSIOM_SPI)
#endif /* (UART_SPI_SLAVE_PINS) */

#if (UART_SPI_SLAVE_MOSI_PIN)
    #define UART_MOSI_S_HSIOM_REG   (*(reg32 *) UART_mosi_s__0__HSIOM)
    #define UART_MOSI_S_HSIOM_PTR   ( (reg32 *) UART_mosi_s__0__HSIOM)
    
    #define UART_MOSI_S_HSIOM_MASK      (UART_mosi_s__0__HSIOM_MASK)
    #define UART_MOSI_S_HSIOM_POS       (UART_mosi_s__0__HSIOM_SHIFT)
    #define UART_MOSI_S_HSIOM_SEL_GPIO  (UART_mosi_s__0__HSIOM_GPIO)
    #define UART_MOSI_S_HSIOM_SEL_SPI   (UART_mosi_s__0__HSIOM_SPI)
#endif /* (UART_SPI_SLAVE_MOSI_PIN) */

#if (UART_SPI_SLAVE_MISO_PIN)
    #define UART_MISO_S_HSIOM_REG   (*(reg32 *) UART_miso_s__0__HSIOM)
    #define UART_MISO_S_HSIOM_PTR   ( (reg32 *) UART_miso_s__0__HSIOM)
    
    #define UART_MISO_S_HSIOM_MASK      (UART_miso_s__0__HSIOM_MASK)
    #define UART_MISO_S_HSIOM_POS       (UART_miso_s__0__HSIOM_SHIFT)
    #define UART_MISO_S_HSIOM_SEL_GPIO  (UART_miso_s__0__HSIOM_GPIO)
    #define UART_MISO_S_HSIOM_SEL_SPI   (UART_miso_s__0__HSIOM_SPI)
#endif /* (UART_SPI_SLAVE_MISO_PIN) */

#if (UART_SPI_MASTER_MISO_PIN)
    #define UART_MISO_M_HSIOM_REG   (*(reg32 *) UART_miso_m__0__HSIOM)
    #define UART_MISO_M_HSIOM_PTR   ( (reg32 *) UART_miso_m__0__HSIOM)
    
    #define UART_MISO_M_HSIOM_MASK      (UART_miso_m__0__HSIOM_MASK)
    #define UART_MISO_M_HSIOM_POS       (UART_miso_m__0__HSIOM_SHIFT)
    #define UART_MISO_M_HSIOM_SEL_GPIO  (UART_miso_m__0__HSIOM_GPIO)
    #define UART_MISO_M_HSIOM_SEL_SPI   (UART_miso_m__0__HSIOM_SPI)
#endif /* (UART_SPI_MASTER_MISO_PIN) */

#if (UART_SPI_MASTER_MOSI_PIN)
    #define UART_MOSI_M_HSIOM_REG   (*(reg32 *) UART_mosi_m__0__HSIOM)
    #define UART_MOSI_M_HSIOM_PTR   ( (reg32 *) UART_mosi_m__0__HSIOM)
    
    #define UART_MOSI_M_HSIOM_MASK      (UART_mosi_m__0__HSIOM_MASK)
    #define UART_MOSI_M_HSIOM_POS       (UART_mosi_m__0__HSIOM_SHIFT)
    #define UART_MOSI_M_HSIOM_SEL_GPIO  (UART_mosi_m__0__HSIOM_GPIO)
    #define UART_MOSI_M_HSIOM_SEL_SPI   (UART_mosi_m__0__HSIOM_SPI)
#endif /* (UART_SPI_MASTER_MOSI_PIN) */

#if (UART_SPI_MASTER_SCLK_PIN)
    #define UART_SCLK_M_HSIOM_REG   (*(reg32 *) UART_sclk_m__0__HSIOM)
    #define UART_SCLK_M_HSIOM_PTR   ( (reg32 *) UART_sclk_m__0__HSIOM)
    
    #define UART_SCLK_M_HSIOM_MASK      (UART_sclk_m__0__HSIOM_MASK)
    #define UART_SCLK_M_HSIOM_POS       (UART_sclk_m__0__HSIOM_SHIFT)
    #define UART_SCLK_M_HSIOM_SEL_GPIO  (UART_sclk_m__0__HSIOM_GPIO)
    #define UART_SCLK_M_HSIOM_SEL_SPI   (UART_sclk_m__0__HSIOM_SPI)
#endif /* (UART_SPI_MASTER_SCLK_PIN) */

#if (UART_SPI_MASTER_SS0_PIN)
    #define UART_SS0_M_HSIOM_REG    (*(reg32 *) UART_ss0_m__0__HSIOM)
    #define UART_SS0_M_HSIOM_PTR    ( (reg32 *) UART_ss0_m__0__HSIOM)
    
    #define UART_SS0_M_HSIOM_MASK       (UART_ss0_m__0__HSIOM_MASK)
    #define UART_SS0_M_HSIOM_POS        (UART_ss0_m__0__HSIOM_SHIFT)
    #define UART_SS0_M_HSIOM_SEL_GPIO   (UART_ss0_m__0__HSIOM_GPIO)
    #define UART_SS0_M_HSIOM_SEL_SPI    (UART_ss0_m__0__HSIOM_SPI)
#endif /* (UART_SPI_MASTER_SS0_PIN) */

#if (UART_SPI_MASTER_SS1_PIN)
    #define UART_SS1_M_HSIOM_REG    (*(reg32 *) UART_ss1_m__0__HSIOM)
    #define UART_SS1_M_HSIOM_PTR    ( (reg32 *) UART_ss1_m__0__HSIOM)
    
    #define UART_SS1_M_HSIOM_MASK       (UART_ss1_m__0__HSIOM_MASK)
    #define UART_SS1_M_HSIOM_POS        (UART_ss1_m__0__HSIOM_SHIFT)
    #define UART_SS1_M_HSIOM_SEL_GPIO   (UART_ss1_m__0__HSIOM_GPIO)
    #define UART_SS1_M_HSIOM_SEL_SPI    (UART_ss1_m__0__HSIOM_SPI)
#endif /* (UART_SPI_MASTER_SS1_PIN) */

#if (UART_SPI_MASTER_SS2_PIN)
    #define UART_SS2_M_HSIOM_REG    (*(reg32 *) UART_ss2_m__0__HSIOM)
    #define UART_SS2_M_HSIOM_PTR    ( (reg32 *) UART_ss2_m__0__HSIOM)
    
    #define UART_SS2_M_HSIOM_MASK       (UART_ss2_m__0__HSIOM_MASK)
    #define UART_SS2_M_HSIOM_POS        (UART_ss2_m__0__HSIOM_SHIFT)
    #define UART_SS2_M_HSIOM_SEL_GPIO   (UART_ss2_m__0__HSIOM_GPIO)
    #define UART_SS2_M_HSIOM_SEL_SPI    (UART_ss2_m__0__HSIOM_SPI)
#endif /* (UART_SPI_MASTER_SS2_PIN) */

#if (UART_SPI_MASTER_SS3_PIN)
    #define UART_SS3_M_HSIOM_REG    (*(reg32 *) UART_ss3_m__0__HSIOM)
    #define UART_SS3_M_HSIOM_PTR    ( (reg32 *) UART_ss3_m__0__HSIOM)
    
    #define UART_SS3_M_HSIOM_MASK      (UART_ss3_m__0__HSIOM_MASK)
    #define UART_SS3_M_HSIOM_POS       (UART_ss3_m__0__HSIOM_SHIFT)
    #define UART_SS3_M_HSIOM_SEL_GPIO  (UART_ss3_m__0__HSIOM_GPIO)
    #define UART_SS3_M_HSIOM_SEL_SPI   (UART_ss3_m__0__HSIOM_SPI)
#endif /* (UART_SPI_MASTER_SS3_PIN) */

#if (UART_UART_RX_PIN)
    #define UART_RX_HSIOM_REG   (*(reg32 *) UART_rx__0__HSIOM)
    #define UART_RX_HSIOM_PTR   ( (reg32 *) UART_rx__0__HSIOM)
    
    #define UART_RX_HSIOM_MASK      (UART_rx__0__HSIOM_MASK)
    #define UART_RX_HSIOM_POS       (UART_rx__0__HSIOM_SHIFT)
    #define UART_RX_HSIOM_SEL_GPIO  (UART_rx__0__HSIOM_GPIO)
    #define UART_RX_HSIOM_SEL_UART  (UART_rx__0__HSIOM_UART)
#endif /* (UART_UART_RX_PIN) */

#if (UART_UART_RX_WAKE_PIN)
    #define UART_RX_WAKE_HSIOM_REG   (*(reg32 *) UART_rx_wake__0__HSIOM)
    #define UART_RX_WAKE_HSIOM_PTR   ( (reg32 *) UART_rx_wake__0__HSIOM)
    
    #define UART_RX_WAKE_HSIOM_MASK      (UART_rx_wake__0__HSIOM_MASK)
    #define UART_RX_WAKE_HSIOM_POS       (UART_rx_wake__0__HSIOM_SHIFT)
    #define UART_RX_WAKE_HSIOM_SEL_GPIO  (UART_rx_wake__0__HSIOM_GPIO)
    #define UART_RX_WAKE_HSIOM_SEL_UART  (UART_rx_wake__0__HSIOM_UART)
#endif /* (UART_UART_WAKE_RX_PIN) */

#if (UART_UART_CTS_PIN)
    #define UART_CTS_HSIOM_REG   (*(reg32 *) UART_cts__0__HSIOM)
    #define UART_CTS_HSIOM_PTR   ( (reg32 *) UART_cts__0__HSIOM)
    
    #define UART_CTS_HSIOM_MASK      (UART_cts__0__HSIOM_MASK)
    #define UART_CTS_HSIOM_POS       (UART_cts__0__HSIOM_SHIFT)
    #define UART_CTS_HSIOM_SEL_GPIO  (UART_cts__0__HSIOM_GPIO)
    #define UART_CTS_HSIOM_SEL_UART  (UART_cts__0__HSIOM_UART)
#endif /* (UART_UART_CTS_PIN) */

#if (UART_UART_TX_PIN)
    #define UART_TX_HSIOM_REG   (*(reg32 *) UART_tx__0__HSIOM)
    #define UART_TX_HSIOM_PTR   ( (reg32 *) UART_tx__0__HSIOM)
    
    #define UART_TX_HSIOM_MASK      (UART_tx__0__HSIOM_MASK)
    #define UART_TX_HSIOM_POS       (UART_tx__0__HSIOM_SHIFT)
    #define UART_TX_HSIOM_SEL_GPIO  (UART_tx__0__HSIOM_GPIO)
    #define UART_TX_HSIOM_SEL_UART  (UART_tx__0__HSIOM_UART)
#endif /* (UART_UART_TX_PIN) */

#if (UART_UART_RX_TX_PIN)
    #define UART_RX_TX_HSIOM_REG   (*(reg32 *) UART_rx_tx__0__HSIOM)
    #define UART_RX_TX_HSIOM_PTR   ( (reg32 *) UART_rx_tx__0__HSIOM)
    
    #define UART_RX_TX_HSIOM_MASK      (UART_rx_tx__0__HSIOM_MASK)
    #define UART_RX_TX_HSIOM_POS       (UART_rx_tx__0__HSIOM_SHIFT)
    #define UART_RX_TX_HSIOM_SEL_GPIO  (UART_rx_tx__0__HSIOM_GPIO)
    #define UART_RX_TX_HSIOM_SEL_UART  (UART_rx_tx__0__HSIOM_UART)
#endif /* (UART_UART_RX_TX_PIN) */

#if (UART_UART_RTS_PIN)
    #define UART_RTS_HSIOM_REG      (*(reg32 *) UART_rts__0__HSIOM)
    #define UART_RTS_HSIOM_PTR      ( (reg32 *) UART_rts__0__HSIOM)
    
    #define UART_RTS_HSIOM_MASK     (UART_rts__0__HSIOM_MASK)
    #define UART_RTS_HSIOM_POS      (UART_rts__0__HSIOM_SHIFT)    
    #define UART_RTS_HSIOM_SEL_GPIO (UART_rts__0__HSIOM_GPIO)
    #define UART_RTS_HSIOM_SEL_UART (UART_rts__0__HSIOM_UART)    
#endif /* (UART_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define UART_HSIOM_DEF_SEL      (0x00u)
#define UART_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for UART_CY_SCBIP_V0 
* and UART_CY_SCBIP_V1. It is not recommended to use them for 
* UART_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define UART_HSIOM_UART_SEL     (0x09u)
#define UART_HSIOM_I2C_SEL      (0x0Eu)
#define UART_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define UART_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define UART_RX_SCL_MOSI_PIN_INDEX       (0u)
#define UART_TX_SDA_MISO_PIN_INDEX       (1u)
#define UART_SCLK_PIN_INDEX       (2u)
#define UART_SS0_PIN_INDEX       (3u)
#define UART_SS1_PIN_INDEX                  (4u)
#define UART_SS2_PIN_INDEX                  (5u)
#define UART_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define UART_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << UART_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define UART_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << UART_RX_SCL_MOSI_PIN_INDEX)
#define UART_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << UART_TX_SDA_MISO_PIN_INDEX)
#define UART_SCLK_PIN_MASK     ((uint32) 0x01u << UART_SCLK_PIN_INDEX)
#define UART_SS0_PIN_MASK     ((uint32) 0x01u << UART_SS0_PIN_INDEX)
#define UART_SS1_PIN_MASK                ((uint32) 0x01u << UART_SS1_PIN_INDEX)
#define UART_SS2_PIN_MASK                ((uint32) 0x01u << UART_SS2_PIN_INDEX)
#define UART_SS3_PIN_MASK                ((uint32) 0x01u << UART_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define UART_INTCFG_TYPE_MASK           (0x03u)
#define UART_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define UART_PIN_DM_ALG_HIZ  (0u)
#define UART_PIN_DM_DIG_HIZ  (1u)
#define UART_PIN_DM_OD_LO    (4u)
#define UART_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define UART_DM_MASK    (0x7u)
#define UART_DM_SIZE    (3u)
#define UART_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) UART_DM_MASK << (UART_DM_SIZE * (pos)))) >> \
                                                              (UART_DM_SIZE * (pos)) )

#if (UART_TX_SDA_MISO_PIN)
    #define UART_CHECK_TX_SDA_MISO_PIN_USED \
                (UART_PIN_DM_ALG_HIZ != \
                    UART_GET_P4_PIN_DM(UART_uart_tx_i2c_sda_spi_miso_PC, \
                                                   UART_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (UART_TX_SDA_MISO_PIN) */

#if (UART_SS0_PIN)
    #define UART_CHECK_SS0_PIN_USED \
                (UART_PIN_DM_ALG_HIZ != \
                    UART_GET_P4_PIN_DM(UART_spi_ss0_PC, \
                                                   UART_spi_ss0_SHIFT))
#endif /* (UART_SS0_PIN) */

/* Set bits-mask in register */
#define UART_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define UART_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define UART_SET_HSIOM_SEL(reg, mask, pos, sel) UART_SET_REGISTER_BITS(reg, mask, pos, sel)
#define UART_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        UART_SET_REGISTER_BITS(reg, mask, pos, intType)
#define UART_SET_INP_DIS(reg, mask, val) UART_SET_REGISTER_BIT(reg, mask, val)

/* UART_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  UART_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (UART_CY_SCBIP_V0)
#if (UART_I2C_PINS)
    #define UART_SET_I2C_SCL_DR(val) UART_scl_Write(val)

    #define UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                          UART_SET_HSIOM_SEL(UART_SCL_HSIOM_REG,  \
                                                         UART_SCL_HSIOM_MASK, \
                                                         UART_SCL_HSIOM_POS,  \
                                                         (sel))
    #define UART_WAIT_SCL_SET_HIGH  (0u == UART_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (UART_RX_WAKE_SCL_MOSI_PIN)
    #define UART_SET_I2C_SCL_DR(val) \
                            UART_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                    UART_SET_HSIOM_SEL(UART_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   UART_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   UART_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define UART_WAIT_SCL_SET_HIGH  (0u == UART_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (UART_RX_SCL_MOSI_PIN)
    #define UART_SET_I2C_SCL_DR(val) \
                            UART_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                            UART_SET_HSIOM_SEL(UART_RX_SCL_MOSI_HSIOM_REG,  \
                                                           UART_RX_SCL_MOSI_HSIOM_MASK, \
                                                           UART_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define UART_WAIT_SCL_SET_HIGH  (0u == UART_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define UART_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define UART_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define UART_WAIT_SCL_SET_HIGH  (0u)
#endif /* (UART_I2C_PINS) */

/* SCB I2C: sda signal */
#if (UART_I2C_PINS)
    #define UART_WAIT_SDA_SET_HIGH  (0u == UART_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (UART_TX_SDA_MISO_PIN)
    #define UART_WAIT_SDA_SET_HIGH  (0u == UART_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define UART_WAIT_SDA_SET_HIGH  (0u)
#endif /* (UART_MOSI_SCL_RX_PIN) */
#endif /* (UART_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (UART_RX_SCL_MOSI_PIN)
    #define UART_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (UART_RX_WAKE_SCL_MOSI_PIN)
    #define UART_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) UART_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(UART_UART_RX_WAKE_PIN)
    #define UART_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) UART_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (UART_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define UART_REMOVE_MOSI_SCL_RX_WAKE_PIN    UART_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define UART_REMOVE_MOSI_SCL_RX_PIN         UART_REMOVE_RX_SCL_MOSI_PIN
#define UART_REMOVE_MISO_SDA_TX_PIN         UART_REMOVE_TX_SDA_MISO_PIN
#ifndef UART_REMOVE_SCLK_PIN
#define UART_REMOVE_SCLK_PIN                UART_REMOVE_SCLK_PIN
#endif /* UART_REMOVE_SCLK_PIN */
#ifndef UART_REMOVE_SS0_PIN
#define UART_REMOVE_SS0_PIN                 UART_REMOVE_SS0_PIN
#endif /* UART_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define UART_MOSI_SCL_RX_WAKE_PIN   UART_RX_WAKE_SCL_MOSI_PIN
#define UART_MOSI_SCL_RX_PIN        UART_RX_SCL_MOSI_PIN
#define UART_MISO_SDA_TX_PIN        UART_TX_SDA_MISO_PIN
#ifndef UART_SCLK_PIN
#define UART_SCLK_PIN               UART_SCLK_PIN
#endif /* UART_SCLK_PIN */
#ifndef UART_SS0_PIN
#define UART_SS0_PIN                UART_SS0_PIN
#endif /* UART_SS0_PIN */

#if (UART_MOSI_SCL_RX_WAKE_PIN)
    #define UART_MOSI_SCL_RX_WAKE_HSIOM_REG     UART_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UART_MOSI_SCL_RX_WAKE_HSIOM_PTR     UART_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UART_MOSI_SCL_RX_WAKE_HSIOM_MASK    UART_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UART_MOSI_SCL_RX_WAKE_HSIOM_POS     UART_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define UART_MOSI_SCL_RX_WAKE_INTCFG_REG    UART_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UART_MOSI_SCL_RX_WAKE_INTCFG_PTR    UART_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define UART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   UART_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  UART_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (UART_RX_WAKE_SCL_MOSI_PIN) */

#if (UART_MOSI_SCL_RX_PIN)
    #define UART_MOSI_SCL_RX_HSIOM_REG      UART_RX_SCL_MOSI_HSIOM_REG
    #define UART_MOSI_SCL_RX_HSIOM_PTR      UART_RX_SCL_MOSI_HSIOM_PTR
    #define UART_MOSI_SCL_RX_HSIOM_MASK     UART_RX_SCL_MOSI_HSIOM_MASK
    #define UART_MOSI_SCL_RX_HSIOM_POS      UART_RX_SCL_MOSI_HSIOM_POS
#endif /* (UART_MOSI_SCL_RX_PIN) */

#if (UART_MISO_SDA_TX_PIN)
    #define UART_MISO_SDA_TX_HSIOM_REG      UART_TX_SDA_MISO_HSIOM_REG
    #define UART_MISO_SDA_TX_HSIOM_PTR      UART_TX_SDA_MISO_HSIOM_REG
    #define UART_MISO_SDA_TX_HSIOM_MASK     UART_TX_SDA_MISO_HSIOM_REG
    #define UART_MISO_SDA_TX_HSIOM_POS      UART_TX_SDA_MISO_HSIOM_REG
#endif /* (UART_MISO_SDA_TX_PIN_PIN) */

#if (UART_SCLK_PIN)
    #ifndef UART_SCLK_HSIOM_REG
    #define UART_SCLK_HSIOM_REG     UART_SCLK_HSIOM_REG
    #define UART_SCLK_HSIOM_PTR     UART_SCLK_HSIOM_PTR
    #define UART_SCLK_HSIOM_MASK    UART_SCLK_HSIOM_MASK
    #define UART_SCLK_HSIOM_POS     UART_SCLK_HSIOM_POS
    #endif /* UART_SCLK_HSIOM_REG */
#endif /* (UART_SCLK_PIN) */

#if (UART_SS0_PIN)
    #ifndef UART_SS0_HSIOM_REG
    #define UART_SS0_HSIOM_REG      UART_SS0_HSIOM_REG
    #define UART_SS0_HSIOM_PTR      UART_SS0_HSIOM_PTR
    #define UART_SS0_HSIOM_MASK     UART_SS0_HSIOM_MASK
    #define UART_SS0_HSIOM_POS      UART_SS0_HSIOM_POS
    #endif /* UART_SS0_HSIOM_REG */
#endif /* (UART_SS0_PIN) */

#define UART_MOSI_SCL_RX_WAKE_PIN_INDEX UART_RX_WAKE_SCL_MOSI_PIN_INDEX
#define UART_MOSI_SCL_RX_PIN_INDEX      UART_RX_SCL_MOSI_PIN_INDEX
#define UART_MISO_SDA_TX_PIN_INDEX      UART_TX_SDA_MISO_PIN_INDEX
#ifndef UART_SCLK_PIN_INDEX
#define UART_SCLK_PIN_INDEX             UART_SCLK_PIN_INDEX
#endif /* UART_SCLK_PIN_INDEX */
#ifndef UART_SS0_PIN_INDEX
#define UART_SS0_PIN_INDEX              UART_SS0_PIN_INDEX
#endif /* UART_SS0_PIN_INDEX */

#define UART_MOSI_SCL_RX_WAKE_PIN_MASK UART_RX_WAKE_SCL_MOSI_PIN_MASK
#define UART_MOSI_SCL_RX_PIN_MASK      UART_RX_SCL_MOSI_PIN_MASK
#define UART_MISO_SDA_TX_PIN_MASK      UART_TX_SDA_MISO_PIN_MASK
#ifndef UART_SCLK_PIN_MASK
#define UART_SCLK_PIN_MASK             UART_SCLK_PIN_MASK
#endif /* UART_SCLK_PIN_MASK */
#ifndef UART_SS0_PIN_MASK
#define UART_SS0_PIN_MASK              UART_SS0_PIN_MASK
#endif /* UART_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_UART_H) */


/* [] END OF FILE */
