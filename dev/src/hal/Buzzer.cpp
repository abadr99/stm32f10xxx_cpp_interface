/**
 * @file Buzzer.cpp
 * @author
 * @brief
 * @version 0.1
 * @date 2024-07-7
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "mcal/stm32f103xx.h"
#include "utils/Types.h"
#include "utils/Define.h"
#include "utils/Constant.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "hal/Buzzer.h"
#include "utils/Assert.h"
#include "utils/Util.h"
#include "mcal/Rcc.h"

using namespace stm32;
using namespace stm32::util;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::buzzer;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::type;

template<ConnectionType CT>
Buzzer<CT>::Buzzer(const Pin& buzzerPin)
: buzzerState_(kOff), buzzerPin_(buzzerPin) {
    STM32_ASSERT(buzzerPin.IsOutput(), CONFIG_ERROR(_BUZZER, _CONFIG));
    Rcc::Enable(MapPortToPeripheral(buzzerPin_.GetPort()));
    Gpio::Set(buzzerPin_);
}

template<ConnectionType CT>
void Buzzer<CT>::TurnOn() {
    Gpio::SetPinValue(buzzerPin_, constant::DigitalState<CT>::kActiveVoltage);
    buzzerState_ = kOn;
}

template<ConnectionType CT>
void Buzzer<CT>::TurnOff() {
    Gpio::SetPinValue(buzzerPin_, constant::DigitalState<CT>::kInActiveVoltage);
    buzzerState_ = kOff;
}

template<ConnectionType CT>
void Buzzer<CT>::Toggle() {
    if (buzzerState_ == kOn) {
        TurnOff();
        return;
    }
    TurnOn();
}

template<ConnectionType CT>
BuzzerState Buzzer<CT>::GetBuzzerState() {
    return buzzerState_;
}

INSTANTIATE_CONNECTION_CLASS(Buzzer)
