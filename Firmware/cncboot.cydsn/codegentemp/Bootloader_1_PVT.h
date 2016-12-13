/****************************************************************************//**
* \file Bootloader_1.c
* \version 1.50
*
* \brief
*   Provides an API for the Bootloader.
*
********************************************************************************
* \copyright
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_BOOTLOADER_Bootloader_1_PVT_H)
#define CY_BOOTLOADER_Bootloader_1_PVT_H

#include "Bootloader_1.h"


typedef struct
{
    uint32 SiliconId;
    uint8  Revision;
    uint8  BootLoaderVersion[3u];

} Bootloader_1_ENTER;


#define Bootloader_1_VERSION        {\
                                            (uint8)50, \
                                            (uint8)1, \
                                            (uint8)0x01u \
                                        }

/* Packet framing constants. */
#define Bootloader_1_SOP            (0x01u)    /* Start of Packet */
#define Bootloader_1_EOP            (0x17u)    /* End of Packet */

/**
 \defgroup constants_group Constants
 @{
*/

/** \addtogroup errorCodes Error Codes
 *  Error codes that are returned while communicating with Host 
 *  @{
 */
/* Bootloader command responses */
#define Bootloader_1_ERR_KEY       (0x01u)  /**< The provided key does not match the expected value          */
#define Bootloader_1_ERR_VERIFY    (0x02u)  /**< The verification of flash failed                            */
#define Bootloader_1_ERR_LENGTH    (0x03u)  /**< The amount of data available is outside the expected range  */
#define Bootloader_1_ERR_DATA      (0x04u)  /**< The data is not of the proper form                          */
#define Bootloader_1_ERR_CMD       (0x05u)  /**< The command is not recognized                               */
#define Bootloader_1_ERR_DEVICE    (0x06u)  /**< The expected device does not match the detected device      */
#define Bootloader_1_ERR_VERSION   (0x07u)  /**< The bootloader version detected is not supported            */
#define Bootloader_1_ERR_CHECKSUM  (0x08u)  /**< The checksum does not match the expected value              */
#define Bootloader_1_ERR_ARRAY     (0x09u)  /**< The flash array is not valid                                */
#define Bootloader_1_ERR_ROW       (0x0Au)  /**< The flash row is not valid                                  */
#define Bootloader_1_ERR_PROTECT   (0x0Bu)  /**< The flash row is protected and can not be programmed        */
#define Bootloader_1_ERR_APP       (0x0Cu)  /**< The application is not valid and cannot be set as active    */
#define Bootloader_1_ERR_ACTIVE    (0x0Du)  /**< The application is currently marked as active               */
#define Bootloader_1_ERR_CALLBACK  (0x0Eu)  /**< The callback function returns invalid data                  */
#define Bootloader_1_ERR_UNK       (0x0Fu)  /**< An unknown error occurred                                   */
/** @}*/

/** \addtogroup commands Commands
 * Commands for communication with Host
 *  @{
 */
/* Bootloader command definitions. */
#define Bootloader_1_COMMAND_CHECKSUM          (0x31u)    /* Verify the checksum for the bootloadable project   */
#define Bootloader_1_COMMAND_REPORT_SIZE       (0x32u)    /* Report the programmable portions of flash          */
#define Bootloader_1_COMMAND_APP_STATUS        (0x33u)    /* Gets status info about the provided app status     */
#define Bootloader_1_COMMAND_ERASE             (0x34u)    /* Erase the specified flash row                      */
#define Bootloader_1_COMMAND_SYNC              (0x35u)    /* Sync the bootloader and host application           */
#define Bootloader_1_COMMAND_APP_ACTIVE        (0x36u)    /* Sets the active application                        */
#define Bootloader_1_COMMAND_DATA              (0x37u)    /* Queue up a block of data for programming           */
#define Bootloader_1_COMMAND_ENTER             (0x38u)    /* Enter the bootloader                               */
#define Bootloader_1_COMMAND_PROGRAM           (0x39u)    /* Program the specified row                          */
#define Bootloader_1_COMMAND_GET_ROW_CHKSUM    (0x3Au)    /* Compute flash row checksum for verification        */
#define Bootloader_1_COMMAND_EXIT              (0x3Bu)    /* Exits the bootloader & resets the chip             */
#define Bootloader_1_COMMAND_GET_METADATA      (0x3Cu)    /* Reports the metadata for a selected application    */
#define Bootloader_1_COMMAND_VERIFY_FLS_ROW    (0x45u)    /* Verifies data in buffer with specified row in flash*/
/** @}*/
/** @}*/

