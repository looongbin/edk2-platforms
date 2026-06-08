/** @file

  Copyright (c) 2024, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_DATA (SMBIOS_TABLE_TYPE4, PlatformProcessor) = {
  {                                         // Table 1
    {                                       // Header
      EFI_SMBIOS_TYPE_PROCESSOR_INFORMATION,     // Type
      sizeof (SMBIOS_TABLE_TYPE4),          // Length
      SMBIOS_HANDLE_PROCESSOR,		    // Handle
    },
    1,                                       // socket type
    3,                                       // processor type CPU
    ProcessorFamilyIndicatorFamily2,         // processor family, acquire from field2
    2,                                       // manufactuer
    {{0,},{0.}},                             // processor id
    3,                                       // version
    {0,0,0,1,0,1},                           // voltage
    0,                                       // external clock
    2600,                                    // max speed
    2600,                                    // current speed - requires update
    0x41,                                    // status
    ProcessorUpgradeOther,
    0xFFFE,                                  // L1CacheHandle
    0xFFFE,                                  // L2CacheHandle
    0xFFFE,                                  // L3CacheHandle
    4,                                       // serial not set
    0,                                       // asset not set
    5,                                       // part number
    64,                                      // core count in socket
    64,                                      // enabled core count in socket
    64,                                      // threads per socket
    0xAC,                                    // processor characteristics
    ProcessorFamilyRiscVRV64,                // RISC-V core
    0,                                       // CoreCount2;
    0,                                       // EnabledCoreCount2;
    0,                                       // ThreadCount2;
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
SMBIOS_PLATFORM_DXE_STRING_TOKEN_DATA (PlatformProcessor) = {
  {                                         // Table 1
    {                                       // Tokens array
      STRING_TOKEN (STR_PLATFORM_DXE_PROCESSOR_SOCKET_DESIGNATION),
      STRING_TOKEN (STR_PLATFORM_DXE_PROCESSOR_MANUFACTURER),
      STRING_TOKEN (STR_PLATFORM_DXE_PROCESSOR_VERSION),
      STRING_TOKEN (STR_PLATFORM_DXE_PROCESSOR_SERIAL),
      STRING_TOKEN (STR_PLATFORM_DXE_PROCESSOR_PART_NUMBER)
    },
    ADDITIONAL_STR_INDEX_5                  // Size of Tokens array
  }
};
