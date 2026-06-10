/** @file

  Copyright (c) 2024, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_DATA (SMBIOS_TABLE_TYPE3, PlatformChassis) = {
  {                                         // Table 1
    {                                       // Header
      EFI_SMBIOS_TYPE_SYSTEM_ENCLOSURE,     // Type
      sizeof (SMBIOS_TABLE_TYPE3),          // Length
      SMBIOS_HANDLE_PI_RESERVED             // Handle
    },
    1,                                      // Manufacturer
    2,                                      // enclosure type
    2,                                      // version
    3,                                      // serial
    4,                                      // asset tag
    ChassisStateUnknown,                    // boot chassis state
    ChassisStateSafe,                       // power supply state
    ChassisStateSafe,                       // thermal state
    ChassisSecurityStatusNone,              // security state
    {0,0,0,0,},                             // OEM defined
    1,                                      // 1U height
    1,                                      // number of power cords
    0,                                      // no contained elements
  },
  {                                         // Null-terminated table
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
SMBIOS_PLATFORM_DXE_STRING_TOKEN_DATA (PlatformChassis) = {
  {                                         // Table 1
    {                                       // Tokens array
      STRING_TOKEN (STR_PLATFORM_DXE_CHASSIS_MANUFACTURER),
      STRING_TOKEN (STR_PLATFORM_DXE_CHASSIS_VERSION),
      STRING_TOKEN (STR_PLATFORM_DXE_CHASSIS_SERIAL),
      STRING_TOKEN (STR_PLATFORM_DXE_CHASSIS_ASSET_TAG)
    },
    ADDITIONAL_STR_INDEX_4                  // Size of Tokens array
  }
};