/* Bootloader response lengths */ 
#define Bootloader_1_RSP_SIZE_0                 (0x00u)
#define Bootloader_1_RSP_SIZE_VERIFY_CHKSM      (0x01u)
#define Bootloader_1_RSP_SIZE_VERIFY_ROW_CHKSM  (0x01u)
#define Bootloader_1_RSP_SIZE_GET_APP_STATUS    (0x02u)
#define Bootloader_1_RSP_SIZE_GET_COPIER_STATUS (0x03u)
#define Bootloader_1_RSP_SIZE_GET_FLASH_SIZE    (0x04u)
#define Bootloader_1_RSP_SIZE_GET_METADATA      (0x56u)


/*******************************************************************************
* Bootloader packet byte addresses:
* [1-byte] [1-byte ] [2-byte] [n-byte] [ 2-byte ] [1-byte]
* [ SOP  ] [Command] [ Size ] [ Data ] [Checksum] [ EOP  ]
*******************************************************************************/
#define Bootloader_1_SOP_ADDR             (0x00u)         /* Start of packet offset from beginning     */
#define Bootloader_1_CMD_ADDR             (0x01u)         /* Command offset from beginning             */
#define Bootloader_1_SIZE_ADDR            (0x02u)         /* Packet size offset from beginning         */
#define Bootloader_1_DATA_ADDR            (0x04u)         /* Packet data offset from beginning         */
#define Bootloader_1_CHK_ADDR(x)          (0x04u + (x))   /* Packet checksum offset from end           */
#define Bootloader_1_EOP_ADDR(x)          (0x06u + (x))   /* End of packet offset from end             */

/*******************************************************************************
Bootloader_1_ValidateBootloadable()
*******************************************************************************/
#define Bootloader_1_FIRST_APP_BYTE(appId)      ((uint32)CYDEV_FLS_ROW_SIZE * \
        ((uint32) Bootloader_1_GetMetadata(Bootloader_1_GET_BTLDR_LAST_ROW, appId) + \
         (uint32) 1u))

#define Bootloader_1_MD_BTLDB_IS_VERIFIED       (0x01u)


/*******************************************************************************
* Bootloader_1_Start()
*******************************************************************************/
#define Bootloader_1_MD_BTLDB_IS_ACTIVE         (0x01u)
#define Bootloader_1_WAIT_FOR_COMMAND_FOREVER   (0x00u)


/*******************************************************************************
* Bootloader_1_HostLink()
*******************************************************************************/
#define Bootloader_1_COMMUNICATION_STATE_IDLE   (0u)
#define Bootloader_1_COMMUNICATION_STATE_ACTIVE (1u)

#if(!CY_PSOC4)

    /*******************************************************************************
    * The Array ID indicates the unique ID of the SONOS array being accessed:
    * - 0x00-0x3E : Flash Arrays
    * - 0x3F      : Selects all Flash arrays simultaneously
    * - 0x40-0x7F : Embedded EEPROM Arrays
    *******************************************************************************/
    #define Bootloader_1_FIRST_FLASH_ARRAYID          (0x00u)
    #define Bootloader_1_LAST_FLASH_ARRAYID           (0x3Fu)
    #define Bootloader_1_FIRST_EE_ARRAYID             (0x40u)
    #define Bootloader_1_LAST_EE_ARRAYID              (0x7Fu)

#endif   /* (!CY_PSOC4) */


/*******************************************************************************
* Bootloader_1_CalcPacketChecksum()
*******************************************************************************/
#if(0u != Bootloader_1_PACKET_CHECKSUM_CRC)
    #define Bootloader_1_CRC_CCITT_POLYNOMIAL       (0x8408u)       /* x^16 + x^12 + x^5 + 1 */
    #define Bootloader_1_CRC_CCITT_INITIAL_VALUE    (0xffffu)
