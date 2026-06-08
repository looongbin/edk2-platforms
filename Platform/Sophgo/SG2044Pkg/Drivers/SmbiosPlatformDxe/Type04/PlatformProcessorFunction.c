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

SMBIOS_PLATFORM_DXE_TABLE_FUNCTION (PlatformProcessor) {
  EFI_STATUS          Status;
  STR_TOKEN_INFO      *InputStrToken;
  SMBIOS_TABLE_TYPE4  *Type4Record;
  SMBIOS_TABLE_TYPE4  *InputData;
  UINT64              Freq;
  UINT32              ChipInfo;
  CHAR16              *ChipType;
  UINT32              ChipTypeVal;
  UINTN               MachineVendorId;
  UINT32              SerialNum;
  CHAR16              SerialNumStr[SMBIOS_UNICODE_STRING_MAX_LENGTH];
  CHAR16              *TpuStatus;
  CHAR16              VersionStr[SMBIOS_UNICODE_STRING_MAX_LENGTH];
  UINTN               HandleCount;
  UINT16              *HandleArray;

  InputData     = (SMBIOS_TABLE_TYPE4 *)RecordData;
  InputStrToken = (STR_TOKEN_INFO *)StrToken;

  HandleArray = NULL;
  SmbiosPlatformDxeGetLinkTypeHandle (
    EFI_SMBIOS_TYPE_CACHE_INFORMATION,
    &HandleArray,
    &HandleCount
    );
  if (HandleArray == NULL || HandleCount < 3) {
    DEBUG ((DEBUG_ERROR, "[%a] Failed to get Cache (Type7) handles (count=%u)\n", __func__, HandleCount));
    if (HandleArray != NULL) {
      FreePool (HandleArray);
    }
    return EFI_NOT_FOUND;
  }

  while (InputData->Hdr.Type != NULL_TERMINATED_TYPE) {
    Status = SmbiosPlatformDxeSaveHiiDefaultString (InputStrToken);
    if (EFI_ERROR (Status)) {
      FreePool (HandleArray);
      return Status;
    }

    // Ensure socket designation is a reasonable non-empty string
    HiiSetString (mSmbiosPlatformDxeHiiHandle, InputStrToken->TokenArray[0], L"SOCKET 0", NULL);

    Freq = FixedPcdGet64(PcdCpuFrequencyHz);
    if (Freq >= 1000000) {
          Freq = Freq / 1000000;
    }
    InputData->CurrentSpeed = Freq;

    //
    // Read chip info from efuse1 offset 0x178:
    //   bit15      : TPU status
    //   bits[19:16]: Chip type (0xF/0 = A, 0x1 = B, 0x2 = C, 0x3 = D, 0x4 = E)
    //
    if (UpdateSmbiosFromEfuse (1, EFUSE_CPU_INFO_OFFSET, 4, &ChipInfo) == 0) {
      TpuStatus = ((ChipInfo >> 15) & 1) ? L"" : L"T";
      ChipTypeVal = (ChipInfo >> 16) & 0xF;
      switch (ChipTypeVal) {
      case 0x1: ChipType = L"B"; break;
      case 0x2: ChipType = L"C"; break;
      case 0x3: ChipType = L"D"; break;
      case 0x4: ChipType = L"E"; break;
      default:  ChipType = L"A"; break;  // 0 or 0xF
      }
      UnicodeSPrint (VersionStr, sizeof (VersionStr), L"SG2044%s%s @ 2.6GHz", ChipType, TpuStatus);
    } else {
      UnicodeSPrint (VersionStr, sizeof (VersionStr), L"SG2044");
    }
    HiiSetString (mSmbiosPlatformDxeHiiHandle, InputStrToken->TokenArray[2], VersionStr, NULL);

    // Set processor voltage capability to indicate a non-zero voltage (3.3V flag)
    // This sets the PROCESSOR_VOLTAGE bitfield so SMBIOS will not report 0.0V.
    InputData->Voltage.ProcessorVoltageCapability5V = 0;
    InputData->Voltage.ProcessorVoltageCapability3_3V = 0;
    InputData->Voltage.ProcessorVoltageCapability2_9V = 0;
    InputData->Voltage.ProcessorVoltageCapabilityReserved = 1;
    InputData->Voltage.ProcessorVoltageIndicateLegacy = 1;

    InputData->ExternalClock = 25;

    SbiGetMachineVendorId (&MachineVendorId);
    *(UINT64 *)&InputData->ProcessorId = MachineVendorId;

    if (UpdateSmbiosFromEfuse(0, EFUSE_CPU_SERIAL_NUM_OFFSET, 4, &SerialNum) == 0) {
      UnicodeSPrint (SerialNumStr, sizeof (SerialNumStr), L"%02X-%02X-%02X-%02X",
                    (SerialNum >> 24) & 0xFF, (SerialNum >> 16) & 0xFF,
                    (SerialNum >> 8) & 0xFF, SerialNum & 0xFF);
      HiiSetString (mSmbiosPlatformDxeHiiHandle, InputStrToken->TokenArray[3], SerialNumStr, NULL);
    }

    SmbiosPlatformDxeCreateTable (
      (VOID *)&Type4Record,
      (VOID *)&InputData,
      sizeof (SMBIOS_TABLE_TYPE4),
      InputStrToken
    );
    if (Type4Record == NULL) {
      FreePool (HandleArray);
      return EFI_OUT_OF_RESOURCES;
    }

    Type4Record->L1CacheHandle = HandleArray[0];
    Type4Record->L2CacheHandle = HandleArray[1];
    Type4Record->L3CacheHandle = HandleArray[2];

    Status = SmbiosPlatformDxeAddRecord ((UINT8 *)Type4Record, NULL);
    if (EFI_ERROR (Status)) {
      FreePool (Type4Record);
      FreePool (HandleArray);
      return Status;
    }

    FreePool (Type4Record);
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
