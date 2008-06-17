/*
 * Copyright (c) 2008 James Molloy, Jörg Pfähler, Matthew Iselin
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
#ifndef ATA_ATA_CONTROLLER_H
#define ATA_ATA_CONTROLLER_H

#include <processor/types.h>
#include <machine/Device.h>
#include <machine/Disk.h>
#include <machine/Controller.h>
#include <processor/IoPort.h>
#include "AtaDisk.h"

/** The controller for up to two AtaDisks. This uses a background thread
 * and a request queue. */
class AtaController : public Controller
{
public:
  AtaController(Controller *pDev);
  ~AtaController();

  virtual void getName(String &str)
  {
    str = "ata";
  }

#ifndef X86_COMMON
#error No port IO. Must use mmapped IO.
#endif
  IoPort m_CommandRegs;
  IoPort m_ControlRegs;
};

#endif