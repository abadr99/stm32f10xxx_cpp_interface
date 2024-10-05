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
#include "mcal/stm32f103xx.h"
#include "utils/Constant.h"
#include "utils/Define.h"
#include "utils/Assert.h"
#include "utils/Util.h"
#include "mcal/Pin.h"
#include "mcal/Rcc.h"
#include "mcal/Gpio.h"
#include "hal/Led.h"

using namespace stm32;
using namespace stm32::type;
using namespace stm32::util;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::hal::led;

template<ConnectionType CT>
Led<CT>::Led(const Pin& LedPin) : LedPin(LedPin) {
    STM32_ASSERT(LedPin.IsOutput(), CONFIG_ERROR(_LED, _CONFIG));
    Rcc::Enable(MapPortToPeripheral(LedPin.GetPort()));
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
