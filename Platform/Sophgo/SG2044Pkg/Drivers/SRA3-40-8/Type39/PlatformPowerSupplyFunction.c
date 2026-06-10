/** @file

  Copyright (c) 2024, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/HiiLib.h>
#include <Library/PrintLib.h>

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_FUNCTION (PlatformPowerSupply) {
  EFI_STATUS            Status;
  STR_TOKEN_INFO        *InputStrToken;
  SMBIOS_TABLE_TYPE39   *Type39Record;
  SMBIOS_TABLE_TYPE39   *InputData;

  InputData     = (SMBIOS_TABLE_TYPE39 *)RecordData;
  InputStrToken = (STR_TOKEN_INFO *)StrToken;

  while (InputData->Hdr.Type != NULL_TERMINATED_TYPE) {
    Status = SmbiosPlatformDxeSaveHiiDefaultString (InputStrToken);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    // Ensure power supply is marked present
    InputData->PowerSupplyCharacteristics.PowerSupplyPresent = 1;
    InputData->PowerSupplyCharacteristics.PowerSupplyHotReplaceable = 0;
    InputData->PowerSupplyCharacteristics.PowerSupplyUnplugged = 0;
    InputData->PowerSupplyCharacteristics.InputVoltageRangeSwitch = 4;
    InputData->PowerSupplyCharacteristics.PowerSupplyStatus = 3;
    InputData->PowerSupplyCharacteristics.PowerSupplyType = 4; // Other/AC

    SmbiosPlatformDxeCreateTable (
      (VOID *)&Type39Record,
      (VOID *)&InputData,
      sizeof (SMBIOS_TABLE_TYPE39),
      InputStrToken
    );
    if (Type39Record == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    Status = SmbiosPlatformDxeAddRecord ((UINT8 *)Type39Record, NULL);
    if (EFI_ERROR (Status)) {
      FreePool (Type39Record);
      return Status;
    }

    FreePool (Type39Record);
    Status = SmbiosPlatformDxeRestoreHiiDefaultString (InputStrToken);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    InputData++;
    InputStrToken++;
  }

  return EFI_SUCCESS;
}