#endif /* (0u != Bootloader_1_PACKET_CHECKSUM_CRC) */


/*******************************************************************************
* CyBtldr_CheckLaunch()
*******************************************************************************/
#define Bootloader_1_RES_CAUSE_RESET_SOFT                (0x10u)


/*******************************************************************************
* Metadata addresses and pointer defines
*******************************************************************************/
#define Bootloader_1_MD_SIZEOF                  (64u)


/*******************************************************************************
* Upgradable Stack use case declaration
* If the combination project is a Stack application.
*******************************************************************************/
#if (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER)
    #if (0u != CYDEV_IS_EXPORTING_CODE)
        #define Bootloader_1_IS_STACK_APPLICATION   (1u)
        #define Bootloader_1_STACK_APPLICATION      (Bootloader_1_MD_BTLDB_ACTIVE_0)
        #define Bootloader_1_USER_APPLICATION       (Bootloader_1_MD_BTLDB_ACTIVE_1)
    #else
        #define Bootloader_1_IS_STACK_APPLICATION   (0u)
    #endif /* (0u != CYDEV_IS_EXPORTING_CODE) */
#else
    #define Bootloader_1_IS_STACK_APPLICATION   (0u)	
#endif /* (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER) */

/*******************************************************************************
* The Metadata base address. In the case of the Bootloader application, 
* metadata is placed in row N-1; in the case of the Dual-application
* bootloader, Bootloadable application number 1 will use row N-1, and
* application number 2 will use row N-2 to store its metadata, where N is the
* total number of the rows for the selected device.
*******************************************************************************/
#define Bootloader_1_MD_BASE_ADDR(appId)        (CYDEV_FLASH_BASE + \
                                                        (CYDEV_FLASH_SIZE - ((uint32)(appId) * CYDEV_FLS_ROW_SIZE) - \
                                                        Bootloader_1_MD_SIZEOF))

#define Bootloader_1_MD_FLASH_ARRAY_NUM         (Bootloader_1_NUM_OF_FLASH_ARRAYS - 1u)

#if(!CY_PSOC4)
    #define Bootloader_1_MD_ROW_NUM(appId)      ((CY_FLASH_NUMBER_ROWS / Bootloader_1_NUM_OF_FLASH_ARRAYS) - \
                                                    1u - (uint32)(appId))
#else
    #define Bootloader_1_MD_ROW_NUM(appId)      (CY_FLASH_NUMBER_ROWS - 1u - (uint32)(appId))
#endif /* (!CY_PSOC4) */


#define     Bootloader_1_MD_BTLDB_CHECKSUM_OFFSET(appId)       (Bootloader_1_MD_BASE_ADDR(appId) + 0u)
#if(CY_PSOC3)
    #define Bootloader_1_MD_BTLDB_ADDR_OFFSET(appId)           (Bootloader_1_MD_BASE_ADDR(appId) + 3u)
    #define Bootloader_1_MD_BTLDR_LAST_ROW_OFFSET(appId)       (Bootloader_1_MD_BASE_ADDR(appId) + 7u)
    #define Bootloader_1_MD_BTLDB_LENGTH_OFFSET(appId)         (Bootloader_1_MD_BASE_ADDR(appId) + 11u)
#else
    #define Bootloader_1_MD_BTLDB_ADDR_OFFSET(appId)           (Bootloader_1_MD_BASE_ADDR(appId) + 1u)
    #define Bootloader_1_MD_BTLDR_LAST_ROW_OFFSET(appId)       (Bootloader_1_MD_BASE_ADDR(appId) + 5u)
    #define Bootloader_1_MD_BTLDB_LENGTH_OFFSET(appId)         (Bootloader_1_MD_BASE_ADDR(appId) + 9u)
