#include "hd44780.h"

#include "../gpio.h"

#include <util/delay.h>

// DB7 high and DB0..DB6 low, represents busy flag.
const uint8_t BUSY_FLAG = 0x80;

// Tested with 2x16 and 4x20 displays.
const uint8_t LINE_1_ADDRESS = 0x00;
const uint8_t LINE_2_ADDRESS = 0x40;
const uint8_t LINE_3_ADDRESS = 0x14;
const uint8_t LINE_4_ADDRESS = 0x54;

const uint8_t SET_CGRAM_ADDRESS  = 0x40;
const uint8_t SET_DDRAM_ADDRESS  = 0x80;
const uint8_t ENTRY_MODE         = 0x04;
const uint8_t DISPLAY_CONTROLL   = 0x08;
const uint8_t FUNCTION_SET       = 0x20;
const uint8_t ENTRY_CURSOR_RIGHT = ENTRY_MODE | 0x02;
const uint8_t ENTRY_CURSOR_LEFT  = ENTRY_MODE | 0x00;
const uint8_t DisplayOn          = DISPLAY_CONTROLL | 0x04;
const uint8_t DisplayOff         = DISPLAY_CONTROLL | 0x00;
const uint8_t DisplayCursor      = DISPLAY_CONTROLL | 0x02;
const uint8_t CursorBlink        = DISPLAY_CONTROLL | 0x01;
const uint8_t Mode_8Bit          = FUNCTION_SET | 0x10;
const uint8_t Mode_4Bit          = FUNCTION_SET | 0x00;
const uint8_t Lines_2            = FUNCTION_SET | 0x08;
const uint8_t Lines_1            = FUNCTION_SET | 0x00;
const uint8_t Dots_5x10          = FUNCTION_SET | 0x04;
const uint8_t Dots_5x8           = FUNCTION_SET | 0x00;

auto const High = GPIO::PinState::High;
auto const Low  = GPIO::PinState::Low;
/*
RS is a Register select pin.
Low for command,
High for data,
*/
auto const COMMAND = Low;
auto const DATA    = High;

void
HD44780::LCD::enable_high()
{
    bus.e = High;
    _delay_us(1);
}

void
HD44780::LCD::enable_low()
{
    bus.e = Low;
    _delay_us(1);
}

uint8_t
HD44780::LCD::read()
{
    bus.rw = High;
    enable_high();
    uint8_t result = bus.line.input().read();
    enable_low();
    return result;
}

void
HD44780::LCD::waitUntillReady()
{
    bus.rs = COMMAND;
    while ((read() & BUSY_FLAG)) {
    };
}

void
HD44780::LCD::sendByte(uint8_t data, const GPIO::PinState reg)
{
    bus.rs = reg;
    bus.rw = GPIO::PinState::Low;
    enable_high();
    bus.line.output() = data;
    enable_low();
    waitUntillReady();
}

void
HD44780::LCD::write(const char * str)
{
    char character;
    while ((character = *(str++))) {
        sendByte(character, DATA);
    };
}

void
HD44780::LCD::set(HD44780::Cmd c)
{
    sendByte(c, COMMAND);
}

void
HD44780::LCD::set(const Position & position)
{
    uint8_t address;
    switch (position.line) {
        case 0:
            address = LINE_1_ADDRESS;
            break;
        case 1:
            address = LINE_2_ADDRESS;
            break;
        case 2:
            address = LINE_3_ADDRESS;
            break;
        case 3:
            address = LINE_4_ADDRESS;
            break;
    }
    sendByte(static_cast<uint8_t>(SET_DDRAM_ADDRESS + address + position.row), COMMAND);
}

/*
Refer to page 45 for initializaton details in datasheet.

For some unknown reason, all stages are not required.
With winstar WEH oled displays, third stage caused weird characters
to be displayed, when initialized more than once without power cycle.

Regular stages found in others code.
const uint8_t INIT_8_BIT = 0x30;
enable_high();
PORTC = INIT_8_BIT;
enable_low();
_delay_ms(5);

enable_high();
PORTC = INIT_8_BIT;
enable_low();
_delay_us(100);
*/
HD44780::LCD::LCD(Bus8bit bus) :
    bus(bus)
{
    bus.line.output();
    _delay_ms(15);
    sendByte(Mode_8Bit | Lines_2 | Dots_5x8, COMMAND);
    sendByte(DisplayOn, COMMAND);
    sendByte(ClearScreen, COMMAND);
    sendByte(ENTRY_CURSOR_RIGHT, COMMAND);
}