/** @file

  Copyright (c) 2023, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_DATA (SMBIOS_TABLE_TYPE19, PlatformMemoryArrayMappedAddress) = {
  {                                                 // Table 1
    {                                               // Header
      EFI_SMBIOS_TYPE_MEMORY_ARRAY_MAPPED_ADDRESS,  // Type
      sizeof (SMBIOS_TABLE_TYPE19),                 // Length
      SMBIOS_HANDLE_PI_RESERVED                     // Handle
    },
    0xFFFFFFFF,                                     // invalid, look at extended addr field
    0xFFFFFFFF,
    0xFFFE,                                         // MemoryArrayHandle
    1,
    0x80000000,                                     // starting addr (2G)
    0x2080000000,                                   // ending addr (130G)
  },
  {                                                 // Null-terminated table
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
SMBIOS_PLATFORM_DXE_STRING_TOKEN_DATA (PlatformMemoryArrayMappedAddress) = {
  {                          // Table 1
    {                        // Tokens array
      NULL_TERMINATED_TOKEN
    },
    0                        // Size of Tokens array
  }
};
