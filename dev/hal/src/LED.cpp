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
#include "mcal/inc/Pin.h"
#include "mcal/inc/Gpio.h"
#include "hal/inc/LED.h"

using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::led;

Led::Led(Pin LedPin) : LedPin(LedPin) {
    Gpio::SetOutputMode(LedPin, OutputMode::kPushPull_2MHZ);
}
void Led::TurnOn() {
    Gpio::SetPinValue(LedPin, kHigh);
    LedState = kHigh;
}
void Led::TurnOff() {
    Gpio::SetPinValue(LedPin, kLow);
    LedState = kLow;
}
void Led::Toggle() {
    LedState == kLow?TurnOn():TurnOff();
}

