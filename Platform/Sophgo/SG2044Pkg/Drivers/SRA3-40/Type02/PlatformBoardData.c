/** @file

  Copyright (c) 2024, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_DATA (SMBIOS_TABLE_TYPE2, PlatformBoard) = {
  {						// Table 1
    {						// Header
      EFI_SMBIOS_TYPE_BASEBOARD_INFORMATION,	// Type
      sizeof (SMBIOS_TABLE_TYPE2),		// Length
      SMBIOS_HANDLE_PI_RESERVED			// Handle
    },
    1,                                          // Manufacturer
    2,                                          // Product Name
    3,                                          // Version
    4,                                          // Serial
    0,                                          // Asset tag
    {1},                                        // motherboard, not replaceable
    0,                                          // location of board
    0xFFFE,                                     // ChassisHandle
    BaseBoardTypeMotherBoard,
    0,
    {},
  },
  {                                             // Null-terminated table
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
SMBIOS_PLATFORM_DXE_STRING_TOKEN_DATA (PlatformBoard) = {
  {                                         // Table 1
    {                                       // Tokens array
      STRING_TOKEN (STR_PLATFORM_DXE_BOARD_MANUFACTURER),
      STRING_TOKEN (STR_PLATFORM_DXE_BOARD_PRODUCT_NAME),
      STRING_TOKEN (STR_PLATFORM_DXE_BOARD_VERSION),
      STRING_TOKEN (STR_PLATFORM_DXE_BOARD_SERIAL)
    },
    ADDITIONAL_STR_INDEX_4                  // Size of Tokens array
  }
};
