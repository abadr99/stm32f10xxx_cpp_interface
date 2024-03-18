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

#define ISMODE_VALID(MODE) ((MODE == kIN_analog)  || \
                       (MODE == kIN_floating) || \
                       (MODE == kIN_pullup) || \
                       (MODE == kIN_pulldown)  || \
                       (MODE == kOP_pushpull_10MHZ) || \
                       (MODE == kOP_pushpull_2MHZ) || \
                       (MODE == kOP_pushpull_50MHZ) || \
                       (MODE == kOP_opendrain_10MHZ) || \
                       (MODE == kOP_opendrain_2MHZ) || \
                       (MODE == kOP_opendrain_50MHZ) || \
                       (MODE == kaf_pushpull_10MHZ) || \
                       (MODE == kaf_pushpull_2MHZ) || \
                       (MODE == kaf_pushpull_50MHZ) || \
                       (MODE == kaf_opendrain_10MHZ) || \
                       (MODE == kaf_opendrain_2MHZ) || \
                       (MODE == kaf_opendrain_50MHZ))

void Gpio::SetPinDirection(volatile GpioRegDef* GPIOX, Pin pinNum, Mode mode) {
    STM32_ASSERT(ISMODE_VALID(mode));
    STM32_ASSERT((pinNum >= 0 && pinNum <= 7) || (pinNum >= 8 && pinNum <= 15));    // NOLINT

    if ((pinNum >= 0 && pinNum <= 7)) {
        GPIOX->CRL &= (~(0b1111 << (pinNum*4)));
        GPIOX->CRL |= (mode << (pinNum*4));
    } else {
        GPIOX->CRH &= (~(0b1111 << (pinNum*4)));
        GPIOX->CRH |= (mode << (pinNum*4));
    }
}
/*void Gpio::SetPortDirection(volatile GpioRegDef* GPIOX, Mode mode, Pin start , Pin end ) { //NOLINT
    uint32_t configReg;
    for (uint32_t pin = start; pin <= end; pin++) {
      if ((pinNum >= 0 && pinNum <= 7)) {
         configReg = GPIOX->CRL;
    } else {
         configReg = GPIOX->CRH;
    }
    configReg &= (~(0b1111 << (pin*4)));
    configReg |= (mode << (pin*4));
    }
}*/
void Gpio::SetPinVal(volatile GpioRegDef* GPIOX, Pin pinNum, State pinState) {
    STM32_ASSERT((pinNum >= 0 && pinNum <= 7) || (pinNum >= 8 && pinNum <= 15));    // NOLINT
    if (pinState == kLow) {
        GPIOX -> ODR &= ~(1 << pinNum);
        //  GPIOX -> BRR |= (1 << pinNum);
    } else if (pinState == kHigh) {
        GPIOX -> ODR |= (1 << pinNum);
        //  GPIOX -> BSRR |= (1 << pinNum);
    }
}
void Gpio::GetPinVal(volatile GpioRegDef* GPIOX, Pin pinNum, uint32_t * ReturnVal) {    // NOLINT
    STM32_ASSERT((pinNum >= 0 && pinNum <= 7) || (pinNum >= 8 && pinNum <= 15));    // NOLINT
    *ReturnVal = GPIOX ->IDR &(1 << pinNum) >> pinNum;
}
