/**
 * @file main.cpp
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-07-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/Types.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/Pin.h"
#include "mcal/inc/Gpio.h"
#include "mcal/inc/Rcc.h"
#include "mcal/inc/Usart.h"
#include "hal/inc/Esp.h"

using namespace stm32::type;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::usart;
using namespace stm32::dev::hal::esp;
int main() {
    Rcc::InitSysClock();
    Rcc::SetExternalClock(kHseCrystal);
    Rcc::Enable(Peripheral::kIOPA);
    Rcc::Enable(Peripheral::kIOPC);
    Rcc::Enable(Peripheral::kUSART1);

    Pin pc13(kPortC, kPin13, PinMode::kOutputPushPull_10MHz);
    Pin rx1(kPortA,  kPin10, PinMode::kInputFloat);
    Pin tx1(kPortA,  kPin9,  PinMode::kAlternativePushPull_10MHz);

    Gpio::Set(pc13);
    Gpio::Set(rx1);
    Gpio::Set(tx1);

    Esp esp(kUsart1);

    Gpio::SetPinValue(pc13, kHigh);
    esp.SetMode(EspMode::kAP);
    esp.SetEchoState(EchoState::kOn);
    esp.WiFiConnect("\"userName\"", "\"Password\"");
    esp.ServerConnect("UDP", "192.169.1.1", 8080);
    while (1) {
    }
}
