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
using namespace stm32::dev::hal::keypad;

template<uint8_t Rows, uint8_t Columns>
void Keypad<Rows, Columns>::SetRowArr(Pin rows[Rows]) {
    for (uint8_t numRow =0 ; numRow <Rows; numRow++) {
        KeypadRow[numRow] = rows[numRow];
    }
}
template<uint8_t Rows, uint8_t Columns>
void Keypad<Rows, Columns>::setColArr(Pin cols[Columns]) {
    for (uint8_t numCol =0; numCol <Columns; numCol++) {
        KeypadCol[numCol] = cols[numCol];
    }
}
template<uint8_t Rows, uint8_t Columns>
void Keypad<Rows, Columns>::KeypadInit() {
    for (uint8_t numRow =0 ; numRow <Rows; numRow++) {
        SetInputMode(KeypadRow[numRow], InputMode::kPullup);
    }
    for (uint8_t numCol =0; numCol <Columns; numCol++) {
        SetOutputMode(KeypadCol[numCol], OutputMode::kPushPull_2MHZ);
    }
}
template<uint8_t Rows, uint8_t Columns>
uint8_t Keypad<Rows, Columns>::GetPressed(uint8_t keypadButtons[Rows][Columns]) {
    for (uint8_t numCol =0; numCol <Columns; numCol++) {
        SetPinValue(KeypadCol[numCol], kLow);
        for (uint8_t numRow =0 ; numRow <Rows; numRow++) {
            if (GetPinValue(KeypadRow[numRow]) == kLow) {
                return keypadButtons[numRow][numCol];
            }
        }
        SetPinValue(KeypadCol[numCol], kHigh);
    }
}
