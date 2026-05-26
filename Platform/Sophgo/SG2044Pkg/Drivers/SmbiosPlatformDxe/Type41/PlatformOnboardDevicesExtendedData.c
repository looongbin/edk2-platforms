/** @file

  Copyright (c) 2023, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2025. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "SmbiosPlatformDxe.h"

//
// Define data for SMBIOS Type 41 Table.
//
SMBIOS_PLATFORM_DXE_TABLE_DATA (SMBIOS_TABLE_TYPE41, PlatformOnboardDevicesExtended) = {
  {                                                         // Table 1
    {                                                       // Header
      EFI_SMBIOS_TYPE_ONBOARD_DEVICES_EXTENDED_INFORMATION, // Type
      sizeof (SMBIOS_TABLE_TYPE41),                         // Length
      SMBIOS_HANDLE_PI_RESERVED                             // Handle
    },
    ADDITIONAL_STR_INDEX_1,                                 // Reference Designation
    0x85,                                                   // Device Type
    0,                                                      // Device Type Instance
    0xFFFF,                                                 // Segment Group Number
    0xFF,                                                   // Bus Number
    0xFF                                                    // Device Function Number
  },
  {                                                         // Null-terminated table
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
SMBIOS_PLATFORM_DXE_STRING_TOKEN_DATA (PlatformOnboardDevicesExtended) = {
  {                                                                                 // Table 1
    {                                                                               // Tokens array
      STRING_TOKEN (STR_PLATFORM_DXE_ONBOARD_DEVICES_EXTENDED_DEVICE_TYPE_INSTANCE)
    },
    ADDITIONAL_STR_INDEX_1                                                          // Size of Tokens array
  }
};
