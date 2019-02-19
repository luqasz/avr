#ifndef irq_h
#define irq_h

#include "sfr.h"

#define VECTOR(vector) __asm__(vector) __attribute__((signal, used, externally_visible))

class RestoreIrq {
private:
    uint8_t               sreg_value;
    constexpr static auto reg = Register<SFR::SREG>();

public:
    RestoreIrq()
    {
        sreg_value = reg;
        // clang-format off
        __asm__ __volatile__ ("cli" ::: "memory");
        // clang-format on
    }
    ~RestoreIrq()
    {
        reg = sreg_value;
        // clang-format off
        __asm__ volatile ("" ::: "memory");
        // clang-format on
    }
};

class Irq_Base {
public:
    static void
    enable(void)
    {
        // clang-format off
        __asm__ __volatile__("sei" ::: "memory");
        // clang-format on
    }

    static void
    disable(void)
    {
        // clang-format off
        __asm__ __volatile__ ("cli" ::: "memory");
        // clang-format on
    }
    static void
    atomicRestore(void)
    {
        RestoreIrq();
    }

    /* Vector executed when an IRQ fires with no accompanying handler. This
    may be used to create a catch-all for undefined but used IRQs for debugging purposes.
    */
    static void
    CatchAll() VECTOR("__vector_default");
};

#if defined(__AVR_ATmega328P__)
#    include "irq/atmega328_irq.h"
#elif defined(__AVR_ATmega328__)
#    include "irq/atmega328_irq.h"
#elif defined(__AVR_ATmega32__)
#    include "irq/atmega32_irq.h"
#elif defined(__AVR_ATmega32A__)
#    include "irq/atmega32_irq.h"
#else
#    error "Unsupported MCU."
#endif

#endif