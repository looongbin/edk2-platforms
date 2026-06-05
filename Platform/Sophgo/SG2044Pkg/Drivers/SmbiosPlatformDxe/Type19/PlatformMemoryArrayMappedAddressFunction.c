/** @file

  Copyright (c) 2023, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_FUNCTION (PlatformMemoryArrayMappedAddress) {
  EFI_STATUS           Status;
  STR_TOKEN_INFO       *InputStrToken;
  SMBIOS_TABLE_TYPE19  *InputData;
  SMBIOS_TABLE_TYPE19  *Type19Record;
  UINTN                HandleCount;
  UINT16               *HandleArray;

  InputData     = (SMBIOS_TABLE_TYPE19 *)RecordData;
  InputStrToken = (STR_TOKEN_INFO *)StrToken;

  HandleArray = NULL;
  SmbiosPlatformDxeGetLinkTypeHandle (
    EFI_SMBIOS_TYPE_PHYSICAL_MEMORY_ARRAY,
    &HandleArray,
    &HandleCount
    );
  if (HandleArray == NULL || HandleCount == 0) {
    DEBUG ((DEBUG_ERROR, "[%a] Failed to get Physical Memory Array (Type16) handle\n", __func__));
    return EFI_NOT_FOUND;
  }

  while (InputData->Hdr.Type != NULL_TERMINATED_TYPE) {
    SmbiosPlatformDxeCreateTable (
      (VOID *)&Type19Record,
      (VOID *)&InputData,
      sizeof (SMBIOS_TABLE_TYPE19),
      InputStrToken
      );
    if (Type19Record == NULL) {
      FreePool (HandleArray);
      return EFI_OUT_OF_RESOURCES;
    }

    Type19Record->MemoryArrayHandle = HandleArray[0];

    Status = SmbiosPlatformDxeAddRecord ((UINT8 *)Type19Record, NULL);
    if (EFI_ERROR (Status)) {
      FreePool (Type19Record);
      FreePool (HandleArray);
      return Status;
    }

    FreePool (Type19Record);

    InputData++;
  }

  FreePool (HandleArray);
  return Status;
}
