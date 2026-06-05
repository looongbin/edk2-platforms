/** @file

  Copyright (c) 2023, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_DATA (SMBIOS_TABLE_TYPE16, PlatformPhysicalMemoryArray) = {
  {                                          // Table 1
    {                                        // Header
      EFI_SMBIOS_TYPE_PHYSICAL_MEMORY_ARRAY, // Type
      sizeof (SMBIOS_TABLE_TYPE16),          // Length
      SMBIOS_HANDLE_MEMORY,                  // Handle
    },
    MemoryArrayLocationSystemBoard,          // on motherboard
    MemoryArrayUseSystemMemory,              // system RAM
    MemoryErrorCorrectionNone,               // None hardware error correction
    0x8000000,                               // 128GB
    0xFFFE,                                  // No error information structure
    0x1,                                     // soldered memory
  },
  {                                          // Null-terminated table
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
SMBIOS_PLATFORM_DXE_STRING_TOKEN_DATA (PlatformPhysicalMemoryArray) = {
  {                                         // Table 1
    {                                       // Tokens array
      NULL_TERMINATED_TOKEN
    },
    0                                       // Size of Tokens array
  }
};
