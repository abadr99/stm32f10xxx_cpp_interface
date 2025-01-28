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

// commit-id: 2d5c61a00cf50cc54d36aac6a3458e62b3ef57e1

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

int main() {
    Rcc::Init();
    Gpio::Init();
    Systick::Init();

    Rcc::InitSysClock();
    Rcc::SetExternalClock(kHseCrystal);
    Rcc::Enable(Peripheral::kIOPC);

    Pin pc13(kPortC, kPin13, PinMode::kOutputPushPull_10MHz);
    Gpio::Set(pc13);
    
    Systick::Enable(kAHB_Div_8);
    while (1) { 
        Gpio::SetPinValue(pc13, kHigh);
        Systick::Delay_ms(1000);
        Gpio::SetPinValue(pc13, kLow);
        Systick::Delay_ms(1000);
    }
}
