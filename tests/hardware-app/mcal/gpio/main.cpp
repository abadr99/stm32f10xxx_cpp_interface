#include "stm32f103xx.h"
#include "BitManipulation.h"
#include "Pin.h"
#include "Gpio.h"
#include "Rcc.h"
#include "Systick.h"

using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::systick;
int main() {
    Rcc::InitSysClock();
    Rcc::SetExternalClock(kHseCrystal);

    Pin pc13(kPortC, kPin13, PinMode::kOutput);
    Gpio::EnablePort(kPortC);
    Gpio::SetOutputMode(pc13, OutputMode::kPushPull_10MHZ);
    uint32_t Local_u16Counter = 0;
    while (1) {
        Gpio::SetPinValue(pc13, kLow);
        for(Local_u16Counter = 0 ; Local_u16Counter < 50000 ; Local_u16Counter++) {
            __asm("NOP");
        }
        Gpio::SetPinValue(pc13, kLow);
        for(Local_u16Counter = 0 ; Local_u16Counter < 50000 ; Local_u16Counter++) {
             __asm("NOP");
        }
    }
}
