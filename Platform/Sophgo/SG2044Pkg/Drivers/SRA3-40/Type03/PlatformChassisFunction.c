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
#include <Library/HiiLib.h>
#include <Library/PrintLib.h>
#include <Library/IniParserLib.h>

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_FUNCTION (PlatformChassis) {
  EFI_STATUS          Status;
  STR_TOKEN_INFO      *InputStrToken;
  SMBIOS_TABLE_TYPE3  *Type3Record;
  SMBIOS_TABLE_TYPE3  *InputData;
  // CHAR16               UnicodeStr[SMBIOS_UNICODE_STRING_MAX_LENGTH];
  // CHAR8                value[SMBIOS_UNICODE_STRING_MAX_LENGTH];

  InputData     = (SMBIOS_TABLE_TYPE3 *)RecordData;
  InputStrToken = (STR_TOKEN_INFO *)StrToken;

  while (InputData->Hdr.Type != NULL_TERMINATED_TYPE) {
    Status = SmbiosPlatformDxeSaveHiiDefaultString (InputStrToken);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    InputData->Type = MiscChassisTypeMainServerChassis;
    InputData->NumberofPowerCords = 2;

    HiiSetString (mSmbiosPlatformDxeHiiHandle, InputStrToken->TokenArray[1], L"v1.0", NULL);

    // cluster SN

    InputData->Height = 4;

    // SKU NUM

    SmbiosPlatformDxeCreateTable (
      (VOID *)&Type3Record,
      (VOID *)&InputData,
      sizeof (SMBIOS_TABLE_TYPE3),
      InputStrToken
      );
    if (Type3Record == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    Status = SmbiosPlatformDxeAddRecord ((UINT8 *)Type3Record, NULL);
    if (EFI_ERROR (Status)) {
      FreePool (Type3Record);
      return Status;
    }

    FreePool (Type3Record);
    Status = SmbiosPlatformDxeRestoreHiiDefaultString (InputStrToken);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    InputData++;
    InputStrToken++;
  }

  return EFI_SUCCESS;
}
