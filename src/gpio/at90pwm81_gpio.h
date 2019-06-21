#ifndef at90pwm81_gpio_h
#define at90pwm81_gpio_h

#include "../gpio.h"

#include <stdint.h>

/*
Source            Atmel.ATmega_DFP.1.3.300.atpack
Family            megaAVR
Architecture      AVR8
Device name       AT90PWM81
*/

namespace GPIO {

    auto const PortD = GPIO::Port {
        0x2b,
        0x29,
        0x2a,
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

    auto const PortB = GPIO::Port {
        0x25,
        0x23,
        0x24,
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

    auto const PortE = GPIO::Port {
        0x2e,
        0x2c,
        0x2d,
    };

    auto const PE0 = GPIO::Pin {
        PortE,
        GPIO::Pin0,
    };

    auto const PE1 = GPIO::Pin {
        PortE,
        GPIO::Pin1,
    };

    auto const PE2 = GPIO::Pin {
        PortE,
        GPIO::Pin2,
    };

    auto const PE3 = GPIO::Pin {
        PortE,
        GPIO::Pin3,
    };

    auto const PE4 = GPIO::Pin {
        PortE,
        GPIO::Pin4,
    };

    auto const PE5 = GPIO::Pin {
        PortE,
        GPIO::Pin5,
    };

    auto const PE6 = GPIO::Pin {
        PortE,
        GPIO::Pin6,
    };

    auto const PE7 = GPIO::Pin {
        PortE,
        GPIO::Pin7,
    };

}

#endif
