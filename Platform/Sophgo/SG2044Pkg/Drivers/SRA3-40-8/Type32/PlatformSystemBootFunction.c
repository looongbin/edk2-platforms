/** @file

  Copyright (c) 2022, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_FUNCTION (PlatformSystemBoot) {
  EFI_STATUS           Status;
  STR_TOKEN_INFO       *InputStrToken;
  SMBIOS_TABLE_TYPE32  *InputData;
  SMBIOS_TABLE_TYPE32  *Type32Record;

  InputData     = (SMBIOS_TABLE_TYPE32 *)RecordData;
  InputStrToken = (STR_TOKEN_INFO *)StrToken;

  while (InputData->Hdr.Type != NULL_TERMINATED_TYPE) {
    SmbiosPlatformDxeCreateTable (
      (VOID *)&Type32Record,
      (VOID *)&InputData,
      sizeof (SMBIOS_TABLE_TYPE32),
      InputStrToken
      );
    if (Type32Record == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    Status = SmbiosPlatformDxeAddRecord ((UINT8 *)Type32Record, NULL);
    if (EFI_ERROR (Status)) {
      FreePool (Type32Record);
      return Status;
    }

    FreePool (Type32Record);
    InputData++;
  }

  return Status;
}
