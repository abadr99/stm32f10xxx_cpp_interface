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

using namespace stm32::dev::mcal::pin;
using namespace stm32::registers::gpio;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::registers::rcc;
using namespace stm32::utils::bit_manipulation;

ASSERT_STRUCT_SIZE(GpioRegDef, (sizeof(RegWidth_t) * 7));

ASSERT_MEMBER_OFFSET(GpioRegDef, CRL, 0);
ASSERT_MEMBER_OFFSET(GpioRegDef, CRH,  sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(GpioRegDef, IDR,  sizeof(RegWidth_t) * 2);
ASSERT_MEMBER_OFFSET(GpioRegDef, ODR,  sizeof(RegWidth_t) * 3);
ASSERT_MEMBER_OFFSET(GpioRegDef, BSRR, sizeof(RegWidth_t) * 4);
ASSERT_MEMBER_OFFSET(GpioRegDef, BRR,  sizeof(RegWidth_t) * 5);
ASSERT_MEMBER_OFFSET(GpioRegDef, LCKR, sizeof(RegWidth_t) * 6);

static volatile GpioRegDef *GPIOx[3] = {GPIOA, GPIOB, GPIOC};

void Gpio::Set(const Pin& pin) {
    SetPinMode(pin, pin.GetPinMode());
}

void Gpio::SetPinValue(const Pin& pin, State pinState) {
    const PinNumber pin_num   = pin.GetPinNumber();
    volatile GpioRegDef* gpio = GPIOx[pin.GetPort()];

    switch (pinState) {
        case State::kLow  : gpio->ODR = ClearBit<RegWidth_t>(gpio->ODR, pin_num); break;
        case State::kHigh : gpio->ODR = SetBit<RegWidth_t>(gpio->ODR, pin_num);   break;
        default: /* TODO(@abadr99): Support Unreachable code */ break;
    }
}

typename Gpio::PinVal_t Gpio::GetPinValue(Pin pin) {
    RegWidth_t pin_num = pin.GetPinNumber();
    return ExtractBits<RegWidth_t>(GPIOx[pin.GetPort()]->IDR, pin_num);
}

void Gpio::SetPinMode(const Pin& pin, PinMode mode) {
    auto IsInput = [mode]() -> bool {
        return mode >= PinMode::kInputFloat && mode <= PinMode::kInputPullDown;
    };

    volatile GpioRegDef* gpio = GPIOx[pin.GetPort()];
    PinNumber pinNum = pin.GetPinNumber();
    uint8_t startBit = 0;
    
    if (pinNum <= PinNumber::kPin7) {
        startBit = pinNum * 4;
        gpio->CRL = WriteBits<RegWidth_t>(startBit, startBit + 3, gpio->CRL, static_cast<RegWidth_t>(mode));  // NOLINT [whitespace/line_length]
    } else {
        startBit = (pinNum - 8) * 4;
        gpio->CRH = WriteBits<uint32_t>(startBit, startBit + 3, gpio->CRH, static_cast<RegWidth_t>(mode));  // NOLINT [whitespace/line_length]
    }

    // --- SPECIAL CARE FOR INPUT-PULLUP/DOWN MODES
    if (IsInput()) {
        switch (mode) {
            case PinMode::kInputPullDown:
                gpio->ODR = ClearBit<RegWidth_t>(gpio->ODR, pinNum);
                break;
            case PinMode::kInputPullUp:
                gpio->ODR = SetBit<RegWidth_t>(gpio->ODR, pinNum);
                break;
            default: /* DO NO THING */ break;
        }
    }
}