#endif /* (CY_PSOC3) */
#define     Bootloader_1_MD_BTLDB_ACTIVE_OFFSET(appId)         (Bootloader_1_MD_BASE_ADDR(appId) + 16u)
#define     Bootloader_1_MD_BTLDB_VERIFIED_OFFSET(appId)       (Bootloader_1_MD_BASE_ADDR(appId) + 17u)
#define     Bootloader_1_MD_BTLDR_APP_VERSION_OFFSET(appId)    (Bootloader_1_MD_BASE_ADDR(appId) + 18u)
#define     Bootloader_1_MD_BTLDB_APP_ID_OFFSET(appId)         (Bootloader_1_MD_BASE_ADDR(appId) + 20u)
#define     Bootloader_1_MD_BTLDB_APP_VERSION_OFFSET(appId)    (Bootloader_1_MD_BASE_ADDR(appId) + 22u)
#define     Bootloader_1_MD_BTLDB_APP_CUST_ID_OFFSET(appId)    (Bootloader_1_MD_BASE_ADDR(appId) + 24u)
#define     Bootloader_1_MD_BTLDB_COPY_FLAG_OFFSET(appId)      (Bootloader_1_MD_BASE_ADDR(appId) + 28u)
#define     Bootloader_1_MD_BTLDB_USER_DATA_OFFSET(appId)      (Bootloader_1_MD_BASE_ADDR(appId) + 32u)


/*******************************************************************************
* Launcher + Copier use case definitions and masks
*******************************************************************************/
#if ((CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER) || \
     (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LAUNCHER))
    #define Bootloader_1_COPIER_SUPPORT_AVAIL_MASK             (0x01u)
    #define Bootloader_1_COPIER_SUPPORT_SET_BIT                (0x01u)
    #define Bootloader_1_NEED_TO_COPY_MASK                     (0x01u)
    #define Bootloader_1_NEED_TO_COPY_SET_BIT                  (0x01u)
    
    #define Bootloader_1_MD_BUFFER_START_OFFSET                (CYDEV_FLS_ROW_SIZE - Bootloader_1_MD_SIZEOF)
    #define Bootloader_1_MD_ACTIVE_APP_BYTE_OFFSET             (0x10u)
    #define Bootloader_1_MD_FAST_VALID_BYTE_OFFSET             (0x11u)
    #define Bootloader_1_MD_COPY_FLAG_BYTE_OFFSET              (0x1Cu)
#endif /* (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER) || 
          (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LAUNCHER)*/

/*******************************************************************************
* Get data byte from flash
*******************************************************************************/
#if(CY_PSOC3)
    #define Bootloader_1_GET_CODE_BYTE(addr)            (*((uint8  CYCODE *) (addr)))
#else
    #define Bootloader_1_GET_CODE_BYTE(addr)            (*((uint8  *)(CYDEV_FLASH_BASE + (addr))))
#endif /* (CY_PSOC3) */


#if(!CY_PSOC4)
    #define Bootloader_1_GET_EEPROM_BYTE(addr)          (*((uint8  *)(CYDEV_EE_BASE + (addr))))
#endif /* (CY_PSOC3) */


/* Our definition of row size. */
#if((!CY_PSOC4) && (CYDEV_ECC_ENABLE == 0))
    #define Bootloader_1_FROW_SIZE          ((CYDEV_FLS_ROW_SIZE) + (CYDEV_ECC_ROW_SIZE))
#else
    #define Bootloader_1_FROW_SIZE          CYDEV_FLS_ROW_SIZE
#endif  /* ((!CY_PSOC4) && (CYDEV_ECC_ENABLE == 0)) */

/* Definition of row amount in EEPROM array */
#if (!CY_PSOC4)
    #define Bootloader_1_NUMBER_OF_ROWS_IN_EEPROM_SECTOR (CYDEV_EEPROM_SECTOR_SIZE/CYDEV_EEPROM_ROW_SIZE)
    #define Bootloader_1_NUMBER_OF_EEPROM_SECTORS        (CY_EEPROM_NUMBER_SECTORS)
#endif /*(!CY_PSOC4)*/

/* Macro to check if row number is within array address range */
#define Bootloader_1_CHECK_ROW_NUMBER(rowNum, upperRange) (((rowNum) < (upperRange)) ? CYRET_SUCCESS : \
                                                               Bootloader_1_ERR_ROW)

/*******************************************************************************
* Number of addresses remapped from flash to RAM, when interrupt vectors are
* configured to be stored in RAM (default setting, configured by cy_boot).
*******************************************************************************/
#if(CY_PSOC4)
    #define Bootloader_1_MD_BTLDR_ADDR_PTR        (0xC0u)     /* Exclude the vector */
