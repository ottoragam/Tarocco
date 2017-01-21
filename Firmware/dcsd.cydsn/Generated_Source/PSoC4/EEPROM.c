/*******************************************************************************
* File Name: EEPROM.c
* Version 1.10
*
* Description:
*  This file provides the source code to API for the Emulated EEPROM Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "EEPROM.h"


/*******************************************************************************
* Function Name: EEPROM_Start
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other
*  components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EEPROM_Start(void) 
{

}


/*******************************************************************************
* Function Name: EEPROM_Stop
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other
*  components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EEPROM_Stop(void) 
{

}


/*******************************************************************************
* Function Name: EEPROM_Write
********************************************************************************
*
* Summary:
*  Writes the specified number of bytes from the source buffer in SRAM to the
*  emulated EEPROM array in flash, without modifying other data in flash.
*
* Parameters:
*  srcBuf:    Pointer to the SRAM buffer holding the data to write.
*  eepromPtr: Pointer to the array or variable in flash representing
*             the emulated EEPROM.
*  byteCount: Number of bytes to write from srcBuf to eepromPtr.
*
* Return:
*    CYRET_SUCCESS     Successful write.
*    CYRET_BAD_PARAM   eepromPtr is out of range of flash memory.
*    CYRET_UNKNOWN     Other error in writing flash.
*
*******************************************************************************/
#if (CY_PSOC3)
    cystatus EEPROM_Write(const uint8 srcBuf[], const uint8 eepromPtr[], uint16 byteCount)
                                                                            
#else
    cystatus EEPROM_Write(const uint8 srcBuf[], const uint8 eepromPtr[], uint32 byteCount)
#endif /* (!CY_PSOC3) */
{
    uint8 writeBuffer[CY_FLASH_SIZEOF_ROW];
    uint32 arrayId;
    uint32 rowId;
    uint32 dstIndex;
    uint32 srcIndex;
    cystatus rc;
    uint32 eeOffset;
    uint32 byteOffset;
    
    #if (!CY_PSOC4)
        #if (CYDEV_ECC_ENABLE == 0)
            uint8 rowBuffer[CY_FLASH_SIZEOF_ROW + CY_FLASH_SIZEOF_ECC_ROW];
        #endif /* CYDEV_ECC_ENABLE == 0) */
    #endif /* (!CY_PSOC4) */

    eeOffset = (uint32)eepromPtr;
    #if (CY_PSOC3)
        eeOffset &= EEPROM_CODE_ADDR_MASK;
    #endif /* (CY_PSOC3) */

    /* Make sure, that eepromPtr[] points to ROM */
    #if (CY_PSOC3)
        if (((uint32)eepromPtr >= EEPROM_CODE_ADDR_OFFSET) &&
            (((uint32)eepromPtr + byteCount) <= EEPROM_CODE_ADDR_END))
    #else
        if (((uint32)eepromPtr + byteCount) < EEPROM_FLASH_END_ADDR)
    #endif /* (CY_PSOC3) */
    {
        #if (!CY_PSOC4)
            (void)CySetTemp();

            #if(CYDEV_ECC_ENABLE == 0)
                (void)CySetFlashEEBuffer(rowBuffer);
            #endif
        #endif /* (!CY_PSOC4) */

        arrayId = eeOffset / CY_FLASH_SIZEOF_ARRAY;
        rowId = (eeOffset / CY_FLASH_SIZEOF_ROW) % EEPROM_ROWS_IN_ARRAY;
        byteOffset = (CY_FLASH_SIZEOF_ARRAY * arrayId) + (CY_FLASH_SIZEOF_ROW * rowId);
        srcIndex = 0u;

        rc = CYRET_SUCCESS;

        while ((srcIndex < byteCount) && (CYRET_SUCCESS == rc))
        {
            /* Copy data to the write buffer either from the source buffer or from the flash */
            for (dstIndex = 0u; dstIndex < CY_FLASH_SIZEOF_ROW; dstIndex++)
            {
                if ((byteOffset >= eeOffset) && (srcIndex < byteCount))
                {
                    writeBuffer[dstIndex] = srcBuf[srcIndex];
                    srcIndex++;
                }
                else
                {
                    writeBuffer[dstIndex] = CY_GET_XTND_REG8(CYDEV_FLASH_BASE + byteOffset);
                }
                byteOffset++;
            }

            /* Write flash row */
            #if (CY_PSOC4)
                rc = CySysFlashWriteRow(rowId, writeBuffer);
            #else
                rc = CyWriteRowData((uint8)arrayId, (uint16)rowId, writeBuffer);
            #endif /* (CY_PSOC4) */

            /* Go to the next row */
            rowId++;
            #if (CY_FLASH_NUMBER_ARRAYS > 1)
                if (rowId >= EEPROM_ROWS_IN_ARRAY)
                {
                    arrayId++;
                    rowId = 0u;
                }
            #endif /* (CY_FLASH_NUMBER_ARRAYS > 1) */
        }

        /* Flush both Cache and PHUB prefetch buffer */
        #if (CY_PSOC5)
            CyFlushCache();
        #elif (CY_PSOC3)
            CY_FLASH_CONTROL_REG |= 6u;
        #endif /* (CY_PSOC5) */
    }
    else
    {
        rc = CYRET_BAD_PARAM;
    }

    /* Mask return codes from flash, if they are not supported */
    if ((CYRET_SUCCESS != rc) && (CYRET_BAD_PARAM != rc))
    {
        rc = CYRET_UNKNOWN;
    }
    
    return (rc);
}


/* [] END OF FILE */
