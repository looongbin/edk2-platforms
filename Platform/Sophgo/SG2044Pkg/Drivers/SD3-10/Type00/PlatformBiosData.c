/** @file

  Copyright (c) 2024, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_DATA (SMBIOS_TABLE_TYPE0, PlatformBios) = {
  {                                         // Table 1
    {                                       // Header
      EFI_SMBIOS_TYPE_BIOS_INFORMATION,     // Type
      sizeof (SMBIOS_TABLE_TYPE0),          // Length
      SMBIOS_HANDLE_PI_RESERVED             // Handle
    },
    ADDITIONAL_STR_INDEX_1,                 // SMBIOS_TABLE_STRING       Vendor
    ADDITIONAL_STR_INDEX_2,                 // SMBIOS_TABLE_STRING       BiosVersion
    0x0,                                    // UINT16                    BiosSegment
    ADDITIONAL_STR_INDEX_3,		    // SMBIOS_TABLE_STRING       BiosReleaseDate
    0,                                      // UINT8                     BiosRomSize
    {                                       // BiosCharacteristics
      0,                                    // Reserved                          :2
      0,                                    // Unknown                           :1
      0,                                    // BiosCharacteristicsNotSupported   :1
      0,                                    // IsaIsSupported                    :1
      0,                                    // McaIsSupported                    :1
      0,                                    // EisaIsSupported                   :1
      1,                                    // PciIsSupported                    :1
      0,                                    // PcmciaIsSupported                 :1
      0,                                    // PlugAndPlayIsSupported            :1
      0,                                    // ApmIsSupported                    :1
      1,                                    // BiosIsUpgradable                  :1
      0,                                    // BiosShadowingAllowed              :1
      0,                                    // VlVesaIsSupported                 :1
      0,                                    // EscdSupportIsAvailable            :1
      0,                                    // BootFromCdIsSupported             :1
      1,                                    // SelectableBootIsSupported         :1
      0,                                    // RomBiosIsSocketed                 :1
      0,                                    // BootFromPcmciaIsSupported         :1
      0,                                    // EDDSpecificationIsSupported       :1
      0,                                    // JapaneseNecFloppyIsSupported      :1
      0,                                    // JapaneseToshibaFloppyIsSupported  :1
      0,                                    // Floppy525_360IsSupported          :1
      0,                                    // Floppy525_12IsSupported           :1
      0,                                    // Floppy35_720IsSupported           :1
      0,                                    // Floppy35_288IsSupported           :1
      0,                                    // PrintScreenIsSupported            :1
      0,                                    // Keyboard8042IsSupported           :1
      0,                                    // SerialIsSupported                 :1
      0,                                    // PrinterIsSupported                :1
      0,                                    // CgaMonoIsSupported                :1
      0,                                    // NecPc98                           :1
      0                                     // ReservedForVendor                 :3
    },
    {
      0x3,                                  // BIOSCharacteristicsExtensionBytes[0]
      0x8,                                  // BIOSCharacteristicsExtensionBytes[1]
    },
    0xFF,                                   // UINT8                     SystemBiosMajorRelease
    0xFF,                                   // UINT8                     SystemBiosMinorRelease
    0xFF,                                   // UINT8                     EmbeddedControllerFirmwareMajorRelease
    0xFF,                                   // UINT8                     EmbeddedControllerFirmwareMinorRelease
    {
      0x0,                                  // SIZE
      0x0                                   // UNIT
    }
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
SMBIOS_PLATFORM_DXE_STRING_TOKEN_DATA (PlatformBios) = {
  {                                         // Table 1
    {                                       // Tokens array
      STRING_TOKEN (STR_PLATFORM_DXE_BIOS_VENDOR),
      STRING_TOKEN (STR_PLATFORM_DXE_BIOS_VERSION),
      STRING_TOKEN (STR_PLATFORM_DXE_BIOS_RELEASE_DATE)
    },
    ADDITIONAL_STR_INDEX_3                  // Size of Tokens array
  }
};
