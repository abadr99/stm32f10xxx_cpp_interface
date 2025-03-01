/**
 * @file Pin.cpp
 * @brief 
 * @version 0.1
 * @date 2024-03-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>
#include "mcal/stm32f103xx.h"
#include "utils/BitSet.h"
#include "utils/Assert.h"
#include "utils/BitManipulation.h"
#include "mcal/Pin.h"

using  namespace stm32::dev::mcal::pin;
using  namespace stm32::registers::gpio;
using  namespace stm32::util;
using  namespace stm32::util;

#define PIN_PIN_NUMBER_ERROR  "[Pin.cpp]: Invalid Pin Number"

Pin::Pin(Port port, PinNumber pinNumber, PinMode pinMode):data_(0) {
    data_.SetValue<0, 1>(port);
    data_.SetValue<2, 5>(pinNumber);
    data_.SetValue<6, 7>(static_cast<uint8_t>(pinMode));
}

void Pin::SetPort(Port port) {
    data_.SetValue<0, 1>(port);
}

void Pin::SetPinNumber(PinNumber pinNumber) {
    STM32_ASSERT((pinNumber >= kPin0) && (pinNumber <= kPin15), PIN_PIN_NUMBER_ERROR);
    data_.SetValue<2, 5>(pinNumber);
}

void Pin::SetPinMode(PinMode pinMode) {
    data_.SetValue<6, 9>(static_cast<uint8_t>(pinMode));
}

Port Pin::GetPort() {
    return static_cast<Port>(data_.GetValue<0, 1>());
}

Port Pin::GetPort() const {
    return static_cast<Port>(data_.GetValue<0, 1>());
}

PinNumber Pin::GetPinNumber() {
    return static_cast<PinNumber>(data_.GetValue<2, 5>());
}

PinNumber Pin::GetPinNumber() const {
    return static_cast<PinNumber>(data_.GetValue<2, 5>());
}

PinMode Pin::GetPinMode() {
    return static_cast<PinMode>(data_.GetValue<6, 9>());
}

PinMode Pin::GetPinMode() const {
    return static_cast<PinMode>(data_.GetValue<6, 9>());
}

bool Pin::IsInput() {
    PinMode mode = GetPinMode();
    return mode >= PinMode::kInputFloat && mode <= PinMode::kInputPullDown;
}

bool Pin::IsInput() const {
    PinMode mode = GetPinMode();
    return mode >= PinMode::kInputFloat && mode <= PinMode::kInputPullDown;
}

bool Pin::IsOutput() {
    PinMode mode = GetPinMode();
    return (mode >= PinMode::kOutputPushPull_10MHz 
        && mode <= PinMode::kOutputPushPull_50MHz)
        ||(mode >= PinMode::kOutputOpenDrain_10MHz
        && mode <= PinMode::kOutputOpenDrain_50MHz);
}

bool Pin::IsOutput() const {
    PinMode mode = GetPinMode();
    return (mode >= PinMode::kOutputPushPull_10MHz 
        && mode <= PinMode::kOutputPushPull_50MHz)
        ||(mode >= PinMode::kOutputOpenDrain_10MHz
        && mode <= PinMode::kOutputOpenDrain_50MHz);
}

bool Pin::IsAlternative() {
    PinMode mode = GetPinMode();
    return mode >= PinMode::kAlternativeOpenDrain_2MHz 
        && mode <= PinMode::kAlternativePushPull_50MHz;
}

bool Pin::IsAlternative() const {
    PinMode mode = GetPinMode();
    return mode >= PinMode::kAlternativeOpenDrain_2MHz 
        && mode <= PinMode::kAlternativePushPull_50MHz;
}


bool Pin::IsAnalog() {
    return GetPinMode() == PinMode::kAnalog ? true : false;
}

bool Pin::IsAnalog() const {
    return GetPinMode() == PinMode::kAnalog ? true : false;
}
