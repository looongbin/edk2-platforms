/** @file

  Copyright (c) 2024, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_DATA (SMBIOS_TABLE_TYPE13, PlatformLanguage) = {
  {						     // Table 1
    {						     // Header
      EFI_SMBIOS_TYPE_BIOS_LANGUAGE_INFORMATION,     // Type
      sizeof (SMBIOS_TABLE_TYPE13),                  // Length
      SMBIOS_HANDLE_PI_RESERVED                      // Handle
    },
    1,                                               // InstallableLanguages
    1,                                               // Flags
    {
      0                                              // Reserved[15]
    },
    1                                                // CurrentLanguage
  },
  {                                                  // Null-terminated table
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
SMBIOS_PLATFORM_DXE_STRING_TOKEN_DATA (PlatformLanguage) = {
  {                                         // Table 1
    {                                       // Tokens array
      STRING_TOKEN (STR_PLATFORM_DXE_LANGUAGE),
    },
    ADDITIONAL_STR_INDEX_1                  // Size of Tokens array
  }
};
