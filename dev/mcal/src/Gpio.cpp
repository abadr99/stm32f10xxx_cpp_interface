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

#define ISMODE_VALID(MODE) ((MODE == kIN_analog)          || \
                            (MODE == kIN_floating)        || \
                            (MODE == kIN_pullup)          || \
                            (MODE == kIN_pulldown)        || \
                            (MODE == kOP_pushpull_10MHZ)  || \
                            (MODE == kOP_pushpull_2MHZ)   || \
                            (MODE == kOP_pushpull_50MHZ)  || \
                            (MODE == kOP_opendrain_10MHZ) || \
                            (MODE == kOP_opendrain_2MHZ)  || \
                            (MODE == kOP_opendrain_50MHZ) || \
                            (MODE == kaf_pushpull_10MHZ)  || \
                            (MODE == kaf_pushpull_2MHZ)   || \
                            (MODE == kaf_pushpull_50MHZ)  || \
                            (MODE == kaf_opendrain_10MHZ) || \
                            (MODE == kaf_opendrain_2MHZ)  || \
                            (MODE == kaf_opendrain_50MHZ))

ASSERT_STRUCT_SIZE(GpioRegDef, (sizeof(RegWidth_t) * 7));

ASSERT_MEMBER_OFFSET(GpioRegDef, CRL, 0);
ASSERT_MEMBER_OFFSET(GpioRegDef, CRH, sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(GpioRegDef, IDR, sizeof(RegWidth_t) * 2);
ASSERT_MEMBER_OFFSET(GpioRegDef, ODR, sizeof(RegWidth_t) * 3);
ASSERT_MEMBER_OFFSET(GpioRegDef, BSRR, sizeof(RegWidth_t) * 4);
ASSERT_MEMBER_OFFSET(GpioRegDef, BRR, sizeof(RegWidth_t) * 5);
ASSERT_MEMBER_OFFSET(GpioRegDef, LCKR, sizeof(RegWidth_t) * 6);

void Gpio::SetPinMode(volatile GpioRegDef* GPIOx, Pin pinNum, Mode mode) {
    STM32_ASSERT(ISMODE_VALID(mode));
    STM32_ASSERT((pinNum >= 0 && pinNum <= 7) || (pinNum >= 8 && pinNum <= 15));    // NOLINT

    if ((pinNum >= 0 && pinNum <= 7)) {
        GPIOx->CRL &= (~(0b1111 << (pinNum*4)));
        GPIOx->CRL |= (mode << (pinNum*4));
    } else {
        GPIOx->CRH &= (~(0b1111 << (pinNum*4)));
        GPIOx->CRH |= (mode << (pinNum*4));
    }
}
void Gpio::SetPinValue(volatile GpioRegDef* GPIOx, Pin pinNum, State pinState) {
    STM32_ASSERT((pinNum >= 0 && pinNum <= 7) || (pinNum >= 8 && pinNum <= 15));    // NOLINT
    if (pinState == kLow) {
        GPIOx -> ODR &= ~(1 << pinNum);
        //  GPIOx -> BRR |= (1 << pinNum);
    } else if (pinState == kHigh) {
        GPIOx -> ODR |= (1 << pinNum);
        //  GPIOx -> BSRR |= (1 << pinNum);
    }
}
void Gpio::GetPinValue(volatile GpioRegDef* GPIOx, Pin pinNum, uint32_t * pPinValue) {    // NOLINT
    STM32_ASSERT((pinNum >= 0 && pinNum <= 7) || (pinNum >= 8 && pinNum <= 15));    // NOLINT
    *pPinValue = GPIOx ->IDR &(1 << pinNum) >> pinNum;
}
