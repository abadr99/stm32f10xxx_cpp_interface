/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// commit-id: a5020f63948e1e8a5aa0cf6949409dc7bf34a49e

#include "utils/inc/Types.h"
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/Pin.h"
#include "mcal/inc/Gpio.h"
#include "mcal/inc/Rcc.h"
#include "mcal/inc/Systick.h"

using namespace stm32::type;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::systick;
int main() {
    Rcc::InitSysClock();
    Rcc::SetExternalClock(kHseCrystal);
    Rcc::Enable(Peripheral::kIOPC);

    Pin pc13(kPortC, kPin13, PinMode::kOutputPushPull_10MHz);
    Gpio::Set(pc13);
    uint32_t Local_u16Counter = 0;
    while (1) {
        Gpio::SetPinValue(pc13, kLow);
        for (Local_u16Counter = 0; Local_u16Counter < 50000; Local_u16Counter++) {
            __asm("NOP");
        }
        Gpio::SetPinValue(pc13, kLow);
        for (Local_u16Counter = 0; Local_u16Counter < 50000; Local_u16Counter++) {
             __asm("NOP");
        }
    }
}
