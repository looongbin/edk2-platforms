/** @file

  Copyright (c) 2024, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2024. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/ConfigUtilsLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/HiiLib.h>
#include <Library/PrintLib.h>
#include <Library/IniParserLib.h>
#include <Library/PcdLib.h>

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_FUNCTION (PlatformBoard) {
  EFI_STATUS          Status;
  STR_TOKEN_INFO      *InputStrToken;
  SMBIOS_TABLE_TYPE2  *Type2Record;
  SMBIOS_TABLE_TYPE2  *InputData;
  CHAR16              *UnicodeStrFromPcd;
  CHAR16              SerialNumStr[SMBIOS_UNICODE_STRING_MAX_LENGTH];
  UINT32              SerialNum;
  UINT32              HashValue;
  UINTN               HandleCount;
  UINT16              *HandleArray;

  InputData     = (SMBIOS_TABLE_TYPE2 *)RecordData;
  InputStrToken = (STR_TOKEN_INFO *)StrToken;

  HandleArray = NULL;
  SmbiosPlatformDxeGetLinkTypeHandle (
    EFI_SMBIOS_TYPE_SYSTEM_ENCLOSURE,
    &HandleArray,
    &HandleCount
    );
  if (HandleArray == NULL || HandleCount == 0) {
    DEBUG ((DEBUG_ERROR, "[%a] Failed to get Chassis (Type3) handle\n", __func__));
    return EFI_NOT_FOUND;
  }

  while (InputData->Hdr.Type != NULL_TERMINATED_TYPE) {
    Status = SmbiosPlatformDxeSaveHiiDefaultString (InputStrToken);
    if (EFI_ERROR (Status)) {
      FreePool (HandleArray);
      return Status;
    }

    UnicodeStrFromPcd = FixedPcdGetPtr(PcdProductName);
    HiiSetString (mSmbiosPlatformDxeHiiHandle, InputStrToken->TokenArray[1], UnicodeStrFromPcd, NULL);
    UnicodeStrFromPcd = FixedPcdGetPtr(PcdBoardVersion);
    HiiSetString (mSmbiosPlatformDxeHiiHandle, InputStrToken->TokenArray[2], UnicodeStrFromPcd, NULL);

    if (UpdateSmbiosFromEfuse(0, EFUSE_CPU_SERIAL_NUM_OFFSET, 4, &SerialNum) == 0) {
      HashValue = CalculateCrc32 (&SerialNum, sizeof (SerialNum));
      UnicodeSPrint (SerialNumStr, sizeof (SerialNumStr), L"%02X-%02X-%02X-%02X",
          (HashValue >> 24) & 0xFF, (HashValue >> 16) & 0xFF,
          (HashValue >> 8) & 0xFF, HashValue & 0xFF);
      HiiSetString (mSmbiosPlatformDxeHiiHandle, InputStrToken->TokenArray[3], SerialNumStr, NULL);
    }

    SmbiosPlatformDxeCreateTable (
      (VOID *)&Type2Record,
      (VOID *)&InputData,
      sizeof (SMBIOS_TABLE_TYPE2),
      InputStrToken
      );
    if (Type2Record == NULL) {
      FreePool (HandleArray);
      return EFI_OUT_OF_RESOURCES;
    }

    Type2Record->ChassisHandle = HandleArray[0];

    Status = SmbiosPlatformDxeAddRecord ((UINT8 *)Type2Record, NULL);
    if (EFI_ERROR (Status)) {
      FreePool (Type2Record);
      FreePool (HandleArray);
      return Status;
    }

    FreePool (Type2Record);
    Status = SmbiosPlatformDxeRestoreHiiDefaultString (InputStrToken);
    if (EFI_ERROR (Status)) {
      FreePool (HandleArray);
      return Status;
    }
    InputData++;
    InputStrToken++;
  }

  FreePool (HandleArray);
  return EFI_SUCCESS;
}
