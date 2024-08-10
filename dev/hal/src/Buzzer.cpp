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
#include "mcal/inc/stm32f103xx.h"
#include "Types.h"
#include "mcal/inc/Pin.h"
#include "mcal/inc/Gpio.h"
#include "hal/inc/Buzzer.h"

using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::buzzer;
using namespace stm32::utils::types;

template<ConnectionType CT>
Buzzer<CT>::Buzzer(const Pin buzzerPin)
: buzzerPin_(buzzerPin) {
    Gpio::Set(buzzerPin_);
}

template<ConnectionType CT>
void Buzzer<CT>::TurnOn() {
    Gpio::SetPinValue(buzzerPin_, HANDLE_ACTIVE_VOLTAGE(CT));
    buzzerState_ = kOn;
}

template<ConnectionType CT>
void Buzzer<CT>::TurnOff() {
    Gpio::SetPinValue(buzzerPin_, HANDLE_INACTIVE_VOLTAGE(CT));
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
