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
#include "mcal/inc/Pin.h"
#include "mcal/inc/Gpio.h"
#include "hal/inc/Buzzer.h"

using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::buzzer;

Buzzer::Buzzer(const Pin buzzerPin, const ConnectionType connectionType)
    : buzzerPin_(buzzerPin), connectionType_(connectionType) {
        Gpio::SetOutputMode(buzzerPin_, OutputMode::kPushPull_2MHZ);
}

void Buzzer::TurnOn() {
    Gpio::SetPinValue(buzzerPin_, static_cast<State>(!connectionType_));
    buzzerState_ = kOn;
}

void Buzzer::TurnOff() {
    Gpio::SetPinValue(buzzerPin_, static_cast<State>(connectionType_));
    buzzerState_ = kOff;
}

void Buzzer::Toggle() {
    if(buzzerState_ == kOn) {
        TurnOff();
    } else if (buzzerState_ == kOff) {
        TurnOn();
    }
}

BuzzerState Buzzer::GetBuzzerState() {
    return buzzerState_;
}