#pragma once

#include "sfr.h"

#ifdef __AVR__
#    include "gpio/avr.h"
#else
#    error "GPIO MCU not supported"
#endif

#include <stdint.h>

namespace GPIO {

    enum State {
        Low,
        High,
    };

    enum Logic {
        Off = State::Low,
        On  = State::High,
    };

    struct Output {
        const State on_state;
        const Pin   pin;

        constexpr Output(const Pin p, const State s = High) :
            on_state(s),
            pin(p)
        {
            SFR::setBit(pin.port.ddr_address, pin.number);
        }

        void
        operator=(const State state) const
        {
            set_state(state);
        }

        void
        operator=(const Logic logic) const
        {
            switch (logic) {
                case Logic::On:
                    set_state(on_state);
                    break;
                case Logic::Off:
                    set_state(static_cast<State>(!on_state));
                    break;
            }
        }

        void
        toggle() const
        {
            SFR::iomem<uint8_t>(pin.port.port_address) ^= pin.number;
        }

    private:
        void
        set_state(const State state) const
        {
            switch (state) {
                case State::High:
                    SFR::setBit(pin.port.port_address, pin.number);
                    break;
                case State::Low:
                    SFR::clearBit(pin.port.port_address, pin.number);
                    break;
            }
        }
    };

    struct Input {
        const State on_state;
        const Pin   pin;

        constexpr Input(const Pin p, const State s = High) :
            on_state(s),
            pin(p)
        {
            SFR::clearBit(pin.port.ddr_address, pin.number);
        }

        void
        set(const PullMode mode) const
        {
            switch (mode) {
                case PullMode::PullUp:
                    SFR::setBit(pin.port.ddr_address, pin.number);
                    break;
                case PullMode::HiZ:
                    SFR::clearBit(pin.port.ddr_address, pin.number);
                    break;
            }
        }

        bool
        operator==(const Logic logic) const
        {
            const auto state = read_state();
            switch (logic) {
                case Logic::On:
                    return state == on_state;
                    break;
                case Logic::Off:
                    return state != on_state;
                    break;
            }
        }

        bool
        operator==(const State state) const
        {
            return read_state() == state;
        }

    private:
        bool
        read_state() const
        {
            return SFR::iomem<uint8_t>(pin.port.pin_address) & pin.number;
        };
    };

}
#include <mcu_gpio.h>
