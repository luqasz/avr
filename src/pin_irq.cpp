#include "pin_irq.h"

#include "irq.h"
#include "sfr.h"
#include "utils.h"

#include <stdint.h>

auto INT_EDGE_REG       = Register<SFR::MCUCR>();
auto INT_IRQ_ENABLE_REG = Register<SFR::GICR>();

constexpr uint8_t INT1_TRIGGER_MASK = inverted<uint8_t>(INT_EDGE_REG.ISC11 | INT_EDGE_REG.ISC10);
constexpr uint8_t INT0_TRIGGER_MASK = inverted<uint8_t>(INT_EDGE_REG.ISC01 | INT_EDGE_REG.ISC00);

void
set_int_edge(const uint8_t value, const uint8_t mask)
{
    uint8_t reg_value = INT_EDGE_REG;
    reg_value &= mask;
    reg_value |= value;
    INT_EDGE_REG = reg_value;
}

void
PinInterrupts::set(Pin pin, Trigger trigger)
{
    uint8_t reg_value;
    uint8_t bit_position;
    switch (pin) {
        case Pin::INT0:
            bit_position = firstLSBBitPos(static_cast<uint8_t>(INT_EDGE_REG.ISC00)) - 1;
            reg_value    = static_cast<uint8_t>(trigger << bit_position);
            set_int_edge(reg_value, INT0_TRIGGER_MASK);
            break;
        case Pin::INT1:
            bit_position = firstLSBBitPos(static_cast<uint8_t>(INT_EDGE_REG.ISC01)) - 1;
            reg_value    = static_cast<uint8_t>(trigger << bit_position);
            set_int_edge(reg_value, INT1_TRIGGER_MASK);
            break;
    }
}

void
PinInterrupts::enable(Pin pin)
{
    switch (pin) {
        case Pin::INT0:
            INT_IRQ_ENABLE_REG.setBit(INT_IRQ_ENABLE_REG.INT0);
            break;
        case Pin::INT1:
            INT_IRQ_ENABLE_REG.setBit(INT_IRQ_ENABLE_REG.INT1);
            break;
    }
}

void
PinInterrupts::disable(Pin pin)
{
    switch (pin) {
        case Pin::INT0:
            INT_IRQ_ENABLE_REG.clearBit(INT_IRQ_ENABLE_REG.INT0);
            break;
        case Pin::INT1:
            INT_IRQ_ENABLE_REG.clearBit(INT_IRQ_ENABLE_REG.INT1);
            break;
    }
}