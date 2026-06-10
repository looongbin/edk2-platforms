/** @file

  Copyright (c) 2022, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_DATA (SMBIOS_TABLE_TYPE32, PlatformSystemBoot) = {
  {                                        // Table 1
    {                                      // SMBIOS_STRUCTURE Hdr
      EFI_SMBIOS_TYPE_SYSTEM_BOOT_INFORMATION,   // UINT8 Type
      sizeof (SMBIOS_TABLE_TYPE32),        // UINT8 Length
      SMBIOS_HANDLE_PI_RESERVED,
    },
    {0, 0, 0, 0, 0, 0},                    // reserved
    BootInformationStatusNoError,
  },
  {                                        // Null-terminated table
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
SMBIOS_PLATFORM_DXE_STRING_TOKEN_DATA (PlatformSystemBoot) = {
  {                          // Table 1
    {                        // Tokens array
      NULL_TERMINATED_TOKEN
    },
    0                        // Size of Tokens array
  }
};
