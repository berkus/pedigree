/*
 * Copyright (c) 2008 James Molloy, James Pritchett, Jörg Pfähler, Matthew Iselin
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef KERNEL_MACHINE_ACPI_H
#define KERNEL_MACHINE_ACPI_H

#include <compiler.h>
#include <processor/types.h>
#include <processor/MemoryRegion.h>
#include <utilities/Vector.h>
#include "../../core/processor/x86_common/Multiprocessor.h"

/** @addtogroup kernelmachinex86common
 * @{ */

class Acpi
{
  public:
    inline static Acpi &instance()
      {return m_Instance;}

    void initialise();
    void parseFixedACPIDescriptionTable();

    #if defined(MULTIPROCESSOR)
      bool getProcessorList(uint64_t &localApicsAddress,
                            Vector<ProcessorInformation*> &Processors,
                            Vector<IoApicInformation*> &IoApics,
                            bool &bHasPics,
                            bool &bPicMode);
    #endif

  private:
    Acpi();
    Acpi(const Acpi &);
    Acpi &operator = (const Acpi &);
    inline ~Acpi(){}

    struct RsdtPointer
    {
      // ACPI 1.0+
      uint64_t signature;
      uint8_t checksum;
      char oemId[6];
      uint8_t revision;
      uint32_t rsdtAddress;

      // ACPI 2.0+
      uint32_t length;
      uint64_t xsdtAddress;
      uint8_t extendedChecksum;
      uint8_t reserved[3];
    } PACKED;

    struct SystemDescriptionTableHeader
    {
      uint32_t signature;
      uint32_t length;
      uint8_t revision;
      uint8_t checksum;
      char oemId[6];
      char oemTableId[8];
      uint32_t oemRevision;
      uint32_t creatorId;
      uint32_t creatorRevision;
    } PACKED;

    struct FixedACPIDescriptionTable
    {
      SystemDescriptionTableHeader header;

      uint32_t firmwareControl;
      uint32_t dsdt;
      uint8_t interruptModel;
      uint8_t reserved0;
      uint16_t sciInterrupt;
      uint32_t smiCommandPort;
      uint8_t acpiEnableCommand;
      uint8_t acpiDisableCommand;
      uint8_t s4BiosCommand;
      uint8_t reserved1;
      uint32_t pm1aEventBlock;
      uint32_t pm1bEventBlock;
      uint32_t pm1aControlBlock;
      uint32_t pm1bControlBlock;
      uint32_t pm2ControlBlock;
      uint32_t pmTimerBlock;
      uint32_t gpe0Block;
      uint32_t gpe1Block;
      uint8_t pm1EventLength;
      uint8_t pm1ControlLength;
      uint8_t pm2ControlLength;
      uint8_t pmTimerLength;
      uint8_t gpe0BlockLength;
      uint8_t gpe1BlockLength;
      uint8_t gpe1Base;
      uint8_t reserved2;
      uint16_t pmLevel2Latency;
      uint16_t pmLevel3Latency;
      uint16_t flushSize;
      uint16_t flushStride;
      uint8_t dutyOffset;
      uint8_t dutyWidth;
      uint8_t cmosDayAlarmIndex;
      uint8_t cmosMonthAlarmIndex;
      uint8_t cmosCenturyIndex;
      uint8_t reserved3[3];
      uint32_t flags;
    } PACKED;

    struct ProcessorLocalApic
    {
      uint8_t processorId;
      uint8_t apicId;
      uint32_t flags;
    } PACKED;

    struct IoApic
    {
      uint8_t apicId;
      uint8_t reserved;
      uint32_t address;
      uint32_t globalSystemInterruptBase;
    } PACKED;

    struct InterruptSourceOverride
    {
      uint8_t bus;
      uint8_t source;
      uint8_t globalSystemInterrupt;
      uint16_t flags;
    } PACKED;

    bool find();
    RsdtPointer *find(void *pMemory, size_t sMemory);
    bool checksum(const RsdtPointer *pRdstPointer);
    bool checksum(const SystemDescriptionTableHeader *pHeader);

    RsdtPointer *m_pRsdtPointer;
    MemoryRegion m_AcpiMemoryRegion;
    SystemDescriptionTableHeader *m_pRsdt;
    FixedACPIDescriptionTable *m_pFacp;

    #if defined(MULTIPROCESSOR)
      SystemDescriptionTableHeader *m_pApic;
    #endif

    static Acpi m_Instance;
};

/** @} */

#endif
