#pragma once

#include "../gpio.h"
#include "mcu_sfr.h"

#include <stdint.h>

namespace GPIO {

    auto const PortC = GPIO::Port {
        SFR::PORTC::address,
        SFR::PINC::address,
        SFR::DDRC::address,
    };

    auto const PC0 = GPIO::Pin {
        PortC,
        GPIO::Pin0,
    };
    auto const PC1 = GPIO::Pin {
        PortC,
        GPIO::Pin1,
    };
    auto const PC2 = GPIO::Pin {
        PortC,
        GPIO::Pin2,
    };
    auto const PC3 = GPIO::Pin {
        PortC,
        GPIO::Pin3,
    };
    auto const PC4 = GPIO::Pin {
        PortC,
        GPIO::Pin4,
    };
    auto const PC5 = GPIO::Pin {
        PortC,
        GPIO::Pin5,
    };
    auto const PC6 = GPIO::Pin {
        PortC,
        GPIO::Pin6,
    };
    auto const PC7 = GPIO::Pin {
        PortC,
        GPIO::Pin7,
    };

    auto const PortB = GPIO::Port {
        SFR::PORTB::address,
        SFR::PINB::address,
        SFR::DDRB::address,
    };

    auto const PB0 = GPIO::Pin {
        PortB,
        GPIO::Pin0,
    };
    auto const PB1 = GPIO::Pin {
        PortB,
        GPIO::Pin1,
    };
    auto const PB2 = GPIO::Pin {
        PortB,
        GPIO::Pin2,
    };
    auto const PB3 = GPIO::Pin {
        PortB,
        GPIO::Pin3,
    };
    auto const PB4 = GPIO::Pin {
        PortB,
        GPIO::Pin4,
    };
    auto const PB5 = GPIO::Pin {
        PortB,
        GPIO::Pin5,
    };
    auto const PB6 = GPIO::Pin {
        PortB,
        GPIO::Pin6,
    };
    auto const PB7 = GPIO::Pin {
        PortB,
        GPIO::Pin7,
    };

    auto const PortD = GPIO::Port {
        SFR::PORTD::address,
        SFR::PIND::address,
        SFR::DDRD::address,
    };

    auto const PD0 = GPIO::Pin {
        PortD,
        GPIO::Pin0,
    };
    auto const PD1 = GPIO::Pin {
        PortD,
        GPIO::Pin1,
    };
    auto const PD2 = GPIO::Pin {
        PortD,
        GPIO::Pin2,
    };
    auto const PD3 = GPIO::Pin {
        PortD,
        GPIO::Pin3,
    };
    auto const PD4 = GPIO::Pin {
        PortD,
        GPIO::Pin4,
    };
    auto const PD5 = GPIO::Pin {
        PortD,
        GPIO::Pin5,
    };
    auto const PD6 = GPIO::Pin {
        PortD,
        GPIO::Pin6,
    };
    auto const PD7 = GPIO::Pin {
        PortD,
        GPIO::Pin7,
    };

}