#include <datetime.h>
#include <ds1337.h>
#include <i2c.h>
#include <irq.h>
#include <printer.h>
#include <sfr.h>
#include <stdio.h>
#include <units.h>
#include <usart.h>
#include <util/delay.h>

auto constexpr fcpu = 11059200_Hz;
auto constexpr baud = USART::get_baud(fcpu, 115200, 2);
static_assert(baud.is_ok, "Calculated error rate too high");
auto usart  = USART::Async<USART::USART0>();
auto serial = Printer(usart, LineEnd::CRLF);

int
main(void)
{
    Irq::enable();
    usart.set(baud);
    usart.enable(USART::Channel::TX);
    auto bus     = I2C::Master(fcpu);
    auto rtc     = DS1337(bus);
    auto dt      = DateTime {};
    dt.year      = 2019;
    dt.month     = 11;
    dt.month_day = 30;
    dt.hour      = 23;
    dt.minute    = 59;
    dt.second    = 50;
    serial.printLn("Setting date and time.");
    rtc.setDateTime(dt);
    char buf[30];
    while (true) {
        rtc.getDateTime(dt);
        sprintf(buf, "%d.%d.%d %d:%d:%d", dt.year, dt.month, dt.month_day, dt.hour, dt.minute, dt.second);
        serial.printLn(buf);
        _delay_ms(1000);
    }
}
