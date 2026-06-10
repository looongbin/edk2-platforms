/** @file
  This file provides SMBIOS Type.

  Based on files under Nt32Pkg/MiscSubClassPlatformDxe/

  Copyright (c) 2023 - 2024, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2021, NUVIA Inc. All rights reserved.<BR>
  Copyright (c) 2006 - 2011, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2015, Hisilicon Limited. All rights reserved.<BR>
  Copyright (c) 2015, Linaro Limited. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE0,
  PlatformBios
  )
SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE1,
  PlatformSystem
  )
SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE2,
  PlatformBoard
  )
SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE3,
  PlatformChassis
  )
SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE4,
  PlatformProcessor
  )
SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE7,
  PlatformCache
  )
SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE9,
  PlatformSystemSlot
  )
SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE11,
  PlatformOemString
  )
SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE13,
  PlatformLanguage
  )
SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE16,
  PlatformPhysicalMemoryArray
  )
SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE17,
  PlatformMemoryDevice
  )
SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE19,
  PlatformMemoryArrayMappedAddress
  )
SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE32,
  PlatformSystemBoot
  )
SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE39,
  PlatformPowerSupply
  )
SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE41,
  PlatformOnboardDevicesExtended
  )
SMBIOS_PLATFORM_DXE_TABLE_EXTERNS (
  SMBIOS_TABLE_TYPE44,
  PlatformProcessorAdditional
  )

SMBIOS_PLATFORM_DXE_DATA_TABLE mSmbiosPlatformDxeDataTable[] = {
  // Type0
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformBios
    ),
  // Type1
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformSystem
    ),
  // Type3 (before Type2)
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformChassis
    ),
  // Type2
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformBoard
    ),
  // Type7 (before Type4)
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformCache
    ),
  // Type4 (before Type44)
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformProcessor
    ),
  // Type9
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformSystemSlot
    ),
  // Type11
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformOemString
    ),
  // Type13
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformLanguage
    ),
  // Type16 (before Type17 and Type19)
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformPhysicalMemoryArray
    ),
  // Type17
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformMemoryDevice
    ),
  // Type19
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformMemoryArrayMappedAddress
    ),
  // Type32
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformSystemBoot
    ),
  // Type39
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformPowerSupply
    ),
  // Type41
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformOnboardDevicesExtended
    ),
  // Type44
  SMBIOS_PLATFORM_DXE_TABLE_ENTRY_DATA_AND_FUNCTION (
    PlatformProcessorAdditional
    )
};

//
// Number of Data Table entries.
//
UINTN  mSmbiosPlatformDxeDataTableEntries = ARRAY_SIZE (mSmbiosPlatformDxeDataTable);
