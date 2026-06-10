/** @file

  Copyright (c) 2022, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_DATA (SMBIOS_TABLE_TYPE44, PlatformProcessorAdditional) = {
  {							// Table 1
    {							// Header
      EFI_SMBIOS_TYPE_PROCESSOR_ADDITIONAL_INFORMATION, // Type
      sizeof (SMBIOS_TABLE_TYPE44),			// Length
      SMBIOS_HANDLE_PI_RESERVED				// Handle
    },
  },
  {							// Null-terminated table
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
SMBIOS_PLATFORM_DXE_STRING_TOKEN_DATA (PlatformProcessorAdditional) = {
  {                          // Table 1
    {                        // Tokens array
      NULL_TERMINATED_TOKEN
    },
    0                        // Size of Tokens array
  }
};
