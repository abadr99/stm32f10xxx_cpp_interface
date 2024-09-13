/**
 * @file Led.cpp
 * @brief 
 * @version 0.1
 * @date 2024-04-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>
#include "mcal/inc/stm32f103xx.h"
#include "Constant.h"
#include "Define.h"
#include "Assert.h"
#include "Rcc.h"
#include "Pin.h"
#include "Gpio.h"
#include "Led.h"

using namespace stm32;
using namespace stm32::type;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::hal::led;

template<ConnectionType CT>
Led<CT>::Led(Pin LedPin) : LedPin(LedPin) {
    STM32_ASSERT(LedPin.IsOutput());
        switch (LedPin.GetPort()) {
        case kPortA: Rcc::Enable(Peripheral::kIOPA); break;
        case kPortB: Rcc::Enable(Peripheral::kIOPB); break;
        case kPortC: Rcc::Enable(Peripheral::kIOPC); break;
        default:STM32_ASSERT(false);                 break;
    }
    Gpio::Set(LedPin);
}

template<ConnectionType CT>
void Led<CT>::TurnOn() {
    Gpio::SetPinValue(LedPin, constant::DigitalState<CT>::kActiveVoltage);
    LedState = kTurnedOn;
}

template<ConnectionType CT>
void Led<CT>::TurnOff() {
    Gpio::SetPinValue(LedPin, constant::DigitalState<CT>::kInActiveVoltage);
    LedState = kTurnedOff;
}

template<ConnectionType CT>
void Led<CT>::Toggle() {
    if (LedState == kTurnedOn) {
        TurnOff();
        return;
    }
    TurnOn();
}

INSTANTIATE_CONNECTION_CLASS(Led)
