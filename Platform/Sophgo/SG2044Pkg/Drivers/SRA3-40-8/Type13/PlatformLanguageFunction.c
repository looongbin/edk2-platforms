/** @file

  Copyright (c) 2024, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_FUNCTION (PlatformLanguage) {
  EFI_STATUS          Status;
  STR_TOKEN_INFO      *InputStrToken;
  SMBIOS_TABLE_TYPE13  *Type13Record;
  SMBIOS_TABLE_TYPE13  *InputData;

  InputData     = (SMBIOS_TABLE_TYPE13 *)RecordData;
  InputStrToken = (STR_TOKEN_INFO *)StrToken;

  while (InputData->Hdr.Type != NULL_TERMINATED_TYPE) {
    SmbiosPlatformDxeCreateTable (
      (VOID *)&Type13Record,
      (VOID *)&InputData,
      sizeof (SMBIOS_TABLE_TYPE13),
      InputStrToken
      );
    if (Type13Record == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    Status = SmbiosPlatformDxeAddRecord ((UINT8 *)Type13Record, NULL);
    if (EFI_ERROR (Status)) {
      FreePool (Type13Record);
      return Status;
    }

    FreePool (Type13Record);
    InputData++;
    InputStrToken++;
  }

  return EFI_SUCCESS;
}
