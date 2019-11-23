#include <irq.h>
#include <printer.h>
#include <sfr.h>
#include <stdio.h>
#include <usart.h>
#include <util/delay.h>

auto constexpr baud = USART::get_baud<115200, 2>();
auto usart          = USART::Async<USART::USART0>();
auto serial         = Printer<USART::Async<USART::USART0>, RN>(usart);

int
main(void)
{
    Irq::enable();
    usart.set(baud);
    usart.enable(USART::Channel::TX);
    while (true) {
        serial.printLn("This string will repeat every second.");
        _delay_ms(1000);
    }
}
