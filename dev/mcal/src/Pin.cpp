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
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/BitSet.h"
#include "utils/inc/Assert.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/Pin.h"

using  namespace stm32::dev::mcal::pin;
using  namespace stm32::registers::gpio;
using  namespace stm32::utils::bitset;
using  namespace stm32::utils::bit_manipulation;

Pin::Pin(Port port, PinNumber pinNumber, PinMode pinMode):data_(0) {
    data_.SetValue<0, 1>(port);
    data_.SetValue<2, 5>(pinNumber);
    data_.SetValue<6, 7>(static_cast<uint8_t>(pinMode));
}

void Pin::SetPort(Port port) {
    data_.SetValue<0, 1>(port);
}

void Pin::SetPinNumber(PinNumber pinNumber) {
    STM32_ASSERT(pinNumber >= kPin0 && pinNumber <= kPin15);
    data_.SetValue<2, 5>(pinNumber);
}

void Pin::SetPinMode(PinMode pinMode) {
    data_.SetValue<6, 7>(static_cast<uint8_t>(pinMode));
}

Port Pin::GetPort() {
    return static_cast<Port>(data_.GetValue<0, 1>());
}

PinNumber Pin::GetPinNumber() {
    return static_cast<PinNumber>(data_.GetValue<2, 5>());
}

PinMode Pin::GetPinMode() {
    return static_cast<PinMode>(data_.GetValue<6, 7>());
}


