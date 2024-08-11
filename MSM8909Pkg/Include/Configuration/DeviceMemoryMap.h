#ifndef _DEVICE_MEMORY_MAP_H_
#define _DEVICE_MEMORY_MAP_H_

#include <Library/ArmLib.h>

#define MAX_ARM_MEMORY_REGION_DESCRIPTOR_COUNT 64

/* Below flag is used for system memory */
#define SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES                               \
  EFI_RESOURCE_ATTRIBUTE_PRESENT | EFI_RESOURCE_ATTRIBUTE_INITIALIZED |        \
      EFI_RESOURCE_ATTRIBUTE_TESTED | EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |     \
      EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |                               \
      EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |                         \
      EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE |                            \
      EFI_RESOURCE_ATTRIBUTE_EXECUTION_PROTECTABLE

typedef enum { NoHob, AddMem, AddDev, HobOnlyNoCacheSetting, MaxMem } DeviceMemoryAddHob;

#define MEMORY_REGION_NAME_MAX_LENGTH 32

typedef struct {
  EFI_PHYSICAL_ADDRESS         Address;
  UINT64                       Length;
  CHAR8                        Name[MEMORY_REGION_NAME_MAX_LENGTH];
  DeviceMemoryAddHob           HobOption;
  EFI_RESOURCE_TYPE            ResourceType;
  EFI_RESOURCE_ATTRIBUTE_TYPE  ResourceAttribute;
  EFI_MEMORY_TYPE              MemoryType;
  ARM_MEMORY_REGION_ATTRIBUTES ArmAttributes;
} ARM_MEMORY_REGION_DESCRIPTOR_EX, *PARM_MEMORY_REGION_DESCRIPTOR_EX;

#define MEM_RES EFI_RESOURCE_MEMORY_RESERVED
#define MMAP_IO EFI_RESOURCE_MEMORY_MAPPED_IO
#define SYS_MEM EFI_RESOURCE_SYSTEM_MEMORY

#define SYS_MEM_CAP SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES
#define INITIALIZED EFI_RESOURCE_ATTRIBUTE_INITIALIZED
#define WRITE_COMBINEABLE EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE
#define UNCACHEABLE EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE

#define Reserv EfiReservedMemoryType
#define Conv EfiConventionalMemory
#define BsData EfiBootServicesData
#define RtData EfiRuntimeServicesData
#define LdData EfiLoaderData
#define MmIO EfiMemoryMappedIO
#define MaxMem EfiMaxMemoryType
#define BsCode EfiBootServicesCode
#define RtCode EfiRuntimeServicesCode

#define DEVICE ARM_MEMORY_REGION_ATTRIBUTE_DEVICE
#define WRITE_THROUGH ARM_MEMORY_REGION_ATTRIBUTE_WRITE_THROUGH
#define WRITE_THROUGH_XN ARM_MEMORY_REGION_ATTRIBUTE_WRITE_THROUGH
#define WRITE_BACK ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK
#define WRITE_BACK_XN ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK
#define UNCACHED_UNBUFFERED ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED
#define UNCACHED_UNBUFFERED_XN ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED

