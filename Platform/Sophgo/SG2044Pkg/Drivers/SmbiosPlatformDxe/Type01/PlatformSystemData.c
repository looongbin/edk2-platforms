/** @file

  Copyright (c) 2024, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_DATA (SMBIOS_TABLE_TYPE1, PlatformSystem) = {
  {						// Table 1
    {						// Header
      EFI_SMBIOS_TYPE_SYSTEM_INFORMATION,	// Type
      sizeof (SMBIOS_TABLE_TYPE1),		// Length
      SMBIOS_HANDLE_PI_RESERVED			// Handle
    },
    1,						// Manufacturer
    2,						// Product Name
    3,						// Version
    4,						// Serial
    { 0x9987FD42, 0x907E, 0x5446, { 0x1D,0x7D,0x7D,0xA0,0x10,0x9F,0x60,0xA1 }},    //UUID
    6,						//Wakeup type
    5,						//SKU
    6,						//Family
  },
  {                                             // Null-terminated table
    {
      NULL_TERMINATED_TYPE,
      0,
      0
    },
  }
};

//
// Define string Tokens for additional strings.
//
SMBIOS_PLATFORM_DXE_STRING_TOKEN_DATA (PlatformSystem) = {
  {                                         // Table 1
    {                                       // Tokens array
      STRING_TOKEN (STR_PLATFORM_DXE_SYSTEM_MANUFACTURER),
      STRING_TOKEN (STR_PLATFORM_DXE_SYSTEM_PRODUCT_NAME),
      STRING_TOKEN (STR_PLATFORM_DXE_SYSTEM_VERSION),
      STRING_TOKEN (STR_PLATFORM_DXE_SYSTEM_SERIAL),
      STRING_TOKEN (STR_PLATFORM_DXE_SYSTEM_SKU_NUMBER),
      STRING_TOKEN (STR_PLATFORM_DXE_SYSTEM_FAMILY)
    },
    ADDITIONAL_STR_INDEX_6                  // Size of Tokens array
  }
};
