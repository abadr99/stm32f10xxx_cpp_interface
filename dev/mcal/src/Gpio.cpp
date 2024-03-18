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
#include "mcal/inc/Gpio.h"

using namespace stm32::dev::mcal::gpio; // NOLINT[build/namespaces]
using namespace stm32::registers::gpio; // NOLINT[build/namespaces]

void Gpio::SetPinDirection(volatile GpioRegDef* GPIOX, Pin pinNum, Mode mode) {
    STM32_ASSERT(ISMODE_VALID(mode));
    uint32_t configReg;
    if (pinNum <= kpin7) {
        configReg = GPIOX->CRL;
    } else {
        configReg = GPIOX->CRH;
    }
    configReg &= (~(0b1111 << (pinNum*4)));
    configReg |= (mode << (pinNum*4));
}
void Gpio::SetPinVal(volatile GpioRegDef* GPIOX, Pin pinNum, State pinState) {
    if (pinState == kLow) {
        GPIOX -> ODR &= ~(1 << pinNum);
        //  GPIOX -> BRR |= (1 << pinNum);
    } else if (pinState == kHigh) {
        GPIOX -> ODR |= (1 << pinNum);
        //  GPIOX -> BSRR |= (1 << pinNum);
    }
}
void Gpio::GetPinVal(volatile GpioRegDef* GPIOX, Pin pinNum, uint32_t * ReturnVal) {    // NOLINT
    *ReturnVal = GPIOX ->IDR &(1 << pinNum) >> pinNum;
}
