#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>

// 定义内存相关的标识符
#define AddMem             0x1
#define AddDev             0x2
#define SYS_MEM            0x3
#define MMIO               0x4
#define Conv               0x5
#define NS_DEVICE          0x6
#define WriteBack          0x7
#define UNCACHED           0x8

// 定义 DEVICE_MEMORY_DESCRIPTOR 类型
typedef struct {
    EFI_PHYSICAL_ADDRESS BaseAddress;
    EFI_PHYSICAL_ADDRESS Length;
    UINT32 Attributes;
    UINT32 Type;
    UINT32 MemoryType;
    UINT32 CacheAttributes;
} DEVICE_MEMORY_DESCRIPTOR;

// 内存映射表
DEVICE_MEMORY_DESCRIPTOR DeviceMemoryDescriptor[] = {
    { 0x80894000, 0x0000C000, AddMem, SYS_MEM, Conv, WriteBack },   // System RAM
    { 0x8E71C000, 0x0000E400, AddMem, SYS_MEM, Conv, WriteBack },   // System RAM
    { 0x8E900000, 0x00700000, AddMem, SYS_MEM, Conv, WriteBack },   // System RAM
    { 0x9F000000, 0x184FFFFF, AddMem, SYS_MEM, Conv, WriteBack },   // System RAM
    { 0xC0000000, 0x16000000, AddMem, SYS_MEM, Conv, WriteBack },   // System RAM
    { 0xD6800000, 0x02000000, AddMem, SYS_MEM, Conv, WriteBack },   // System RAM
    { 0xE0A00000, 0x276FFFFFF, AddMem, SYS_MEM, Conv, WriteBack },  // System RAM
    { 0x370C00000, 0x019600000, AddDev, MMIO, NS_DEVICE, UNCACHED }, // Reserved Memory
    { 0x37E63A000, 0x0000001000, AddDev, MMIO, NS_DEVICE, UNCACHED }, // Reserved
    { 0x37E63D000, 0x0000001000, AddDev, MMIO, NS_DEVICE, UNCACHED }, // Reserved
    { 0x37E63E000, 0x0000001000, AddDev, MMIO, NS_DEVICE, UNCACHED }, // Reserved
    { 0x37E63F000, 0x000005000, AddDev, MMIO, NS_DEVICE, UNCACHED }, // Reserved
    { 0x37E645000, 0x018000000, AddDev, MMIO, NS_DEVICE, UNCACHED }, // Reserved
};

// 数组大小
UINTN DeviceMemoryDescriptorCount = sizeof(DeviceMemoryDescriptor) / sizeof(DeviceMemoryDescriptor[0]);

// 主函数实现，返回内存描述符数组
VOID
EFIAPI
GetPlatformMemoryMap (
    OUT DEVICE_MEMORY_DESCRIPTOR **MemoryMap,
    OUT UINTN *DescriptorCount
    )
{
    *MemoryMap = DeviceMemoryDescriptor;
    *DescriptorCount = DeviceMemoryDescriptorCount;
}
