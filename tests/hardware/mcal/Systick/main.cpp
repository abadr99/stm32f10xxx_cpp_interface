/**
 * @file main.cpp
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-07-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// commit-id: a5020f63948e1e8a5aa0cf6949409dc7bf34a49e

#include "mcal/stm32f103xx.h"
#include "utils/Types.h"
#include "utils/BitManipulation.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"
#include "mcal/Systick.h"

using namespace stm32::type;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::systick;

void STK_ISR(void);
int main() {
    Rcc::InitSysClock();
    Rcc::SetExternalClock(kHseCrystal);
    Rcc::Enable(Peripheral::kIOPC);

    Pin pc13(kPortC, kPin13, PinMode::kOutputPushPull_10MHz);
    Gpio::Set(pc13);
    
    Systick::Enable(kAHB_Div_8);
    while (1) { 
        Gpio::SetPinValue(pc13, kHigh);
        Systick::Delay_ms(10000);
        Gpio::SetPinValue(pc13, kLow);
        Systick::Delay_ms(10000);
    }
}
