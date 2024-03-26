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


ASSERT_STRUCT_SIZE(GpioRegDef, (sizeof(RegWidth_t) * 7));

ASSERT_MEMBER_OFFSET(GpioRegDef, CRL, 0);
ASSERT_MEMBER_OFFSET(GpioRegDef, CRH, sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(GpioRegDef, IDR, sizeof(RegWidth_t) * 2);
ASSERT_MEMBER_OFFSET(GpioRegDef, ODR, sizeof(RegWidth_t) * 3);
ASSERT_MEMBER_OFFSET(GpioRegDef, BSRR, sizeof(RegWidth_t) * 4);
ASSERT_MEMBER_OFFSET(GpioRegDef, BRR, sizeof(RegWidth_t) * 5);
ASSERT_MEMBER_OFFSET(GpioRegDef, LCKR, sizeof(RegWidth_t) * 6);

volatile GpioRegDef *GPIO[3] = {GPIOA, GPIOB, GPIOC};

void Gpio::SetPinValue(Pin pin, State pinState) {
    if (pinState == kLow) {
        GPIO[pin.GetPort()]->ODR &= ~(1 << pin.GetPinNumber());
        // GPIOx -> ODR &= ~(1 << pinNum);
        GPIO[pin.GetPort()]->BRR |= (1 << pin.GetPinNumber());
        // GPIOx -> BRR |= (1 << pinNum);
    } else if (pinState == kHigh) {
        GPIO[pin.GetPort()]->ODR |= (1 << pin.GetPinNumber());
       // GPIOx -> ODR |= (1 << pinNum);
       GPIO[pin.GetPort()]->BSRR |= (1 << pin.GetPinNumber());
        //  GPIOx -> BSRR |= (1 << pinNum);
    }
}
/*void Gpio::GetPinValue(volatile GpioRegDef* GPIOx, Pin pinNum, uint32_t * pPinValue) {    // NOLINT
    STM32_ASSERT((pinNum >= 0 && pinNum <= 7) || (pinNum >= 8 && pinNum <= 15));    // NOLINT
    *pPinValue = GPIOx ->IDR &(1 << pinNum) >> pinNum;
}*/
