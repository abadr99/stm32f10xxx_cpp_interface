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
#include "mcal/inc/Pin.h"
#include "mcal/inc/Gpio.h"

using namespace stm32::dev::mcal::pin; // NOLINT[build/namespaces]
using namespace stm32::registers::gpio; // NOLINT[build/namespaces]
using namespace stm32::dev::mcal::gpio; // NOLINT[build/namespaces]
using namespace stm32::registers::rcc; // NOLINT[build/namespaces]

ASSERT_STRUCT_SIZE(GpioRegDef, (sizeof(RegWidth_t) * 7));

ASSERT_MEMBER_OFFSET(GpioRegDef, CRL, 0);
ASSERT_MEMBER_OFFSET(GpioRegDef, CRH, sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(GpioRegDef, IDR, sizeof(RegWidth_t) * 2);
ASSERT_MEMBER_OFFSET(GpioRegDef, ODR, sizeof(RegWidth_t) * 3);
ASSERT_MEMBER_OFFSET(GpioRegDef, BSRR, sizeof(RegWidth_t) * 4);
ASSERT_MEMBER_OFFSET(GpioRegDef, BRR, sizeof(RegWidth_t) * 5);
ASSERT_MEMBER_OFFSET(GpioRegDef, LCKR, sizeof(RegWidth_t) * 6);

extern volatile GpioRegDef *GPIOx[3];

void Gpio::SetPinValue(Pin pin, State pinState) {
    if (pinState == kLow) {
        GPIOx[pin.GetPort()]->ODR &= ~(1 << pin.GetPinNumber());
        GPIOx[pin.GetPort()]->BRR |= (1 << pin.GetPinNumber());
    } else if (pinState == kHigh) {
       GPIOx[pin.GetPort()]->ODR |= (1 << pin.GetPinNumber());
       GPIOx[pin.GetPort()]->BSRR |= (1 << pin.GetPinNumber());
    }
}
uint32_t  Gpio::GetPinValue(Pin pin) {
  return GPIOx[pin.GetPort()]->IDR & (1 << pin.GetPinNumber()) >> pin.GetPinNumber(); //NOLINT
}
void Gpio::EnablePort(Port port) {
        switch (port) {
            case kPortA:       RCC->APB2ENR.IOPAEN = 1; break;
            case kPortB:       RCC->APB2ENR.IOPBEN = 1; break;
            case kPortC:       RCC->APB2ENR.IOPCEN = 1; break;
        }
}
