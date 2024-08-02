/**
 * @file Gpio.cpp
 * @author
 * @brief
 * @version 0.1
 * @date 2024-03-16
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/Assert.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/Pin.h"
#include "mcal/inc/Gpio.h"

using namespace stm32::dev::mcal::pin;          // NOLINT[build/namespaces]
using namespace stm32::registers::gpio;         // NOLINT[build/namespaces]
using namespace stm32::dev::mcal::gpio;         // NOLINT[build/namespaces]
using namespace stm32::registers::rcc;          // NOLINT[build/namespaces]
using namespace stm32::utils::bit_manipulation; // NOLINT[build/namespaces]

ASSERT_STRUCT_SIZE(GpioRegDef, (sizeof(RegWidth_t) * 7));

ASSERT_MEMBER_OFFSET(GpioRegDef, CRL, 0);
ASSERT_MEMBER_OFFSET(GpioRegDef, CRH,  sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(GpioRegDef, IDR,  sizeof(RegWidth_t) * 2);
ASSERT_MEMBER_OFFSET(GpioRegDef, ODR,  sizeof(RegWidth_t) * 3);
ASSERT_MEMBER_OFFSET(GpioRegDef, BSRR, sizeof(RegWidth_t) * 4);
ASSERT_MEMBER_OFFSET(GpioRegDef, BRR,  sizeof(RegWidth_t) * 5);
ASSERT_MEMBER_OFFSET(GpioRegDef, LCKR, sizeof(RegWidth_t) * 6);

volatile GpioRegDef *GPIOx[3] = {GPIOA, GPIOB, GPIOC};

void Gpio::SetPinValue(Pin pin, State pinState) {
    if (pinState == kLow) {
        GPIOx[pin.GetPort()]->ODR &= ~(1 << pin.GetPinNumber());
    } else if (pinState == kHigh) {
       GPIOx[pin.GetPort()]->ODR |= (1 << pin.GetPinNumber());
    }
}
uint32_t  Gpio::GetPinValue(Pin pin) {
  return GPIOx[pin.GetPort()]->IDR & (1 << pin.GetPinNumber()) >> pin.GetPinNumber(); //NOLINT
}

void Gpio::SetInputMode(Pin pin, InputMode inputMode) {
    STM32_ASSERT(pin.GetPinMode() == PinMode::kInput);
    Helper_SetInputMode(pin, inputMode);
    /* check  whether the pin mode is set as pull-up or pull-down */
    if (inputMode == InputMode::kPullup) {
        GPIOx[pin.GetPort()]->ODR = (1 << pin.GetPinNumber());
    } else if (inputMode == InputMode::kPulldown) {
        GPIOx[pin.GetPort()]->ODR &= ~(1<< pin.GetPinNumber());
    }
}

void Gpio::SetOutputMode(Pin pin, OutputMode outputMode) {
    STM32_ASSERT(pin.GetPinMode() == PinMode::kOutput);
    Helper_SetOutputMode(pin, outputMode);
}

void Gpio::SetAlternativeMode(Pin pin, AlternativeMode alternativeMode) {
    STM32_ASSERT(pin.GetPinMode() == PinMode::kAlternative);
    Helper_AlternateMode(pin, alternativeMode);
}
void Gpio::Helper_SetInputMode(Pin pin, InputMode inputMode) {
    uint32_t lcoInputMode = static_cast<uint8_t>(inputMode) & 0x0F;
    uint8_t startBit = 0;
    if (pin.GetPinNumber() <= static_cast<uint8_t>(PinNumber::kPin7)) {
        startBit = (pin.GetPinNumber()*4);
        GPIOx[pin.GetPort()]->CRL = WriteBits<uint32_t>(startBit, startBit + 3, GPIOx[pin.GetPort()]->CRL, lcoInputMode);  // NOLINT [whitespace/line_length]
    } else if (pin.GetPinNumber() <= static_cast<uint8_t>(PinNumber::kPin15)) {
        startBit = ((pin.GetPinNumber()-8) * 4);
        GPIOx[pin.GetPort()]->CRH = WriteBits<uint32_t>(startBit, startBit + 3, GPIOx[pin.GetPort()]->CRH, lcoInputMode);  // NOLINT [whitespace/line_length]
    }
}

void Gpio::Helper_SetOutputMode(Pin pin, OutputMode outputMode) {
    uint8_t lcoOutputMode = static_cast<uint8_t>(outputMode) & 0x0F;
    uint8_t startBit = 0;
    if (pin.GetPinNumber() <= static_cast<uint8_t>(PinNumber::kPin7)) {
        startBit = (pin.GetPinNumber()*4);
        GPIOx[pin.GetPort()]->CRL = WriteBits<uint32_t>(startBit, startBit + 3, GPIOx[pin.GetPort()]->CRL, lcoOutputMode);  // NOLINT [whitespace/line_length]
    } else if (pin.GetPinNumber() <= static_cast<uint8_t>(PinNumber::kPin15)) {
        startBit = ((pin.GetPinNumber()-8) * 4);
        GPIOx[pin.GetPort()]->CRH = WriteBits<uint32_t>(startBit, startBit + 3, GPIOx[pin.GetPort()]->CRH, lcoOutputMode);  // NOLINT [whitespace/line_length]
    }
}
void Gpio::Helper_AlternateMode(Pin pin, AlternativeMode alternateMode) {
    uint8_t lcoAlternateMode = static_cast<uint8_t>(alternateMode) & 0x0F;
    uint8_t startBit = 0;
    if (pin.GetPinNumber() <= static_cast<uint8_t>(PinNumber::kPin7)) {
        startBit = (pin.GetPinNumber()*4);
        GPIOx[pin.GetPort()]->CRL = WriteBits<uint32_t>(startBit, startBit + 3, GPIOx[pin.GetPort()]->CRL, lcoAlternateMode);  // NOLINT [whitespace/line_length]
    } else if (pin.GetPinNumber() <= static_cast<uint8_t>(PinNumber::kPin15)) {
        startBit = ((pin.GetPinNumber()-8) * 4);
        GPIOx[pin.GetPort()]->CRH = WriteBits<uint32_t>(startBit, startBit + 3, GPIOx[pin.GetPort()]->CRH, lcoAlternateMode);  // NOLINT [whitespace/line_length]
    }
}
