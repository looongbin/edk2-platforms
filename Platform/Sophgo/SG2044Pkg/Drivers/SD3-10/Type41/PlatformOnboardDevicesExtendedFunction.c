/** @file

  Copyright (c) 2023, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2025. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/HiiLib.h>
#include <Library/PrintLib.h>

#include "SmbiosPlatformDxe.h"

#include <Include/PcieHostPcd.h>

#define TYPE41_DEVICE_TYPE_OTHERS 0x81

/**
  This function adds SMBIOS Table (Type 41) records.

  @param  RecordData                 Pointer to SMBIOS Table with default values.
  @param  Smbios                     SMBIOS protocol.

  @retval EFI_SUCCESS                The SMBIOS Table was successfully added.
  @retval Other                      Failed to update the SMBIOS Table.

**/
SMBIOS_PLATFORM_DXE_TABLE_FUNCTION (PlatformOnboardDevicesExtended) {
  EFI_STATUS                        Status;
  STR_TOKEN_INFO                    *InputStrToken;
  SMBIOS_TABLE_TYPE41               *InputData;
  SMBIOS_TABLE_TYPE41               *Type41Record;
  UINT32                            Index, SlotID, InstanceNum, NumberOfControllers, BoardSlotID;
  CHAR16                            SlotDesignation[SMBIOS_UNICODE_STRING_MAX_LENGTH];
  PCIE_HOST_BRIDGE_TABLE            *PcieRcConfig;


  InputData     = (SMBIOS_TABLE_TYPE41 *)RecordData;
  InputStrToken = (STR_TOKEN_INFO *)StrToken;

  InstanceNum = 0;
  PcieRcConfig  = (PCIE_HOST_BRIDGE_TABLE *)PcdGetPtr (PcdPcieHostBridgeTable);
  NumberOfControllers = PcieRcConfig->NumOfControllers;

  if (PcieRcConfig == NULL) {
    DEBUG ((DEBUG_ERROR, "[%a] No PCIe host bridge configuration found\n", __func__));
    return EFI_NOT_FOUND;
  }

  for (Index = 0; Index < NumberOfControllers; ++Index) {
    SlotID = PcieRcConfig->PcieDomain[Index][0] | (PcieRcConfig->PcieDomain[Index][1] << 8) |
             (PcieRcConfig->PcieDomain[Index][2] << 16) | (PcieRcConfig->PcieDomain[Index][3] << 24);
    BoardSlotID = MapSlot (SlotID);
    UnicodeSPrint (SlotDesignation, sizeof (SlotDesignation), L"SLOT%u", BoardSlotID);
    HiiSetString (mSmbiosPlatformDxeHiiHandle, InputStrToken->TokenArray[0], SlotDesignation, NULL);
    InputData->DeviceType = TYPE41_DEVICE_TYPE_OTHERS;
    InputData->DeviceTypeInstance = InstanceNum;
    InputData->SegmentGroupNum = (UINT16) SlotID;
    InputData->BusNum = 0;
    InputData->DevFuncNum = 0;

    SmbiosPlatformDxeCreateTable (
      (VOID *)&Type41Record,
      (VOID *)&InputData,
      sizeof (SMBIOS_TABLE_TYPE41),
      InputStrToken
      );
    if (Type41Record == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    Status = SmbiosPlatformDxeAddRecord ((UINT8 *)Type41Record, NULL);
    if (EFI_ERROR (Status)) {
      FreePool (Type41Record);
      return Status;
    }

    FreePool (Type41Record);
    InstanceNum++;
  }

  return EFI_SUCCESS;
}