#else
    #define Bootloader_1_MD_BTLDR_ADDR_PTR        (0x00u)
#endif  /* (CY_PSOC4) */


/*******************************************************************************
* The maximum number of Bootloadable applications.
*******************************************************************************/
#if((1u == Bootloader_1_DUAL_APP_BOOTLOADER) || \
    (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER))
    #define Bootloader_1_MAX_NUM_OF_BTLDB       (0x02u)
#else
    #define Bootloader_1_MAX_NUM_OF_BTLDB       (0x01u)
#endif  /* (1u == Bootloader_1_DUAL_APP_BOOTLOADER) ||
           (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER)*/


/*******************************************************************************
* Returns TRUE if the row specified as a parameter contains a metadata section.
*******************************************************************************/
#if ((0u != Bootloader_1_DUAL_APP_BOOTLOADER) || \
     (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER))
    #define Bootloader_1_CONTAIN_METADATA(row)  \
                                        ((Bootloader_1_MD_ROW_NUM(Bootloader_1_MD_BTLDB_ACTIVE_0) == (row)) || \
                                         (Bootloader_1_MD_ROW_NUM(Bootloader_1_MD_BTLDB_ACTIVE_1) == (row)))
#else
    #define Bootloader_1_CONTAIN_METADATA(row)  \
                                        (Bootloader_1_MD_ROW_NUM(Bootloader_1_MD_BTLDB_ACTIVE_0) == (row))
#endif  /* (0u != Bootloader_1_DUAL_APP_BOOTLOADER) || 
           (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER) */


/*******************************************************************************
* The Metadata section is located in the last flash row for the Bootloader, for
* the Dual-application Bootloader, the metadata section of Bootloadable
* application # 0 is located in the last flash row, and the metadata section of
* Bootloadable application # 1 is located in the flash row before last.
*******************************************************************************/
#if ((0u != Bootloader_1_DUAL_APP_BOOTLOADER) || \
     (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER))
    #define Bootloader_1_GET_APP_ID(row)     \
                                        ((Bootloader_1_MD_ROW_NUM(Bootloader_1_MD_BTLDB_ACTIVE_0) == (row)) ? \
                                          Bootloader_1_MD_BTLDB_ACTIVE_0 : \
                                          Bootloader_1_MD_BTLDB_ACTIVE_1)
#else
    #define Bootloader_1_GET_APP_ID(row)     (Bootloader_1_MD_BTLDB_ACTIVE_0)
#endif  /* (0u != Bootloader_1_DUAL_APP_BOOTLOADER) || 
           (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER)*/


/*******************************************************************************
* Defines the number of flash rows reserved for the metadata section.
*******************************************************************************/
#if ((1u == Bootloader_1_DUAL_APP_BOOTLOADER) || \
     (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER))
    #define Bootloader_1_NUMBER_OF_METADATA_ROWS            (2u)
#else
    #define Bootloader_1_NUMBER_OF_METADATA_ROWS            (1u)
#endif /* (0u == Bootloader_1_DUAL_APP_BOOTLOADER) ||
          (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER)*/


/*******************************************************************************
* Defines the number of possible bootloadable applications.
*******************************************************************************/
#if ((1u == Bootloader_1_DUAL_APP_BOOTLOADER) || \
     (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER))
    #define Bootloader_1_NUMBER_OF_BTLDBLE_APPS            (2u)
#else
    #define Bootloader_1_NUMBER_OF_BTLDBLE_APPS            (1u)
#endif /* (0u == Bootloader_1_DUAL_APP_BOOTLOADER) ||
          (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER) */

#define Bootloader_1_NUMBER_OF_ROWS_IN_ARRAY                ((uint16)(CY_FLASH_SIZEOF_ARRAY/CY_FLASH_SIZEOF_ROW))
#define Bootloader_1_FIRST_ROW_IN_ARRAY                     (0u)

#endif /* CY_BOOTLOADER_Bootloader_1_PVT_H */


/* [] END OF FILE */
