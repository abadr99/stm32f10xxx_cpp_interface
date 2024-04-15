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


volatile GpioRegDef *GPIOx[3] = {GPIOA, GPIOB, GPIOC};

Pin::Pin(Port port, PinNumber pinNumber, PinMode pinMode):data_(0) {
    data_.SetValue<0, 1>(port);
    data_.SetValue<2, 5>(pinNumber);
    data_.SetValue<6, 7>(static_cast<uint8_t>(pinMode));
}

void Pin::SetPort(Port port) {
    data_.SetValue<0, 1>(port);
}

void Pin::SetPinNumber(PinNumber pinNumber) {
    data_.SetValue<2, 5>(pinNumber);
}

void Pin::SetPinMode(PinMode pinMode) {
    data_.SetValue<6, 7>(static_cast<uint8_t>(pinMode));
}

void Pin::SetInputMode(InputMode inputMode) {
    STM32_ASSERT(GetPinMode() == PinMode::kInput);
    Helper_SetInputMode(inputMode);
    /* check  whether the pin mode is set as pull-up or pull-down */
    if (inputMode == InputMode::kPullup) {
        GPIOx[GetPort()]->ODR = (1 << GetPinNumber());
    } else if (inputMode == InputMode::kPulldown) {
        GPIOx[GetPort()]->ODR &= ~(1<< GetPinNumber());
    }
}

void Pin::SetOutputMode(OutputMode outputMode) {
    STM32_ASSERT(GetPinMode() == PinMode::kOutput);
    Helper_SetOutputMode(outputMode);
}

void Pin::SetAlternativeMode(AlternativeMode alternativeMode) {
    STM32_ASSERT(GetPinMode() == PinMode::kAlternative);
    Helper_AlternateMode(alternativeMode);
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

void Pin::Helper_SetInputMode(InputMode inputMode) {
    uint32_t lcoInputMode = static_cast<uint8_t>(inputMode) & 0x0F;
    uint8_t startBit = (GetPinNumber()*4);
    if (GetPinNumber() <= static_cast<uint8_t>(PinNumber::kPin7)) {
        WriteBits<uint32_t>(startBit, startBit + 4, GPIOx[GetPort()]->CRL, lcoInputMode);  // NOLINT [whitespace/line_length]
    } else if (GetPinNumber() <= static_cast<uint8_t>(PinNumber::kPin15)) {
        WriteBits<uint32_t>(startBit, startBit + 4, GPIOx[GetPort()]->CRH, lcoInputMode);  // NOLINT [whitespace/line_length]
    }
}

void Pin::Helper_SetOutputMode(OutputMode outputMode) {
    uint8_t lcoOutputMode = static_cast<uint8_t>(outputMode) & 0x0F;
    uint8_t startBit = (GetPinNumber()*4);
    if (GetPinNumber() <= static_cast<uint8_t>(PinNumber::kPin7)) {
        WriteBits<uint32_t>(startBit, startBit + 4, GPIOx[GetPort()]->CRL, lcoOutputMode);  // NOLINT [whitespace/line_length]
    } else if (GetPinNumber() <= static_cast<uint8_t>(PinNumber::kPin15)) {
        WriteBits<uint32_t>(startBit, startBit + 4, GPIOx[GetPort()]->CRH, lcoOutputMode);  // NOLINT [whitespace/line_length]
    }
}
void Pin::Helper_AlternateMode(AlternativeMode alternateMode) {
    uint8_t lcoAlternateMode = static_cast<uint8_t>(alternateMode) & 0x0F;
    uint8_t startBit = (GetPinNumber()*4);
    if (GetPinNumber() <= static_cast<uint8_t>(PinNumber::kPin7)) {
        WriteBits<uint32_t>(startBit, startBit + 4, GPIOx[GetPort()]->CRL, lcoAlternateMode);  // NOLINT [whitespace/line_length]
    } else if (GetPinNumber() <= static_cast<uint8_t>(PinNumber::kPin15)) {
        WriteBits<uint32_t>(startBit, startBit + 4, GPIOx[GetPort()]->CRH, lcoAlternateMode);  // NOLINT [whitespace/line_length]
    }
}
