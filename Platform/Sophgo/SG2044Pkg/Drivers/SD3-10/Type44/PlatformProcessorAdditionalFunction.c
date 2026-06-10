/** @file

  Copyright (c) 2023, Ampere Computing LLC. All rights reserved.<BR>
  Copyright (c) 2025. SOPHGO Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <ProcessorSpecificHobData.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseRiscVSbiLib.h>

#include "SmbiosPlatformDxe.h"

SMBIOS_PLATFORM_DXE_TABLE_FUNCTION (PlatformProcessorAdditional) {
  EFI_STATUS                  Status;
  SMBIOS_TABLE_TYPE44         *Type44Ptr;
  UINT32                      Index;
  UINT32                      CoreReg;
  UINTN                       MachineVendorId, MachineArchId, MachineImplId;
  EFI_RISCV_FIRMWARE_CONTEXT  *FirmwareContext;
  UINT32                      CpuNum;
  UINT32                      *CpuRegs;
  UINTN                       HandleCount;
  UINT16                      *HandleArray;

  GetFirmwareContext (&FirmwareContext);
  SbiGetMachineVendorId (&MachineVendorId);
  SbiGetMachineArchId (&MachineArchId);
  SbiGetMachineImplId (&MachineImplId);

  DEBUG ((DEBUG_INFO, "BootHardId: %lu\n", FirmwareContext->BootHartId));
  DEBUG ((DEBUG_INFO, "MachineVendorId: %lx, MachineArchId: %lx, MachineImplId: %lx\n", MachineVendorId, MachineArchId, MachineImplId));

  CpuNum  = FixedPcdGet32 (PcdCpuCount);
  CpuRegs = (UINT32 *)PcdGetPtr (PcdCpuReg);
  if (CpuNum == 0 || CpuRegs == NULL) {
    DEBUG ((DEBUG_ERROR, "No CPU info found in PCD\n"));
    return EFI_NOT_FOUND;
  }

  HandleArray = NULL;
  SmbiosPlatformDxeGetLinkTypeHandle (
    EFI_SMBIOS_TYPE_PROCESSOR_INFORMATION,
    &HandleArray,
    &HandleCount
    );
  if (HandleArray == NULL || HandleCount == 0) {
    DEBUG ((DEBUG_ERROR, "[%a] Failed to get Processor (Type4) handle\n", __func__));
    return EFI_NOT_FOUND;
  }

  for (Index = 0; Index < CpuNum; Index++) {

    CoreReg = CpuRegs[Index];
    DEBUG ((DEBUG_INFO, "CoreReg: %lx\n", CoreReg));

    Type44Ptr = AllocateZeroPool (sizeof (SMBIOS_TABLE_TYPE44) + sizeof (SMBIOS_BRS_PROCESSOR_SPECIFIC_DATA) + 2); // Two ending zero.
    if (Type44Ptr == NULL) {
      FreePool (HandleArray);
      return EFI_NOT_FOUND;
    }

    Type44Ptr->Hdr.Type                                 = SMBIOS_TYPE_PROCESSOR_ADDITIONAL_INFORMATION;
    Type44Ptr->Hdr.Handle                               = 0x10;
    Type44Ptr->Hdr.Length                               = sizeof (SMBIOS_TABLE_TYPE44) + sizeof (SMBIOS_BRS_PROCESSOR_SPECIFIC_DATA);
    Type44Ptr->RefHandle                                = HandleArray[0];
    Type44Ptr->ProcessorSpecificBlock.Length            = sizeof (SMBIOS_BRS_PROCESSOR_SPECIFIC_DATA);
    Type44Ptr->ProcessorSpecificBlock.ProcessorArchType = 0x7;

    //
    // The SMBIOS_BRS_PROCESSOR_SPECIFIC_DATA structure is compatible with SMBIOS Table Specification v3.9.0
    //
    ((SMBIOS_BRS_PROCESSOR_SPECIFIC_DATA *)(Type44Ptr + 1))->Revision = SMBIOS_RISC_V_PROCESSOR_SPECIFIC_DATA_REVISION;
    ((SMBIOS_BRS_PROCESSOR_SPECIFIC_DATA *)(Type44Ptr + 1))->HartId = CoreReg;
    ((SMBIOS_BRS_PROCESSOR_SPECIFIC_DATA *)(Type44Ptr + 1))->MachineVendorId = MachineVendorId;
    ((SMBIOS_BRS_PROCESSOR_SPECIFIC_DATA *)(Type44Ptr + 1))->MachineArchId = MachineArchId;
    ((SMBIOS_BRS_PROCESSOR_SPECIFIC_DATA *)(Type44Ptr + 1))->MachineImplId = MachineImplId;

    Status = SmbiosPlatformDxeDirectAddRecord ((UINT8 *)Type44Ptr, NULL);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Fail to add SMBIOS Type 44\n"));
      FreePool (Type44Ptr);
      FreePool (HandleArray);
      return Status;
    }

    FreePool (Type44Ptr);
  }

  FreePool (HandleArray);
  return EFI_SUCCESS;
}