static ARM_MEMORY_REGION_DESCRIPTOR_EX gDeviceMemoryDescriptorEx[] = {
//                                                    EFI_RESOURCE_ EFI_RESOURCE_ATTRIBUTE_        ARM_REGION_ATTRIBUTE_
//MemBase,   MemSize,   MemLabel(32 Char.), BuildHob, ResourceType, ResourceAttribute, MemoryType, CacheAttributes

//------------- DDR Regions ------},
{0x00010000, 0x00011000, "DBI Dump",         NoHob,  MMAP_IO, INITIALIZED, Conv,   DEVICE},
{0x00010000, 0x00100000, "HLOS 0",           AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
{0x00200000, 0x00100000, "UEFI FD",          AddMem, SYS_MEM, SYS_MEM_CAP, BsCode, WRITE_BACK},
{0x00300000, 0x00040000, "MPPark Code",      AddMem, MEM_RES, UNCACHEABLE, RtCode, UNCACHED_UNBUFFERED},
{0x00340000, 0x00040000, "Reser. Uncached1", AddMem, SYS_MEM, SYS_MEM_CAP, BsData, UNCACHED_UNBUFFERED},
{0x00380000, 0x00001000, "FBPT Payload",     AddMem, SYS_MEM, SYS_MEM_CAP, RtData, UNCACHED_UNBUFFERED},
{0x00381000, 0x00004000, "DBG2",             AddMem, SYS_MEM, SYS_MEM_CAP, RtData, UNCACHED_UNBUFFERED},
{0x00385000, 0x00001000, "Capsule Header",   AddMem, SYS_MEM, SYS_MEM_CAP, RtData, UNCACHED_UNBUFFERED},
{0x00386000, 0x00003000, "TPM Control Area", AddMem, SYS_MEM, SYS_MEM_CAP, RtData, UNCACHED_UNBUFFERED},
{0x00389000, 0x00001000, "UEFI Info Block",  AddMem, SYS_MEM, SYS_MEM_CAP, RtData, UNCACHED_UNBUFFERED},
{0x0038A000, 0x00003000, "Reset Data",       AddMem, SYS_MEM, SYS_MEM_CAP, BsData, UNCACHED_UNBUFFERED},
{0x0038A000, 0x00073000, "Reser. Uncached0", AddMem, SYS_MEM, SYS_MEM_CAP, BsData, UNCACHED_UNBUFFERED},
{0x03200000, 0x00800000, "Display Reserved", AddMem, MEM_RES, WRITE_THROUGH, MaxMem, WRITE_THROUGH},
{0x00C00000, 0x00040000, "UEFI Stack",       AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
{0x00C40000, 0x00010000, "CPU Vectors",      AddMem, SYS_MEM, SYS_MEM_CAP, BsCode, WRITE_BACK},
{0x00C50000, 0x000B0000, "Reser. Cached 0",  AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
{0x00D00000, 0x07300000, "HLOS 2",           AddMem, SYS_MEM, SYS_MEM_CAP, BsData,   WRITE_BACK},
{0x08000000, 0x07700000, "PIL_REGION",       AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, DEVICE},
{0x0F700000, 0x00300000, "TZ Apps",          AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, DEVICE},
{0x08400000, 0x01f00000, "MPSS_EFS / SBL",   AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, DEVICE},
{0x0D900000, 0x01800000, "ADSP_EFS",         AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, DEVICE},
{0x0FA00000, 0x00100000, "SMEM",             AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED},
{0x0FB00000, 0x00100000, "HLOS 3",           AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
{0x0FC00000, 0x00300000, "NonRelocateable 0",AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, DEVICE},
{0x10700000, 0x4FE00000, "HLOS 5",           AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
//------------- Other Memory Regions ------
{0xFE800000, 0x00004000, "IMEM Boot Base",   NoHob,  SYS_MEM, INITIALIZED, Conv,   DEVICE},
{0xFC42B000, 0x00001000, "IMEM Cookie Base", AddDev, MMAP_IO, INITIALIZED, Conv,   DEVICE},
{0xFE805000, 0x00001000, "IMEM Cookie Base2",AddDev, MMAP_IO, INITIALIZED, Conv,   DEVICE},
//------------- Register Regions ----------
{0xF9000000, 0x02000000, "REG 1",           AddDev, MMAP_IO,  UNCACHEABLE, MmIO,   DEVICE},
{0xFC400000, 0x00002000, "REG 2",           AddDev, MMAP_IO,  UNCACHEABLE, MmIO,   DEVICE},
{0xFC428000, 0x00008000, "REG 3",           AddDev, MMAP_IO,  UNCACHEABLE, MmIO,   DEVICE},
{0xFC4AB000, 0x00001000, "REG 4",           AddDev, MMAP_IO,  UNCACHEABLE, MmIO,   DEVICE},
{0xFC4C0000, 0x00040000, "REG 5",           AddDev, MMAP_IO,  UNCACHEABLE, MmIO,   DEVICE},
{0xFD400000, 0x00D00000, "REG 6",           AddDev, MMAP_IO,  UNCACHEABLE, MmIO,   DEVICE},
{0xFC4B8000, 0x00008000, "REG 7",           AddDev, MMAP_IO,  UNCACHEABLE, MmIO,   DEVICE},
{0xFC4A9000, 0x00008000, "REG 8",           AddDev, MMAP_IO,  UNCACHEABLE, MmIO,   DEVICE},

//------------- Terminator for MMU ----------
{0, 0, "Terminator", 0, 0, 0, 0, 0}

};

#endif
