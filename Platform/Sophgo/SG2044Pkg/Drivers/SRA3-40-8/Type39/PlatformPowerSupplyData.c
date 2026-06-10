/** @file

  Copyright (c) 2024, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_DATA (SMBIOS_TABLE_TYPE39, PlatformPowerSupply) = {
  {                                         // Table 1 - PSU #1
    {                                       // Header
      EFI_SMBIOS_TYPE_SYSTEM_POWER_SUPPLY,  // Type
      sizeof (SMBIOS_TABLE_TYPE39),         // Length
      SMBIOS_HANDLE_PI_RESERVED             // Handle
    },
    1,                                      // PowerUnitGroup
    1,                                      // Location (string token)
    2,                                      // DeviceName
    3,                                      // Manufacturer
    4,                                      // SerialNumber
    5,                                      // AssetTagNumber
    6,                                      // ModelPartNumber
    7,                                      // RevisionLevel
    2000,                                   // MaxPowerCapacity (Watts)
    {0,},                                   // PowerSupplyCharacteristics (will set present flag in function)
    0xFFFE,                                 // InputVoltageProbeHandle - not implemented
    0xFFFE,                                 // CoolingDeviceHandle - not implemented
    0xFFFE,                                 // InputCurrentProbeHandle - not implemented
  },
  {                                         // Table 2 - PSU #2
    {                                       // Header
      EFI_SMBIOS_TYPE_SYSTEM_POWER_SUPPLY,  // Type
      sizeof (SMBIOS_TABLE_TYPE39),         // Length
      SMBIOS_HANDLE_PI_RESERVED             // Handle
    },
    2,                                      // PowerUnitGroup (same group = redundant pair)
    1,                                      // Location (string token)
    2,                                      // DeviceName
    3,                                      // Manufacturer
    4,                                      // SerialNumber
    5,                                      // AssetTagNumber
    6,                                      // ModelPartNumber
    7,                                      // RevisionLevel
    2000,                                   // MaxPowerCapacity (Watts)
    {0,},                                   // PowerSupplyCharacteristics (will set present flag in function)
    0xFFFE,                                 // InputVoltageProbeHandle - not implemented
    0xFFFE,                                 // CoolingDeviceHandle - not implemented
    0xFFFE,                                 // InputCurrentProbeHandle - not implemented
  },
  {                                         // Null-terminated table
    {
      NULL_TERMINATED_TYPE,
      0,
      0
    },
  }
};

// Define string Tokens for additional strings.
SMBIOS_PLATFORM_DXE_STRING_TOKEN_DATA (PlatformPowerSupply) = {
  {                                         // Table 1 - PSU #1
    {                                       // Tokens array
      STRING_TOKEN (STR_PLATFORM_DXE_PSU_LOCATION_1),
      STRING_TOKEN (STR_PLATFORM_DXE_PSU_DEVICE_NAME_1),
      STRING_TOKEN (STR_PLATFORM_DXE_PSU_MANUFACTURER_1),
      STRING_TOKEN (STR_PLATFORM_DXE_PSU_SERIAL_1),
      STRING_TOKEN (STR_PLATFORM_DXE_PSU_ASSET_TAG_1),
      STRING_TOKEN (STR_PLATFORM_DXE_PSU_PART_NUMBER_1),
      STRING_TOKEN (STR_PLATFORM_DXE_PSU_REVISION_1)
    },
    7                                       // Size of Tokens array
  },
  {                                         // Table 2 - PSU #2
    {                                       // Tokens array
      STRING_TOKEN (STR_PLATFORM_DXE_PSU_LOCATION_2),
      STRING_TOKEN (STR_PLATFORM_DXE_PSU_DEVICE_NAME_2),
      STRING_TOKEN (STR_PLATFORM_DXE_PSU_MANUFACTURER_2),
      STRING_TOKEN (STR_PLATFORM_DXE_PSU_SERIAL_2),
      STRING_TOKEN (STR_PLATFORM_DXE_PSU_ASSET_TAG_2),
      STRING_TOKEN (STR_PLATFORM_DXE_PSU_PART_NUMBER_2),
      STRING_TOKEN (STR_PLATFORM_DXE_PSU_REVISION_2)
    },
    7                                       // Size of Tokens array
  }
};
