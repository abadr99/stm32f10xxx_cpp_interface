/**
 * @file Keypad.cpp
 * @brief 
 * @version 0.1
 * @date 2024-04-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Pin.h"
#include "mcal/inc/Gpio.h"
#include "hal/inc/Keypad.h"
using  namespace stm32::dev::mcal::pin;
using  namespace stm32::dev::mcal::gpio;
template<uint8_t Rows, uint8_t Columns>
void Keypad<Rows, Columns>::KeypadInit() {
    for (uint8_t numRow =0 ; numRow <Rows; numRow++) {
        SetInputMode(KeypadRow[numRow], stm32::dev::mcal::gpio::InputMode::kPullup);
    }
    for (uint8_t numCol =0; numCol <Columns; numCol++) {
        SetOutputMode(KeypadCol[numCol], stm32::dev::mcal::gpio::OutputMode::kPushPull_2MHZ);
    }
}
