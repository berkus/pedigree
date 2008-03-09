#include "Elf32.h"

#include "autogen.h"

#define LOAD_ADDR 0x80200000
extern int memset(void *buf, int c, size_t len);
struct BootstrapStruct_t
{
  // If we are passed via grub, this information will be completely different to
  // via the bootstrapper.
  uint32_t flags;
  
  uint32_t mem_lower;
  uint32_t mem_upper;
  
  uint32_t boot_device;
  
  uint32_t cmdline;
  
  uint32_t mods_count;
  uint32_t mods_addr;
  
  /* ELF information */
  uint32_t num;
  uint32_t size;
  uint32_t addr;
  uint32_t shndx;
  
  uint32_t mmap_length;
  uint32_t mmap_addr;
  
  uint32_t drives_length;
  uint32_t drives_addr;
  
  uint32_t config_table;
  
  uint32_t boot_loader_name;
  
  uint32_t apm_table;
  
  uint32_t vbe_control_info;
  uint32_t vbe_mode_info;
  uint32_t vbe_mode;
  uint32_t vbe_interface_seg;
  uint32_t vbe_interface_off;
  uint32_t vbe_interface_len;
} __attribute__((packed));

void writeChar(char c)
{
  unsigned int *p = reinterpret_cast<unsigned int*>(0x91100004);
  *p = static_cast<unsigned int>(c);
}

void writeStr(const char *str)
{
  char c;
  while ((c = *str++))
    writeChar(c);
}

extern "C" int start()
{

  Elf32 elf("kernel");
  elf.load((uint8_t*)file, 0);
  elf.writeSections();
  int (*main)(struct BootstrapStruct_t*) = (int (*)(struct BootstrapStruct_t*)) elf.getEntryPoint();
  
  struct BootstrapStruct_t bs;
  
  memset(&bs, 0, sizeof(bs));
  bs.shndx = elf.m_pHeader->shstrndx;
  bs.num = elf.m_pHeader->shnum;
  bs.size = elf.m_pHeader->shentsize;
  bs.addr = (unsigned int)elf.m_pSectionHeaders;
  
  // For every section header, set .addr = .offset + m_pBuffer.
  for (int i = 0; i < elf.m_pHeader->shnum; i++)
  {
    elf.m_pSectionHeaders[i].addr = elf.m_pSectionHeaders[i].offset + (uint32_t)elf.m_pBuffer;
  }
  
  int a = main(&bs);
  return a;
}
