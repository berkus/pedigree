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
#ifndef KERNEL_MACHINE_X86_COMMON_PIC_H
#define KERNEL_MACHINE_X86_COMMON_PIC_H

#include <machine/irq.h>

/** @addtogroup kernelmachinex86common x86-common
 * x86-common
 *  @ingroup kernelmachine
 * @{ */

/** The x86/x64 programmable interrupt controller as IrqManager */
class Pic : public IrqManager
{
  public:
    virtual irq_id_t registerIsaIrqHandler(uint8_t, IrqHandler *handler);
    virtual irq_id_t registerPciIrqHandler(IrqHandler *handler);
    virtual void acknoledgeIrq(irq_id_t Id);
    virtual void unregisterHandler(irq_id_t Id);

  private:
    /** The default constructor */
    inline Pic(){}
    /** The destructor */
    inline virtual ~Pic(){}
    /** The copy-constructor
     *\note NOT implemented */
    Pic(const Pic &);
    /** The assignment operator
     *\note NOT implemented */
    Pic &operator = (const Pic &);

    /** The Pic instance */
    static Pic m_Instance;
};

/** @} */

#endif
