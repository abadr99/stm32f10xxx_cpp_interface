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
#include "Assert.h"
#include "Pin.h"
#include "Gpio.h"
#include "Led.h"

using namespace stm32::utils::types;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::led;

template<ConnectionType CT>
Led<CT>::Led(Pin LedPin) : LedPin(LedPin) {
    STM32_ASSERT(LedPin.IsOutput());
    Gpio::Set(LedPin);
}

template<ConnectionType CT>
void Led<CT>::TurnOn() {
    Gpio::SetPinValue(LedPin, HANDLE_ACTIVE_VOLTAGE(CT));
    LedState = kTurnedOn;
}

template<ConnectionType CT>
void Led<CT>::TurnOff() {
    Gpio::SetPinValue(LedPin, HANDLE_ACTIVE_VOLTAGE(CT));
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
